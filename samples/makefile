CFLAGS =  -std=c++11 -Wall
EXEC = test

LIBS = `xml2-config --libs`
INC = `xml2-config --cflags`  -I../include
CPP_FILES := $(wildcard ../src/*.cc)
OBJ_FILES := $(addprefix ../obj/,$(notdir $(CPP_FILES:.cc=.o)))

all: main.cc $(OBJ_FILES)
	$(CXX)  $(CFLAGS) $(INC) -o $(EXEC) $^ $(LIBS)

../obj/%.o: ../src/%.cc
	@mkdir -p ../obj
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<

lib: $(OBJ_FILES) 
	@mkdir -p ../lib
	ar rcsv ../lib/libparserxcsp3core.a $(OBJ_FILES)

testlib: main.cc
	$(CXX)  $(CFLAGS) $(INC) -o testlib main.cc -L ../lib $(LIBS) -lparserxcsp3core

testTree: testTree.cc
	$(CXX)  $(CFLAGS) $(INC) -o testTree testTree.cc -L ../lib $(LIBS) -lparserxcsp3core

clean:
	rm -rf ../obj/*.o test ../lib/* testlib


