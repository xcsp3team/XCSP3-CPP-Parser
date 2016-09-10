C++ = g++
CFLAGS = -g -Wall -std=c++11 
EXEC = test

LIBS = `xml2-config --libs`
INC = `xml2-config --cflags`  -I../include
CPP_FILES := $(wildcard ../src/*.cc)
OBJ_FILES := $(addprefix ../obj/,$(notdir $(CPP_FILES:.cc=.o)))
all: main.cc $(OBJ_FILES) 
	$(C++)  $(CFLAGS) $(INC) -L/usr/local/opt/libxml2/lib/ $(LIBS) -o $(EXEC) $^

../obj/%.o: ../src/%.cc
	-@(test -d "../obj") || mkdir ../obj
	$(C++) $(CFLAGS) $(INC) -c -o $@ $<

lib: $(OBJ_FILES) 
	ar rcsv ../lib/libparserxcsp3core.a $(OBJ_FILES)

testlib: main.cc
	$(C++)  $(CFLAGS) $(INC) -L/usr/local/opt/libxml2/lib/ -L ../lib $(LIBS) -lparserxcsp3core -o testlib main.cc

clean: 
	rm -rf ../obj/*.o test ../lib/*


