# Define compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++20 -fsanitize=address -g

# Linker flags
LDFLAGS = -fsanitize=address

# Automatically find all subdirectories, excluding the current directory
SUBDIRS = $(shell find . -maxdepth 1 -type d | grep -v '^\./$$' | sed 's^\./^^')

# Find all .cpp files in the current folder
SOURCES = $(wildcard *.cpp)

# Define executable files (one for each source file)
EXECUTABLES = $(SOURCES:.cpp=)

all: subdirs $(EXECUTABLES)

$(EXECUTABLES): %: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@

subdirs:
	for dir in $(SUBDIRS); do \
		if [ "$$dir" != "." ]; then \
			$(MAKE) -C $$dir; \
		fi \
	done

clean:
	rm -f $(EXECUTABLES)
	for dir in $(SUBDIRS); do \
		if [ "$$dir" != "." ]; then \
			$(MAKE) -C $$dir clean; \
		fi \
	done