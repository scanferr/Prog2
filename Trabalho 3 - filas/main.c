#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "fila.h"

//No algoritmo entregue na aula prática foi explicado que seria usada a estrutura de dados "tabelas de dispersão".
//Durante a execução do trabalho verificou-se que a estrutura de dados "vectores" eram de uma mais fácil execução e, por isso, foi a usada


fila *terra;

int mapa_pos(int x, int y)
{
    /* devolve tipo de terreno na posicao x,y */
	int j, i=0;

	j=fila_tamanho(terra);

	while (i<j)
		{
			if(terra->cabeca->x == x && terra->cabeca->y == y)
			{
				return terra->cabeca->id;
			}
		 	fila_pop(terra);
			i++;
		}

    return TERRA_INCOGNITA;
}

int main(int argc, char *argv[])
{
    /* 1) iniciar comunicacao com exploradores
          NOTA: primeiros parametros deverao ser argc e argv */

	int exp, position[1000][2], type;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int id, i=0, j;
	char move;

	terra = fila_nova();

	intro(argc, argv, &exp, position);

	/* 2) comunicar com os exploradores e receber informacoes,
	              enquanto existem movimentacoes a realizar */

	move = explorator(&id, &type);

	while(move != 'X')
	{
	      if(move == 'N')
	      {
	         position[id][1]--;
	         fila_push(terra, position[id][0], position[id][1], type);

	          if(position[id][1] < y1)
	          {
	            y1 = position[id][1];
	          }
	          if(position[id][1] > y2)
	          {
	            y2 = position[id][1];
	          }
	        }

	      if(move == 'S')
	      {
	         position[id][1]++;
	         fila_push(terra, position[id][0], position[id][1], type);

	         if(position[id][1] < y1)
	         {
	           y1 = position[id][1];
	         }
	         if(position[id][1] > y2)
	         {
	           y2 = position[id][1];
	         }
	       }

	      if(move == 'E')
	      {
	         position[id][0]++;
	         fila_push(terra, position[id][0], position[id][1], type);

	         if(position[id][0] < x1)
	         {
	           x1 = position[id][0];
	         }
	         if(position[id][0] > x2)
	         {
	           x2 = position[id][0];
	         }
	       }

	      if(move == 'O')
	      {
	         position[id][0]--;
	         fila_push(terra, position[id][0], position[id][1], type);

	         if(position[id][0] < x1)
	         {
	           x1 = position[id][0];
	         }
	         if(position[id][0] > x2)
	         {
	           x2 = position[id][0];
	         }
	       }

	      move = explorator(&id, &type);
	}

	x2 = abs(x1)+abs(x2) + 1;
	y2 = abs(y1)+abs(y2) + 1;

	j=fila_tamanho(terra);

	for(i= 0; i< j; i++)
		  {
			terra->cabeca->x = terra->cabeca->x -x1;
			terra->cabeca->y = terra->cabeca->y -y1;
			fila_pop(terra);
		  }

	/* 3) imprime e verifica o mapa
	     *NOTA: funcao mapa_pos e' o primeiro das funcoes */
	tabula(mapa_pos, x2, y2);
	veritas(mapa_pos, x2, y2);

	/* 4) termina comunicacoes com os exploradores */
	relinquo();

	//LIBERTA A MEMORIA DO VETOR CRIADO
	fila_apaga(terra);

	return 0;
}
