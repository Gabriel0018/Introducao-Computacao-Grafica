#include <GL/glut.h>		// biblioteca do GLUT
#include <stdlib.h>		// bibliotecas do C
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef __HAVE_LIB_X11__
#include "display_info.h"
#endif

#include "jogo.h"
// #include "mydebuglib.h"
#include "texturas.h"
#include "desenha.h"
#include "teclado.h"
#include "mouse.h"
#include "movimentos.h"
#include "objetos.h"
#include "record.h"
#include "tragetoria.h"


void CalculaTrajetoriaInicial(int i) {

Tiros[i].xr =  (2*Mira.x-JanelaX);
Tiros[i].yr = -(2*Mira.y-JanelaY);
Tiros[i].ta =  (Tiros[i].xr/(-Mira.z * 1.0));
Tiros[i].tt =  (Tiros[i].yr/(-Mira.z * 1.0));
Tiros[i].x = -Tiros[i].z * Tiros[i].ta;
Tiros[i].y = -Tiros[i].z * Tiros[i].tt;
Tiros[i].z -= Tiros[i].iz;
}

void CalculaTrajetoria(int i) {
Tiros[i].x = -Tiros[i].z * Tiros[i].ta;
Tiros[i].y = -Tiros[i].z * Tiros[i].tt;
Tiros[i].z -= Tiros[i].iz;
if ((Tiros[i].z > WIDTH+DEPTH) || (abs(Tiros[i].x) > WIDTH) || (abs(Tiros[i].y) > HEIGHT))
	Tiros[i].visible = O_DISABLE;

}
