#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "geomag.h"
#include "sqlite3ext_geomag.h"

#include <ctype.h>

enum sqlite3ext_geomag_property {
  SQLITE3EXT_GEOMAG_PROPERTY___DECL,
  SQLITE3EXT_GEOMAG_PROPERTY___DECL_YC
};

void sqlite3ext_geomag_common(sqlite3_context * context, int argc, sqlite3_value ** argv, int prop);
void sqlite3ext_geomag_decl(sqlite3_context * context, int argc, sqlite3_value ** argv);
void sqlite3ext_geomag_decl_yc(sqlite3_context * context, int argc, sqlite3_value ** argv);

void sqlite3ext_geomag_common(sqlite3_context * context, int argc, sqlite3_value ** argv, int prop){
	double latitude  = sqlite3_value_double(argv[0]);
	double longitude = sqlite3_value_double(argv[1]);
	double altitude  = sqlite3_value_double(argv[2]);

	double date;

	if (sqlite3_value_type(argv[3]) != SQLITE_NULL){
		const char* datestr = sqlite3_value_text(argv[3]);
		date = (
			datestr != NULL
			&& strlen(datestr)>=10
			&& isdigit(datestr[0])
			&& isdigit(datestr[1])
			&& isdigit(datestr[2])
			&& isdigit(datestr[3])
			&& datestr[4] == '-'
			&& isdigit(datestr[5])
			&& isdigit(datestr[6])
			&& datestr[7] == '-'
			&& isdigit(datestr[8])
			&& isdigit(datestr[9])
		) ? julday(
			/*month*/   10*(datestr[5]-'0') +   1*(datestr[6]-'0'),
			/*day*/     10*(datestr[8]-'0') +   1*(datestr[9]-'0'),
			/*year*/  1000*(datestr[0]-'0') + 100*(datestr[1]-'0') + 10*(datestr[2]-'0') + 1*(datestr[3]-'0')
		) : NAN;
	} else {
		const time_t today_time = time(NULL);
		struct tm today;
		memcpy(&today, gmtime(&today_time), sizeof(struct tm));
		date = julday(today.tm_mon+1, today.tm_mday, today.tm_year+1900);
	}

#ifdef GEOMAG_DECL_TRACE
	printf("[geomag_decl invoked: latitude=%f, longitude=%f, altitude=%f, datestr=%s, date=%f]\n", latitude, longitude, altitude, datestr, date);
#endif

	BField o_bfield;

	get_field_components(
		&o_bfield,
		&model,
		altitude, kUnitsMeters, kCoordSysGeodetic,
		latitude,
		longitude,
		date);

	switch(prop){
	case SQLITE3EXT_GEOMAG_PROPERTY___DECL_YC:
		#ifdef GEOMAG_DECL_TRACE
			printf("[geomag yearlychange result: %f]\n", o_bfield.ddot/60.0); //ddot is in arcmin/year
		#endif
		sqlite3_result_double(context, o_bfield.ddot/60.0);
		break;
	case SQLITE3EXT_GEOMAG_PROPERTY___DECL:
	default:
		#ifdef GEOMAG_DECL_TRACE
		printf("[geomag decl result: %f]\n", o_bfield.d);
		#endif
		sqlite3_result_double(context, o_bfield.d);
		break;
	}
}

void sqlite3ext_geomag_decl(sqlite3_context * context, int argc, sqlite3_value ** argv){
  sqlite3ext_geomag_common(context, argc, argv, SQLITE3EXT_GEOMAG_PROPERTY___DECL);
}

void sqlite3ext_geomag_decl_yc(sqlite3_context * context, int argc, sqlite3_value ** argv){
  sqlite3ext_geomag_common(context, argc, argv, SQLITE3EXT_GEOMAG_PROPERTY___DECL_YC);
}

int sqlite3_extension_init(sqlite3 * db, char **pzErrMsg, const sqlite3_api_routines * pApi){
	int retval=0;
	SQLITE_EXTENSION_INIT2(pApi);
	retval |= sqlite3_create_function(db, "geomag_decl",    4, SQLITE_UTF8, NULL, sqlite3ext_geomag_decl,    NULL, NULL);
	retval |= sqlite3_create_function(db, "geomag_decl_yc", 4, SQLITE_UTF8, NULL, sqlite3ext_geomag_decl_yc, NULL, NULL);
	return retval;
}
