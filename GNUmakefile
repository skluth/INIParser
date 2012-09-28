
# GNU makefile for INIParser
# S. Kluth 9/2012

LD = $(CXX)
CXXFLAGS = -Wall -fPIC

LIBFILES = INIReader.cc ini.cc
TESTFILE = testINIReader.cc
TESTEXE = $(basename $(TESTFILE) )
LIBOBJS = $(LIBFILES:.cc=.o)
LIB = libINIParser.so
DEPS = $(LIBFILES:.cc=.d) $(TESTFILE:.cc=.d)
ifdef HEPROOT
CPPFLAGS = -I $(HEPROOT)/include/boost-1_48/
LDFLAGS = -L $(HEPROOT)/lib64
LDLIBS = -lboost_unit_test_framework-gcc46-mt-1_48
else
LDLIBS = -lboost_unit_test_framework
endif

.INTERMEDIATE: $(LIBOBJS) $(TESTFILE:.cc=.o)

all: $(TESTEXE)

$(DEPS): %.d: %.cc
	$(CXX) -MM $< -MF $@
-include $(DEPS)

$(LIB): $(LIBOBJS)
	$(LD) -shared -o $@ $^

$(TESTEXE): $(TESTFILE:.cc=.o) $(LIB)
	$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH): ./$@ --log_level=message

INIReaderTest: INIReaderTest.cc $(LIB)
	$(CXX) -o $@ $^

clean:
	rm -f $(DEPS) $(TESTEXE) $(LIB)

