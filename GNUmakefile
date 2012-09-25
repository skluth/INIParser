
# GNU makefile for INIParser
# S. Kluth 9/2012

LD = $(CXX)
CXXFLAGS = -Wall

LIBFILES = INIReader.cc ini.cc
TESTFILE = testINIReader.cc
TESTEXE = $(basename $(TESTFILE) )
LIBOBJS = $(LIBFILES:.cc=.o)
LIB = libINIParser.so
DEPS = $(LIBFILES:.cc=.d) $(TESTFILE:.cc=.d)

all: $(TESTEXE)

$(DEPS): %.d: %.cc
	$(CXX) -MM $< -MF $@
-include $(DEPS)

$(LIB): $(LIBOBJS)
	$(LD) -shared -o $@ $^

$(TESTEXE): $(TESTFILE:.cc=.o) $(LIB)
	$(LD) -o $@ $^ -lboost_unit_test_framework
	./$@ --log_level=message

INIReaderTest: INIReaderTest.cc $(LIB)
	$(CXX) -o $@ $^

clean:
	rm -f *.o $(DEPS) $(TESTEXE) $(LIB) INIReaderTest

