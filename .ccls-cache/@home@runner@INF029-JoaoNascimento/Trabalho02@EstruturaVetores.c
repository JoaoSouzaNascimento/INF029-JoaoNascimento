#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct vetor{
  int *auxvetor;
  int qtd;
  int tamanho;
}vtrprincipal;

vtrprincipal vetorPrincipal[TAM];

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
  if (posicao >= 0 && posicao < TAM)
  {
      return 1;
  }

  return 0;
}

void troca(int vet[], int i, int j)
{
  int aux = vet[i];
  vet[i] = vet[j];
  vet[j] = aux;
}

int particiona(int vet[], int inicio, int fim)
{
  int pivo, pivo_indice, i;

  pivo = vet[fim]; 
  pivo_indice = inicio;

  for(i = inicio; i < fim; i++)
  {

    if(vet[i] <= pivo)
    {

      troca(vet, i, pivo_indice);

      pivo_indice++;
    }
  }

  troca(vet, pivo_indice, fim);

  return pivo_indice;
}


void quick_sort(int vet[], int inicio, int fim)
{
  if(inicio < fim)
  {
    int pivo_indice = particiona(vet, inicio, fim);

    quick_sort(vet, inicio, pivo_indice - 1);
    quick_sort(vet, pivo_indice + 1, fim);
  }
}

