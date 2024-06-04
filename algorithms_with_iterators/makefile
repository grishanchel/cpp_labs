SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
CFLAGS := -std=c++2a -Wall -Werror -fsanitize=address
RESULT := main
LDFLAGS := -fsanitize=address

all: run

run: compile
	ASAN_OPTIONS=detect_leaks=1 ./$(RESULT)

compile: $(SOURCES) check $(RESULT)

check:
	./check.sh

.cpp.o:
	g++ -c $(CFLAGS) $< -o $@

$(RESULT): $(OBJECTS)
	g++ $(OBJECTS) $(LDFLAGS) -o $(RESULT)

clean:
	rm -f $(OBJECTS) $(RESULT)
