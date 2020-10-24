CC    	= gcc
CFLAGS	= -fopenmp -O2 -g  -Wall -fmessage-length=0  -lpython2.7
LIBS		= -lm
TARGET	= ../kshingle
OBJECTS	= kshingle.o \
		  		loadgraph.o \
	      	lib.o \
	      	elib.o \
	      	hashtbl.o \
		  		search.o \
	      	strhash.o \
          shingle.o \
          uFind.o \
          heap.o \
					loadGUI.o\
	      	vidmap.o

$(TARGET):  $(OBJECTS)
		$(CC)   -fopenmp -g -o $(TARGET) $(OBJECTS) $(LIBS) -lpython2.7

all: $(TARGET)

install:
	cp ./kshingle ~/bin/

clean:
	rm -f $(TARGET) $(OBJECTS)
