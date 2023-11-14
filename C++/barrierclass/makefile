# Define compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++20 -fsanitize=address -g

# Linker flags
LDFLAGS = -fsanitize=address

# Find all .cpp files in the current folder
SOURCES = $(wildcard *.cpp)

# Define object files
OBJECTS = $(SOURCES:.cpp=.o)

# Define the executable file
EXECUTABLE = MyProgram

all: $(EXECUTABLE)
	rm -f $(OBJECTS)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
