#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include "systems.h"




ready_mat* create_blank_matrix(int lines, int columns)
{
	ready_mat* matr = (ready_mat*) calloc(1,               sizeof(ready_mat));


	double*      line = (double* ) calloc(columns * lines, sizeof(double ));
	double**   matrix = (double**) calloc(          lines, sizeof(double*));		
	double* sollution = (double* ) calloc(          lines, sizeof(double ));

	for (int i = 0; i < lines; i++)
	{
		matrix[i] = &line[i * columns];
	}

	
	matr->matr_ptr  =    matrix;
	matr->line_ptr  =      line;
	matr->   lines  =     lines;
	matr-> columns  =   columns;
	matr->     det  =         0;
	matr->sollution = sollution;


	return matr;
}

ready_mat* init_matrix(int lines)
{
	ready_mat* matr = (ready_mat*) calloc(1,                   sizeof(ready_mat));
	double*    line = (double*   ) calloc((lines + 1) * lines, sizeof(double   ));
	double** matrix = (double**  ) calloc(              lines, sizeof(double*  ));
	int*  sollution = (int*      ) calloc(              lines, sizeof(int      ));


	for (int i = 0; i < lines; i++)
	{
		matrix[i]        = &line[i * (lines + 1)];
		matrix[i][i]     =                      1;
		matrix[i][lines] =       rand() % 100 - 0;
		sollution[i]     =       matrix[i][lines];
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
	int x = rand() %  10 - 0;

	matr->matr_ptr[i][i] = x;
	det *= x;					
	}
	
	matr->det = det;
}

void rand_line_change(ready_mat* matr)
{
	//srand(time(NULL));

	int line_changed =     rand() %  matr->lines;
	int line_added   =     rand() %  matr->lines;
	int koef         = 1 + rand() %            4;

	for (int i = 0; i <= matr->lines; i++)
	{
		matr->matr_ptr[line_changed][i] += koef * matr->matr_ptr[line_added][i];
		//printf("matr_ptr[%d][%d] += %d * matr_ptr[%d][%d] \n", line_changed, i, koef, line_added, i);
	}


	printf("changed line %d, added line %d, koef %d \n", line_changed + 1, line_added + 1, koef);
}	

void change_matrix(ready_mat* matr)
{
	for (int j = 0; j < matr->lines * matr->lines; j++)
	{
		rand_line_change(matr);
		//printf("%d change \n", j);
		print_matrix2(matr);
		printf("\n");
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

/*int test_prog()
{
	int size = rand() % 12;
	ready_mat* matr = init_matrix(size);
	change_matrix(matr);

}*/
	
