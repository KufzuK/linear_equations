#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
//#include "systems.h"


typedef struct ready_matrix
{
	double** matr_ptr;
	double*  line_ptr;

	int         lines;
	int       columns;
	int           det;

} ready_mat;


ready_mat*i create_blank_matrix()
{
	ready_mat* matr = (ready_mat*) calloc(1,               sizeof(ready_mat));


	double*    line = (double*   ) calloc(columns * lines, sizeof(double   ));
	double** matrix = (double**  ) calloc(          lines, sizeof(double*  ));

	matr->matr_ptr =  matrix;
	matr->line_ptr =    line;
	matr->   lines =   lines;
	matr-> columns = columns;
	matr->     det =       0;
	

	for (int i = 0; i < lines; i++)
	{
		matrix[i] = &line[i * columns];
	}
	
	return matr;
}


/// lines = columns      if only determinant must be checked

/// lines = columns - 1  if system sollution must be checked


void feel_diagonal(ready_mat* matr)  
{
	srand(time(NULL));

	for (int i = 0; i < matr->lines; i++)
	{
	int det = 1;
	int x = rand() % 100 - 0;

	matr->matr_ptr[i][i] = x;
	det *= x;					
	}
	
	matr->det = det;
}

void rand_line_change(ready_mat* matr)
{
	srand(time(NULL));

	int line_changed = rand() % (matr->lines - 1) - 0;
	int line_added   = rand() % (matr->lines - 1) - 0;
	int koef         = rand() %                15 - 0;

	for (int i = 0; i < matr->columns; i++)
	{
		matr->matr_ptr[line_changed][i] += koef * matr->matr_ptr[line_added][i];
	}
}	

void change_matrix(ready_mat* matr)
{
	for (int i = 0; i < 20 * matr->lines; i++)
	{
		rand_line_change(matr);
	}

}



int main()
{
	int lines = 2, columns = 2;
	
	srand(time(NULL));

	int x = rand() % 1000 - 0;
	printf("%d \n", x);
	
	double*    line = (double* ) calloc( columns * lines, sizeof(double ));
	double** matrix = (double**) calloc(           lines, sizeof(double*));

	for (int i = 0; i < lines; i++)
	{
		matrix[i] = &line[i * columns];
	}


	printf("%lg", matrix[1][1]);
}	
	
