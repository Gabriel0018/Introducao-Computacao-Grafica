#include <GL/glut.h>		// biblioteca do GLUT
#include <stdlib.h>		// bibliotecas do C
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "jogo.h"
// #include "mydebuglib.h"
#include "desenha.h"
#include "teclado.h"
#include "mouse.h"
#include "movimentos.h"
#include "record.h"


int		DrawRecords;
unsigned long int records[MAX_RECORD];


void InsereRecord(unsigned long int r){
int i,j;

	for (i=0;i < MAX_RECORD ; i++) {
		if (r > records[i] )
			break;
	}
	if ( i < MAX_RECORD ) {
		for (j=MAX_RECORD-1;j > i;j--)
			records[j] = records[j-1];
		records[i]=r;
	}
}
int LoadRecords(){
FILE *fp;
int	r,i;

	r = R_FILE_OPEN;
	if ((fp = fopen("records.bin","rb"))==(FILE *)(NULL))	{
		fp = fopen("records.bin","wb");
		fwrite(records,sizeof(unsigned long int),MAX_RECORD,fp);
		fflush(fp);
		fclose(fp);
		for(i=0; i< MAX_RECORD; i++)
			records[i]=0;
		r = R_FILE_CREATE;
	}
	else {
		if (fread(records,sizeof(unsigned long int),MAX_RECORD,fp)!=MAX_RECORD){
			r = R_FILE_ERROR;
		}
		fclose(fp);
	}
	return (r);
}

int WriteRecords(void){
FILE *fp;
int r;

	r = R_FILE_OK;
	if ((fp = fopen("records.bin","wb"))==(FILE *)(NULL))	{
		r = R_FILE_ERROR;
	}
	else {
		if (fwrite(records,sizeof(unsigned long int),MAX_RECORD,fp)!=MAX_RECORD){
			r =R_FILE_ERROR;
		}
		fflush(fp);
		fclose(fp);
	}
	return(r);
}

void SortRecords(void) {
int i,j;
unsigned long int tmp;

	for(i=0;i<MAX_RECORD-1;i++)
		for(j=i+1;j<MAX_RECORD;j++)
			if (records[i] < records[j]) {
				tmp = records[i];
				records[i] = records[j];
				records[j] = tmp;
			}
}
