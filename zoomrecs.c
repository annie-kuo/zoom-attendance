/*
Contains functions to manipulate data
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zoomrecs.h"

// DEFINE REQUIRED FUNCTIONS
struct ZoomRecord *head;

int addZoomRecord(struct ZoomRecord **head, char* semail, char* sname, int duration, char lab) {
	// search for the student's information in the linked list	
	// in case the list is empty, create a new node
	if (*head == NULL || strcmp((*head)->email,semail) > 0) {
		// create new node
		struct ZoomRecord *newRecord;
		newRecord = (struct ZoomRecord*) malloc(sizeof(struct ZoomRecord));
		if (newRecord == NULL) {
			printf("Error! Program ran out of memory \n");
			return 1;
		}
		// define fields
		strcpy(newRecord->email, semail);
		strcpy(newRecord->name,sname);
		newRecord->durations[lab-'A'] = duration;

		// add to list
		newRecord->next = *head;
		*head = newRecord;
	} else {
		// search for the student's data
		struct ZoomRecord* current;
		current = *head;

		while (current->next != NULL && strcmp(current->next->email,semail) < 0) {
			current = current->next;
		}
		// update node if student has been found (either it is the head, or after current)
		if (strcmp(current->email,semail) == 0) {
			current->durations[lab-'A'] += duration;
			
		} else if (current->next != NULL && strcmp(current->next->email,semail) == 0) {
			current->next->durations[lab-'A'] += duration;
			
		} else {
			// create new node if student has not been found
			struct ZoomRecord *newRecord;
			newRecord = (struct ZoomRecord*) malloc(sizeof(struct ZoomRecord));
			if (newRecord == NULL) {
				printf("Error! Program ran out of memory \n");
				return 1;
			}
			// define fields
			strcpy(newRecord->email, semail);
			strcpy(newRecord->name, sname);
			newRecord->durations[lab-'A'] = duration;

			// add to list
			newRecord->next = current->next;
			current->next = newRecord;
		}
	}
	return 0;

}


void generateAttendance(struct ZoomRecord **head, FILE *output) {
	struct ZoomRecord* current;
	current = *head;

	fprintf(output, "User Email,Name (Original Name),A,B,C,D,E,F,G,H,I,Attendance (Percentage)\n");
	
	// write the data to the output file
	while (current != NULL) {
		// calculate percentage and create string of duration
		int attendance = 0;
		char durationString[300];
		strcpy(durationString,"");

		for (int i = 0; i < 9; i++) {
			if (current->durations[i] >= 45) {
				attendance++;
			}
			char str[3];
			sprintf(str, "%d", current->durations[i]);
			strcat(durationString,str);
			if (i != 8) {
				strcat(durationString,",");
			}

		}

		float percentage = (attendance/(float) 9)*100;

		// write data to the output fine
		fprintf(output, "%s,%s,%s,%0.2f\n", current->email,current->name,durationString, percentage);
		current=current->next;
	}
}

// DEFINE HELPER FUNCTIONS
void printNodes(struct ZoomRecord *ptr) {
	// traverse the list and print
	while (ptr != NULL) {
		printf("\n%s ", ptr->name);
		for (int i=0; i<9; i++) {
		printf("%d ",ptr->durations[i]);
		}
		ptr=ptr->next;
	}
}
