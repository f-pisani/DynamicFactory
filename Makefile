# DynamicFactory Makefile
# A simple C++11 project demonstrating a template-based factory pattern

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic
DEBUGFLAGS = -g -O0
RELEASEFLAGS = -O2 -DNDEBUG

# Build directories
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release

# Source files and objects
SOURCES = main.cpp
HEADERS = DynamicFactory.hpp DynamicFactory.tpp \
          AbstractInstantiator.hpp \
          Instantiator.hpp Instantiator.tpp

# Executable names
DEBUG_TARGET = $(DEBUG_DIR)/DynamicFactory
RELEASE_TARGET = $(RELEASE_DIR)/DynamicFactory

# Default target
.PHONY: all
all: debug

# Debug build
.PHONY: debug
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(SOURCES) $(HEADERS) | $(DEBUG_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

# Release build
.PHONY: release
release: CXXFLAGS += $(RELEASEFLAGS)
release: $(RELEASE_TARGET)

$(RELEASE_TARGET): $(SOURCES) $(HEADERS) | $(RELEASE_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

# Create build directories
$(DEBUG_DIR):
	mkdir -p $(DEBUG_DIR)

$(RELEASE_DIR):
	mkdir -p $(RELEASE_DIR)

# Run the debug version
.PHONY: run
run: debug
	$(DEBUG_TARGET)

# Run the release version
.PHONY: run-release
run-release: release
	$(RELEASE_TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all (default) - Build debug version"
	@echo "  debug        - Build with debug symbols"
	@echo "  release      - Build optimized release version"
	@echo "  run          - Build and run debug version"
	@echo "  run-release  - Build and run release version"
	@echo "  clean        - Remove all build artifacts"
	@echo "  help         - Show this help message"