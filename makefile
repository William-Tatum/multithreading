# Makefile to compile specified C++ scripts into an executable

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++20 -fsanitize=address -g

# Linker flags
LDFLAGS = -fsanitize=address

# Default target
all:
	@echo "Usage: make file1 file2 ..."
	@echo "This will compile file1.cpp, file2.cpp, etc., into file1 executable"

# Pattern rule for building executables
%: %.cpp
	$(CXX) $(CXXFLAGS) $^ $(filter-out $<,$(MAKECMDGOALS:=.cpp)) -o $@ $(LDFLAGS)

# To handle the case when no .cpp extension is provided
%: 
	@if [ -f $@.cpp ]; then \
		$(MAKE) $@.cpp; \
	else \
		echo "No rule to make target '$@'"; \
	fi

# Disable built-in rules
MAKEFLAGS += --no-builtin-rules
.SUFFIXES:

# Dummy targets for each additional file
$(filter-out all,$(MAKECMDGOALS)):

# Clean target: remove executables
# Clean target: remove all executables in the folder
clean:
	@echo "Cleaning up..."
	@find . -maxdepth 1 -type f -executable -delete
