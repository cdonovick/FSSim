CC=g++
CFLAGS=-c -std=c++11 -Wall -Wextra -pedantic -ggdb
LDFLAGS=
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE=program3
	
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $@ $^
	
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $^

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.*~

