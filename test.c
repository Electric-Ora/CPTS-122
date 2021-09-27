#include "test.h"


int createdeleterecord(Record* record, List* plist) { //this is used to import the katy perry record from the rubric

	char artist[30] = "Katy Perry";
	char album[15] = "Witness";
	char title[20] = "Chained to the Rythm";
	char genre[10] = "pop";
	int minute = 4, second = 32, timesplayed = 3, rating = 5, success = 0;

	strcpy(record->artist, artist);
	strcpy(record->album, album);
	strcpy(record->songname, title);
	strcpy(record->genre, genre);
	record->songLength.minute = minute;
	record->songLength.second = second;
	record->timesPlayed = timesplayed;
	record->rating = rating;

	success =insertAtFront(plist, record);
	if (success != 1) {
		printf("record creation failed\n");
	}
	else {
		printf("Success!\n");
	}
}

int testinsert(List* plist, Record* record) {

	Record newrecord;

	char artistname[30] = { '\0' }, albumname[30] = { '\0' }, genre[15] = { '\0' }, songname[30] = { '\0' };

	int minutes = 0, seconds = 0, rating = 0, times_played = 0, test;

	strcpy(artistname, record->artist);
	strcpy(albumname, record->album);
	strcpy(genre, record->genre);
	strcpy(songname, record->songname);
	minutes = record->songLength.minute;
	seconds = record->songLength.second;
	times_played = record->timesPlayed;
	if (times_played == -1) {
		printf("They hated that song so much they reversed time to unhear it\n");
	}
	while (rating > 1 || rating < 5) {
		rating = record->rating;
		if (rating > 5) {
			printf("I know it was good, but keep it within the limits\n");
		}
		else if (rating < 1) {
			printf("You cant give it a rating lower than one.");
		}
	}
	//this is a little redundant but this will work for any test album you want to import
	strcpy(newrecord.artist, artistname);
	strcpy(newrecord.album, albumname);
	strcpy(newrecord.genre, genre);
	strcpy(newrecord.songname, songname);
	newrecord.songLength.minute = minutes;
	newrecord.songLength.second = seconds;
	newrecord.timesPlayed = times_played;
	newrecord.rating = rating;

	test = insertAtFront(plist, &newrecord);

	if (test == 1) {
		printf("Node added!\n");
		return 1;
	}
	else if (plist->pHead == NULL) {
		printf("Error adding record to list\n");
	}
	else {
		printf("Error adding record, please try again..\n");
		return 0;
	}
}

int deleteRecord_test(List* plist, Record* data) {

	Node* pMem = plist->pHead, * pPrev = NULL;

	char song[100];

	strcpy(song, data->songname);

	if (pMem == NULL) {
		printf("List is empty, nothing to delete\n");
		return 0;
	}

	char temp;
	//these are removed from the original function since it asks for user input
	//printf("What song would you like to delete? (This will delete the entire record as well)\n");   
	//scanf("%s", &input);

	while (pMem != NULL && strcmp(song, pMem->record.songname) != 0) { //sorts through list until the node is found
		pPrev = pMem;
		pMem = pMem->pNext;
	}

	if (pMem != NULL) {
		//node is found
		printf("Are you sure you want to delete this record?(Y/N)\n");
		scanf(" %c", &temp);

		if (temp == 'y' || temp == 'Y') {
			if (pPrev == NULL) {
				plist->pHead = pMem->pNext; //if list only has one node, or is at the end of the list
				if (plist->pHead == NULL) {
					printf("List only had one item, or everything got corrupt (hopefully its the latter)\n"); //checks to make sure the head pointer got updated
				}
			}
			else {
				pPrev->pNext = pMem->pNext; //patches the hole made in the list if the node is in the middle
			}
			free(pMem);
			printf("Delete successful\n");
			return 1;
		}
		else {
			printf("returning to main menu\n");
		}
	}
	else {
		printf("Song is not in the database, please try again\n");
		return -1;
	}
}

int testshuffle(List* plist, Record* record1, Record* record2, Record* record3) { 

	//inserting our three records for testing
	testinsert(plist, record1);
	testinsert(plist, record2);
	testinsert(plist, record3);

	srand(time(NULL)); //random seed generator for the rand function

	int totalSongs = 0, ran = 0, i = 0, j = 0;

	Node* pCur = plist->pHead, * pPrev = NULL;

	if (pCur == NULL) {
		printf("Something went wrong or list is empty\n");
	}

	while (pCur != NULL) {
		pCur = pCur->pNext;
		totalSongs++; //loops through the list to figure out how many records there are
	}

	int temp[3] = { 3, 1, 2 }; //temp array to hold randomized values

	/*this chunk took me forever to figure out
						|
						V
	*/
	/*
	commenting this out since we dont need the randomized one
	for (i = 0; i < totalSongs; i++) {
		ran = rand() % totalSongs;
		temp[i] = ran;
		for (j = 0; j < i; j++) {
			if (temp[i] == temp[j]) {
				temp[i] = rand() % totalSongs;
			}
		}
	}*/
	pCur = plist->pHead;
	int traverse = 0;
	for (i = 0; i < totalSongs; i++) {
		while (traverse != temp[i]) {
			pCur = pCur->pNext;
			traverse++;
		}
		printf("Song node number: %d", traverse); //prints the node location to ensure it is playing in the correct "random" order.
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

int createdeleterecord_Soundgarden(Record* record, List* plist) { 

	char artist[30] = "Soundgarden";
	char album[15] = "A-Sides";
	char title[20] = "Black Hole Sun"; //one of the best songs ever btw, Teddy Roosevelt said so himself
	char genre[10] = "Grunge";
	int minute = 3, second = 36, timesplayed = 4, rating = 5, success = 0;

	strcpy(record->artist, artist);
	strcpy(record->album, album);
	strcpy(record->songname, title);
	strcpy(record->genre, genre);
	record->songLength.minute = minute;
	record->songLength.second = second;
	record->timesPlayed = timesplayed;
	record->rating = rating;

	success = insertAtFront(plist, record);
	if (success != 1) {
		printf("record creation failed\n");
	}
	else {
		printf("Success!\n");
	}
}

int createdeleterecord_Beck(Record* record, List* plist) {

	char artist[30] = "Beck";
	char album[15] = "Mellow Gold";
	char title[20] = "Loser"; 
	char genre[15] = "Alternative";
	int minute = 3, second = 55, timesplayed = 2, rating = 3, success = 0;

	strcpy(record->artist, artist);
	strcpy(record->album, album);
	strcpy(record->songname, title);
	strcpy(record->genre, genre);
	record->songLength.minute = minute;
	record->songLength.second = second;
	record->timesPlayed = timesplayed;
	record->rating = rating;

	success = insertAtFront(plist, record);
	if (success != 1) {
		printf("record creation failed\n");
	}
	else {
		printf("Success!\n");
	}
}
