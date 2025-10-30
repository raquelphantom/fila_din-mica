#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

#define  true  1      /* apoio para uso nas funções */ 
#define  false 0      /* apoio para uso nas funções */ 

typedef  int   bool;  /* apoio para uso nas funções */ 

/* Definindo o REGISTRO */
typedef struct   
{         
   int		  chave; 
   /* campos do registro */        
   char       NOME[100+1];
   char       DATANASC [10+1]; 
} 
REGISTRO;

/* Definindo o ELEMENTO */
typedef struct aux
{  
   REGISTRO 	reg;
   struct 	    aux * PROX;  /* prox APONTA para o endereço de memória  */
}                            /* de um elemento com essa mesma estrutura */
ELEMENTO;

/* Definindo a fila */
typedef ELEMENTO  *PONT;

typedef struct 
{
   PONT inicio;    /* inicio APONTA para o endereço do primeiro ELEMENTO da fila */
   PONT fim;       /* fim APONTA para o endereço do último ELEMENTO da fila */
} 
fila;

/* Protótipos de funções */
void 	inicializarfila 	(fila * f);
int 	tamanho 			(fila * f);
void 	exibirfila 			(fila * f);
bool 	estaVazia			(fila * f);
bool 	inserirNaFila 		(fila * f);
bool    insereElemFila      (fila * f, REGISTRO  reg);
bool 	excluirDaFila		(fila * f, REGISTRO *reg);
void 	reinicializarFila	(fila * f);

REGISTRO oqueInserir (void);
void     msgErro	 (void);
void cadastraDefault (fila * f); 

/* 
Para inicializar uma fila já criada pelo usuário,  precisamos acertar o valor do campo inicio e do campo fim.
Já que o inicio conterá o endereço do elemento que será o primeiro da fila e a fila está vazia, iniciaremos esse campo com valor NULL. 
Já que o fim conterá o endereço do elemento que será o último da fila e a fila está vazia, iniciaremos esse campo com o valor NULL.
*/
void inicializarfila (fila * f)
{
  f->inicio = NULL;
  f->fim    = NULL;
}

/* Já que não temos um campo com o número de elementos na fila, precisaremos percorrer todos os elementos para contar quantos são.
*/
int tamanho (fila * f) 
{  
	PONT    end = f->inicio;  
	int     tam = 0;
	while (end != NULL) 
	{  
  		tam++;
  		end = end->PROX;
	}
	return tam;
}

/* Para exibir os elementos da estrutura precisaremos  percorrer os elementos 
   (iniciando pelo elemento do início da fila) e, por exemplo, imprimir suas chaves. */
void exibirfila (fila* f) 
{  
   PONT end = f->inicio;  
   system ("cls"); system ("mode 110, 12");
   printf("fila:\n");  
   while (end != NULL) 
   {
	printf("[%i-%s-%s]", end->reg.chave, end->reg.NOME, end->reg.DATANASC);  
	end = end->PROX;
   }
}

/* Se início está  armazenando o endereço NULL, significa que a fila está vazia. */
bool estaVazia(fila* f) 
{
   if (f->inicio == NULL) 
      return true;  
   return false;
}

bool inserirNaFila (fila * f)
{
   REGISTRO	elem;
   PONT novo = (PONT) malloc(sizeof(ELEMENTO));  
   if ( novo == NULL )
   {  
      printf ("\nErro ao alocar novo registro.");
      getch();
      return false;
   }
   elem  = oqueInserir();
   novo->reg = elem;
   novo->PROX = NULL;
   if (f->inicio==NULL) 
      f->inicio = novo;  
   else 
      f->fim->PROX = novo;
   f->fim = novo;
   system ("cls"); system ("mode 110, 12");
   printf ("\nChave [%i-%s-%s] inserida com sucesso.", 
   elem.chave, elem.NOME, elem.DATANASC );
   return true;
}

/* 
O usuário solicita a exclusão do elemento do início da fila. 
Se a fila não estiver vazia, 
  iremos copiar esse elemento para um local indicado pelo usuário;
  acertar o valor do campo inicio;
  eventualmente acertar o valor do campo fim.
*/
bool excluirDaFila(fila * f, REGISTRO *reg) 
{  
   if (f->inicio==NULL) 
   	  return false;
   *reg = f->inicio->reg;  
   PONT apagar = f->inicio;
   f->inicio = f->inicio->PROX;  
   free(apagar);
   if (f->inicio == NULL) 
      f->fim = NULL;  
   return true;
}

