# Executable names:
EXE = airmap
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o 
OBJS = main.o routes.o airport.o graph.o

# Generated files
CLEAN_RM = mapOut.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk

project_program : main.o routes.o airport.o graph.o
	clang++ -c main.o routes.o airport.o graph.o -o project_program

main.o : main.cpp 
	clang++ -c main.cpp
routes.o : routes.cpp routes.h
	clang++ -c routes.cpp
airport.o : airports.cpp airports.h
	clang++ -c airports.cpp
graph.o : graph.cpp graph.h
	clang++ -c graph.cpp


clean :
	rm project_program * .o
# MP-specific target

# TMP_OBJ := $(OBJS)
# OBJS = $(filter-out $(EXE_OBJ), $(TMP_OBJ))
# OBJS += testimage.o

# testimage: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
# 	$(LD) $^ $(LDFLAGS) -o $@




#//try this out as well a different version of the make file that might work better

# CXX = g++
# CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
# LDFLAGS =  -fsanitize=address

# SRC = 
# OBJ = $(SRC:.cc=.o)
# EXEC = main

# all: $(EXEC)

# $(EXEC): $(OBJ)
# 	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

# clean:
# 	rm -rf $(OBJ) $(EXEC)