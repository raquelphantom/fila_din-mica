/* --------------------------------------- Bibliotecas -------------------------------------- */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>


/* ------------------------------- Constantes pré-definidas --------------------------------- */
#define INVALIDO -1
#define false    -1  
#define true      1

/* --------------------- Tipos de dados definidos pelo programador -------------------------- */
int TAMANHO_VETOR =10;
/* definição do tipo booleano */
typedef int 	bool;

/* definição do tipo chave utilizado:  a chave da nossa implementação será um número inteiro */
typedef int TIPOCHAVE;//ele é o id da carga

/* definição do registro*/
typedef struct   
{         
   TIPOCHAVE  chave; 
   /* campos do registro */   
   char       DESCRITIVO[100+1];
   char 	  UNIDADE[10+1];
   int 		  QTD;
   int 		  PESO; 
} 
REGISTRO;

typedef struct ELEMENTO
{  
	REGISTRO 	reg;
	struct 		ELEMENTO	* PROX; // prox APONTA para o endereço de memória  
}                           // de um elemento com essa mesma estrutura 
ELEMENTO;

typedef ELEMENTO * PONT;  

typedef struct 
{
	PONT topo; /* topo APONTA para o endereço do ELEMENTO do TOPO da PILHA */
} 
PILHA;

REGISTRO carga[10] = {
        {1, "Caixas de eletrônicos", "unidade", 10, 120},
        {2, "Paletes de papel", "palete", 2, 300},
        {3, "Sacos de cimento", "saco", 20, 500},
        {4, "Bobinas de aço", "unidade", 1, 800},
        {5, "Caixas de roupas", "unidade", 15, 100},
        {6, "Encomendas leves", "pacote", 25, 50},
        {7, "Ferramentas manuais", "caixa", 5, 150},
        {8, "Equipamentos de cozinha", "unidade", 8, 200},
        {9, "Produtos de limpeza", "caixa", 12, 90},
        {10, "Materiais escolares", "caixa", 18, 70}
    };

/* --------------------------- Protótipos das funções --------------------------------------- */
void 		inicializarPilha (PILHA* p);
int 		tamanho (PILHA* p);
bool 		estaVazia(PILHA* p); 
void 		exibirPilha (PILHA* p); 
void 		reinicializarPilha (PILHA* p);
bool 		inserirElemPilha(PILHA* p, REGISTRO reg); 
void 		excluiDaPilha (PILHA* p); 
bool 		excluirElemPilha(PILHA* p, REGISTRO* reg); 
void 		mostrar(void);
void 		bubble_sort(void);

void mostrar(void){
	int i;
	for(i=0; i<TAMANHO_VETOR; i++)
		printf("%i",carga[i].PESO);
}

void bubble_sort(void) 
{ 
	mostrar();
  int i, j; int aux;
  for ( j = 0; j<TAMANHO_VETOR-1; j++) 
  {
    for ( i = 0; i<TAMANHO_VETOR-1-j; i++) 
    {
      if ( carga[i].PESO < carga[i+1].PESO)//esse cara nessa posição é maior que a do lado?
      {
         aux 	   = carga[i].PESO;//guarda valor pra não sobrescrever dados
	carga[i] .PESO	   = carga[i+1].PESO;//troca de lugar
	carga[i+1].PESO  = aux;//troca de lugar pt2
      }
    }
   }
   mostrar();
}
/*
void addToPilha(PILHA* p, REGISTRO* reg){
	int i;
	for(i=0; i<TAMANHO_VETOR; i++)
	{
		reg->chave = carga[i].chave;
		reg->DESCRITIVO = carga[i].DESCRITIVO;
		reg->PESO = carga[i].PESO;
		reg->QTD = carga[i].QTD;
		reg->UNIDADE = carga[i].UNIDADE;
		bool inserirElemPilha(PILHA* p, REGISTRO* reg);
	}
}
*/
void inicializarPilha (PILHA* p)
{
  p->topo = NULL;
}

int tamanho (PILHA* p) 
{  
   PONT end = p->topo;  
   int tam = 0;
   while (end != NULL) 
   {  
      tam++;
      end = end->PROX;
   }  
   return tam;
}
bool estaVazia(PILHA* p) 
{
   if (p->topo == NULL) 
      return true;  
   return false;
}

