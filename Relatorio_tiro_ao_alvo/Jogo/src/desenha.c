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
#include "objetos.h"
#include "movimentos.h"
#include "record.h"
#include "desenha.h"

void DesenhaLuminarias(void);
void LigaLampadas(void);

void LigaLampadas(void) {
int l;
GLfloat vet[3];

	glEnable(GL_LIGHTING);
/*	for(l=0; l< MAX_LUMINARIAS_SCR; l ++) {
*/		
	if (Luminarias[0].visible == O_VISIBLE) {
			glEnable(GL_LIGHT0);
			vet[0] = Lampadas[0].x;
			vet[1] = Lampadas[0].y;
			vet[2] = Lampadas[0].z;
			glLightfv(GL_LIGHT0, GL_POSITION, vet);
			vet[0] = vet[1] =vet[2] = 1.0;
			glLightfv(GL_LIGHT0, GL_DIFFUSE, vet);
		}
	if (Luminarias[1].visible == O_VISIBLE) {
			glEnable(GL_LIGHT1);
			vet[0] = Lampadas[1].x;
			vet[1] = Lampadas[1].y;
			vet[2] = Lampadas[1].z;
			glLightfv(GL_LIGHT1, GL_POSITION, vet);
			vet[0] = vet[1] =vet[2] = 1.0;
			glLightfv(GL_LIGHT1, GL_SPECULAR, vet);
		}
	if (Luminarias[2].visible == O_VISIBLE) {
			glEnable(GL_LIGHT2);
			vet[0] = Lampadas[2].x;
			vet[1] = Lampadas[2].y;
			vet[2] = Lampadas[2].z;
			glLightfv(GL_LIGHT2, GL_POSITION, vet);
			vet[0] = vet[1] =vet[2] = 1.0;
			glLightfv(GL_LIGHT2, GL_SPECULAR, vet);
		}
	glDisable(GL_LIGHTING);
/*	}
*/			
			
}

void DesenhaLuminarias(void){
int l;

	for (l=0;l<MAX_LUMINARIAS_SCR;l++) {
		glColor3dv(TabelaCores[C_CINZA][255]);
		glBegin(GL_QUADS);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y                 ,Luminarias[l].z-Luminarias[l].dz);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z-Luminarias[l].dz);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y                 ,Luminarias[l].z+Luminarias[l].dz);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y                 ,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y                 ,Luminarias[l].z+Luminarias[l].dz);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y                 ,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z-Luminarias[l].dz);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y                 ,Luminarias[l].z-Luminarias[l].dz);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z-Luminarias[l].dz);
			glVertex3d(Luminarias[l].x-Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z+Luminarias[l].dz);
			glVertex3d(Luminarias[l].x+Luminarias[l].dx,Luminarias[l].y-Luminarias[l].dy,Luminarias[l].z-Luminarias[l].dz);
		glEnd();
	}
}


GLdouble TabelaCores[4][256][3];


void InicializaCores(void){
int c;

	for(c=0;c<256;c++) {
		TabelaCores[C_CINZA][c][C_IRED] = TabelaCores[C_CINZA][c][C_IGREEN] = TabelaCores[C_CINZA][c][C_IBLUE] = TCOLOR(c);
		TabelaCores[C_VERMELHO][c][C_IRED] = TCOLOR(c);
		TabelaCores[C_VERMELHO][c][C_IGREEN] = TabelaCores[C_VERMELHO][c][C_IBLUE] = 0.0;
		TabelaCores[C_VERDE][c][C_IGREEN] = TCOLOR(c);
		TabelaCores[C_VERDE][c][C_IRED] = TabelaCores[C_VERDE][c][C_IBLUE] = 0.0;
		TabelaCores[C_AZUL][c][C_IBLUE] = TCOLOR(c);
		TabelaCores[C_AZUL][c][C_IRED] = TabelaCores[C_AZUL][c][C_IGREEN] = 0.0;
	}
}

