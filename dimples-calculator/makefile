CC=g++
CFLAGS=-c -Wall -std=c++0x 
LDFLAGS=
SOURCES=main.cpp Generator.cpp Operations.cpp MathNode.cpp NodeBuilder.cpp
INC=-I/usr/include/boost/
#LIBS += -stdlib=libc++
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_regex
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=NodeBuilder

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS)  $(INC) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(LIBS) $(INC) $< -o $@

clean:
	rm *o NodeBuilder