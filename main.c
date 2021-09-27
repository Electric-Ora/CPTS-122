#include"header.h"
#include"test.h"

int main(void) {

	int input = 0;

	int test;

	List plist;

	Record KatyPerry, Soundgarden, Beck;

	initList(&plist);

	printf("Welcome to the digital music manager!\n Please select an option: \n");
	printf("1.Load\n2.Store\n3.Display\n4.Insert\n5.Delete\n6.Edit\n7.Sort\n8.Rate\n9.Play\n10.Shuffle\n11.Exit\n");
	do {
		scanf("%d", &input);
		switch (input) {
		case 1:
			test = load(&plist);
			if (test == -1) {
				printf("Load function Successful.\n");
			}
			display(&plist);
			break;

		case 2:
			test = store(&plist);

			if (test == -1) {
				printf("Store function failed.\n");
		}
			break;

		case 3:
			display(&plist);
			break;

		case 4:
			insert(&plist);
			break;

		case 5:
			test = deleteRecord(&plist);
			if (test == -1) {
				printf("Please try again");
			}
			break;
		case 6:
			edit(&plist);
			break;

		case 7:
			sort(&plist);
			break;

		case 8:
			test = rate(&plist);
			if (test == -1) {
				printf("Rate function failed\n");
			}
			break;

		case 9:
			play(&plist);
			break;

		case 10:
			shuffle(&plist);
			break;

		case 11:
			exit(&plist);
			break;

		case 12:
			createdeleterecord(&KatyPerry, &plist);
			deleteRecord_test(&plist, &KatyPerry);
			createdeleterecord(&KatyPerry, &plist); //recreating it for the other test functions
			createdeleterecord_Soundgarden(&Soundgarden, &plist);
			createdeleterecord_Beck(&Beck, &plist);
			testinsert(&plist, &KatyPerry);
			testshuffle(&plist, &KatyPerry, &Soundgarden, &Beck);
			break;
		case 13:
			if (input > 12) {
				printf("That is not a valid input, please try again\n");
				break;
			}
		}

	} while (input != 11);

	



	return 0;
}

//Joe

//Joe who?

//Joe mama