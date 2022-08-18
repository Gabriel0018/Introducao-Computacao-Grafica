#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>

#include "jogo.h"
#include "desenha.h"
#include "objetos.h"
// #include "texturas.h"
#include "mouse.h"
#include "teclado.h"
#include "tragetoria.h"
#include "movimentos.h"


void MoveMira(int x, int y) {
	
	Mira.x = x;
	Mira.y = y;

}

void MoveDireita(void ){

	if ( Corredor.y < 90 ){
		Corredor.y += Corredor.iy;   // Gira iy graus
		glTranslated(0,0,(GLdouble)(-WIDTH));
		glRotatef((GLfloat)(Corredor.y),0,1,0);
		glTranslated(0.0,0.0,(GLdouble)(WIDTH));
	}
	else
		Corredor.y =  90;
}

void MoveEsquerda(void ){

	if ( Corredor.y > -90 ) {
		Corredor.y -= Corredor.iy;	// Gira iy Graus
		glTranslated(0.0,0.0,(GLdouble)(-WIDTH));
		glRotatef((GLfloat)(Corredor.y),0,1,0);
		glTranslated(0.0,0.0,(GLdouble)(WIDTH));
	}
	else
		Corredor.y = -90;

	
}

void MoveFrente(void ){

	if (Mira.z > -(WIDTH+DEPTH-50)) {
		glTranslated(0,0,Corredor.iz);
		Mira.z+=-Corredor.iz;
	}
	
}

void MoveTras(void ){

	if (Mira.z < -(WIDTH+50)) {
		glTranslated(0,0,-Corredor.iz);
		Mira.z+= Corredor.iz;
	}
	
}

void MoveTiros(void) {
int t;

	for(t=0;t<MAX_TIROS_SCR;t++)
		if (Tiros[t].visible == O_VISIBLE){
			if (FlagTiro)
				CalculaTrajetoria(t);
			else
				Tiros[t].z -= Tiros[t].iz;
		}
}

void MoveTiro(void){
}

void MoveAlvo(int b){	
}

