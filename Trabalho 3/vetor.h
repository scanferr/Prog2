/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2017/18           */
/*****************************************************************/

//BIBLIOTECA VETOR USADA NAS AULAS, LIGEIRAMENTE MODIFICADA PARA ACOMODAR O TRABALHO 3
//STRUCT ALTERADA PARA CONTER OS VALORES PRETENDIDOS
//REMOCAO DE FUNCOES DESNECESSARIAS PARA ESTE TRABALHO
//ALTERACAO DA FUNCAO VETOR_INSERE DE ACORDO COM O PRETENDIDO

#ifndef VETOR_H

/**
* registo para armazenar cada elemento (coordenada X, Y e tipo de terreno)
*/

typedef struct
{
  int x;
  int y;
  int id;

} v_elemento;

/**
* este registo contem um vetor de elementos, um contador do tamanho e outro para a capacidade
*/
typedef struct
{
  /** numero de elementos do vetor */
  int tamanho;

  /** capacidade do vetor */
  int capacidade;

  /** array de elementos armazenados */
  v_elemento* elementos;

} vetor;

/**
*  cria um novo vetor com tamanho 0 e capacidade 0
*  retorno: apontador para o vetor criado
*  nota: se vetor nao foi criado retorna NULL
*/
vetor* vetor_novo();

/**
*  elimina um vetor, libertando toda a memoria ocupada
*  parametro: vec apontador para vetor
*  nota: se vec = NULL retorna sem fazer nada
*/
void vetor_apaga(vetor *vec);

/**
*  indica o o numero de elementos do vetor
*  parametro: vec apontador para vetor
*  retorno: -1 se ocorrer algum erro ou numero de elementos do vetor
*/
int vetor_tamanho(vetor *vec);

/**
*  insere um elemento na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: coordenada X
*  parametro: coordenada Y
*  parametro: tipo de terreno
*  parametro: pos indice do elemento onde se pretende inserir a struct, se pos=tamanho ou pos=-1 insere no fim do vetor
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida), o valor de pos se bem sucedido ou 0 se posicao for repetida 
*  nota: se a capacidade nao for suficiente para guardar novo elemento, devera ser aumentada para 2x em relacao a capacidade anterior; inicialmente aumenta para capacidade 1
*/
int vetor_insere(vetor *vec, int x, int y, int type, int pos);

#define VETOR_H
#endif
