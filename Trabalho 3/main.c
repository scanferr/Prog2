#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "vetor.h"

//No algoritmo entregue na aula prática foi explicado que seria usada a estrutura de dados "tabelas de dispersão".
//Durante a execução do trabalho verificou-se que a estrutura de dados "vectores" era de uma mais fácil execução e, por isso, foi a usada

vetor *terra;

int mapa_pos(int x, int y)
{
    /* devolve tipo de terreno na posicao x,y */
	int j;

	j=vetor_tamanho(terra);

	for(int i=0; i<j; i++)
	{
	      if(terra->elementos[i].x == x && terra->elementos[i].y == y)
	    {
	        return terra->elementos[i].id;
	    }
	}

    return TERRA_INCOGNITA;
}

int main(int argc, char *argv[])
{
    /* 1) iniciar comunicacao com exploradores
          NOTA: primeiros parametros deverao ser argc e argv */

	int exp, expos[1000][2], type;
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	int id, i=0;
	int j;
	char jump;

	terra = vetor_novo();
	intro(argc, argv, &exp, expos);
	jump = explorator(&id, &type);

	while(jump != 'X')
	{
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

	      jump = explorator(&id, &type);
	}

	x2 = abs(x1)+abs(x2) + 1;
	y2 = abs(y1)+abs(y2) + 1;

	j=vetor_tamanho(terra);

	for(i= 0; i< j; i++)
	  {
	     terra->elementos[i].x = terra->elementos[i].x - x1;
	     terra->elementos[i].y = terra->elementos[i].y - y1;
	  }

	/* 3) imprime e verifica o mapa
	     *NOTA: funcao mapa_pos e' o primeiro das funcoes */
	tabula(mapa_pos, x2, y2);
	veritas(mapa_pos, x2, y2);

	/* 4) termina comunicacoes com os exploradores */
	relinquo();

	//LIBERTA A MEMORIA DO VETOR CRIADO
	vetor_apaga(terra);

	return 0;
}
