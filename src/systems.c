#include "systems.h"


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
//#include <math.h>



const double EPSYLON = 1e-14;

#if(0)
struct  matrix_info;
{
	data** used_ptr;
	data*  line_ptr;
	int     columns;
	int       lines;
} info;
#endif

ready_mat* read_matrix(int n, int m)
{
	#if(0)
	data*  in_line = (data* ) calloc(n * m * n * m, sizeof(data ));
	data**  matrix = (data**) calloc(n * m * n * m, sizeof(data*));
	#endif
	
	ready_mat* matr = create_blank_matrix(n, m);

	for (int i = 0; i < matr->lines; i++)
	{
		for (int j = 0; j < matr->lines + 1; j++)
		{
			scanf("%lg", &matr->matr_ptr[i][j]);
		}
	}

	return matr;
}

//-----------------------------------------------------------------------------------------------------

void print_matrix(ready_mat* matr) 
{
	for (int i = 0; i < matr->lines; i++)
	{
		for (int j = 0; j < matr->columns; j++)
		{
			printf("%lg ", matr->matr_ptr[i][j]);
		}
		printf("\n");
	}
}

//-----------------------------------------------------------------------------------------------------

void print_vline(double* column, int lines)
{
	for (int i = 0; i < lines; i++)
	{
		printf("%lg \n", column[i]);
	}
}

void destruct_2d(double** matrix, int lines)
{
	free(matrix[0]);
	
	for (int i = 0; i < lines; i++)
	{
		matrix[i] = NULL;
	}
	free(matrix);
}


//--------------------------------------------------------------------------------------------------------------

void destruct(ready_mat* matr)
{
	free(matr->sollution);
	free(matr->matr_ptr );
	free(matr->line_ptr );
}
///----------------------------------------------------------------------------------------------------------

double triangle_det(ready_mat* matr)
{
	
	double s = 1.0;
	for (int i = 0; i < matr->lines; i++)
		{
			if (matr->matr_ptr[i][i] == 0)
				return 0;
	
			s *= matr->matr_ptr[i][i];
		}
	return s;
}

//------------------------------------------------------------------------------------------------------
/*

double** to_triangle(data** matrix)
{
	if (matr == NULL)
	{
		printf("tryndets\n");
		return NULL;
	}

	if (matr->matr_ptr == NULL)


	if (n < 1)
		return NULL;

	if (n == 1)
		return matrix;	


	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)	
		{
			if (matrix[i][j] == 0)
				continue;

				
			if (matrix[j][j] == 0)
			{
				for (int c = 0; c < n; c++)
				{
					matrix[j][c] += matrix[i][c];	
				}

			}


			double koef = matrix[i][j] / matrix[j][j];

			for (int k = 0; k < n; k++)
			{
				double x = koef * matrix[j][k];

				if (fabs(x) < EPSYLON)
				{
					matrix[i][k] = 0;
					continue;
				}
				matrix[i][k] -= x;
				
			}
		}
	}
	
	if (triangle_det(matr) == 0)
		return NULL;

	return matrix;
}
*/

//----------------------------------------------------------------------------------------------------------------------


/// for matrixes n * (n + 1)


ready_mat* triangle_expanded(ready_mat* matr)
{
	if (matr           == NULL)
		return   NULL;

	if (matr->matr_ptr == NULL)
		return   NULL;

	if (matr->lines    ==    1)
		return matr;

	if (matr->lines     <    1)
		return   NULL;


	for     (int i = 1; i < matr->lines; i++)
	{
		for (int j = 0; j < i;           j++)	
		{

			
			if (matr->matr_ptr[i][j] == 0)
				continue;

				
			if (matr->matr_ptr[j][j] == 0)
			{
				for (int c = 0; c < matr->lines; c++)
				{
					matr->matr_ptr[j][c] += matr->matr_ptr[i][c];	
				}

			}


			double koef = matr->matr_ptr[i][j] / matr->matr_ptr[j][j];

			for (int k = 0; k < matr->lines + 1; k++)
			{
				double x = koef * matr->matr_ptr[j][k];

				if (fabs(matr->matr_ptr[i][k] - x) < EPSYLON)
				{
					matr->matr_ptr[i][k] = 0;
					continue;
				}
				matr->matr_ptr[i][k] -= x;
				
			}
		}
	}
	
	if (triangle_det(matr) == 0)
		return NULL;

	return matr;
}



//------------------------------------------------------------------------------------------------------------


///case of n equations for n - 1 variables will be considered later

ready_mat* to_diagonal(ready_mat* matr)
{
	ready_mat* matr2 = triangle_expanded(matr);
	
	if (matr == NULL)
		return  NULL;

	matr = matr2;
	
	for (int i = matr->lines - 2; i >= 0; i--)
	{
		for (int j = matr->lines - 1; j > i; j--)	

		{

			if (matr->matr_ptr[i][j] == 0)
				continue;

			
			if (matr->matr_ptr[j][j] == 0)
			{
				return NULL; // undef_sol
			}


			double koef = matr->matr_ptr[i][j] / matr->matr_ptr[j][j];

			double x    = koef *  matr->matr_ptr[j][          j];
			double y    = koef *  matr->matr_ptr[j][matr->lines];
				
				
			if (fabs(matr->matr_ptr[i][j] - x) < EPSYLON)
			{
				matr->matr_ptr[i][j] = 0;
			}
			else
			{
				matr->matr_ptr[i][j] -= x;
			}



			if (fabs(matr->matr_ptr[i][j] - y) < EPSYLON)
			{
				matr->matr_ptr[i][matr->lines] = 0;
			}
			else
			{
				matr->matr_ptr[i][matr->lines] -= y;			
			}

		}


	}
	return matr; 
}

