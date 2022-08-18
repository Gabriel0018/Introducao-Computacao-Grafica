/*
**
** Programa para Testar Texturas
**	simulando o sistema solar
**
** 2013-04-28
** $Id$ 
** $Author$
** $Date$
** 
*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include <string.h>

#include "jogo.h"
#include "desenha.h"
#include "objetos.h"
#include "texturas.h"
#include "movimentos.h"



GLuint	textura[MAX_TEXT];
char 	*t_file_names[MAX_TEXT];
char	*t_files_names_readed[MAX_TEXT];
int   	t_file_numbers;
int		t_files_numbers_readed;
int		t_dim[MAX_TEXT];
int		t_numbers;
int		t_index[MAX_TEXT];
int		a_index[MAX_TEXT];

int t_index[]={T_CHAO,T_TETO,T_PAREDE,T_TIRO,T_FUNDO};
char *nomes[]= { 
					"../texturas/chao.raw",			// T_CHAO  Defindas em texturas.h 
					"../texturas/teto.raw",			// T_TETO
					"../texturas/parede.raw", 		// T_PAREDE
					"../texturas/tiro.raw",			// T_TIRO
					"../texturas/fundo.raw"			// T_FUNDO

				};

char *dir[]=	{"texturas/","labirinto/","estrategias/"};
int	 tam_text[]={128,128,128,128,128};
int	 len_nomes=3; // T_MAX 


void loadtextura(char *fn, int tw, int th, GLuint t, int wrap);
void loadimage_raw(unsigned char *data,char *fn, int tw, int th);



void InicializaTexturas(void) {


	t_numbers = 3;
	a_index[T_CHAO]		=GL_TEXTURE0;
	a_index[T_TETO]		=GL_TEXTURE1;
	a_index[T_PAREDE]	=GL_TEXTURE2;
	a_index[T_TIRO]		=GL_TEXTURE3;
	a_index[T_FUNDO]	=GL_TEXTURE4;
	
}
void setNomeArquivos(char *nome,int dim, int i){
int slen;

	slen = strlen(nome);
	t_dim[i]=dim;
		if ((t_file_names[i]=(char *)(malloc(sizeof(char)*slen)))==(char *)(NULL)) {
			printf("TEXTURA: ALLOC_ERROR: [ %d - %s ]\n",i,nome);
			exit(-1);
		}
		strcpy(t_file_names[i],nome);
		if ((t_files_names_readed[i]=(char *)(malloc(sizeof(char)*slen)))==(char *)(NULL)) {
			printf("TEXTURA: ALLOC_ERROR: [ %d - %s ]\n",i,nome);
			exit(-1);
		}
		strcpy(t_files_names_readed[i],nome);
		t_file_numbers++;
}

int getMaxTexturas(void){
	return(MAX_TEXT);
}

GLuint getTextura(int text){

	// Verifica se o indice passado esta dentro da faixa
	if (text < 0 || text > t_numbers)
		// Caso  esteja fora da faixa, retorna erro (-1)
		return ((GLuint)(-1));
	else
		// Caso contrario retorna a textura solicitada
		return(textura[text]);
}

char **getArquivosLidos(void){
	return(t_files_names_readed);
}

int	getTotalArquivosLidos(void){
	return(t_files_numbers_readed);
}

int getDimension(int text){

	if (text < 0 || text > t_numbers)
		// Caso  esteja fora da faixa, retorna erro (-1)
		return ((GLuint)(-1));
	else
		// Caso contrario retorna a textura solicitada
		return(t_dim[text]);
}

void endTexturas(void){
int i;

	for(i=0;i<t_file_numbers;i++){
		free(t_file_names[i]);
	}
	for(i=0;i<getTotalArquivosLidos();i++){
		free(t_files_names_readed[i]);
	}
}

int	getTexturas(void){
	return(t_files_numbers_readed);
}

int	CarregaTexturas(void){
int i,dim;

	setNomeArquivos(nomes[T_CHAO]  ,tam_text[T_CHAO]  ,T_CHAO  );	// Cria os nomes de arquivos a serem carregados
	setNomeArquivos(nomes[T_TETO]  ,tam_text[T_TETO]  ,T_TETO  );	// Cria os nomes de arquivos a serem carregados
	setNomeArquivos(nomes[T_PAREDE],tam_text[T_PAREDE],T_PAREDE);	// Cria os nomes de arquivos a serem carregados
	t_files_numbers_readed=0;
//	glEnable(GL_TEXTURE_2D);
	for(i=0;i<t_file_numbers;i++) {
		dim = getDimension(t_index[i]);
		glGenTextures(1,&textura[t_index[i]]);
		loadtextura(t_file_names[t_index[i]], dim, dim,textura[t_index[i]],1);
		t_files_numbers_readed++;
	}
//	glDisable(GL_TEXTURE_2D);
}

void loadimage_raw(unsigned char *data,char *fn, int tw, int th){
FILE *fp;
long int tam,r;

	tam=tw * th * 3;
	if ((fp = fopen( fn, "rb" )) == (FILE *)(NULL)){
		printf("FILE_LOAD: OPEN_ERROR na carga do arquivo [ %s ]\n",fn);
		exit(-1);
	}
	r=fread( data, tam, 1, fp );
	if ( ferror(fp) || feof(fp) ) {
		printf("FILE_LOAD: READ_ERROR: leitura do arquivo [ %s ]\n",fn);
		exit(-1);
	}
	fclose( fp );
}

void loadtextura(char *fn, int tw, int th, GLuint t, int wrap){
unsigned char *img;

	// Alloca buffer para carga da imagem
	if((img=(unsigned char *)(malloc(tw*th*3)))==(unsigned char *)(NULL)){// RGB
		printf("LOAD_TEXT: ALLOC_ERROR: Falha de alocacao de textura");
		exit(-1);
	}
	loadimage_raw(img,fn, tw, th);
	// Associa a textura com a imagem carregada do arquivo
/*	if (glIsTexture(t) != GL_TRUE) {
		printf("Textura ERRADA! [%d]\n",t);
		exit(-1);
	}
*/
	glBindTexture(GL_TEXTURE_2D,t);
	setParametrosTexturas(1);
//	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tw,th,0,GL_RGB, GL_UNSIGNED_BYTE, img);
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, tw, th,GL_RGB, GL_UNSIGNED_BYTE, img );
	free(img);
	
}

char *getErroArquivo(void){
	return((char *)(NULL));
}

void setParametrosTexturas(int wrap){

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  	// when texture area is small, bilinear filter the closest mipmap
  	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrap ? GL_REPEAT : GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,wrap ? GL_REPEAT : GL_CLAMP );
}
