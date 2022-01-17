/*
Program to generate an ordered list of student lab attendance
***************************************************************
* Author	Dept.		Date		Notes
***************************************************************
* Annie K	Comp. Science.	Apr 26 2021	Inital blank version.
* Annie K	Comp. Science.	Apr 27 2021	Added
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ZoomRecord
{
char email[60]; // email of the student
char name[60]; // name of the student
int durations[9]; // duration for each lab.
struct ZoomRecord *next;
};

int addZoomRecord(struct ZoomRecord **head, char* semail, char* sname, int duration, char lab);
void generateAttendance(struct ZoomRecord **head, FILE* output);
void printNodes(struct ZoomRecord *ptr);