//------------------------------------------------------------------------------------------------------


#if(0)

double** to_triangle_expanded(data** matrix, int lines, int exception)
{
	if (lines < 1)
		return NULL;

	if (lines == 1)
		return matrix;

	for (int i = 1; i < lines; i++)
	{
		for (int j = 0; j < i; j++)	
		{
			if (j == exception)
			{
				j = lines;
			}
			
			if (matrix[j][j] == 0)
			{
				for (int c == 0; c < lines; c++)
				{
					
				}

			}
	
			double koef = matrix[i][j] / matrix[j][j];

			for (int k = 0; k < lines; k++)

	}
	return matrix;
}

#endif


//--------------------------------------------------------------------------------------------------------------

ready_mat* copy_mat(ready_mat* matr)
{
	ready_mat*  matr2 = (ready_mat*) calloc(1,                           sizeof(ready_mat));
	double**  matrix0 = (double**)   calloc(matr->lines,                 sizeof(double*  ));
	double*  in_line0 = (double* )   calloc(matr->lines * matr->columns, sizeof(double   ));
		
	
	for (int i = 0; i < matr->lines; i++)
	{
		matrix0[i] = &in_line0[i * matr->columns];

		for (int j = 0; j < matr->columns; j++)   
		{
			in_line0[i * matr->columns + j] = matr->matr_ptr[i][j]; 
		}

	matr2->matr_ptr  =         matrix0;
	matr2->line_ptr  =        in_line0;
	matr2->sollution = matr->sollution; 
	matr2->lines     = matr->    lines;
	matr->columns    = matr->  columns;
		
	}
	return matr2;
}

//--------------------------------------------------------------------------------------------------------------------------


ready_mat* expand_mat(ready_mat* matr, int except)
{
	ready_mat*  matr0 = (ready_mat*) calloc(1,                         sizeof(ready_mat));
	double**  matrix0 = (double**  ) calloc(matr->lines,               sizeof(double*  ));
	double*  in_line0 = (double*   ) calloc(matr->lines * matr->lines, sizeof(double   ));
	
	
	for (int i = 0; i < matr->lines; i++)
	{
		matrix0[i] = &in_line0[i * matr->lines];
		for (int j = 0; j < matr->lines; j++)
		{
			if (j == except)
			{
				in_line0[i * matr->lines + j] = matr->matr_ptr[i][matr->lines];
				continue;
			}
			in_line0[i * matr->lines + j] = matr->matr_ptr[i][j]; 
		}
		
	}
	
	matr0->line_ptr =      in_line0;
	matr0->matr_ptr =       matrix0;
	matr0->lines    = matr->  lines;	
	matr->columns   = matr->columns;
	

	return matr0;
}

//------------------------------------------------------------------------------------------------------------------------------

#if(0)  // might be repaired
double det_expanded(ready_mat* matr, int except)
{
	ready_mat* mat = NULL;
	mat = expand_mat(matr, except);

	if (mat == NULL)
		return 0;
	
	if (mat->matr_ptr == NULL)
		return 0;

	matr = mat;

	mat = to_triangle(matr);   // somewhere here might be a problem

	if (mat == NULL)
	{
		printf("ops");
		return 0;
	}

	if (mat->matr_ptr == NULL)
		return 0;
	
	matr = mat;
	
	mat = to_triangle(matr);

	double det = triangle_det(matr);

	destruct(matr);	
	return det;
	
}


//-------------------------------------------------------------------------------------------------------------------------------

double* solve_line_syst3(double** matrix, int lines)
{
	double* dets = (double*) calloc(lines + 1, sizeof(double));
	double* res  = (double*) calloc(lines,     sizeof(double));

	dets[0] = det_expanded(matrix, lines, lines);
	
	if (dets[0] == 0)
		return NULL;

	
	for (int i = 0; i < lines; i++)
	{
		dets[i + 1] = det_expanded(matrix, lines, i);
	}

	for (int i = 0; i < lines; i++)
	{
		res[i] = dets[i + 1] / dets[0];
	}

	free(dets);

	return res;
}
#endif // unchanged for Cramer


double* solve_diagonal(ready_mat* matr)
{
	if (matr == NULL)		
		return NULL; // probably, better to print 'no sollution' from here
	

	if (matr->matr_ptr == NULL)
		return NULL;

	if (matr->sollution == NULL)
		return NULL;
	
	
	double* res = (double*) calloc(matr->lines, sizeof(double));
	
	for (int i = 0; i < matr->lines; i++)
	{
		res[i] = matr->matr_ptr[i][matr->lines] / matr->matr_ptr[i][i];	
	}
	
	matr->sollution = res;

	return res;

}
//----------------------------------------------------------------------------------------------------------------------------------

void solve_syst(ready_mat* matr)
{
	ready_mat* matr1 = to_diagonal(matr);

	if (matr1 == NULL)
		return;

	matr = matr1;
	
	double* res = solve_diagonal(matr);
	matr->sollution = res;
}
