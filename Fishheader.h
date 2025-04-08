#ifndef FISHARDUINO_H
#define FISHARDUINO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Arduino.h>
#include <Servo.h>

struct song {
	//to be initialized with initsong 
	//files should be in format :
	/*
	first line: line that has time numbers for when the MOUTH of the fish is to be opened

	second line: line that has number for how long the MOUTH should stay open

	third line: line that has time numbers for when the TAIL of the fish is to be flipped

	must be in format mm:ss mm:ss for line 1 and 3
	ex: 00:10 00:11
	for line 2:
	ss ss ss
	ex: 01 15

  end of the lines defined with -1
	*/
	long long* song; //dynamically allocated
	int* mtime; //dynamically allocated
	long long* flip; //dynamically allocated
};

typedef struct song SONG;

int static retsecs(char* str, int size);

int initsong(SONG* Song, const char* filename);

void freeSong(SONG* Song);

int charcounter(const char* filename, int line);

void openmouth(int pin, long long duration);

void fliptail(Servo servo, long long duration, int top, int bottom); //duration = const

int checkptr(int check);

#endif
