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

# MP-specific target
# TMP_OBJ := $(OBJS)
# OBJS = $(filter-out $(EXE_OBJ), $(TMP_OBJ))
# OBJS += testimage.o

# testimage: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
# 	$(LD) $^ $(LDFLAGS) -o $@