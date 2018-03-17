#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
float comprimento_medio(lista *lst)
{
	// A COMPLEXIDADE É O(n), SÓ TEM UM CICLO

	int size;
	int i=0, j;
	float avg, numLetters;
	l_elemento *word;

	size = lista_tamanho(lst);

	if(lst== NULL || size==0)
		return 0;

	for(i=0;i<size;i++)
	{
		word=lista_elemento(lst,i);
		j=strlen(word->str);
		numLetters += j;
	}
	//printf("letras %d\n", numLetters);
	//printf("size %d\n", size);

	avg = (numLetters/size);

	return avg;
}

/*** problema 1.2 ***/
lista* filtra_nomes(lista *lst, char *existe)
{
	int i, size;
	lista *aux = lista_nova();
	l_elemento *word;

	if(lst == NULL)
		return NULL;

	size=lista_tamanho(lst);

	for(i=0;i<size;i++)
	{
		word=lista_elemento(lst,i);

		if(strstr(word->str,existe)!=NULL)
			lista_insere(aux,word->str,NULL);
			//lista_remove(lst,word); PROBLEMAS A REMOVER. NÃO SE ENTENDE O PORQUÊ. FAVOR VERIFICAR.
	}
	return aux;
}

/*** problema 1.3 ***/
const char* mais_palavras(vetor *vec)
{
	if(vec == NULL || vec->tamanho == 0)
	return NULL;


}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

vetor* lerParaVetor(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	vetor* v;
	
	if (ficheiro == NULL)
		return NULL;

	v = vetor_novo();

	while(!feof(ficheiro)) 
	{	
		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr) 
			*nlptr = '\0';
		
		vetor_insere(v,buffer,v->tamanho);
	}

	return v;
}

lista* lerParaLista(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	lista* l;
	
	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();
	
	while(!feof(ficheiro)) 
	{	
		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr) 
			*nlptr = '\0';
		
		lista_insere(l,buffer,NULL);
	}

	return l;
}

int main()
{
	FILE *f;
    vetor *v;
    lista *l, *resultado;
    l_elemento *e;
    const char *nome;
    int i;
    double comp;
    
	/* testes */
	f = fopen("freguesias.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l = lerParaLista(f);
		
	/* testa comprimento_medio */
	comp = comprimento_medio(l);
	if(comp)
		printf("\nComprimento medio das palavras: %.1f\n", comp);
	else
	   	printf("\ncomprimento_medio retornou 0\n");

	/* testa filtra_nomes */
    resultado = filtra_nomes(l, "Mamede");
    
	if(resultado)
	{
            printf("\nNomes filtrados (total de %d):\n", lista_tamanho(resultado));
            for (e = resultado->inicio; e != NULL; e = e->proximo)
                printf("%s\n", e->str);

            if(lista_tamanho(l) != 4230)
            	printf("Nem todos os nomes foram removidos do vetor (tamanho: %d; esperado: 4218)\n", lista_tamanho(l));
    }
	else
		printf("\nfiltra_nomes retornou NULL\n");

	/* testa mais_palavras */
	rewind(f);
	v = lerParaVetor(f);    
	nome = mais_palavras(v);
	if(nome)
	  	printf("\nNome com mais palavras: %s\n\n", nome);
	else
	   	printf("\nmais_palavras retornou NULL\n\n");
	
	vetor_apaga(v);
	lista_apaga(l);
	lista_apaga(resultado);
	
	fclose(f);
		
	return 0;
}
