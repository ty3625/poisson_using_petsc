CC		= mpicc
CXX		= mpicxx
CPPFLAGS	= 
# CFLAGS	= -O2 -Wall -fopenmp
CFLAGS		= -g -O0 -Wall
INCLUDES	= -I${PETSC_DIR}/include
LIBS		= -Wl,-rpath,${PETSC_DIR}/lib -L${PETSC_DIR}/lib -lpetsc -lm -ldl
SRCS		= $(wildcard *.c)
PROGRAM		= $(SRCS:.c=.out)

.PHONY: all clean
all:	$(PROGRAM)

%.out : %.c
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(INCLUDES) $^ $(LIBS)

clean:	
	-rm -f $(PROGRAM)



