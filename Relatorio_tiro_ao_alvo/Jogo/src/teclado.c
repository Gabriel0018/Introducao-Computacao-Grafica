#include <GL/glut.h>		// biblioteca do GLUT
#include <stdlib.h>		// bibliotecas do C
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#ifdef __HAVE_LIB_X11__
#include "display_info.h"
#endif

#include "jogo.h"
#include "movimentos.h"
// #include "mydebuglib.h"
#include "teclado.h"
#include "movimentos.h"
#include "record.h"
#include "objetos.h"
#include "desenha.h"


static unsigned char LCmd;

unsigned char  getLastCommand(void)
{

   return(toupper(LCmd));
}

void setLastCommand(unsigned char lc)
{
	LCmd = lc;
}

void Teclado(unsigned char k, int x, int y){

	if (getLastCommand() =='Q' ) {
		switch( k ) {
			case 's'	:
			case 'S'	:
							FimJogo(1);
							break;
			case 'n'	:
			case 'N'	:
							SortRecords();
							WriteRecords();
							InicializaObjetosVar();
							InicializaObjetos();
							break;
		}
	} else {
		switch( k ) {
			case  'a'	:
			case  'A'	:
						MoveEsquerda();
						break;
			case  'w'	:
			case  'W'	:
						MoveFrente();
						break;
			case  'z'	:
			case  'Z'	:
						MoveTras();
						break;
			case  's'	:
			case  'S'	:
						MoveDireita();
						break;
			case 'q'	:
			case 'Q'	:
						setLastCommand(k);
						FimJogo(0);
						break;
			case 'r'	:
			case 'R'	:
						InicializaAlvos();
						break;
			case 'i'	:
						DecrementaAlvos(5);
						break;
			case 'I'	:
						IncrementaAlvos(5);
						break;
			case 'c'	:
						FlagMira=0;
						break;
			case 'C'	:
						FlagMira=1;
						break;
			case 't'	:
						FlagTiro=0;
						break;
			case 'T'	:
						FlagTiro=1;
						break;
			default 	:
						break;
		}
	}
}

