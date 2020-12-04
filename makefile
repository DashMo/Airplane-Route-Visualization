# # Executable names:
# # EXE = airmap
# # TEST = test

# # # Add all object files needed for compiling:
# # EXE_OBJ = main.o 
# # OBJS = main.o routes.o airport.o graph.o

# # Generated files
# CLEAN_RM = mapOut.png

# # Use the cs225 makefile template:
# include cs225/make/cs225.mk

# project_program : main.o routes.o airport.o graph.o
# 	clang++ -c main.o routes.o airport.o graph.o -o project_program

# main.o : main.cpp 
# 	clang++ -c main.cpp
# routes.o : routes.cpp routes.h
# 	clang++ -c routes.cpp
# airport.o : airports.cpp airports.h
# 	clang++ -c airports.cpp
# graph.o : graph.cpp graph.h
# 	clang++ -c graph.cpp


# clean :
# 	rm project_program * .o






EXENAME = main
TEST = test
OBJS = main.o routes.o airport.o graph.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif

# .PHONY: all test clean output_msg
include cs225/make/cs225.mk

all : $(EXENAME)
output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

project_program : main.o graph.o routes.o airport.o PNG.o
	$(CXX) $(CXXFLAGS) graph.o routes.o aiport.o PNG.o main.o

main.o : main.cpp graph.h routes.h airport.h 
	$(CXX) $(CXXFLAGS) main.cpp

graph.o : graph.cpp graph.h
	$(CXX) $(CXXFLAGS) graph.cpp

routes.o : routes.cpp routes.h
	$(CXX) $(CXXFLAGS) routes.cpp

airport.o : airport.cpp airport.h 
	$(CXX) $(CXXFLAGS) airport.cpp









# test: output_msg catchmain.o tests.o PNG.o HSLAPixel.o lodepng.o 
# 	$(LD) catchmain.o tests.o PNG.o HSLAPixel.o lodepng.o  $(LDFLAGS) -o test

# catchmain.o : cs225/catch/catchmain.cpp cs225/catch/catch.hpp
# 	$(CXX) $(CXXFLAGS) cs225/catch/catchmain.cpp

# tests.o : tests/tests.cpp cs225/catch/catch.hpp 
# 	$(CXX) $(CXXFLAGS) tests/tests.cpp

.PHONY: clean
clean :
	rm -f *.o main





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