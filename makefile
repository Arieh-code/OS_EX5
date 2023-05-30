CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -pthread

all: st_pipeline

st_pipeline: main.o activeObject.o queue.o is_prime.o st_pipeline.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o st_pipeline