void MoveAlvos(void){
static flag=0;
int i;
int m,n,mx,my,mz,rx,ry,rz;

    if (flag == 0 ) {
		flag = 1;
		for (i=0; i < Total_Inimigos_Scr; i++) {
			if ( Alvos[i].visible == O_DISABLE ) {
				InicializaAlvo(i);
			}
			if (Alvos[i].visible == O_VISIBLE) {
				Alvos[i].x += Alvos[i].ix; 
				Alvos[i].y += Alvos[i].iy; 
				Alvos[i].z += Alvos[i].iz;
				Alvos[i].xr = Alvos[i].x * JanelaX / (-Alvos[i].z);
				Alvos[i].yr = Alvos[i].y * JanelaX / (-Alvos[i].z);
				Alvos[i].zr = -JanelaX;
				// Colisao com as paredes
				if (   (Alvos[i].x + Alvos[i].dx )>= JanelaX     )
					{Alvos[i].ix = -Alvos[i].ix; Alvos[i].x += Alvos[i].ix;}
				if (   (Alvos[i].y + Alvos[i].dy )>= JanelaY     )
					{Alvos[i].iy = -Alvos[i].iy; Alvos[i].y += Alvos[i].iy;}
				if (abs(Alvos[i].z - Alvos[i].dz )>=(WIDTH+DEPTH))
					{Alvos[i].iz = -Alvos[i].iz; Alvos[i].z += Alvos[i].iz;}
				if (   (Alvos[i].x - Alvos[i].dx )<=-JanelaX     )
					{Alvos[i].ix = -Alvos[i].ix; Alvos[i].x += Alvos[i].ix;}
				if (   (Alvos[i].y - Alvos[i].dy )<=-JanelaY     )
					{Alvos[i].iy = -Alvos[i].iy; Alvos[i].y += Alvos[i].iy;}
				if (abs(Alvos[i].z + Alvos[i].dz )<= JanelaX     )
					{Alvos[i].iz = -Alvos[i].iz; Alvos[i].z += Alvos[i].iz;}
				// Colisao Entre si
				for (m=0;m< Total_Inimigos_Scr-1; m++)
					for(n=m+1;n<Total_Inimigos_Scr; n++){
						mx = Alvos[m].x - Alvos[n].x;
						my = Alvos[m].y - Alvos[n].y;
						mz = Alvos[m].z - Alvos[n].z;
						mx = sqrt(mx * mx + my * my + mz * mz);
						rx = Alvos[m].dx + Alvos[n].dx;
						if (rx > mx ) {
							Alvos[m].ix = Alvos[m].ix * pow(-1, random()&0x1);
							Alvos[n].ix = Alvos[n].ix * pow(-1, random()&0x1);
							Alvos[m].iy = Alvos[m].iy * pow(-1, random()&0x1);
							Alvos[n].iy = Alvos[n].iy * pow(-1, random()&0x1);
							Alvos[m].iz = Alvos[m].iz * pow(-1, random()&0x1);
							Alvos[n].iz = Alvos[n].iz * pow(-1, random()&0x1);
							Alvos[m].x += Alvos[m].ix * 2;
							Alvos[m].y += Alvos[m].iy * 2;
							Alvos[m].z += Alvos[m].iz * 2;
							Alvos[n].x += Alvos[n].ix * 2;
							Alvos[n].y += Alvos[n].iy * 2;
							Alvos[n].z += Alvos[n].iz * 2;
							Alvos[m].cor[RED] +=  Alvos[m].cor[GREEN] = Alvos[m].cor[BLUE] = TCOLOR(random()&0xFF);
							Alvos[n].cor[RED] +=  Alvos[n].cor[GREEN] = Alvos[n].cor[BLUE] = TCOLOR(random()&0xFF);
							printf("Objeto [ %d ] Colidiu com [ %d ]\n",m,n); 	
						}
					}
			}
		}
		flag=0;
	}
}

int MoveExplosao(void){}

void ExplodeAlvo(int i){
	DesenhaExplosao(i);
}

void MovePersonagem(void){}

int InterceptaAlvo(void){
register int i,j,d;
int stx, sty, stz, sax,say,saz;  // Sinais das coordenadas

	for (i=0; i < MAX_TIROS_SCR; i++ ) {
		if (Tiros[i].visible == O_VISIBLE) {
			for (j=0; j< Total_Inimigos_Scr ; j++) {
				d  = (Tiros[i].x - Alvos[j].x) * (Tiros[i].x - Alvos[j].x);
				d += (Tiros[i].y - Alvos[j].y) * (Tiros[i].y - Alvos[j].y);
				d += (Tiros[i].z - Alvos[j].z) * (Tiros[i].z - Alvos[j].z);
				d = sqrt(d);
				if ( d < Alvos[j].dx ) {
					Alvos[j].visible=O_INTERCEPTED;
					Tiros[i].visible=O_DISABLE;
					Tiros[i].id = 0;  // Desmarca alvo;	
					Tiros[i].xr = Tiros[i].yr = Tiros[i].zr = 0;	// Zera as coordenadas do alvo no tiro
					Placar.valor += Alvos[j].valor;
					Placar.ix --;
					Placar.dx ++;
					ExplodeAlvo(j);
				}
			}
		}
	}
}

void MoveCamera(void) {
	
int CameraX,CameraY,CameraZ;

	CameraX =  (2*Mira.x-JanelaX );
	CameraY = -(2*Mira.y-JanelaY);
	CameraZ = Mira.z;
	
//	gluLookAt(CameraX,CameraY,CameraZ,0,0,-(WIDTH+DEPTH),0,1,0);
	gluLookAt(0,0,Mira.z,CameraX,CameraY,-(WIDTH+DEPTH),0,1,0);
//	gluLookAt(CameraX,CameraY,Mira.z,CameraX,CameraY,-(WIDTH+DEPTH),0,1,0);
}

