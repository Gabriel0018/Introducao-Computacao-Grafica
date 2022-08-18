#ifndef __OBJETO_H__
#define __OBJETO_H__

#define	MAX_TIROS_SCR	3
#define	MAX_INIMIGOS_SCR	50
#define MIN_INIMIGOS_SCR	7
#define MAX_LUMINARIAS_SCR	4
#define MAX_EXPLOSAO_SCR	0x0F
#define	MAX_TARGET_VALUE	(unsigned long int)(23000)

// Objeto parede 
#define		ESQUERDA	0
#define		DIREITA		1
#define		TETO		2
#define		CHAO		3
#define		FUNDO		4

// Objetos
#define		PAREDE		0
#define		PISO		1
#define		MIRA		2
#define		INIMIGO		3
#define		TIRO		4

// Index para o vetor de cores dos objetos
#define		RED			0
#define		GREEN		1
#define		BLUE		2

//  Valores para a variavel Visible
#define		O_DISABLE		0x00
#define		O_VISIBLE		0x01
#define		O_HIDE			0x02
#define		O_EXPLODE_0		0x04
#define		O_EXPLODE_1		0x08
#define		O_EXPLODE_2 	0x10
#define		O_EXPLODE_3		0x20
#define		O_EXPLODE_4		0x40
#define		O_INTERCEPTED	0x80

#define		MIRA_CIRCULOS		 2
#define		MIRA_COORDENADAS	 3
#define		MIRA_X			 	 0
#define		MIRA_Y				 1
#define		MIRA_Z				 2
#define		MIRA_PONTOS			36

struct _mira {
	
		int x;
		int y;
		int z;
		int xr;			// Coordenadas X,Y,Z rebatidas no plano da mira
		int yr;
		int zr;
		int raios[MIRA_CIRCULOS];
		int pontos[MIRA_CIRCULOS][MIRA_PONTOS][MIRA_COORDENADAS];
		GLdouble	cor[3];	// Cores (R,G,B)
		int	visible;	// Obseto visivel, Desabilitado ou Explodindo
		unsigned int id;	// Id do objeto, Não implementado
		unsigned int class;	// Classe do Objeto, Não implementado
		void (*DrawObject)(int x, int y, int z, struct _mira *obj);   // Funcao para desenha o objeto, NI
		void (*MoveObject)(int x, int y, int z, struct _mira *obj);	// Funcao Para mover o objeto, NI
		void (*InterceptObject)(int x, int y, int z, struct _mira *obj);	// Funcao para verificar se objeto
};
		
struct _objeto {

		int	x;			// Coordenadas X,Y,Z
		int y;			
		int	z;
		int xr;			// Coordenadas X,Y,Z rebatidas no plano da mira
		int yr;
		int zr;
		int	dx;			// Distancias do ponto central (X,Y<Z) na direcao X
		int	dy;
		int	dz;
		int	ix;			// Incremento na direcao X (velocidade)
		int iy;
		int iz;
		double ta,tt;	// Angulos para a trajetória do tiro
		GLdouble	cor[3];	// Cores (R,G,B)
		int	visible;	// Obseto visivel, Desabilitado ou Explodindo
		unsigned int id;	// Id do objeto, Não implementado
		unsigned int class;	// Classe do Objeto, Não implementado
		unsigned long int valor;	// Valor do Objeto
		void (*DrawObject)(int x, int y, int z, struct _objeto *obj);   // Funcao para desenha o objeto, NI
		void (*MoveObject)(int x, int y, int z, struct _objeto *obj);	// Funcao Para mover o objeto, NI
		void (*InterceptObject)(int x, int y, int z, struct _objeto *obj);	// Funcao para verificar se objeto																		// Foi interceptado, NI
};
						
typedef	struct _objeto Objeto;
typedef struct _mira ObjMira;

extern ObjMira	Mira;
extern Objeto	Camera;
extern Objeto	Corredor;
extern Objeto	Tiros[MAX_TIROS_SCR];
extern Objeto	Alvos[MAX_INIMIGOS_SCR];
extern Objeto 	Placar;
extern Objeto	Luminarias[MAX_LUMINARIAS_SCR];
extern Objeto	Lampadas[MAX_LUMINARIAS_SCR];
extern Objeto	Explosao[MAX_INIMIGOS_SCR][MAX_EXPLOSAO_SCR];
extern int		Total_Inimigos_Scr;
extern int		FontesLuminosas[GL_MAX_LIGHTS];

extern int     FlagMira;   // 0-> Camera Fixa, mira move 1 -> Camera Move junto com a mira
extern int     FlagTiro;   // 0 -> Tajetoria paralela 1-> trajetoria tangenciada
extern int     Saindo;     // 0 -> Jogo funcionando 1-> terminando jogo (pausa)
extern int     Pausa;      // 0 -> Jogo funcionando 1-> Jogo Pausado





void _InicializaObjeto(Objeto *obj,int x, int y, int z, int tipo, void (*func)(int x, int y, int z, struct _objeto *obj));

void InicializaObjetos(void);
void InicializaAlvos(void);
void InicializaAlvo(int i);
void InicializaTiros(void);
void InicializaPlacar(void);
void InicializaMira(void);
void InicializaCorredores(void);
void InicializaLuminarias(void);

void InicializaObjetosVar(void);
void IncrementaAlvos(int i);
void DecrementaAlvos(int i);

#endif
