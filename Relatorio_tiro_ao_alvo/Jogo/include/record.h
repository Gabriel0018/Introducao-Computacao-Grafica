#ifndef _RECORD_H_
#define _RECORD_H_

#define	MAX_RECORD	10
#define  R_FILE_OK		0
#define  R_FILE_OPEN		1
#define	R_FILE_CREATE	2
#define	R_FILE_ERROR	3

extern int  DrawRecords;
extern unsigned long int records[MAX_RECORD];


int 	LoadRecords();
int 	WriteRecords(void);
void 	SortRecords(void);

#endif
