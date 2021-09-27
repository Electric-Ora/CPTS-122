/*
Programmer: Gabriel Falk
Class: CPTS 122, Fall 2021, Lab section 01
Programming assignment: PA2 (functions)
Date: 9/10/2021
Description: This is the functions that make up the main body of the program*/
#include"header.h"

//most of the linked list functions are courteous of Andy
void initList(List* plist) {
	//creates an empty list
	plist->pHead = NULL; 
}

Node* make_node(const Record* pNewData) {

	Node* pMem = (Node*)malloc(sizeof(Node)); //allocates data space for a node

	if (pMem != NULL) {
		strcpy(pMem->record.artist, pNewData->artist);
		strcpy(pMem->record.album, pNewData->album);
		strcpy(pMem->record.songname, pNewData->songname);
		strcpy(pMem->record.genre, pNewData->genre);
		pMem->record.songLength.minute = pNewData->songLength.minute;
		pMem->record.songLength.second = pNewData->songLength.second;
		pMem->record.timesPlayed = pNewData->timesPlayed;
		pMem->record.rating = pNewData->rating;
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}
	return pMem;
}

int insertAtFront(List* plist, const Record* pNewData) {

	Node* pMem = make_node(pNewData);

	int success = 0; //this is the return value to determine whether make node was successful or not

	if (pMem != NULL) {
		success = 1;
		if (plist->pHead != NULL) {
			pMem->pNext = plist->pHead;
			plist->pHead = pMem;
		}
		plist->pHead = pMem;
	}
	return success;
}

int load(List* plist) {

	Record record = { '\0' };
	char temp[100] = { '\0' };

	int minute = 0, second = 0, timesplayed = 0, rating = 0, test = -1;

	char* token;

	//FILE* infile = NULL;

	FILE* infile = fopen("musicPlayList.csv", "r"); 

	if (infile == NULL) {
		return 0;
	}

	while ((fgets(temp, 100, infile) != NULL)) { //"Swift, Taylor",1989,Shake it Off,Pop,3:35,12,3
		fgets(temp, 100, infile);

		if (temp[0] == '"') {
			token = strtok(temp, ",");				//I debugged this shit for 4 hours so I hope you appreciate this lol
			strcat(token, strtok(NULL, ","));
			strcpy(record.artist, token);
			token = strtok(NULL, ","); 
			strcpy(record.album, token);
			token = strtok(NULL, ","); 
			strcpy(record.songname, token);
			token = strtok(NULL, ",");
			strcpy(record.genre, token);
			token = strtok(NULL, ":"); 
			minute = atoi(token); 
			record.songLength.minute = minute;
			token = strtok(NULL, ","); 
			second = atoi(token);
			record.songLength.second = second;
			token = strtok(NULL, ","); 
			timesplayed = atoi(token);
			record.timesPlayed = timesplayed;
			token = strtok(NULL, ","); 
			rating = atoi(token);
			record.rating = rating;
			insertAtFront(plist, &record);
		}
		else {                                     //Drake,NOTHING WAS THE SAME,Own it,Rap,3:23,3,3 
			token = strtok(temp, ","); //temp = "Drake"
			strcpy(record.artist, token);
			token = strtok(NULL, ","); //temp = "NOTHING WAS THE SAME"
			strcpy(record.album, token);
			token = strtok(NULL, ","); //temp = "Own it"
			strcpy(record.songname, token);
			token = strtok(NULL, ","); //temp = "Rap"
			strcpy(record.genre, token);
			token = strtok(NULL, ":"); //token = "3"
			minute = atoi(token); //token = 3 (int)
			record.songLength.minute = minute;
			token = strtok(NULL, ","); //token = 23 (int)
			second = atoi(token);
			record.songLength.second = second;
			token = strtok(NULL, ","); //timesplayed = 3
			timesplayed = atoi(token);
			record.timesPlayed = timesplayed;
			token = strtok(NULL, ","); //rating = 3
			rating = atoi(token);
			record.rating = rating;
			insertAtFront(plist, &record);
		}
	}

	fclose(infile);

	if (infile != NULL) {

		return -1; //checks to make sure infile was closed correctly
	}
	else {
		return 1;
	}
}

