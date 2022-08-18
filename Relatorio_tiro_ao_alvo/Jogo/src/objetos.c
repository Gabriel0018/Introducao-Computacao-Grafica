#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#include "jogo.h"
#include "objetos.h"
#include "movimentos.h"
#include "record.h"
#include "desenha.h"

ObjMira	Mira;
Objeto	Camera;
Objeto   Placar;
Objeto	Corredor;
Objeto	Tiros[MAX_TIROS_SCR];
Objeto	Alvos[MAX_INIMIGOS_SCR];
Objeto	Luminarias[MAX_LUMINARIAS_SCR];
Objeto	Lampadas[MAX_LUMINARIAS_SCR];
Objeto	Explosao[MAX_INIMIGOS_SCR][MAX_EXPLOSAO_SCR];
int		Total_Inimigos_Scr;
int		FontesLuminosas[GL_MAX_LIGHTS];
int		FlagMira;		// 0 -> Camera fixa  1 -> Camera na mira
int		FlagTiro;		// 0 -> Tiro Paralelo  1 -> Tiro em trajetoria
int 		Saindo;			// 0 -> Jogo Normal 1 -> Saindo
int 		Pausa;			// 0 -> Jogo Normal 1 -> Pausa

void IncrementaAlvos(int i){
int j,k=0;
	
	if (Total_Inimigos_Scr < MAX_INIMIGOS_SCR) {
		for (j=0; (j < Total_Inimigos_Scr+i) && (k < i);j++) {
			if (Alvos[j].visible == O_DISABLE) {
				InicializaAlvo(j);
				k++;
			}
			if ( k >= i )
				break;
		}
		Total_Inimigos_Scr += i;
	}
}

void DecrementaAlvos(int i){
int j,k;
	
	k=i;
	if (Total_Inimigos_Scr > MIN_INIMIGOS_SCR ) {
		for (j=Total_Inimigos_Scr; (j > 0) && k; j--)
			if (Alvos[j].visible == O_VISIBLE) {
				Alvos[j].visible = O_DISABLE;
				k--;
			}
		Total_Inimigos_Scr -= i;
	}
}

void InicializaObjetosVar(void) {
int i;
	
	Total_Inimigos_Scr = 10;
	printf("Luzes = %d sizeof %d\n",GL_MAX_LIGHTS,sizeof(GL_LIGHT0));
	for(i=0;i<GL_MAX_LIGHTS;i++)
		FontesLuminosas[i] = i;
	Mira.x		= Mira.y = 0; 
    Mira.z 		= -WIDTH;
	Camera.x 	= Camera.y = 0;
	Camera.z 	= -WIDTH;
	Camera.xr 	= Camera.yr = 0;
	Camera.zr 	= -(WIDTH + DEPTH);
	DrawRecords = 0;
	Saindo = 0;
	LoadRecords();
		
}

void InicializaLuminarias(void){
int  ex,ez;
int  l;

	ez = DEPTH/4;
	for (l=0;l<MAX_LUMINARIAS_SCR;l++){
		Luminarias[l].x = 0;
		Luminarias[l].y = HEIGHT - 2;
		Luminarias[l].z = -(WIDTH + 250 + ez * l);
		Luminarias[l].dx = 50;
		Luminarias[l].dz = 50;
		Luminarias[l].dy = 20;
		Lampadas[l].x = Luminarias[l].x;
		Lampadas[l].z = Luminarias[l].z;
		Lampadas[l].y = Luminarias[l].y;
	}
}

void InicializaCorredores(void) {

	Corredor.visible = O_VISIBLE;
	Corredor.iy = 10;
	Corredor.y = 0;
	Corredor.iz = 50;
	Corredor.z = -WIDTH;
}

void InicializaObjetos(void){

	InicializaObjetosVar();
	InicializaMira();
	InicializaPlacar();
	InicializaTiros();
	InicializaAlvos();
	InicializaCorredores();
	InicializaLuminarias();

}

