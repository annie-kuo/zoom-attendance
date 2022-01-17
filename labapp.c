/*
Program to generate an ordered list of student lab attendance
***************************************************************
* Author	Dept.		Date		Notes
***************************************************************
* Annie K	Comp. Science.	Apr 26 2021	Inital blank version.
* Annie K	Comp. Science.	Apr 27 2021	Added input validation.
* Annie K	Comp. Science.	Apr 27 2021	Added zoomrecs functions.
* Annie K	Comp. Science.	Apr 27 2021	Implemented attendance algorithm.
* Annie K	Comp. Science.	Apr 27 2021	Added debugging function.
*/

#include "zoomrecs.h"

int main(int argc, char *argv[]) {
	// INPUT VALIDATION
	/* argv[1] is an input CSV file
	 * argv[2] is an ourput filename
	 */
	
	// check if the program is passed 2 arguments
	if (argc != 3) {
		printf("Usage ./labapp <inputcsv> <outputcsv>\n");
		return 1;
	}

	// check if the program can open the input file
	FILE *input=fopen(argv[1],"rt");
	if (input == NULL) {
		printf("Error! Unable to open the input file %s\n", argv[1]);
		return 1;
	}

	// check if the program can open the output file
	FILE *output=fopen(argv[2],"wt");
	if (output == NULL) {
		printf("Error! Unable to open the output file %s\n", argv[2]);
		return 1;
	}


	// LAB ATTENDANCE ALGORITHM
	extern struct ZoomRecord *head;
	char line[200];
	fgets(line,200,input);
	fgets(line,200,input);

	while (!feof(input)) {
		// get data for the line
		char *semail = strtok(line,",");
		char *sname = strtok(NULL, ",");
		char lab = *strtok(NULL,",");
		char *duration = strtok(NULL, ",");

		//printf("%s, %s, %c, %s\n", semail,sname, lab, duration);
		
		// add record
		addZoomRecord(&head, semail, sname, atoi(duration), lab);

		fgets(line,200,input);	
				
	}
	
	// check if linked list is correctly created
	//printNodes(head);

	// create output file
	generateAttendance(&head, output);
	
	fclose(input);
	fclose(output);

	// clean
	struct ZoomRecord *cleanNext;
	cleanNext = head;
	while (cleanNext != NULL) {
		head = cleanNext;
		cleanNext = head -> next;
		free(head);
	}

	return 0;
}
