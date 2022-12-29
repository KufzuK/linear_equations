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

data** read_matrix(int n, int m)
{
	data*  in_line = (data* ) calloc(n * m * n * m, sizeof(data ));
	data**  matrix = (data**) calloc(n * m * n * m, sizeof(data*));

	

	for (int i = 0; i < n; i++)
	{
		matrix[i] = &in_line[m * i];
		
		for (int j = 0; j < m; j++)
		{
			scanf("%lg",   &in_line[m * i + j]);
		}
	}
	return matrix;
}

//-----------------------------------------------------------------------------------------------------

void print_matrix(data** matrix, int n, int m) 
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%lg ", matrix[i][j]);
		}
		printf("\n");
	}
}

//-----------------------------------------------------------------------------------------------------

void destruct(double** matrix, int lines)
{
	free(matrix[0]);

	for (int i = 0; i < lines; i++)
	{
		matrix[i] = NULL;
	}
	free(matrix);
}


//--------------------------------------------------------------------------------------------------------------


double triangle_det(double** matrix, int n)
{
	
	double s = 1.0;
	for (int i = 0; i < n; i++)
		{
			if (matrix[i][i] == 0)
				return 0;
	
			s *= matrix[i][i];
		}
	return s;
}

//------------------------------------------------------------------------------------------------------


double** to_triangle(data** matrix, int n)
{
	if (matrix == NULL)
	{
		printf("tryndets\n");
		return NULL;
	}


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
	
	if (triangle_det(matrix, n) == 0)
		return NULL;

	return matrix;
}


//----------------------------------------------------------------------------------------------------------------------


/// for matrixes n * (n + 1)
double** triangle_expanded(double** matrix, int lines)
{
	if (matrix == NULL)
		return NULL;

	if (lines  ==    1)
		return matrix;

	if (lines   <    1)
		return NULL;


	for     (int i = 1; i < lines; i++)
	{
		for (int j = 0; j < i;     j++)	
		{

			
			if (matrix[i][j] == 0)
				continue;

				
			if (matrix[j][j] == 0)
			{
				for (int c = 0; c < lines; c++)
				{
					matrix[j][c] += matrix[i][c];	
				}

			}


			double koef = matrix[i][j] / matrix[j][j];

			for (int k = 0; k < lines + 1; k++)
			{
				double x = koef * matrix[j][k];

				if (fabs(matrix[i][k] - x) < EPSYLON)
				{
					matrix[i][k] = 0;
					continue;
				}
				matrix[i][k] -= x;
				
			}
		}
	}
	
	if (triangle_det(matrix, lines) == 0)
		return NULL;

	return matrix;
}


//------------------------------------------------------------------------------------------------------------


///case of n equations for n - 1 variables will be considered later

double** to_diagonal(double** matrix, int lines)
{
	double** mat = triangle_expanded(matrix, lines);
	
	if (mat == NULL)
		return NULL;

	matrix = mat;
	
	for (int i = lines - 2; i >= 0; i--)
	{
		for (int j = lines - 1; j > i; j--)	

		{

			if (matrix[i][j] == 0)
				continue;

			
			if (matrix[j][j] == 0)
			{
				return NULL; // undef_sol
			}


			double koef = matrix[i][j] / matrix[j][j];

			double x    = koef *  matrix[j][j];
			double y    = koef *  matrix[j][lines];
				
				
			if (fabs(matrix[i][j] - x) < EPSYLON)
			{
				matrix[i][j] = 0;
			}
			else
			{
				matrix[i][j] -= x;
			}



			if (fabs(matrix[i][j] - y) < EPSYLON)
			{
				matrix[i][lines] = 0;
			}
			else
			{
				matrix[i][lines] -= y;			
			}

		}


	}
	return matrix; 
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

double** copy_mat(double** matrix, int lines, int columns)
{
	double**  matrix0 = (double**) calloc(lines,           sizeof(double*));
	double*  in_line0 = (double* ) calloc(lines * columns, sizeof(double ));
	
	
	
	for (int i = 0; i < lines; i++)
	{
		matrix0[i] = &in_line0[i * columns];

		for (int j = 0; j < columns; j++)
		{
			in_line0[i * columns + j] = matrix[i][j]; 
		}
		
	}
	return matrix0;
}

//--------------------------------------------------------------------------------------------------------------------------


double** expand_mat(double** matrix, int lines, int except)
{
	double**  matrix0 = (double**) calloc(lines,         sizeof(double*));
	double*  in_line0 = (double* ) calloc(lines * lines, sizeof(double ));
	
	
	for (int i = 0; i < lines; i++)
	{
		matrix0[i] = &in_line0[i * lines];
		for (int j = 0; j < lines; j++)
		{
			if (j == except)
			{
				in_line0[i * lines + j] = matrix[i][lines];
				continue;
			}
			in_line0[i * lines + j] = matrix[i][j]; 
		}
		
	}
	return matrix0;
}

//------------------------------------------------------------------------------------------------------------------------------


double det_expanded(double** matrix, int lines, int except)
{
	double** mat = NULL;
	mat = expand_mat(matrix, lines, except);

	if (mat == NULL)
		return 0;

	matrix = mat;

	mat = to_triangle(matrix, lines);   // somewhere here might be a problem

	if (mat == NULL)
	{
		printf("ops");
		return 0;
	}
	
	matrix = mat;
	
	mat = to_triangle(mat, lines);

	double det = triangle_det(mat, lines);

	destruct(mat, lines);	
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

double* solve_diagonal(double** matrix, int lines)
{
	if (matrix == NULL)
	{
		
		return NULL; // probably, better to print 'no sollution' from here
	}
	
	double* res = (double*) calloc(lines, sizeof(double));
	
	for (int i = 0; i < lines; i++)
	{
		res[i] = matrix[i][lines] / matrix[i][i];	
	}

	return res;

}
//----------------------------------------------------------------------------------------------------------------------------------


