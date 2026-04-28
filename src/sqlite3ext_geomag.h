#ifndef SQLITE3EXT_GEOMAG_H
#define SQLITE3EXT_GEOMAG_H

#include <sqlite3ext.h>

#include <geomag.h>
extern BFieldModel model;

SQLITE_EXTENSION_INIT1;

int sqlite3_extension_init(sqlite3 * db, char **pzErrMsg, const sqlite3_api_routines * pApi);

#endif // SQLITE3EXT_GEOMAG_H
