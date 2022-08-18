#ifndef	__JOGO_H__
#define __JOGO_H__

#ifndef PI
#define PI		3.1415
#endif

#define		ED_OK			0
#define		ED_FAIL			1
#define		ED_CREATEBLE	2
#define		ED_TEMPORARY	4
#define		ED_RDONLY		8

#define		WIDTH		800		// Largura Minima da Janela do Jogo
#define		HEIGHT		450		// Altura Minima da Janela do Jogo
#define		DEPTH		2000	// Profundidade do Corredor
#define		METER2PX	100		// Converter unidade 1m == 100px

#define		TEXTURAS	0
#define		TEMPORARIO	1
#define		ESTRATEGIAS 2
#define		LABIRINTOS  3

#ifndef 	MAX_STR
#define		MAX_STR		80
#endif

#define		TCOLOR( c )		(GLdouble)((double)((c)) / 255.0 )

struct	_EDir	{
			char nome[MAX_STR];
			unsigned long int permissao;
			unsigned long int flags;
		};
		
typedef struct _EDir	EDir;

extern EDir EstruturaDiretorios[4];
extern int	TimerTick;
extern int	JanelaX,JanelaY;

// Funcoes de inicializacao
void InicializaLocalLibs(void);
void InicializaVariaveis(void);
void InicializaCarregamento(void);
void InicializaOpenGL(int argc, char *argv[]);
//Funcoes de carga de dados
void CriaAmbienteOpenGL(void);
void CarregaLabirinto(void);
void Redimensiona(int x, int y);
void FimJogo(int i);
int strpos(char *s, char c);

int main(int argc, char *argv[]);

#endif