/* 
Para reinicializar a fila, precisamos excluirtodos os  seus elementos 
e colocar NULL nos campos inicio e fim
*/
void reinicializarFila(fila * f) 
{  
   PONT end = f->inicio;
   PONT apagar;
   while (end != NULL) 
   {  
      apagar = end;  
	  end = end->PROX;  
	  free(apagar);
   }
   f->inicio = NULL;  
   f->fim = NULL;
}

REGISTRO oqueInserir (void)
{	REGISTRO r;
    system ("cls"); system ("mode 110, 12");
	printf ("\nTIPOCHAVE          : "); fflush (stdin); scanf("%i", &r.chave);
	printf ("\nNOME               : "); fflush (stdin); gets(r.NOME);
	printf ("\nDATA DE NASCIMENTO : "); fflush (stdin); gets(r.DATANASC);
	return r;
}

void     msgErro	 (void)
{
	system ("cls");
	printf ("\nOpção inválida!");
	getch();
}

bool    insereElemFila      (fila * f, REGISTRO reg)
{
   PONT novo = (PONT) malloc(sizeof(ELEMENTO));  
   novo->reg = reg;
   novo->PROX = NULL;
   if (f->inicio==NULL) 
      f->inicio = novo;  
   else 
      f->fim->PROX = novo;
   f->fim = novo;
   system ("cls"); system ("mode 110, 12");
   printf ("\nChave [%i-%s-%s] inserida com sucesso.", 
   reg.chave, reg.NOME, reg.DATANASC );
   return true;
}

void cadastraDefault  (fila * f) 
{
   	REGISTRO r[5] = {
   		{1, "Caio", 	"01/12/1991"},
   		{2, "Ticio",  	"11/10/1981"},
   		{3, "Melvio",   "14/07/2001"},
   		{4, "Julio",  	"20/03/2010"},
   		{5, "Sempronia","12/03/2011"}
	};
	int i;
	reinicializarFila(f);
	for (i=0 ; i<5; i++)
	   if (insereElemFila(f, r[i]) == false) 
	   {
	   	printf ("\nErro no cadastro default.");
        getch();	   	
	   }
	exibirfila(f);
}

/* CORPO DO PROGRAMA */
int main ()
{
  fila  	* F;
  REGISTRO 	r;
  char      opc;
	
  setlocale (LC_ALL, "");
  
  F = (fila *) malloc (sizeof (fila)); // aloca uma fila
  if (F == NULL)
  {
    printf ("malloc devolveu NULL!\n");
    getch();
    exit (EXIT_FAILURE);
  }        

  inicializarfila (F);
	
  while (opc != 's')
  {
  	system ("cls"); system ("mode 36,12");
  	printf ("\n=============================");
  	printf ("\n    TESTE COM FILA           ");
  	printf ("\n=============================");
  	printf ("\n d = cadastro default        ");
  	printf ("\n i = incluir      		    ");
  	printf ("\n e = excluir      		    ");
  	printf ("\n m = mostrar fila   		    ");
  	printf ("\n t = mostrar tamanho da fila ");
  	printf ("\n r = reinicializar fila      ");
  	printf ("\n s = sair         	  	    ");
  	printf ("\n=============================");
  	printf ("\n Escolha: "); fflush (stdin); opc = getche(); opc = tolower(opc);
  	system ("cls");
   	switch (opc) 
	{
      	case 'i' : 	inserirNaFila(F);			break;
      	case 'e' : 	
		  system ("cls"); system ("mode 110, 12");
		  if (excluirDaFila(F, &r)==true)
      		printf ("\nRegistro excluído: [%i-%s-%s]", 
			r.chave, r.NOME, r.DATANASC);
      	  else
      	  	printf ("\nNao foi possivel excluir o registro.");
		break;
   		case 'm' : exibirfila(F);				break;
   		case 't' : if ( estaVazia(F) == false )
	                    printf ("\n\nTamanho da fila = %d", tamanho(F));
	               else printf ("\n\nFILA VAZIA!");
	    break;
   		case 'r' : reinicializarFila(F);		
   				   printf ("\n\nFILA REINICIALIZADA!");
		break;
   		case 'd' : cadastraDefault(F);			break;
     	case 's' : exit(0); 					break;
		default  : msgErro();					break;
    }
	getch();
  }	
  return (0);
}
