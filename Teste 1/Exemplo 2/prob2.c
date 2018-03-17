#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char nome[100];
	int pop2001;
	int pop2012;
}
municipio;

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
municipio *lerFicheiro(FILE *ficheiro, int *num_municipios)
{
	municipio *mun=NULL;
	char nome[100];
	int n, pop2001, pop2012;

	if (ficheiro==NULL)
		return NULL;

	while (fscanf(ficheiro, "%s %d %d", nome, &pop2001, &pop2012)==3)
	{
		mun = realloc(mun,(n+1)*sizeof(municipio));
		strcpy(mun[n].nome, nome);
		mun[n].pop2001=pop2001;
		mun[n].pop2012=pop2012;
		n++;
	}

	*num_municipios=n;
	return mun;
}

/*** problema 2.2 ***/
void gerarRelatorio(FILE *ficheiro, municipio *resultados, int num_municipios)
{


}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
	FILE *fin, *fout;
	municipio *resultados;
	int n;

	fin = fopen("municipios.txt", "r");
	if(fin == NULL)
		return 1;

	fout = fopen("relatorio.txt", "w");
	if(fout == NULL)
		return 1;

	resultados = lerFicheiro(fin, &n);
	gerarRelatorio(fout, resultados, n);

	fclose(fin);
	fclose(fout);
	free(resultados);

	return 0;
}
