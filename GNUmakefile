
LD = $(CXX)
CXXFLAGS = -Wall

LIBFILES = INIReader.cc ini.cc
TESTFILE = testINIReader.cc
TESTEXE = $(basename $(TESTFILE) )
LIBOBJS = $(LIBFILES:.cc=.o)
DEPS = $(LIBFILES:.cc=.d) $(TESTFILE:.cc=.d)

all: $(TESTEXE)

$(DEPS): %.d: %.cc
	$(CXX) -MM $< -MF $@
-include $(DEPS)

libINIReader.so: $(LIBOBJS)
	$(LD) -shared -o $@ $^

INIReaderTest: INIReaderTest.cc libINIReader.so
	$(CXX) -o $@ $^


$(TESTEXE): $(TESTFILE:.cc=.o) libINIReader.so
	$(LD) -o $@ $^ -lboost_unit_test_framework
	LD_LIBRARY_PATH=$(PWD) ./$@

clean:
	rm -f *.o $(DEPS) $(TESTEXE) libINIReader.so INIReaderTest

