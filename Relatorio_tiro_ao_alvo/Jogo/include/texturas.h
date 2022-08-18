#ifndef _TEXTURAS_H_
#define _TEXTURAS_H_

#define		MAX_TEXT	5

#define		T_CHAO		0
#define		T_TETO		1
#define		T_PAREDE	2
#define		T_TIRO		3
#define		T_FUNDO		4
#define		T_MAX		5



extern GLuint	textura[MAX_TEXT];
extern int		a_index[MAX_TEXT];

// Carrega texturas
int			CarregaTexturas(void);//Ok
// Retorna quantos arquivos de textura forma lidos
int			getTexturas(void);//OK
// Retorna quantas texturas podemos manipular
int 			getMaxTexturas(void);//OK
// Retorna o nome da textura criada (via indece text)
GLuint		getTextura(int text);//OK
// Retorna o tamanho (largura do arquivo de textura)
int			getDimension(int text);//Ok
// Seta nomes de arquivos à serem lidos via CarregaTextura
void			setNomeArquivos(char *nome,int dim, int i); //OK
// Retorna os nomes dos arquivos lidos sem erros
char			**getArquivosLidos(void);//Ok
// Retorna o nome do arquivo que não foi aberto
char			*getErroArquivo(void); // Só implementada a chamada função nula
// Retorna quantos arquivos foram lidos
int			getTotalArquivosLidos(void);//OK
// Finaliza Modulo
void			endTexturas(void);//Ok
void setParametrosTexturas(int wrap);//Ok
void InicializaTexturas(void);


#endif
