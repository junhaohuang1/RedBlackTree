CC=g++

CFLAGS=-c -Wall


all: jhh492_hw17_q1

jhh492_hw17_q1: jhh492_hw17_q1.o RedBlackTree.o
	$(CC) jhh492_hw17_q1.o RedBlackTree.o -o jhh492_hw17_q1 -static-libstdc++ -static-libgcc
	
jhh492_hw17_q1.o:jhh492_hw17_q1.cpp
	$(CC) $(CFLAGS) jhh492_hw17_q1.cpp

RedBlackTree.o:RedBlackTree.cpp
	$(CC) $(CFLAGS) RedBlackTree.cpp
	
clean:
	rm *.o jhh492_hw17_q1