.RECIPEPREFIX +=
CC = g++
CFLAGS = -Wall -lm -lrt -lwiringPi -lpthread

PROG = bin/*
OBJS = obj/*

default:
    mkdir -p bin obj
    $(CC) $(CFLAGS) -c src/adc.cpp -o obj/adc
    $(CC) $(CFLAGS) obj/adc -o bin/adc

run:
    sudo ./bin/adc

clean:
    rm $(PROG) $(OBJS)
