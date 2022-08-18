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

#define	FVER	"Versao 1.0 Beta"
#define FID		1
#define FIDMIN  000000


EDir EstruturaDiretorios[4];
int	 TimerTick;
char MeuNome[30];

int 	JanelaX, JanelaY;
int		AutoRedimensionamento;


int main(int argc, char *argv[]){

	strcpy(MeuNome,argv[0]);
	InicializaVariaveis();
	InicializaOpenGL(argc,argv);	// Inicializa a Biblioteca OpenGL
	InicializaCarregamento();
	CriaAmbienteOpenGL();			// Inicializa o AMbiente (Janela)
	glutMainLoop();					// Loop Principal do OpenGL
	return (0);						// FIM
}

void InicializaLocalLibs(void){
//	initmydebug(MeuNome);
//	pushstackmydebug("IniciaLocalLibs");	
}

void InicializaVariaveis(void) {

	strcpy(EstruturaDiretorios[TEXTURAS].nome,"Texturas");
	strcpy(EstruturaDiretorios[LABIRINTOS].nome,"Labirintos");
	strcpy(EstruturaDiretorios[TEMPORARIO].nome,"/tmp");
	strcpy(EstruturaDiretorios[ESTRATEGIAS].nome,"Estrategias");
	TimerTick = 10;
	JanelaX = WIDTH;
	JanelaY = HEIGHT;
	AutoRedimensionamento=0;
	FlagTiro=0;
	FlagMira=0;
}

void InicializaOpenGL(int argc, char *argv[]){
GLuint	var;
int	x,y,w,h;
char t[MAX_STR];

#ifdef __HAVE_LIB_X11__		// Se a biblioteca do X11 estiver instalada, use-a
_display_info	di;

	display_info(&di);
	w = di.width;
	h = di.height;
#else
	w = 1024;				// Resolucao minima para jogar 1024x768
	h = 768;
#endif

//	if ( getmydebug() == MYDEBUG_ON )
//		strcpy(t,getappnamemydebug());
//	else
		strcpy(t,"Demo Versao 1.0");
		
	glutInit(&argc, argv);	 					// inicia a biblioteca GLUT
	var = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH;	//	sistema de cor rgb e
												// buffer duplo (evita flicks)
	glutInitDisplayMode ( var );
	x = (w - WIDTH)/2;
	y = (h - HEIGHT)/2;
	glutInitWindowPosition(x,y);				// Centraliza janela

	glutInitWindowSize(WIDTH,HEIGHT);			// Define o Tamanho da Janela
	glutCreateWindow (t);						// Cria e rotula a Janela

	// Habilita as variaveis do Open Gl para tratar profundidade
	// e texturas 2D
	glEnable(GL_DEPTH_TEST);	
	//Incializa os CallBacks
	glutTimerFunc(TimerTick,DesenhaTimer,1);	// Funcao para desenhar a tela de tempos em tempos (100ms)
	glutMotionFunc(MoveMira);				// Funcao para gerenciar o movimento do mouse com o botao pressionado
	glutPassiveMotionFunc(MoveMira);		// FUncao para gerenciar o movimento do mouse com o botao livre 
	glutMouseFunc(BotoesMouse);				// Funcao para gerenciar os botoes do mouse
	glutKeyboardFunc(Teclado);				// Funcao para gerenciar o teclado
	glutReshapeFunc(Redimensiona);
	glutDisplayFunc(DesenhaTimer);	
}

void CriaAmbienteOpenGL(void){

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glFrustum(-(JanelaX),(JanelaX),-JanelaY,JanelaY,(WIDTH),(WIDTH+DEPTH));
//	glFrustum(-(WIDTH,(WIDTH),-(HEIGHT),(HEIGHT),WIDTH,(WIDTH+DEPTH));
	glPushMatrix();
}

void CarregaLabirinto(void){
}

void InicializaCarregamento(void){

	InicializaLocalLibs();		// Inicializa bibliotecas locais (erro, debug, ...)
	InicializaVariaveis();		// Inicializa Variaveis Globais
	InicializaObjetos();		// Inicializa os objetos do jogo
		InicializaCores();
		InicializaTexturas();
		InicializaLuminarias();
	CarregaTexturas();			// Carrega Texturas
	CarregaLabirinto();			// Carrega e inicializa o labirinto
}

void FimJogo(int i){
	
	if (i == 0 ){
		DrawRecords = 1;
		Saindo = 1;
		InsereRecord(Placar.valor);
		DesenhaRecords();
	} 
	else {
		DrawRecords = 0;
		Saindo = 0;
		WriteRecords();
		endTexturas();
		exit(0);
	}
}

void Redimensiona(int x, int y){
	
	AutoRedimensionamento = 1;
	JanelaX = x;
	JanelaY = y;
	glPopMatrix();
	CriaAmbienteOpenGL();
	glutPostRedisplay();
}

int strpos(char *s, char c) {
int i,l;

	l = strlen(s);
	for (i=0; i< l; i++ ) {
		if ( c == *(s+i) )
			break;
	}
	if ( i >= l )
		i = -1;
	return i;
}

