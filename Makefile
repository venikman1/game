#
# Makefile
# Game prototype project
#
# Created by AnyKeyShik Rarity 2018-19-12
#

# Compilers
CC := g++

# Flags
CFLAGS := -g --std=c++14
LDFLAGS := -F GLUT -F OpenGL -lpng -lglut -lGLU -lGL
INCLUDE_FLAGS := -Iheaders

# Folders
SRCDIR := src
TARGETDIR := bin

# Files
SRCTEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCTEXT))
TEST_EXECUTABLE := test_build
EXECUTABLE := build

# Target
TARGET := $(TARGETDIR)/$(EXECUTABLE)
TEST_TARGET := $(TARGETDIR)/$(TEST_EXECUTABLE)

frist: release

$(TARGET): $(TARGETDIR)/$(EXECUTABLE)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE_FLAGS) $(SOURCES) -o $(TARGET)

$(TEST_TARGET): $(TARGETDIR)/$(TEST_EXECUTABLE)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE_FLAGS) $(SOURCES) -o $(TEST_TARGET)

test: $(TEST_TARGET)

release: $(TARGET)

clean:
	@echo "Cleaning binaries..."
	@rm -rf bin

.PHONY: first, test, release, clean
