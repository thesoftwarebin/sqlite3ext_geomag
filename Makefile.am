SUBDIRS = src 

if HAVESQLITE3SHELLFORTESTS
TESTS = test/test001-basic.sh
endif

EXTRA_DIST =                   \
	test/test001-basic.sh  \
	test/test001-basic.sql \
	.gitignore

clean-local:
	-rm -vrf test/test001-output
