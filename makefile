#Makefile is based on a combination of the one from lab_intro and the github demo repo for the final project
EXENAME = main
TEST = test
OBJS = main.o PNG.o HSLAPixel.o lodepng.o routes.o airport.o graph.o

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

.PHONY: all test clean output_msg
#include cs225/make/cs225.mk

all : $(EXENAME)
output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

# project_program : main.o graph.o routes.o airport.o PNG.o
# 	$(CXX) $(CXXFLAGS) graph.o routes.o aiport.o PNG.o main.o

main.o : main.cpp cs225/PNG.h cs225/HSLAPixel.h graph.h routes.h airport.h 
	$(CXX) $(CXXFLAGS) main.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp


test: output_msg catchmain.o test.o PNG.o HSLAPixel.o lodepng.o routes.o airport.o graph.o
	$(LD) catchmain.o test.o PNG.o HSLAPixel.o lodepng.o routes.o airport.o graph.o $(LDFLAGS) -o test

catchmain.o : cs225/catch/catchmain.cpp cs225/catch/catch.hpp
	$(CXX) $(CXXFLAGS) cs225/catch/catchmain.cpp

test.o : tests/test.cpp cs225/catch/catch.hpp routes.cpp routes.h airport.cpp airport.h graph.cpp graph.h 
	$(CXX) $(CXXFLAGS) tests/test.cpp

graph.o : graph.cpp graph.h
	$(CXX) $(CXXFLAGS) graph.cpp

routes.o : routes.cpp routes.h
	$(CXX) $(CXXFLAGS) routes.cpp

airport.o : airport.cpp airport.h routes.cpp routes.h
	$(CXX) $(CXXFLAGS) airport.cpp










clean :
	-rm -f *.o $(EXENAME) test






