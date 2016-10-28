#
# This is a common Makefile for code examples from the book
# "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
#

#
# Usage:
#     make        - Build all examples
#     make clean  - Clean all examples
#     make test   - Run the test suite
#

CXX = g++-6
INCLUDES = 
LIBS     = -std=c++17 -lfltk -lfltk_images
CXXFLAGS = $(INCLUDES) -Wall -time -O3 -g3 -DNDEBUG
LIBFLAGS = 

# NOTE: If under Cygwin you get an error that uname command is not found,
#       make sure there are no folders with space in their names that preceed
#       the path to the Cygwin's bin folder inside your PATH variable.
ifeq ($(shell uname),Cygwin)
  OS=Cygwin
else
  OS=$(shell uname)
endif

ifeq ($(OS),Cygwin)
  LIBS := $(LIBS) -lfltk_jpeg -luser32 -lgdi32 -lshell32 -lole32 -luuid -lWs2_32 -lComCtl32
else
ifeq ($(OS),Darwin)
  LIBS := $(LIBS) -ljpeg -framework Carbon
else
  LIBS := $(LIBS) -lX11 -ljpeg
endif
endif

.SUFFIXES: .cpp .o

# Create a list of source files.
SOURCES  = $(shell ls *.cpp)
# Create a list of object files from the source file lists.
OBJECTS = ${SOURCES:.cpp=.o}     
# Create a list of targets.
TARGETS = main.exe    

# Build all targets by default
all: 	$(TARGETS)

# Files with extension .no-link.cpp are not intended for linking
%.no-link: %.no-link.o
	@echo Linking skipped for $@
	@echo ================================================================================
	@echo Done building $@
	@echo ================================================================================
	@echo
	@echo

# A rule to build .exe file out of a .o file
%.exe: $(OBJECTS)
	@echo ================================================================================
	@echo Building $@
	@echo ================================================================================
	@echo
	@echo
	$(CXX) -g3 -o $@ $(LIBFLAGS) $(OBJECTS) $(LIBS)
	@echo ================================================================================
	@echo Done building $@
	@echo ================================================================================
	@echo
	@echo

# A rule to build .o file out of a .cpp file
%.o: %.cpp 
	@echo ================================================================================
	@echo Building $@
	@echo ================================================================================
	@echo
	@echo
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# A rule to build the common GUI library
../GUI/libbookgui.a: ../GUI/*.h ../GUI/*.cpp
	@(cd ../GUI; $(MAKE))

# A rule to clean all the intermediates and targets
clean:	
	rm -rf $(TARGETS) $(OBJECTS) *.out *.stackdump