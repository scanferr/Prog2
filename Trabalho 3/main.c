#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "vetor.h"

//No algoritmo entregue na aula prática foi explicado que seria usada a estrutura de dados "tabelas de dispersão".
//Durante a execução do trabalho verificou-se que a estrutura de dados "vectores" era de uma mais fácil execução e, por isso, foi a usada

//Definiçao de uma variavel do tipo vetor para uso no programa (mapa_pos e main)
vetor *terra;

int mapa_pos(int x, int y)
{
    /* devolve tipo de terreno na posicao x,y */
	int i=0, j;

	j=vetor_tamanho(terra);

//Percorre todo o vetor e compara os valores das coordenadas X e Y. Se forem iguais devolve o tipo de terreno na respetiva coordenada.
	while (i<j)
	{
		if(terra->elementos[i].x == x && terra->elementos[i].y == y)
		{
			return terra->elementos[i].id;
		}
		i++;
	}
    return TERRA_INCOGNITA;
}

int main(int argc, char *argv[])
{
  //DECLARAÇÃO DE VARIAVEIS

	//Guardar o explorador, criaçao de vetor bidimensional com tamanho 1000 (MAX_EXPLORADORES) e guardar tipo de terreno
	int exp, expos[1000][2], type;
	//Variaveis para guardar as coordenadas (1 = min; 2 = max)
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	//Variaveis auxiliares para os ciclos
	int i=0, j;
	//Explorador numero "id"
	int id;
	//Variaveis para o tamanho do mapa
	int lat, longi;
	//Variavel para guardar o char da direção
	char jump;

	//Criação de novo vetor
	terra = vetor_novo();

	 /* 1) iniciar comunicacao com exploradores
          NOTA: primeiros parametros deverao ser argc e argv */
	intro(argc, argv, &exp, expos);

	//Retorno da direção do explorador
	jump = explorator(&id, &type);

	//Enquanto nao atingir o criterio de paragem (X), ira percorrer todos os movimentos dos exploradores
	while(jump != 'X')
	{
		//Se o explorador retorna Este, actualiza valores no vetor e as respetivas posições
				if(jump == 'E')
	      {
	         expos[id][0]++;
	         vetor_insere(terra, expos[id][0], expos[id][1], type, -1);

	         if(expos[id][0] < x1)
	         {
	           x1 = expos[id][0];
	         }
	         if(expos[id][0] > x2)
	         {
	           x2 = expos[id][0];
	         }
	       }
		//Se o explorador retorna Oeste, actualiza valores no vetor e as respetivas posições
	      if(jump == 'O')
	      {
	         expos[id][0]--;
	         vetor_insere(terra, expos[id][0], expos[id][1], type, -1);

	         if(expos[id][0] < x1)
	         {
	           x1 = expos[id][0];
	         }
	         if(expos[id][0] > x2)
	         {
	           x2 = expos[id][0];
	         }
	       }
		//Se o explorador retorna Norte, actualiza valores no vetor e as respetivas posições
	      if(jump == 'N')
	      {
	         expos[id][1]--;
	         vetor_insere(terra, expos[id][0], expos[id][1], type, -1);

	          if(expos[id][1] < y1)
	          {
	            y1 = expos[id][1];
	          }
	          if(expos[id][1] > y2)
	          {
	            y2 = expos[id][1];
	          }
	        }
	//Se o explorador retorna Sul, actualiza valores no vetor e as respetivas posições
	      if(jump == 'S')
	      {
	         expos[id][1]++;
	         vetor_insere(terra, expos[id][0], expos[id][1], type, -1);

	         if(expos[id][1] < y1)
	         {
	           y1 = expos[id][1];
	         }
	         if(expos[id][1] > y2)
	         {
	           y2 = expos[id][1];
	         }
	       }
	      jump = explorator(&id, &type);
	}

	//E necessário guardar numa variável as dimensões do mapa em X e em Y. Somar valores absolutos das coordenadas + 1
	lat = abs(x1)+abs(x2) + 1;
	longi = abs(y1)+abs(y2) + 1;

	//Atualiza as posicoes dos exploradores
	j=vetor_tamanho(terra);

	while(i<j)
	  {
	     terra->elementos[i].x = terra->elementos[i].x - x1;
	     terra->elementos[i].y = terra->elementos[i].y - y1;
			 i++;
	  }

	/* 3) imprime e verifica o mapa
	     *NOTA: funcao mapa_pos e' o primeiro das funcoes */
	tabula(mapa_pos, lat, longi);
	veritas(mapa_pos, lat, longi);

	/* 4) termina comunicacoes com os exploradores */
	relinquo();

	//Liberta a memória do vetor criado
	vetor_apaga(terra);
	
	return 0;
}