void printList(List* plist) {

	Node* pCur = plist->pHead;

	if (pCur != NULL) {
		while (pCur != NULL) {
			printf("-->  %s %s %s %s %d:%d %d %d\n", pCur->record.artist, pCur->record.album, pCur->record.songname,
				pCur->record.genre, pCur->record.songLength.minute, pCur->record.songLength.second, pCur->record.timesPlayed, pCur->record.rating);
			pCur = pCur->pNext;
		}
	}
	else {
		printf("-->\n");
	}
}

void display(List* plist) {

	int temp = 0, counter = 0;
	char artist[30] = { '\0' };

	

	printf("Would you like to print the current list or look for an artist?\n");
	printf("1. Print current list\n2.Look for an artist\n");
	scanf("%d", &temp);

	Node* pCur = plist->pHead;
	
		if (temp == 1) {
			printList(plist);
		}

		if (temp == 2) {
			printf("What artist would you like to look for? (Needs to be case sensitive)\n");  
			scanf("%s", &artist);
			while (strcmp(artist, pCur->record.artist) != 0 && pCur != NULL) {             
				pCur = pCur->pNext;
				if (strcmp(artist, pCur->record.artist) == 0) { //checks to see if the artists match
					printf("-->  %s %s %s %s %d:%d %d %d\n", pCur->record.artist, pCur->record.album, pCur->record.songname,   
						pCur->record.genre, pCur->record.songLength.minute, pCur->record.songLength.second, pCur->record.timesPlayed, pCur->record.rating); 
					counter++;
				}
			}
			if (counter == 0) {
				printf("There were no matches to that artist (check your spelling)\n");
			}
		}
		else {
			printf("Incorrect parameter, please try again\n");
		}
	}

int store(List* plist) {
		Node* pCur = plist->pHead;
	
		FILE* outfile = fopen("musicPlayList.csv", "w");

		if (outfile == NULL) {
			printf("There was an error opening the file..\n");
			return 0; //checks to make sure the infile was opened correctly
		}
		while (pCur != NULL) {
			fprintf(outfile, "%s,%s,%s,%s,%d,%d,%d,%d\n", pCur->record.artist, pCur->record.album, pCur->record.songname, pCur->record.genre,
				pCur->record.songLength.minute, pCur->record.songLength.second, pCur->record.timesPlayed, pCur->record.rating);
			pCur = pCur->pNext;
		}
		printf("Overwrite complete.\n");
}

void edit(List* plist) {

	Node* pCur = plist->pHead;

	int temp = 0, counter = 0, choice = 0, minute = 0, second = 0;
	char input[30] = { '\0' };

	printf("Which record would you like to edit? (Artist name) Case Sensitive\n");
	scanf(" %[^\n]", input);
	while (pCur != NULL && strcmp(pCur->record.artist, input) != 0) {
		pCur = pCur->pNext;
		counter++;
	}
	if (counter == 0) { //if the list doesnt contain the search request
		printf("There are no albums by that artist..\n");
		return;
	}
	printf("There are %d album(s) containing that artist.\n", counter);
	if (counter > 1) {
		 pCur = plist->pHead;
		while (pCur != NULL && strcmp(pCur->record.artist, input) != 0) {
			printf("--> %s", pCur->record.album);
			//pPrev = pCur;
			pCur = pCur->pNext;
		}
		printf("Please enter the album name: \n");
		scanf(" %[^\n]", input);
		while (pCur != NULL && strcmp(pCur->record.album, input) != 0) {
			pCur = pCur->pNext;
		}
		printf("What do you want to edit?\n1.Artist\n2.Album\n3.Song Title\n4.Genre\n5.Song length\n6.Times Played\n 7.Rating\n");
		scanf("%d", &choice);

		switch (choice) {

		case 1:
			printf("What would you like the new Artist name to be?\n");
			scanf(" %[^\n]", input);
			strcpy(pCur->record.artist, input);
			break;

		case 2:
			printf("What would you like to renam the album as?\n");
			scanf(" %[^\n]", input);
			strcpy(pCur->record.album, input);
			break;
		case 3:
			printf("What would you like to rename the song?\n");
			scanf(" %[^\n]", input);
			strcpy(pCur->record.songname, input);
			break;
		case 4:
			printf("What would you like to rename the genre?\n");
			scanf(" %[^\n]", input);
			strcpy(pCur->record.genre, input);
			break;
		case 5:
			printf("What is the new song length in minutes then seconds: \n");
			scanf("%d%d", &minute, &second);
			minute = pCur->record.songLength.minute;
			second = pCur->record.songLength.second;
			break;
		case 6:
			printf("How many times has this song been played?\n");
			scanf("%d", &choice);
			choice = pCur->record.timesPlayed;
			break;
		case 7:
			printf("What is the new rating of the song?\n");
			scanf("%d", &choice);
			choice = pCur->record.rating;
			break;

		}


	}
	
}

