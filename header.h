/*
Programmer: Gabriel Falk
Class: CPTS 122, Fall 2021, Lab section 01
Programming assignment: PA2 (header file)
Date: 9/10/2021
Description: This is the header file that will be imported to the rest of the code files*/
#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h.>
#include<Windows.h>

//the basis of the node list was provided by Andy in class
typedef struct duration {
	int minute;
	int second;
}Duration;

typedef struct record { //this struct contains the data of each song
	char songname[50];
	char artist[50];
	char album[50];
	char genre[15];
	Duration songLength;
	int timesPlayed;
	int rating;
}Record;

typedef struct node {
	//makes a node to access the song data
	Record record;
	struct node* pNext;
	struct node* pPrev;
}Node;

typedef struct list {
	Node* pHead;
}List;

void play(List* plist);
void exit(List* plist);
int rate(List* plist);
void edit(List* plist);
int store(List* plist);
void display(Node* pNode);
void printList(Node* pNode);
int load(List* plist);
int insertAtFront(List* plist, const Record* pNewData);
Node* make_node(const Record* pNewData);
void initList(List* plist);
int insert(List* plist);
int deleteRecord(List* plist);
void sort(List* plist);
void shuffle(List* plist);

#endif