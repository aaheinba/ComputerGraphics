########################################################
# Makefile for CSCI 375
#   In many cases you will ONLY need to modify the
#   SRCS variable below
# Author: Gary M. Zoppetti, Ph.D. and Chad Hogg
########################################################

########################################################
# Variable definitions
########################################################
# C++ compiler
CXX := g++
#CXX := clang++

# Include directories, prefaced with "-I"
INCDIRS  := -isystem /usr/include/catch2

# C++ compiler flags
# Use the first for debugging, the second for release
CXXFLAGS := -g -Wall -std=c++14 $(INCDIRS)
#CXXFLAGS := -O3 -Wall -std=c++14 $(INCDIRS)

# Linker. For C++ should be $(CXX).
LINK := $(CXX)

# Linker flags. Usually none.
LDFLAGS := 

# Library paths, prefaced with "-L". Usually none.
LDPATHS := 

UNAME := $(shell uname)
# Libraries used, prefaced with "-l".
ifeq ($(UNAME),Darwin)
LDLIBS := -framework OpenGL -lGLEW -lglfw -lassimp
else
LDLIBS := -lGLEW -lglfw -lGL -lassimp
endif

# All source files, separated by spaces. Don't include header files. 
SRCS := Main.cpp Material.cpp LightSource.cpp ShaderProgram.cpp OpenGLContext.cpp RealOpenGLContext.cpp Mesh.cpp Scene.cpp MyScene.cpp Camera.cpp Vector3.cpp KeyBuffer.cpp Matrix3.cpp Transform.cpp MouseBuffer.cpp Vector4.cpp Matrix4.cpp Geometry.cpp ColorMesh.cpp NormalsMesh.cpp

# Extension for source files. Do NOT modify.
SOURCESUFFIX := cpp

# Determines object files based on SRCS.
OBJS := $(SRCS:.$(SOURCESUFFIX)=.o)

# Executable name. Defaults to basename of first name in SRCS.
EXEC := $(patsubst %.o, %, $(word 1, $(OBJS))).out

# Command to generate dependency rules for make. 
MAKEDEPEND := $(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM -MP

# The name of the AutoLab course we will submit to.
COURSE := 375-s22

# The name of the current assignment.
ASSIGNMENT := a08models

#############################################################
# Rules
#   Rules have the form
#   target : prerequisites
#   	  recipe
#############################################################

all : $(EXEC)

$(EXEC) : $(OBJS)
	$(LINK) $(LDFLAGS) $(LDPATHS) $^ -o $@ $(LDLIBS)

-include Makefile.deps

#############################################################

.PHONY : clean submit handin.zip

handin.zip :
	zip -r handin.zip * --exclude handin.zip Makefile.deps \*.o \*.out \*~

submit : handin.zip
	git tag $(ASSIGNMENT) -f -m "Final submission of $(ASSIGNMENT)."
	git push --tags -f
	autolab submit $(COURSE):$(ASSIGNMENT) handin.zip

clean :
	$(RM) $(EXEC) $(OBJS) a.out core
	$(RM) Makefile.deps *~

.PHONY :  Makefile.deps
Makefile.deps :
	$(MAKEDEPEND) $(SRCS) > $@

TestVector3.out : TestVector3.cpp Vector3.cpp Vector3.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o TestVector3.out TestVector3.cpp Vector3.cpp

TestMatrix3.out : TestMatrix3.cpp Matrix3.cpp Matrix3.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o TestMatrix3.out TestMatrix3.cpp Matrix3.cpp
#############################################################
#############################################################
