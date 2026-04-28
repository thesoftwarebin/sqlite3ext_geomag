# -*- coding: utf-8 -*-

if [ ! -f "${srcdir}/test/test001-basic.sql" ] ; then exit 99 ; fi

if [ -f "./src/.libs/sqlite3ext_geomag-1.dll" ] ; then
	libtotest="./src/.libs/sqlite3ext_geomag-1.dll"
elif [ -f "./src/.libs/sqlite3ext_geomag.so" ] ; then
	libtotest="./src/.libs/sqlite3ext_geomag"
else
	echo "error: cannot find the binary library to test (so or .dll file)"
	exit 99
fi

if ldd "${libtotest}" | grep -q "=> not found" ; then
    echo "error: ldd can't resolve all imports of ${libtotest}"
    exit 99
fi

if sqlite3 :memory: ".load \"${libtotest}\"" ".param init" ".param set @idir \"${idir}\"" ".read \"${srcdir}/test/test001-basic.sql\"" | tee /dev/stderr | grep -q FAILED ; then
	# fail if at least one test has FAILED 
	exit 1
else
	# no tests are FAILED, they were either PASSED or SKIPPED 
	exit 0
fi

