# Mettre dans SCHEDPATH le repertoire ou se trouve libsched.a et sched.h
SCHEDPATH = ../libsched 
CC = gcc
CFLAGS = -Wall -I$(SCHEDPATH)
DEMO = demo.sched 
EXOS = exo-random.sched exo-sjf.sched exo-rr.sched exo-mlrr.sched

all: $(DEMO) $(EXOS)
	
%.sched: %.o 
	$(CC) $(CFLAGS) -o $@ $< -L$(SCHEDPATH) -lsched -lelf

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
	
clean: 
	rm -f *.o *.sched