int BuscaEnderecoPorSelecao(int posica, int num){

  for(int i = 0; i < vetorPrincipal[posica].qtd; i++){
    if(vetorPrincipal[posica].auxvetor[i] == num)
      return i;
  }

  return -1;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
  int *auxarray;    
  int retorno = 0;
  posicao--;
  
  // se posição é um valor válido {entre 1 e 10}
  if (!ehPosicaoValida(posicao)) {
    retorno = POSICAO_INVALIDA;
  }
  else {
    // a posicao pode já existir estrutura auxiliar
    if (vetorPrincipal[posicao].auxvetor != NULL) {
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    }
      else if (tamanho < 1) {
        // o tamanho nao pode ser menor que 1
        retorno = TAMANHO_INVALIDO;
      }
        else if ((auxarray = (int *)malloc(sizeof(int) * tamanho))==NULL) {
          // o tamanho ser muito grande
          retorno = SEM_ESPACO_DE_MEMORIA;
        }
    else {
        // deu tudo certo, crie
        vetorPrincipal[posicao].auxvetor = auxarray;
        vetorPrincipal[posicao].tamanho = tamanho;
        retorno = SUCESSO;
    }
  }
  return retorno;
}
/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
    posicao--;
  
    if (!ehPosicaoValida(posicao))
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        if (vetorPrincipal[posicao].auxvetor!=NULL)
        {
          if (vetorPrincipal[posicao].qtd<vetorPrincipal[posicao].tamanho)
            {
                //insere
                vetorPrincipal[posicao].auxvetor[vetorPrincipal[posicao].qtd] = valor;
                vetorPrincipal[posicao].qtd++;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
  int retorno = SUCESSO;
  posicao--;

  if(ehPosicaoValida(posicao)) 
  {
    if(vetorPrincipal[posicao].auxvetor!=NULL)
    {
      if(vetorPrincipal[posicao].qtd!=0)
      {
        vetorPrincipal[posicao].qtd--;
      } 
      else
      {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
      }
    }
    else
    {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }
  else
  {
    retorno = POSICAO_INVALIDA;
  }
  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
  int retorno = SUCESSO;
  int num;
  int aux;
  posicao--;
  
  if(ehPosicaoValida(posicao))
  {
    if(vetorPrincipal[posicao].auxvetor!=NULL)
    {
      if(vetorPrincipal[posicao].qtd!=0){
        if((num = BuscaEnderecoPorSelecao(posicao, valor))!=-1)
        {
          for(int i = num; i < vetorPrincipal[posicao].qtd-1; i++){
            vetorPrincipal[posicao].auxvetor[i] = vetorPrincipal[posicao].auxvetor[i+1];
          }
          vetorPrincipal[posicao].qtd--;
        }
        else
        {
          retorno = NUMERO_INEXISTENTE;
        }
      }
      else
      {
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
      }
    }
    else
    {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }
  else
  {
    retorno = POSICAO_INVALIDA;
  }
  
  return retorno;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
  posicao--;
  int i;
  
  if(!ehPosicaoValida(posicao))
  {
    return POSICAO_INVALIDA;
  }  
  else if(vetorPrincipal[posicao].auxvetor==NULL)
  {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  for(i = 0; i<vetorPrincipal[posicao].qtd;i++)
  {
    vetorAux[i] = vetorPrincipal[posicao].auxvetor[i];
  }

  return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
  posicao--;
  if(!ehPosicaoValida(posicao))
  {
    return POSICAO_INVALIDA;
  }
  else if(vetorPrincipal[posicao].auxvetor == NULL)
  {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  for(int i = 0; i<vetorPrincipal[posicao].qtd;i++)
  {
    vetorAux[i] = vetorPrincipal[posicao].auxvetor[i];
  }

  quick_sort(vetorAux, 0, vetorPrincipal[posicao].qtd-1);
  
  return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
  int i=0;
  int j=0;
  
  ///for(i=0 ; i<TAM && vetorPrincipal[i].auxvetor == NULL;i++)
    //{}

  while(i<TAM)
  {
    if(vetorPrincipal[i].qtd == 0)
      j+=1;
    i++;
  }
  
  if(j==10)
  {
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  }

  int k=0;
  
  for( i = 0; i<TAM;i++)
  {
    for(int j=0; j < vetorPrincipal[i].qtd;j++)
    {
      vetorAux[k] = vetorPrincipal[i].auxvetor[j];
      k++;
    }
  }

  return SUCESSO;
}



/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
  int i=0;
  int tamanho;
  
  for(i=0 ; i<TAM && vetorPrincipal[i].qtd == 0;i++);
  if(i==TAM)
  {
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  }

  int k=0;
  for(i = 0; i<TAM;i++)
  {
    for(int j=0; j < vetorPrincipal[i].qtd;j++)
    {
      vetorAux[k] = vetorPrincipal[i].auxvetor[j];
      k++;
    }
  }

  quick_sort(vetorAux, 0, k-1);
  
  return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
  posicao--;
  
  if(novoTamanho + vetorPrincipal[posicao].tamanho < 1)
    return NOVO_TAMANHO_INVALIDO;
  else if(!ehPosicaoValida(posicao))
    return POSICAO_INVALIDA;
  else if (vetorPrincipal[posicao].auxvetor == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  if((vetorPrincipal[posicao].auxvetor = (int *) realloc(vetorPrincipal[posicao].auxvetor, (vetorPrincipal[posicao].tamanho + novoTamanho) * sizeof(int))) == NULL)
    return SEM_ESPACO_DE_MEMORIA;
  
  vetorPrincipal[posicao].tamanho += novoTamanho;
  
  if(vetorPrincipal[posicao].tamanho<vetorPrincipal[posicao].qtd)
    vetorPrincipal[posicao].qtd = vetorPrincipal[posicao].tamanho;
    
  return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
  posicao--;
  if(!ehPosicaoValida(posicao))
  {
    return POSICAO_INVALIDA;
  } 
  else if (vetorPrincipal[posicao].auxvetor == NULL)
  {
    return SEM_ESTRUTURA_AUXILIAR;
  }
  else if (vetorPrincipal[posicao].qtd==0)
  {  
    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  return vetorPrincipal[posicao].qtd;
}

void pushno(No** head, int conteudo) {
  No* novono;
  if((novono = (No*) malloc(sizeof(No)))==NULL)
  {
    printf("Erro na alocação de memória");
    exit(1);
  }
  
  novono->conteudo  = conteudo;
  novono->prox = (*head)->prox;
  (*head)->prox = novono;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
  No *head;
  if((head = (No*) malloc(sizeof(No)))==NULL)
  {
    printf("Erro ao alocar memoria");
    exit(1);
  }
  head->prox = NULL;
  
  int i,j,numexist=0;
  
  for( i = TAM-1; i>=0;i--)
  {
    for(j=vetorPrincipal[i].qtd-1; j >= 0;j--)
    {
      pushno(&head, vetorPrincipal[i].auxvetor[j]);
      numexist=1;
    }
  }
  printf("\n");
  if(!numexist)
  {
    return NULL;
  }
  
  return head;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
  int i=0;
  
  while (inicio->prox != NULL) {
    inicio = inicio->prox;
    vetorAux[i] = inicio->conteudo;
    i++;
  }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
  No *atual = *inicio;
  No *proximo;
  
  while (atual != NULL) {
      proximo = atual->prox;
      free(atual);
      atual = proximo;
  }
  *inicio = atual;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
  int i;
  
  for(i = 0; i < TAM; i++) {
    vetorPrincipal[i].auxvetor = NULL;
    vetorPrincipal[i].qtd = 0;
    vetorPrincipal[i].tamanho = 0;
  }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
}

void dobrar(int *x) 
{
  *x = *x * 2;
}