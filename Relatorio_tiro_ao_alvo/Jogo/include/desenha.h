#ifndef __DESENHA_H__
#define __DESENHA_H__

#define		C_CINZA			0			// Tons de cinza ( 256 tons)
#define		C_VERMELHO		1			// Tons de vermelho ( 256 Tons)
#define		C_VERDE			2			// Tons de verde ( 256 Tons)
#define		C_AZUL			3			// Tons de azul ( 256 Tons)
#define		C_IRED			0			// Indice do vetor para a cor vermelha
#define		C_IGREEN		1			// Indice do vetor para a cor verde
#define		C_IBLUE			2			// Indice do vetor para a cor azul
#define		C_ZERO			0			// Indices para o Tom   0,0%
#define		C_UMOITAVO		32			// Indices para o Tom  12,5%
#define		C_UMQUARTO		64			// Indices para o Tom  25,0%
#define		C_TRESOITAVOS	96			// Indices para o Tom  37,5%
#define		C_MEIO			128			// Indices para o Tom  50,0%
#define		C_CINCOOITAVOS	160			// Indices para o Tom  65,5%
#define		C_TRESQUARTOS	192			// Indices para o Tom  75,0%
#define		C_SETEOITAVOS	224			// Indices para o Tom  87,5%
#define		C_UMTERCO		85			// Indices para o Tom  33,0%
#define		C_DOISTERRCOS	170			// Indices para o Tom  66,0%
#define		C_FULL			256			// Indices para o Tom 100,0%


void InicializaCores(void);
void DesenhaTiro(void);
void DesenhaMira(void);
void DesenhaAlvos(void);
void DesenhaTimer(int i);
void DesenhaPlacar(void);
void DesenhaRecords(void);
void DesenhaCorredor(void);
void DesenhaQuadrado(int xi, int yi, int xf, int yf, int z, double r, double g, double b);
void DesenhaEsfera(int raio, double r, double g, double b, int w);

extern GLdouble TabelaCores[4][256][3];

#endif