void insereNaPilha (PILHA* p)
{	
	int i;
	for(i=0; i<TAMANHO_VETOR; i++){
	REGISTRO	elem;
	elem  = carga[i];
	if ( inserirElemPilha(p, elem) == true )
	   printf ("\nChave [%i] inserida com sucesso.", elem.chave );
	else
	   printf ("\nChave [%i] NÃO inserida!", elem.chave );
	}
}

bool inserirElemPilha(PILHA* p, REGISTRO reg) 
{  
   PONT novo  = (PONT) malloc(sizeof(ELEMENTO)); 
   if (novo==NULL)
   {
      printf ("\nErro ao alocar memória para novo elemento.");
      printf ("\nNão foi possível inserir na pilha!");
      getch();
      return false;
   } 
   novo->reg  = reg;
   novo->PROX = p->topo;  
   p->topo    = novo;  
   return true;
}

void exibirPilha (PILHA* p) 
{  
   PONT end = p->topo;  
   system ("cls");
   printf("Pilha: \n[");  
   while (end != NULL) 
   {
		printf("\n%i - %s - %s - %i - %i", end->reg.chave, end->reg.DESCRITIVO, end->reg.UNIDADE, end->reg.QTD, end->reg.PESO );  
		end = end->PROX;
   }
   printf("]");
}

bool excluirElemPilha(PILHA* p, REGISTRO* reg) 
{  
   if ( p->topo == NULL) 
      return false;
   *reg        = p->topo->reg;  
   PONT apagar = p->topo;
   p->topo     = apagar->PROX; 
   free(apagar);
   return true;
}

void reinicializarPilha (PILHA* p) 
{ 
   REGISTRO regExcluido;
   bool     flag;
   do
   {
   	 flag = excluirElemPilha(p, &regExcluido); 
   }
   while (  flag != false );
}

void excluiDaPilha (PILHA* p)
{	REGISTRO regExcluido;
 	if ( excluirElemPilha(p, &regExcluido) == true )
	   printf ("\nRegistro: [%i][%s][%s][%i][%i] excluído com sucesso.", regExcluido.chave, regExcluido.DESCRITIVO,regExcluido.UNIDADE,regExcluido.QTD,regExcluido.PESO);
	else
	   printf ("\nNão foi possivel excluir o registro.");
	
}

/* ---------------------------------- CORPO DO PROGRAMA ------------------------------------ */
int main (void)
{
   PILHA pil; 
   
   char opc;
   setlocale(LC_ALL, "");
   bubble_sort();
   getch();
   do
   {    system ("color e0");
   		system ("cls");
   		printf ("\n       TESTE COM PILHA  DINÂMICA    ");
   		printf ("\n------------------------------------");
   		printf ("\n 1. Inicializar Pilha               ");
   		printf ("\n 2. Exibir tamanho da Pilha         ");
   		printf ("\n 3. Exibir Pilha                    ");
   		printf ("\n 4. Verificar se a pilha está vazia ");
   		printf ("\n 5. Excluir elemento da Pilha (pop) ");
   		printf ("\n 6. Reinicializa Pilha              ");
   		printf ("\n 7. adcionar vetor a pilha          ");
   		printf ("\n------------------------------------");
   		printf ("\n    Escolha: "); fflush (stdin); opc = getche();
   		
		switch (opc)
   	    {
   	    	case '1': inicializarPilha(&pil); 								break;
   	    	case '2': printf("\n\nTamanho da Pilha = %i", tamanho(&pil) ); 	break;								
			case '3': exibirPilha (&pil);									break;			
   	    	case '4': if ( estaVazia (&pil) == true ) 
			               printf ("\nPilha vazia");	
					  else printf ("\nPilha NÃO vazia");		            break;
   	    	case '5': excluiDaPilha (&pil);									break;
   	    	case '6': reinicializarPilha (&pil);							break;
   	    	case '7': insereNaPilha (&pil);									break;
		}

		printf ("\n\nNovo teste? [n/N = não]"); fflush (stdin); opc = getche();
   }
   while ( opc != 'n' && opc != 'N');
   return 0;
}
