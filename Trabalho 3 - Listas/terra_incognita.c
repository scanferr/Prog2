#include "terra_incognita.h"
#include <stdio.h>
#include <stdlib.h>

static int *terraIncognita;
static int *praesentia;
static unsigned int latitudo;
static unsigned int altitudo;
static unsigned long int iteratio = 0;
static unsigned long int iteratioMaximus;
static unsigned long int proximus = 1;

static int nEx;
static int curEx = 0;

static int statumX[MAX_EXPLORADORES];
static int statumY[MAX_EXPLORADORES];

#define PROBO(x,m) if((x)) { printf(m); e++; }

/*********** funcoes auxiliares ***********/

int incognita_rand()
{
    proximus = proximus * 1103515245 + 12345;
    return (unsigned int)(proximus/65536) % 32768;
}

int incognita_rand_int(int min, int max)
{
    return incognita_rand() % (max-min+1) + min;
}

void coords(char mov, int *x, int *y)
{
    switch(mov)
    {
        case 'N':
            (*y)--; break;
        case 'S':
            (*y)++; break;
        case 'E':
            (*x)++; break;
        case 'O':
            (*x)--; break;
    }
}

/*********** funcoes publicas ***********/

void intro(int argc, char *argv[], int *nExplorator, int positio[][2])
{
    unsigned int i, parametri[3]; 

    if(argc == 4)
    {
        for(i=0; i<3; i++)
        {
            parametri[i] = atoi(argv[i+1]);
            if(i != 2 && parametri[i] == 0)
                break;
        }
    }

    if(argc != 4 || i < 3)
    {
        printf("Programa deve ser chamado com argumentos, tal como indicado no enunciado.\n\n");
        exit(1);
    }

    switch(parametri[2])
    {
        case 0:
            latitudo = 6;
            altitudo = 6;
            nEx = 1;
            statumX[0] = 0;
            statumY[0] = 0;            
            break;
        case 1:
            latitudo = incognita_rand_int(10,20);
            altitudo = incognita_rand_int(10,20);
            nEx = 3;
            statumX[0] = 0;
            statumY[0] = altitudo/2;
            for(i=1; i<nEx; i++)
            {
                statumX[i] = statumX[0] + incognita_rand_int(5,latitudo-1);
                statumY[i] = statumY[0] + incognita_rand_int(-(int)altitudo/2+1, altitudo/2-1);                
            }
            break;
        case 2:
            latitudo = incognita_rand_int(100,150);
            altitudo = incognita_rand_int(100,150);
            nEx = 10;
            statumX[0] = latitudo-1;
            statumY[0] = altitudo/2;
            for(i=1; i<nEx; i++)
            {
                statumX[i] = statumX[0] - incognita_rand_int(5,latitudo-1);
                statumY[i] = statumY[0] + incognita_rand_int(-(int)altitudo/2+1, altitudo/2-1);                
            }
            break;
        case 3:
            latitudo = incognita_rand_int(300,500);
            altitudo = incognita_rand_int(300,500);
            nEx = incognita_rand_int(20,40);
            for(i=0; i<nEx; i++)
            {
                statumX[i] = incognita_rand_int(0,latitudo-1);
                statumY[i] = incognita_rand_int(0,altitudo-1);
            }
            break;
        default: /* parametro errado */
            *nExplorator = 0;
            return;
    }

    proximus = parametri[0];
    iteratioMaximus = parametri[1] * nEx;

    positio[0][0] = positio[0][1] = 0;
    for(i=1; i<nEx; i++)
    {
        positio[i][0] = statumX[i] - statumX[0];
        positio[i][1] = statumY[i] - statumY[0];
    }

    *nExplorator = nEx;

    terraIncognita = calloc(latitudo*altitudo, sizeof(int));
    praesentia = calloc(latitudo*altitudo, sizeof(int));

    for(i=0; i<latitudo*altitudo; i++)
    {
        terraIncognita[i] = incognita_rand() % 4 + 1;
    }
}

char explorator(int *id, int *typus)
{
    char possiveis[5], incognitas[5], res;
    int i, n = 0, ni = 0, posX, posY;
    
    *id = *typus = 0;
    if(++iteratio > iteratioMaximus)
        return 'X';

    curEx++;
    if (curEx >= nEx) curEx = 0;
    *id = curEx;

    posX = statumX[*id];
    posY = statumY[*id];

    if(posX >= 0 && posX < latitudo-1)
        possiveis[n++] = 'E';
    if(posX > 0 && posX <= latitudo-1)
        possiveis[n++] = 'O';
    if(posY >= 0 && posY < altitudo-1)
        possiveis[n++] = 'S';
    if(posY > 0 && posY <= altitudo-1)
        possiveis[n++] = 'N';

    for(i=0; i<n; i++)
    {
        int x = posX;
        int y = posY;

        coords(possiveis[i], &x, &y);
        if(praesentia[y*latitudo + x] == 0)
            incognitas[ni++] = possiveis[i];
    }

    if(ni == 0) /* se tudo visto, escolhe um dos possiveis */
        res = possiveis[incognita_rand() % n];
    else
        res = incognitas[incognita_rand() % ni];

    coords(res, &posX, &posY);
    statumX[*id] = posX;
    statumY[*id] = posY;
    *typus = terraIncognita[posY*latitudo + posX];
    praesentia[posY*latitudo + posX] = 1;
    return res;
}

void tabula(cellulae_func *cell, int lat, int alt)
{
    int i, j;

    if(cell == NULL || lat <= 0 || alt <= 0)
    {
        printf("ERRO no mapa ou nas respetivas dimensoes\n.");
        return;
    }

    for(i=0; i<(lat-4)/2; i++)
        putchar('=');
    printf("MAPA");
    for(i+=4; i<lat; i++)
        putchar('=');
    puts("");    

    for(i=0; i<alt; i++)
    {
        for(j=0; j<lat; j++)
        {
            char c;
            switch(cell(j,i))
            {
                case TERRA_INCOGNITA:
                    c = '?'; break;
                case  TERRA_PLANICIE:
                    c = '_'; break;
                case  TERRA_FLORESTA:
                    c = '#'; break;
                case  TERRA_MONTANHA:
                    c = '^'; break;
                case  TERRA_AGUA:
                    c = '~'; break;
            }
            putchar(c);
        }
        putchar('\n');
    }

    for(i=0; i<lat; i++)
        putchar('=');
    puts(""); 
}

void veritas(cellulae_func *cell, int lat, int alt)
{
    int x, y;
    int bonum = 0, malus = 0, e = 0;

    PROBO(cell == NULL, "ERRO na funcao de mapeamento\n.")
    PROBO(lat != latitudo, "ERRO na largura do mapa\n.")
    PROBO(alt != altitudo, "ERRO na altura do mapa\n.")

    if(e)
        return;

    for(y=0; y<alt; y++)
    {
        for(x=0; x<lat; x++)
        {
            if (cell(x, y) == TERRA_INCOGNITA) continue;
            if (terraIncognita[y*lat+x] == cell(x, y)) {       
                bonum++;
            } else {
                malus++;
                /* printf("(%d,%d): %d <> %d\n", i, j, terraIncognita[j*l+i], cell(i, j)); */
            }
        }
    }

    printf("Dimensao: %dx%d\n", lat, alt);
    printf("Celulas OK: %d\n", bonum);
    printf("Celulas Mal: %d\n", malus);
    printf("\n");
}

void relinquo()
{
    free(terraIncognita);
    free(praesentia);
}