void DesenhaCorredor(void){

	// Comeca pela parede esquerda, chao, parede direita, teto
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		//glActiveTexture(a_index[T_PAREDE]);
		glBindTexture(GL_TEXTURE_2D,textura[T_PAREDE]);
		glBegin(GL_QUADS);		// Parede Esquerda
			glColor3dv(TabelaCores[C_VERMELHO][C_MEIO]);
			glTexCoord2d(0,0);
			glVertex3d(-JanelaX,-JanelaY,-JanelaX);
			glTexCoord2d(4,0);
			glVertex3d(-JanelaX,-JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(4,4);
			glVertex3d(-JanelaX, JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(0,4);
			glVertex3d(-JanelaX, JanelaY,-JanelaX);
			glNormal3d(1,0,0);
		glEnd();
		//glActiveTexture(a_index[T_CHAO]);
		glBindTexture(GL_TEXTURE_2D,textura[T_CHAO]);
		glBegin(GL_QUADS);		// Chao
			glColor3d(TCOLOR(50),TCOLOR(50),TCOLOR(50));
			glTexCoord2d(0,0);
			glVertex3d(-JanelaX,-JanelaY,-JanelaX);
			glTexCoord2d(2,0);
			glVertex3d( JanelaX,-JanelaY,-JanelaX);
			glTexCoord2d(2,2);
			glVertex3d( JanelaX,-JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(0,2);
			glVertex3d(-JanelaX,-JanelaY,-(WIDTH+DEPTH));
			glNormal3d(0,1,0);
		glEnd();
		glColor3d(0.0,0.0,1.0);
		//glActiveTexture(a_index[T_PAREDE]);
		glBindTexture(GL_TEXTURE_2D,textura[T_PAREDE]);
		glBegin(GL_QUADS);		// Parede Direita
			glTexCoord2d(0,0);
			glVertex3d( JanelaX,-JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(4,0);
			glVertex3d( JanelaX,-JanelaY,-JanelaX);
			glTexCoord2d(4,4);
			glVertex3d( JanelaX, JanelaY,-JanelaX);
			glTexCoord2d(0,4);
			glVertex3d( JanelaX, JanelaY,-(WIDTH+DEPTH));
			glNormal3d(-1,0,0);
		glEnd();
		glColor3d(TCOLOR(200),TCOLOR(200),TCOLOR(200));
		//glActiveTexture(a_index[T_TETO]);
		glBindTexture(GL_TEXTURE_2D,textura[T_TETO]);
		glBegin(GL_QUADS);		// Teto
			glTexCoord2d(0,0);
			glVertex3d( JanelaX, JanelaY,-JanelaX);
			glTexCoord2d(1,0);
			glVertex3d(-JanelaX, JanelaY,-JanelaX);
			glTexCoord2d(1,2);
			glVertex3d(-JanelaX, JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(0,2);
			glVertex3d( JanelaX, JanelaY,-(WIDTH+DEPTH));
			glNormal3d(0,-1,0);
		glEnd();
		glColor3d(TCOLOR(255),TCOLOR(0),TCOLOR(0));
		//glActiveTexture(a_index[T_PAREDE]);
		glBindTexture(GL_TEXTURE_2D,textura[T_PAREDE]);
		glBegin(GL_QUADS);		// Teto
			glTexCoord2d(0,0);
			glVertex3d(-JanelaX, -JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(4,0);
			glVertex3d( JanelaX, -JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(4,4);
			glVertex3d( JanelaX,  JanelaY,-(WIDTH+DEPTH));
			glTexCoord2d(0,4);
			glVertex3d(-JanelaX,  JanelaY,-(WIDTH+DEPTH));
			glNormal3d(0,-1,0);
		glEnd();
		glColor3d(TCOLOR(255),TCOLOR(0),TCOLOR(255));
		//glActiveTexture(a_index[T_PAREDE]);
		glBindTexture(GL_TEXTURE_2D,textura[T_PAREDE]);
		glBegin(GL_QUADS);		// Teto
			glTexCoord2d(0,0);
			glVertex3d(-JanelaX, -JanelaY,-(WIDTH-1));
			glTexCoord2d(4,0);
			glVertex3d( JanelaX, -JanelaY,-(WIDTH-1));
			glTexCoord2d(4,4);
			glVertex3d( JanelaX,  JanelaY,-(WIDTH-1));
			glTexCoord2d(0,4);
			glVertex3d(-JanelaX,  JanelaY,-(WIDTH-1));
			glNormal3d(0,-1,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void DesenhaEixos(int z){
int c;

	glPushMatrix();
		glColor3d(255,255,0);
		glBegin(GL_LINES);
			glVertex3d(-JanelaX,0,z);
			glVertex3d(JanelaX,0,z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3d(0,-JanelaX,z);
			glVertex3d(0,JanelaX,z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3d(0,0,-JanelaX);
			glVertex3d(0,0,JanelaX);
		glEnd();
	glPopMatrix();
}

void DesenhaEsfera(int raio, double r, double g, double b, int w){

	glColor3d(r,g,b);
	if ( w )
		glutWireSphere((double)(raio),32,32);
	else
		glutSolidSphere((double)(raio),32,32);
}

void DesenhaQuadrado(int xi, int yi, int xf, int yf, int z, GLdouble r, GLdouble g, GLdouble b){

	glColor3d(r,g,b);
	glBegin(GL_QUADS);
		glVertex3d(xi,yi,z);
		glVertex3d(xf,yi,z);
		glVertex3d(xf,yf,z);
		glVertex3d(xi,yf,z);
	glEnd();
}

void DesenhaMira(void) {
int   alfa,px,py,pz,cx,cy;
char str[80];
register int	c,offset;
int x[4],y[4];
int i;

	x[0]=y[0]= 60;
	x[1]=y[1]= 10;
	x[2]=y[2]=-60;
	x[3]=y[3]=-10;

	glPushMatrix();
		pz = Mira.z;
		cx =  (2*Mira.x-JanelaX );
		cy = -(2*Mira.y-HEIGHT);
		glTranslated(cx,cy,0);
		glColor3dv(Mira.cor);
		for (c=0; c<MIRA_CIRCULOS; c ++){
			glBegin(GL_LINE_LOOP);
//				glVertexPointer(3,GL_INT,MIRA_PONTOS,&Mira.pontos[c][0]);
				for(i=0;i < MIRA_PONTOS;i++)
				glVertex3i(Mira.pontos[c][i][MIRA_X],Mira.pontos[c][i][MIRA_Y],pz);
			glEnd();
		}
		for(c=0;c<4; c++) {
			glRotated(90*c,0,0,1);
			glBegin(GL_LINES);
				glVertex3d(Mira.raios[0], 0, pz);
				glVertex3d(Mira.raios[1], 0, pz);
			glEnd();
		}
	glPopMatrix();
	sprintf(str,"X[ %04d ] Y[ %04d ] z [ %04d ]",Mira.x,Mira.y,Mira.z);
	glColor3d(0.0,1.0,0.0);
	glRasterPos3d(-JanelaX+50, -HEIGHT+80,pz);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
}

void DesenhaAlvos(void){
register int i;
		
	for (i=0;i<Total_Inimigos_Scr;i++)
		if (Alvos[i].visible == O_VISIBLE) {
			glPushMatrix();	
				glTranslated(Alvos[i].x,Alvos[i].y,Alvos[i].z);
				glColor3dv(Alvos[i].cor);
				glutSolidSphere((double)(Alvos[i].dx),16,16);
			glPopMatrix();
		}
}

void DesenhaTiro(void){
int i;
	
	for(i=0;i< MAX_TIROS_SCR; i++)
		if ( Tiros[i].visible == O_VISIBLE ) {
			glPushMatrix();
				glTranslated(Tiros[i].x,Tiros[i].y,Tiros[i].z);
				glColor3d(1.0,1.0,1.0);
				glutSolidSphere(Tiros[i].dx,8,8);
			glPopMatrix();
			if (Tiros[i].z <= -(JanelaX + DEPTH)) {
				Tiros[i].z = -JanelaX;
				Tiros[i].visible = O_DISABLE; 
			}
		}
}

void DesenhaPlacar(void) {
char str[8];
char tiros[20];
int  t;

	Placar.z = Mira.z;
	sprintf(str,"%08lu",Placar.valor);
	glColor3dv(Placar.cor);
	glRasterPos3d(Placar.x,Placar.y,Placar.z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
	sprintf(str,"V: %05d", Placar.ix);
	glRasterPos3d(Placar.x,Placar.y-80,Placar.z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
	sprintf(str,"A: %05d", Placar.dx);
	glRasterPos3d(Placar.x,Placar.y-160,Placar.z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
	for(t=0;t<MAX_TIROS_SCR;t++){
		if (Tiros[t].visible == O_VISIBLE) {
			sprintf(tiros,"[ %d ] [%d,%d,%d]",t,Tiros[t].x,Tiros[t].y,Tiros[t].z);
			glColor3dv(Placar.cor);
			glRasterPos3d(Placar.x-100,Placar.y-190-(30*t),Placar.z);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, tiros);
		}
	}
}

void DesenhaExplosao(int i) {
register int j;
register int k;
register int l;

	j = Alvos[i].visible & (~O_EXPLODE_0);
	if ( (j & O_EXPLODE_1)) {
		Alvos[i].visible = O_EXPLODE_0 | O_EXPLODE_1;
	}
	do Explosao[i][0].valor = random()&MAX_EXPLOSAO_SCR; while (Explosao[i][0].valor < 10);
	switch(j) {
		case O_EXPLODE_1:
							l = O_EXPLODE_0 | O_EXPLODE_2;
							break;
		case O_EXPLODE_2:
							l = O_EXPLODE_0 | O_EXPLODE_3;
							break;
		case O_EXPLODE_3:
							l = O_EXPLODE_0 | O_EXPLODE_4;
							break;
		case O_EXPLODE_4:
							l = O_DISABLE;
							break;
	}
	Alvos[i].visible = l;
	
	for (j=0;j<i;j++){
		glPushMatrix();
		glTranslated(j*j*pow(-1,j),j*j*pow(-1,(3*j)),j*j*pow(-1,(j+1)));
		glTranslated(Alvos[i].x,Alvos[i].y,Alvos[i].z);
		glColor3d(TCOLOR((random()&0xFF)),TCOLOR((random()&0xFF)),TCOLOR((random()&0xFF)));
		glutSolidSphere(5,8,8);
		glPopMatrix();
	}
		
}

int ExplodeAlvos(void){
register int i;
	for (i=0;i<Total_Inimigos_Scr; i++) {
		if ( Alvos[i].visible & O_EXPLODE_0 )
			DesenhaExplosao(i);
	}
}
//
// Funcao Principal para desenhar os Frames
//
void DesenhaTimer(int v) {
static int flag=0;

	if ( !flag ) {
		flag ^= 1;
		glPushMatrix();
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			if (FlagMira)
				MoveCamera();
			MovePersonagem();
			MoveTiros();
			InterceptaAlvo();
			ExplodeAlvos();
			MoveAlvos();
			LigaLampadas();
			DesenhaLuminarias();
			DesenhaCorredor();
//			DesenhaEixos(Mira.z);
			if (!Saindo) {
				DesenhaAlvos();
				DesenhaMira();
				DesenhaTiro();
				DesenhaPlacar();
			}
			if (DrawRecords)
				DesenhaRecords();
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
		glutTimerFunc(TimerTick,DesenhaTimer,1);
		flag=0;
	}
}

void DesenhaRecords(void) {
char str[8];
char *str2 = "Fim de Jogo";
char *str3 = "Sair do Jogo <S/N>?";
int i;
	
	glColor3d(0,0,0);
	glBegin(GL_QUADS);
		glVertex3d(-300,400,Mira.z);
		glVertex3d(-300,-400,Mira.z);
		glVertex3d(300,-400,Mira.z);
		glVertex3d(300,400,Mira.z);
	glEnd();

	glColor3d(0,1,0);
	glRasterPos3d(-200, 350 ,Mira.z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, str2);
	for (i=0; i < MAX_RECORD; i++) {
		sprintf(str,"%08lu",records[i]);
		glColor3d(0,1,0);
		glRasterPos3d(-200, 280-50*i,Mira.z);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
	}
	glColor3d(0,1,0);
	glRasterPos3d(-200, -300 ,Mira.z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, str3);

}

/*
void DesenhaCorredor(void){

	// Comeca pela parede esquerda, chao, parede direita, teto
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		//glActiveTexture(a_index[T_PAREDE]);
		glBindTexture(GL_TEXTURE_2D,textura[T_PAREDE]);
		glBegin(GL_QUADS);		// Parede Esquerda
			glColor3dv(TabelaCores[C_VERMELHO][C_MEIO]);
			glTexCoord2d(0,0);
			glVertex3d(-JanelaX,-HEIGHT,-JanelaX);
			glTexCoord2d(4,0);
			glVertex3d(-JanelaX,-HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(4,4);
			glVertex3d(-JanelaX, HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(0,4);
			glVertex3d(-JanelaX, HEIGHT,-JanelaX);
			glNormal3d(1,0,0);
		glEnd();
		//glActiveTexture(a_index[T_CHAO]);
		glBindTexture(GL_TEXTURE_2D,textura[T_CHAO]);
		glBegin(GL_QUADS);		// Chao
			glColor3d(TCOLOR(50),TCOLOR(50),TCOLOR(50));
			glTexCoord2d(0,0);
			glVertex3d(-JanelaX,-HEIGHT,-JanelaX);
			glTexCoord2d(2,0);
			glVertex3d( JanelaX,-HEIGHT,-JanelaX);
			glTexCoord2d(2,2);
			glVertex3d( JanelaX,-HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(0,2);
			glVertex3d(-JanelaX,-HEIGHT,-(WIDTH+DEPTH));
			glNormal3d(0,1,0);
		glEnd();
		glColor3d(0.0,0.0,1.0);
		//glActiveTexture(a_index[T_PAREDE]);
		glBindTexture(GL_TEXTURE_2D,textura[T_PAREDE]);
		glBegin(GL_QUADS);		// Parede Direita
			glTexCoord2d(0,0);
			glVertex3d( JanelaX,-HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(4,0);
			glVertex3d( JanelaX,-HEIGHT,-JanelaX);
			glTexCoord2d(4,4);
			glVertex3d( JanelaX, HEIGHT,-JanelaX);
			glTexCoord2d(0,4);
			glVertex3d( JanelaX, HEIGHT,-(WIDTH+DEPTH));
			glNormal3d(-1,0,0);
		glEnd();
		glColor3d(TCOLOR(200),TCOLOR(200),TCOLOR(200));
		//glActiveTexture(a_index[T_TETO]);
		glBindTexture(GL_TEXTURE_2D,textura[T_TETO]);
		glBegin(GL_QUADS);		// Teto
			glTexCoord2d(0,0);
			glVertex3d( JanelaX, HEIGHT,-JanelaX);
			glTexCoord2d(1,0);
			glVertex3d(-JanelaX, HEIGHT,-JanelaX);
			glTexCoord2d(1,2);
			glVertex3d(-JanelaX, HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(0,2);
			glVertex3d( JanelaX, HEIGHT,-(WIDTH+DEPTH));
			glNormal3d(0,-1,0);
		glEnd();
		glColor3d(TCOLOR(255),TCOLOR(0),TCOLOR(0));
		//glActiveTexture(a_index[T_PAREDE]);
		glBindTexture(GL_TEXTURE_2D,textura[T_PAREDE]);
		glBegin(GL_QUADS);		// Teto
			glTexCoord2d(0,0);
			glVertex3d(-JanelaX, -HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(4,0);
			glVertex3d( JanelaX, -HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(4,4);
			glVertex3d( JanelaX,  HEIGHT,-(WIDTH+DEPTH));
			glTexCoord2d(0,4);
			glVertex3d(-JanelaX,  HEIGHT,-(WIDTH+DEPTH));
			glNormal3d(0,-1,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
*/