int rate(List* plist) {

	Node* pCur = plist->pHead;

	char input[30] = { '\0' };

	int rate = 0;

	printf("Which song would you like to rate?\n");
	printList(pCur);
	scanf("%s", &input);

	if (pCur == NULL) {
		printf("There was an error allocating the node..\n");
		return -1;
	}

	while (pCur != NULL && strcmp(pCur->record.songname, input) == 0) {
		pCur = pCur->pNext;
	}

	if (pCur == NULL) {
		//in case item wasnt in the list
		printf("Sorry that item wasnt found in the list..\n");
		return -1;
	}
	//after correct node is found

	printf("What would you like to rate this song?\n");
	scanf("%d", &rate);

	pCur->record.rating = rate;

	printf("New rating stored sucessfully\n");
	return 1;
}

void exit(List* plist) {
	Node* pCur = plist->pHead;
	char input = { '\0' };

	FILE* outfile = fopen("musicPlayList.csv", "w");

	printf("Are you sure you want to exit? This will overwrite all current data in the file: (Y/N)\n");
	scanf(" %c", &input);
	if (input == 'y' || input == 'Y') {
		store(plist);
	}

	fclose(outfile);
	//if anything other than yes it just returns to the main menu
}

void play(List* plist) {
	Node* pCur = plist->pHead, * pPrev = NULL;

	char title[100];

	int input;
	printf("Would you like to play all songs? (1) or look for one? (2)\n");
	scanf("%d", &input);

	if (input == 1) {
		while (pCur != NULL) {
			printf("-->  %s %s %s %s %d:%d %d %d\n", pCur->record.artist, pCur->record.album, pCur->record.songname,
				pCur->record.genre, pCur->record.songLength.minute, pCur->record.songLength.second, pCur->record.timesPlayed, pCur->record.rating);
			Sleep(3000);
			system("cls");
			pCur = pCur->pNext;
		}
	}
	if (input == 2) {
		printf("What song do you want to start from?\n");
		scanf("%s", &input);
		while (pCur != NULL && strcmp(input, pCur->record.songname) == 0) {
			pCur = pCur->pNext;
		}
		while (pCur != NULL) {
			printf("-->  %s %s %s %s %d:%d %d %d\n", pCur->record.artist, pCur->record.album, pCur->record.songname,
				pCur->record.genre, pCur->record.songLength.minute, pCur->record.songLength.second, pCur->record.timesPlayed, pCur->record.rating);
			Sleep(3000);
			system("cls");
			pCur = pCur->pNext;
		}
	}

}

int insert(List* plist) {
	Record newrecord;

	char artistname[30] = { '\0' }, albumname[30] = { '\0' }, genre[15] = { '\0' }, songname[30] = { '\0' };

	int minutes = 0, seconds = 0, rating = 0, times_played = 0, test;

	printf("What is the artist name?\n");
	scanf(" %[^\n]", artistname);
	strcpy(newrecord.artist, artistname);
	printf("What is the album name?\n");
	scanf(" %[^\n]", albumname);
	strcpy(newrecord.album, albumname);
	printf("What is the song title?\n");
	scanf(" %[^\n]", songname);
	strcpy(newrecord.songname, songname);
	printf("what is the genre?\n");
	scanf(" %[^\n]", genre);
	strcpy(newrecord.genre, genre);
	printf("How long is the song? (minutes, then seconds)\n");
	scanf("%d %d", &minutes, &seconds);
	newrecord.songLength.minute = minutes;
	newrecord.songLength.second = seconds;
	printf("How many times has it been played, and what is the rating?(in that order)\n");
	scanf("%d %d", &times_played, &rating);
	newrecord.timesPlayed = times_played;
	newrecord.rating = rating;
	//make_node(newrecord);
	test = insertAtFront(plist, &newrecord);

	if (test == 1) {
		printf("Node added!\n");
		return 1;
	}

	else {
		printf("Error adding record, please try again..\n");
		return 0;
	}
}

