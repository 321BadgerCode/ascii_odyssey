CC=g++
CFLAGS=-c -Wall -std=c++11 -w

name:=main
title:=ascii_odyssey
in:=./$(name).cpp
bin:=../bin/$(name).o
out:=../bin/$(title).exe

.SILENT:

default:all

all:compile
	$(out)

compile:$(in)
	$(CC) $(CFLAGS) $(in) -o $(bin)
	$(CC) $(bin) -o $(out)

clean:
	rm -f $(bin)