#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bibl.h"

int main(int argc, char *argv[])
{
	if(argc == 1) /* brak parametrow */
	{
		draw_diagram(0);

		printf("Wybierz sposób wczytania ciągu przejść. Automat wykonuje 100 przejść maksymalnie\n");
		printf("1. Wpisanie po kolei symboli wejściowych ręcznie\n");
		printf("2. Wczytanie ciągu symboli wejściowych z pliku. Symbole muszą być oddzielone spacją\n");
		printf("Wybierz opcję 1 lub 2: ");
		int a;
		scanf("%d", &a);
		
		if(a != 1 && a != 2)
		{
			printf("Error: Wybrano niewłaściwą opcję\n");
			return 1;
		}

		if(a == 1) /* wpisanie po kolei symboli */
		{
			printf("Ile symboli wejściowych chcesz podać: ");
			int n;
			scanf("%d", &n);
			if(n <= 0 || n > 100)
			{
				fprintf(stderr, "Error: Nie podano prawidłowej liczby symboli wejściowych.\n");
				return 1;
			}

			int *v = malloc(sizeof *v * (n + 1));
			machine1(v, n); /* Wywołanie funkcji wczytującej po kolei symbole */
			free(v);

		}
		else /* odczytanie z pliku */
		{
			printf("Podaj nazwę pliku: ");
			char name[100];
			scanf("%s", name);
			
			FILE *f = fopen(name, "r");
			if(f == NULL)
			{
			    fprintf(stderr, "Error: Plik %s nie istnieje.\n", name);
			    return 1;	
			}
			else
			{
		        int i = 0;
		        int symbol;
		        int v[100];
		        
		        while(fscanf(f, "%i", &symbol) == 1)
		        {
		            if(i < 100)
		            {
    		        	if(symbol != 0 && symbol != 1)
    		        	{
    		            	fprintf(stderr, "Error: Plik zawiera niepoprawny ciąg.\n");
    		            	fclose(f);
    						return 1;
    		            }
    		            else
    		            {
    		                v[i] = symbol;
    		                i++;
    		            }
		            }
		            else
		            {
		                fprintf(stderr, "Error: W pliku jest więcej niż 100 symboli wejściowych.\n");
	                    return 1;
		            }
		    	}
		    	
		    	fclose(f);
		    	printf("\nWczytano z pliku ciąg ");
		    	pvect(v, i);
		        printf("\nZa chwilę rozpocznie się praca automatu.\n");
		        sleep(5);
				machine2(v, i); /* Wywołanie funkcji wykonującej operacje na wczytanych symbolach */
			}
		}
	}
	else /* Podanie symboli w argumentach wywołania */
	{
	    if(argc > 101)
	    {
	        fprintf(stderr, "Error: Podano więcej niż 100 symboli wejściowych.\n");
	        return 1;
	    }
	    else
	    {
    		int n = argc - 1;
    		int *v;
    		v = malloc(sizeof *v * (n + 1));
    
    		int i;
    		for(i = 0; i < n; i++)
    		{
    			if(atoi(argv[i + 1]) != 0 && atoi(argv[i + 1]) != 1)
    			{
    				fprintf(stderr, "Error: Podano niepoprawny ciąg.\n");
    				free(v);
    				return 1;
    			}
    			else
    				v[i] = atoi(argv[i + 1]);
    		}
    		printf("Wczytano ciąg ");
    		pvect(v, n);
    		printf("\nZa chwilę rozpocznie się praca automatu.\n");
    		sleep(5);
    		machine2(v, n); /* Wywołanie funkcji wykonującej operacje na wczytanych symbolach */
    		free(v);
	    }
	}

	return 0;
}