int deleteRecord(List* plist) {

	Node* pMem = plist->pHead, *pPrev = NULL;

	char input[30] = { '\0' };
	if (pMem == NULL) {
		printf("List is empty, nothing to delete\n");
		return 0;
	}
	
	char temp;

	printf("What song would you like to delete? (This will delete the entire record as well)\n");
	scanf(" %[^\n]", input);

	while (pMem != NULL && strcmp(input, pMem->record.songname) != 0) { //sorts through list until the node is found
		pPrev = pMem;
		pMem = pMem->pNext;
	}
	
	if (pMem != NULL) {
		//node is found

			if (pPrev == NULL) {
				plist->pHead = pMem->pNext; //if list only has one node, or is at the end of the list
			}
			else {
				pPrev->pNext = pMem->pNext; //patches the hole made in the list if the node is in the middle
			}
			free(pMem);
			printf("Delete successful\n");
			return 1;
		
	}
	else {
			printf("Song is not in the database, please try again\n");
			return -1;
	}
}

void sort(List* plist) {

	Node* pCur = plist->pHead, * pPrev = NULL;

	Record temp;

	int input, totalSongs = 0, test = 0;


	printf("How would you like to sort your playlist?\n1.By Artist, 2.By Album, 3.By Rating, 4.By Times Played\n");
	scanf("%d", &input);


	switch (input) {

	case 1:
		while (pCur != NULL) {
			if (strcmp(pCur->record.artist, pCur->pNext->record.artist) > 0) {
				temp = pCur->record;
				pCur->record = pCur->pNext->record;
				pCur->pNext->record = temp;
				pCur = plist->pHead;
			}
			pCur = pCur->pNext;
		}

		printList(plist);

	case 2:

		while (pCur != NULL) {
			if (strcmp(pCur->record.album, pCur->pNext->record.album) > 0) {
				temp = pCur->record;
				pCur->record = pCur->pNext->record;
				pCur->pNext->record = temp;
				pCur = plist->pHead;
			}
			pCur = pCur->pNext;
		}

		printList(plist);
	case 3:
		while (pCur != NULL) {
			if (pCur->record.rating > pCur->pNext->record.rating) {
				temp = pCur->record;
				pCur->record = pCur->pNext->record;
				pCur->pNext->record = temp;
				pCur = plist->pHead;
			}
			pCur = pCur->pNext;
		}

		printList(plist);

	case 4:
		while (pCur != NULL) {
			if (pCur->record.timesPlayed > pCur->pNext->record.timesPlayed) {
				temp = pCur->record;
				pCur->record = pCur->pNext->record;
				pCur->pNext->record = temp;
				pCur = plist->pHead;
			}
			pCur = pCur->pNext;
		}
	}


}

void shuffle(List* plist) { //regular shuffle, not the truffle shuffle

	srand(time(NULL)); //random seed generator for the rand function

	int totalSongs = 0, ran = 0, i = 0, j = 0;

	Node* pCur = plist->pHead, *pPrev = NULL;
	
	if (pCur == NULL) {
		printf("Something went wrong or list is empty\n");
	}
	
	while (pCur != NULL) {
		pCur = pCur->pNext;
		totalSongs++; //loops through the list to figure out how many records there are
	}

	int temp[30]; //temp array to hold randomized values

	/*this chunk took me forever to figure out
                        |	
	                    V
	*/
	for (i = 0; i < totalSongs; i++) {
		ran = rand() % totalSongs;
		temp[i] = ran;
		for (j = 0; j < i; j++) {
			if (temp[i] == temp[j]) {
				temp[i] = rand() % totalSongs;
			}
		}
	}
	pCur = plist->pHead;
		int traverse = 0;
		for (i = 0; i < totalSongs; i++) {
			while (traverse != temp[i]) {
				pCur = pCur->pNext;
				traverse++;
			}
			printf("Artist: %s\n", pCur->record.artist);
			printf("Album: %s\n", pCur->record.album);
			printf("Song Title: %s\n", pCur->record.songname);
			printf("Genre: %s\n", pCur->record.genre);
			printf("Length: %d:%d\n", pCur->record.songLength.minute, pCur->record.songLength.second);
			printf("Times Played: %d\n", pCur->record.timesPlayed);
			printf("Rating: %d\n", pCur->record.rating);
			Sleep(5000);
			system("cls");
			pCur = plist->pHead; //resets pCur
			traverse = 0;
	}
}

