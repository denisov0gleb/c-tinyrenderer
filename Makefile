CC = gcc
CFLAGS = -o

EXECUTABLE = main

LIBS = ppmImageLib.c objLib.c


ifeq ($(OS),Windows_NT) 
	REMOVE = del /f
else
	REMOVE = rm -rf
endif


all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CFLAGS) $(EXECUTABLE) main.c $(LIBS)


clean:
	$(REMOVE) *.exe *.o *.ppm $(EXECUTABLE)
