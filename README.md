This is a SQLite extension that wraps the libgeomag library. 

# How to Use

After the extension is loaded, some new SQL functions become available. Usage example from the SQLite shell:

```
.load "sqlite3ext_geomag-1"

SELECT GEOMAG_DECL(45.1234 /*latitude[deg]*/, 18.748 /*longitude[deg]*/, 100 /*altitude[m]*/, '2026-03-14 12:00:00' /*datetime*/);
-- Returns 4.41 = the magnetic declination for that location and time

SELECT GEOMAG_DECL_YC(45.1234 /*latitude[deg]*/, 18.748 /*longitude[deg]*/, 100 /*altitude[m]*/, '2026-03-14 12:00:00' /*datetime*/);
-- Returns 0.01 = the yearly change of magnetic declination, in decimal degrees per year
```

See [test/test001-basic.sql](test/test001-basic.sql) for a few more usage examples.

# How to Install

`libgeomag-embedded.a` is a mandatory dependency. You may find sources and binaries in various places, for example [here](https://github.com/thesoftwarebin/geomag).

If you have installed libgeomag in your standard library folders (e.g. `/usr/include/geomag.h` and `/usr/lib/libgeomag-embedded.a`), then building `sqlite3ext_geomag` requires a pretty standard procedure:

```.sh
    ./configure
    make all
    # if build succeeds, look for the compiled .so or .dll binary in folder src/.libs
```

If you don't want or can't install `libgeomag-embedded` in the default folders, unpack it in a folder structure like this:

```
/myabsolutepathtogeomag/include/geomag.h
/myabsolutepathtogeomag/release/libgeomag-embedded.a
```

The build procedure for `sqlite3ext_geomag` requires to pass explicitly these folder locations at configure time:

```.sh
    ./configure LDFLAGS="-L/myabsolutepathtogeomag/release" CFLAGS="-I/myabsolutepathtogeomag/include"
    make all
    # if build succeeds, look for the compiled .so or .dll binary in folder src/.libs
```

