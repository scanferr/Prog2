/*
 ============================================================================
 Name        : 1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"
#include <time.h>
#include "lista.h"

void lst_count()
{
	FILE *f = fopen("englishwords.txt", "r");

	if (f==NULL)
	{
		return;
	}

	long int inicio, fim;

	double tempo;

	inicio = clock();

	/* tarefa a verificar */

	lista *l = lista_nova();

	char buffer[30];

	//printf("%d\n", l->tamanho);

	while (1)
	{
		if(fgets(buffer, 29, f))
			lista_insere(l, buffer, NULL);
		else
			break;
	}

	fim = clock();
	tempo = (double)(fim - inicio)/CLOCKS_PER_SEC;

	//printf("%d\n", l->tamanho);
	printf("Tempo em segundos para listas - %lf\n", tempo);
}

void hash_count()
{
	FILE *f = fopen("englishwords.txt", "r");

	if (f==NULL)
	{
		return;
	}

	long int inicio, fim;

	double tempo;

	inicio = clock();

	/* tarefa a verificar */

	tabela_dispersao *h = tabela_nova(9999999999999999999999, hash_djbm);

	char buffer[30];

	//printf("%d\n", l->tamanho);

	//int i=0;
	while (1)
	{
		if(fgets(buffer, 29, f))
			tabela_adiciona(h, buffer, buffer);
		else
			break;
		//i++;
	}
	//mostraTabela(h);
	fim = clock();
	tempo = (double)(fim - inicio)/CLOCKS_PER_SEC;

	//printf("%d\n", l->tamanho);
	printf("Tempo em segundos para hash - %lf\n", tempo);

}

 int main()

 {
	lst_count();
	hash_count();
}