void InicializaTiros(void) {
int i;
	for (i=0; i < MAX_TIROS_SCR; i ++) {
		Tiros[i].visible = O_DISABLE;
		Tiros[i].dx = 5;
		Tiros[i].iz = 30;
	}
}

void InicializaAlvos(void) {
int i;
	
	for (i=0;i<MAX_INIMIGOS_SCR; i++){
		InicializaAlvo(i);
	}
}

void InicializaAlvo(int i) {
int r;

	Alvos[i].visible = O_VISIBLE;
	Alvos[i].x =  (random()&WIDTH) *(pow(-1,(random()&1)));
	Alvos[i].y =  (random()&HEIGHT)*(pow(-1,(random()&1)));
	do Alvos[i].z = -(random()&(WIDTH+DEPTH)); while ( abs(Alvos[i].z) < WIDTH ); 
	Alvos[i].cor[RED] 	= TCOLOR((random()&0xFF00) >> 8);
	Alvos[i].cor[GREEN] = TCOLOR((random()&0x55));
	Alvos[i].cor[BLUE] 	= TCOLOR((random()&0xAA));
	do 	r = (random()&0x3F); while (r == 0);  // Nao deixa ter tamanho 0 (zero)
	Alvos[i].dz = Alvos[i].dy = Alvos[i].dx = r;
	if ( abs(Alvos[i].x) + Alvos[i].dx > WIDTH )
		if ( Alvos[i].x > 0 )
			Alvos[i].x -= (2 * Alvos[i].dx);
		else
			Alvos[i].x += (2 * Alvos[i].dx);
	if ( abs(Alvos[i].y) + Alvos[i].dy > HEIGHT )
		if ( Alvos[i].y > 0 )
			Alvos[i].y -= (2 * Alvos[i].dy);
		else
			Alvos[i].y += (2 * Alvos[i].dy);
		
	do {									// Nao permite deslocamento nos 3 eixos
		Alvos[i].ix = random()&0x05;		// Igual Zero
		Alvos[i].iy = random()&0x05;
		Alvos[i].iz = random()&0x05;
	} while (( Alvos[i].ix == 0 ) || ( Alvos[i].iy == 0 ) || ( Alvos[i].iz == 0 ));
	Alvos[i].valor = (unsigned long int)(MAX_TARGET_VALUE / (unsigned long int)(Alvos[i].dx) );
}

void InicializaPlacar(void){

	Placar.visible = O_VISIBLE;
	Placar.valor = (unsigned long int)(0);
	Placar.x = WIDTH-200;
	Placar.y = 400;
	Placar.z = Mira.z;
	Placar.cor[RED] = 1.0;
	Placar.cor[GREEN] = 1.0;
	Placar.cor[BLUE] = 1.0;
	Placar.ix = 0;		// Armazena o valor de quantos objetos estao visiveis
	Placar.dx = 0;		// Armazena o valor de quantos objetos foram abatidos
}

void InicializaMira(void) {
int   alfa,cx,cy;
register int	c,i;

	Mira.visible	=  O_VISIBLE;
	Mira.x 			=  Mira.y = 0;
	Mira.z 			= -WIDTH;
	Mira.raios[0] = 50;
	Mira.raios[1] = 10;
	cx =  (2*Mira.x-JanelaX);
	cy = -(2*Mira.y-JanelaY);
	Mira.cor[RED] = TCOLOR(255);
	Mira.cor[GREEN] = TCOLOR(255);
	Mira.cor[BLUE] = TCOLOR(255);
	for (c=0; c< 2 ; c++ ) {
		for(i=0,alfa=0;alfa<=360;alfa+=10,i++) {
			Mira.pontos[c][i][MIRA_X] = Mira.raios[c] * cos(alfa*PI/180);
			Mira.pontos[c][i][MIRA_Y] = Mira.raios[c] * sin(alfa*PI/180);
			Mira.pontos[c][i][MIRA_Z] = Mira.z;
		}
	}
}
