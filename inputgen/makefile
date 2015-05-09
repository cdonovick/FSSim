CC=g++
CFLAGS=-c -std=c++11 -Wno-unused-parameter -Wall -Wextra -pedantic -ggdb
LDFLAGS=
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE=input_gen
	
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $@ $^
	
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $^

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.*~

