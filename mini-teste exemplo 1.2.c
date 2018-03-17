/*** problema 1.1 ***/
lista* encontra_nomes(lista *lst1, lista *lst2)
{

		l_elemento *nome1, *nome2;
		int i=0, j=0;
		lista *aux = lista_nova();

		if(lst1 == NULL || lst2 == NULL)
		{

			return NULL;
		}

		for (i=0; i < lst1->tamanho; i++)
		{
			nome1 = lista_elemento(lst1, i);

			for (j = 0; j < lst2->tamanho; j++)
			{
				nome2 = lista_elemento(lst2, j);

				if (strcmp(nome1->str, nome2->str) == 0)
				{
					lista_insere(aux, nome1->str, NULL);
				}
			}
		}
		return aux;
}

/*** problema 1.2 ***/
int lista_remove_longos(lista *lst, int nomes)
{
	int i, n=0, j=0, count=0;
	l_elemento *temp;


	if(lst == NULL || lst->tamanho == 0 || nomes > 1)
		return -1;


	for(j=0;j<lst->tamanho;j++)
	{
		temp=lista_elemento(lst,j);

		for (i=0; i < strlen(temp->str);i++)
		{

			if(temp->str[i] == ' ')
				count++;

			if(count>=nomes)
			{

				lista_remove(lst,temp);
				n++;
			}

		}
	}
	return n;
}

/*** problema 1.3 ***/
fila* pesquisa_nomes(lista *lst, char *nome)
{
	int i;
	l_elemento *temp;
	fila *new = fila_nova();

	if (lst == NULL || nome == NULL || lst->tamanho ==0)
		return NULL;

	for(i=0;i<lst->tamanho;i++)
	{
		temp=lista_elemento(lst,i);

		if(strstr(temp->str,nome)!=NULL)
			fila_push(new,temp->str);
	}
	return new;
}
