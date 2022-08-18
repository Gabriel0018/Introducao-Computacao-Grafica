#include <GL/glut.h>	// biblioteca do GLUT
#include <stdlib.h>		// bibliotecas do C
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "jogo.h"
// #include "mydebuglib.h"
#include "objetos.h"
#include "tragetoria.h"
#include "mouse.h"
//#include "movimentos.h"

void BotoesMouse(int b, int s, int x, int y){
static int flag=0;
register int t;

	if ( !flag ) {
		flag = 1;
		if ( b == 0 && s == 1 ) {
			for(t=0;t<MAX_TIROS_SCR;t++) {
				if (Tiros[t].visible != O_VISIBLE) {
					Tiros[t].x =  (2*x-WIDTH);
					Tiros[t].y = -(2*y-HEIGHT);
					Tiros[t].z =   Mira.z;
					Tiros[t].visible = O_VISIBLE;
					if (FlagTiro)
						CalculaTrajetoriaInicial(t);
					break;
				}
			}
		}
		flag = 0;		
	}
}
