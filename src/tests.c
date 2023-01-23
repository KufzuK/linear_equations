#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include "systems.h"




ready_mat* create_blank_matrix(int lines, int columns)
{
	ready_mat* matr = (ready_mat*) calloc(1,               sizeof(ready_mat));


	double*    line = (double*   ) calloc(columns * lines, sizeof(double   ));
	double** matrix = (double**  ) calloc(          lines, sizeof(double*  ));	

	for (int i = 0; i < lines; i++)
	{
		matrix[i] = &line[i * columns];
	}

	
	matr->matr_ptr  =  matrix;
	matr->line_ptr  =    line;
	matr->   lines  =   lines;
	matr-> columns  = columns;
	matr->     det  =       0;


	return matr;
}

ready_mat* init_matrix(int lines)
{
	ready_mat* matr = (ready_mat*) calloc(1,                   sizeof(ready_mat));
	double*    line = (double*   ) calloc((lines + 1) * lines, sizeof(double   ));
	double** matrix = (double**  ) calloc(              lines, sizeof(double*  ));


	for (int i = 0; i < lines; i++)
	{
		matrix[i]        = &line[i * (lines + 1)];
		matrix[i][i]     =                      1;
		matrix[i][lines] =       rand() % 100 - 0;
	}
	
	matr->matr_ptr  =    matrix;
	matr->line_ptr  =      line;
	matr->   lines  =     lines;
	matr-> columns  = 1 + lines;
	matr->     det  =         0;

	return matr;
}

/// lines = columns      if only determinant must be checked

/// lines = columns - 1  if system sollution must be checked


void feel_diagonal(ready_mat* matr)  
{
	srand(time(NULL));

	int det = 1;
	
	for (int i = 0; i < matr->lines; i++)
	{
	int x = rand() % 100 - 0;

	matr->matr_ptr[i][i] = x;
	det *= x;					
	}
	
	matr->det = det;
}

void rand_line_change(ready_mat* matr)
{
	srand(time(NULL));

	int line_changed = rand() % (matr->lines - 1);
	int line_added   = rand() % (matr->lines - 1);
	int koef         = rand() %                15;

	for (int i = 0; i <= matr->lines; i++)
	{
		matr->matr_ptr[line_changed][i] += koef * matr->matr_ptr[line_added][i];
	}


	printf("changed line %d, added line %d, koef %d \n", line_changed, line_added,  koef);
}	

void change_matrix(ready_mat* matr)
{
	for (int j = 0; j < 20 * matr->lines; j++)
	{
		rand_line_change(matr);
		print_matrix2(matr);
		printf("%d change \n", j);
	}

}

void print_matrix2(ready_mat* matr)
{
	for (int i = 0; i < matr-> lines; i++)
	{
		for (int j = 0; j < matr->columns; j++)
		{
			printf("%lg ", matr->matr_ptr[i][j]);
		}
		printf("\n");
	}
}


/*int main()
{
	int lines = 2, columns = 2;
	
	srand(time(NULL));

	int x = rand() % 1000 - 0;
	printf("%d \n", x);
	
	//double*    line = (double* ) calloc( columns * lines, sizeof(double ));
	//double** matrix = (double**) calloc(           lines, sizeof(double*));

	ready_mat* matr = create_blank_matrix(lines, columns);
	feel_diagonal(matr);

	for (int i = 0; i < lines; i++)
	{
		matrix[i] = &line[i * columns];
	}


	printf("%lg", matr->matr_ptr[1][1]);
}	*/
	
