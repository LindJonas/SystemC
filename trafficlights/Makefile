# The final executable
PROGRAM = lights.x

# The source files (*.cc)
SRCS = lights.cc controller.cc lights_testbench.cc

##################################
## DO NOT CHANGE ANYTHING BELOW ##
##################################

SYSTEMC = /home/TDTS07/sw/systemc
TARGET_ARCH = linux64

LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-$(TARGET_ARCH)
LIBS = -Wl,-Bstatic -lsystemc -Wl,-Bdynamic -lm -lpthread
LDFLAGS = -g

CC = g++ -std=c++11
OPT = -O3
CFLAGS = -Wno-deprecated
EXE = $(PROGRAM)

INCDIR= -I. -I.. -I$(SYSTEMC)/include

OBJS = $(SRCS:.cc=.o)

.SUFFIXES: .cc .o .x

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(INCDIR) $(LIBDIR) -o $(EXE) $(OBJS) $(LIBS)

# To build the whole project we must compile each .cc file into a .o file, and
# then link all .o-files into an executable. The rule above tells the make tool
# how to link the object files into an executable. To create the object files we
# need additional rules (one for each .cc-file). For each .cc-file we add two
# lines in the make file. The first line consists of a list of one .cc file
# (corresponding to the .o-file beeing created) and possibly a list of .h-files.
# Whenever any of the files in the list has changed, the make tool will
# recompile the object file. The list should be the .cc-file beeing compiled,
# and all the .h-files that are included in that .cc-file.

controller.o: controller.cc controller.h
	$(CC) -c $(CFLAGS) $(INCDIR) controller.cc -o controller.o

lights_testbench.o: lights_testbench.cc lights.h controller.h
	$(CC) -c $(CFLAGS) $(INCDIR) lights_testbench.cc -o lights_testbench.o

lights.o: lights.cc lights.h
	$(CC) -c $(CFLAGS) $(INCDIR) lights.cc -o lights.o

clean:
	rm -f $(OBJS) $(EXE) *~
