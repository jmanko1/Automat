#include <stdio.h>
#include <unistd.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void draw_diagram(int current_state) /* Funkcja rysująca diagram i zaznaczająca obecny stan na zielono */
{
    printf("\e[1;1H\e[2J");
	printf("\nAutomat skończony\n\n");
	
    printf("                       1            \n");
    
    if(current_state == 0) printf(ANSI_COLOR_GREEN "             ----  " ANSI_COLOR_RESET);
    else printf("             ----  ");
    printf("-------->");
    if(current_state == 1) printf(ANSI_COLOR_GREEN "  ----  \n"  ANSI_COLOR_RESET);
    else printf("  ----  \n");
    
    printf("START ---> "); //10
    if(current_state == 0) printf(ANSI_COLOR_GREEN "|| q0 ||    " ANSI_COLOR_RESET);
    else printf("|| q0 ||    ");
    printf("1     ");
    if(current_state == 1) printf(ANSI_COLOR_GREEN "| q1 | \n"  ANSI_COLOR_RESET);
    else printf("| q1 | \n");
    
    if(current_state == 0) printf(ANSI_COLOR_GREEN "             ----  " ANSI_COLOR_RESET);
    else printf("             ----  ");
    printf("<--------");
    if(current_state == 1) printf(ANSI_COLOR_GREEN "  ----  \n"  ANSI_COLOR_RESET);
    else printf("  ----  \n");
    
    printf("             |  ^             |  ^  \n");
    printf("           0 |  | 0         0 |  | 0 \n");
    printf("             |  |             |  |  \n");
    printf("             v  |      1      v  |  \n");
    
    if(current_state == 2) printf(ANSI_COLOR_GREEN "             ----  " ANSI_COLOR_RESET);
    else printf("             ----  ");
    printf("-------->");
    if(current_state == 3) printf(ANSI_COLOR_GREEN "  ----  \n"  ANSI_COLOR_RESET);
    else printf("  ----  \n");
    
    if(current_state == 2) printf(ANSI_COLOR_GREEN "            | q2 |     " ANSI_COLOR_RESET);
    else printf("            | q2 |     ");
    printf("1     ");
    if(current_state == 3) printf(ANSI_COLOR_GREEN "| q3 | \n"  ANSI_COLOR_RESET);
    else printf("| q3 | \n");
    
    if(current_state == 2) printf(ANSI_COLOR_GREEN "             ----  " ANSI_COLOR_RESET);
    else printf("             ----  ");
    printf("<--------");
    if(current_state == 3) printf(ANSI_COLOR_GREEN "  ----  \n"  ANSI_COLOR_RESET);
    else printf("  ----  \n");
    
    printf("\n\nStan początkowy - q0\nStan akceptowalny - q0\nStan obecny - q%d\n\n", current_state);
}

void pvect(int *v, int n) /* Funkcja wyświetlająca ciąg podanych symboli wejściowych */
{
	int i;
	printf("[ ");
	for(i = 0; i < n; i++)
	{
		printf("%d ", *v);
		v++;
	}
	printf("]");
}

void switch_state(int *current_state, int symbol) /* Funkcja przełączająca z jednego stanu automatu na drugi */
{
	switch(*current_state)
	{
		case 0: 
			if(symbol == 0) *current_state = 2;
			else *current_state = 1;
		break;
					
		case 1:	
			if(symbol == 0) *current_state = 3;
			else *current_state = 0;
		break;
					
		case 2:
			if(symbol == 0) *current_state = 0;
			else *current_state = 3;	
		break;
					
		case 3:
			if(symbol == 0) *current_state = 1;
			else *current_state = 2;
	}
}

void machine1(int *v, int n) /* Funkcja wywoływana przy podawaniu symboli ręcznie po kolei */
{
	int i;
	int current_state = 0;
	for(i = 0; i < n; i++)
	{
		draw_diagram(current_state);
		int symbol;
		do
		{
			printf("%d. symbol [0, 1]: ", i + 1);
			scanf("%d", &symbol);
		}
		while(symbol != 1 && symbol != 0);

		v[i] = symbol;

		switch_state(&current_state, symbol);
		draw_diagram(current_state);
	}
	printf("Ciąg ");
	pvect(v, n);
	if(current_state == 0)
		printf(" jest akceptowalny\n\n");
	else
		printf(" nie jest akceptowalny\n\n");	
}

void machine2(int *v, int n) /* Funkcja wywoływana przy pobieraniu symboli z pliku lub z argumentów wywołania */
{
	draw_diagram(0);
	sleep(2);
    int i;
    int current_state = 0;
    for(i = 0; i < n; i++)
	{
		switch_state(&current_state, v[i]);
    	draw_diagram(current_state);
    	sleep(1);
    }
		        
	printf("Ciąg ");
    pvect(v, n);
    
    if(current_state == 0)
    	printf(" jest akceptowalny\n\n");
    else
    	printf(" nie jest akceptowalny\n\n");
}
