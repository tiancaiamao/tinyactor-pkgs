// C primitives use nil only for retryable absence; SQLite failures are -1.
// Handles are opaque integer tokens holding sqlite3/sqlite3_stmt pointers.
#include "ta.h"
#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>

static sqlite3 *db(Val v) { return (sqlite3 *)(uintptr_t)val_get_int(v); }
static sqlite3_stmt *stmt(Val v) { return (sqlite3_stmt *)(uintptr_t)val_get_int(v); }
static char open_error[512];
static Val sdb_open(VM *vm, Val *a, int n) {
    (void)n;
    if (!val_is_string(a[0])) return val_int(-1);
    HeapString *path = val_get_string(a[0]);
    sqlite3 *p = NULL;
    int rc = sqlite3_open_v2(path->data, &p, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (rc != SQLITE_OK) {
        const char *reason = p ? sqlite3_errmsg(p) : sqlite3_errstr(rc);
        snprintf(open_error, sizeof(open_error), "%s", reason);
        if (p) sqlite3_close(p);
        return val_int(-1);
    }
    (void)vm;
    open_error[0] = '\0';
    return val_int((int64_t)(uintptr_t)p);
}
static Val sdb_open_error(VM *vm, Val *a, int n) {
    (void)vm; (void)a; (void)n;
    return val_string(tls_current_proc, open_error, (int)strlen(open_error));
}
static Val sdb_close(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    return val_int(sqlite3_close(db(a[0])) == SQLITE_OK ? 0 : -1);
}
static Val sdb_exec(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    if (!val_is_string(a[1])) return val_int(-1);
    HeapString *sql = val_get_string(a[1]);
    return val_int(sqlite3_exec(db(a[0]), sql->data, NULL, NULL, NULL) == SQLITE_OK ? sqlite3_changes(db(a[0])) : -1);
}
static Val sdb_error(VM *vm, Val *a, int n) {
        (void)vm; (void)n;
    const char *e = sqlite3_errmsg(db(a[0]));
        return val_string(tls_current_proc, e, (int)strlen(e));
}
static Val sdb_prepare(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    if (!val_is_string(a[1])) return val_int(-1);
    HeapString *sql = val_get_string(a[1]);
    sqlite3_stmt *p = NULL;
    if (sqlite3_prepare_v2(db(a[0]), sql->data, sql->len, &p, NULL) != SQLITE_OK || !p) return val_int(-1);
    return val_int((int64_t)(uintptr_t)p);
}
static Val sdb_step(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    int r = sqlite3_step(stmt(a[0]));
    return val_int(r == SQLITE_ROW ? 1 : r == SQLITE_DONE ? 0 : -1);
}
static Val sdb_column_count(VM *vm, Val *a, int n) { (void)vm; (void)n; return val_int(sqlite3_column_count(stmt(a[0]))); }
static Val sdb_column_name(VM *vm, Val *a, int n) {
        (void)vm; (void)n; const char *s = sqlite3_column_name(stmt(a[0]), (int)val_get_int(a[1]));
        return s ? val_string(tls_current_proc, s, (int)strlen(s)) : val_nil();
}
static Val sdb_column_text(VM *vm, Val *a, int n) {
        (void)vm; (void)n; const unsigned char *s = sqlite3_column_text(stmt(a[0]), (int)val_get_int(a[1]));
        return s ? val_string(tls_current_proc, (const char *)s, sqlite3_column_bytes(stmt(a[0]), (int)val_get_int(a[1]))) : val_nil();
}
static Val sdb_bind_int(VM *vm, Val *a, int n) { (void)vm; (void)n; return val_int(sqlite3_bind_int64(stmt(a[0]), (int)val_get_int(a[1]), val_get_int(a[2])) == SQLITE_OK ? 0 : -1); }
static Val sdb_bind_text(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    if (!val_is_string(a[2])) return val_int(-1);
    HeapString *s = val_get_string(a[2]);
    return val_int(sqlite3_bind_text(stmt(a[0]), (int)val_get_int(a[1]), s->data, s->len, SQLITE_TRANSIENT) == SQLITE_OK ? 0 : -1);
}

static Val sdb_finalize(VM *vm, Val *a, int n) { (void)vm; (void)n; return val_int(sqlite3_finalize(stmt(a[0])) == SQLITE_OK ? 0 : -1); }
static TaFunc funcs[] = {{"raw_open",sdb_open,1},{"raw_open_error",sdb_open_error,0},{"raw_close",sdb_close,1},{"raw_exec",sdb_exec,2},{"raw_error",sdb_error,1},{"raw_prepare",sdb_prepare,2},{"raw_step",sdb_step,1},{"raw_column_count",sdb_column_count,1},{"raw_column_name",sdb_column_name,2},{"raw_column_text",sdb_column_text,2},{"raw_bind_int",sdb_bind_int,3},{"raw_bind_text",sdb_bind_text,3},{"raw_finalize",sdb_finalize,1},{NULL,NULL,0}};
void vm_load_self(VM *vm) { vm_register_module(vm, "sqlite", funcs, 13); }