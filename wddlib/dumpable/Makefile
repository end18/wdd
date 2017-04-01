all: test
test: test.cpp dptr.h dumpable.h dpool.h dvector.h dstring.h dmap.h dumpableconf.h
	g++ -Wall -std=c++11 -g -otest test.cpp
	./test
testcov: test.cpp dptr.h dumpable.h dpool.h dvector.h dstring.h dmap.h dumpableconf.h
	g++ -Wall -std=c++11 -g --coverage -otestcov test.cpp   -fkeep-inline-functions -fno-default-inline  -fno-inline-small-functions
	./testcov
	gcov -r test.cpp


