#include <stdio.h>
#include <stdlib.h>

typedef double data;

#if(0)
typedef struct
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
	for (int i = 0; i < lines; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

//------------------------------------------------------------------------------------------------------


double** to_triangle(data** matrix, int n)
{
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
				matrix[i][k] -= koef *  matrix[j][k];
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
			{
				if (k == exception)
				{
					k = lines;
				}
				matrix[i][k] -= koef *  matrix[j][k];
			}

		}


	}
	return matrix;
}

#endif


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
	
	mat = to_triangle(mat, lines);

	double det = triangle_det(mat, lines);

	destruct(mat, lines);	
	return det;
	
}

//-------------------------------------------------------------------------------------------------------------------------------

double* solve_line_syst3(double** matrix, int lines)
{
	double d  = det_expanded(matrix, lines, 3);

	double d0 = det_expanded(matrix, lines, 0);
	double d1 = det_expanded(matrix, lines, 1);
	double d2 = det_expanded(matrix, lines, 2);
	
	if (d == 0)
		return NULL;

	
	double x1 = d0 / d;
	double x2 = d1 / d;
	double x3 = d2 / d;
	
	double* res = NULL;
	res = (double*) calloc(3, sizeof(double));
	
	res[0] = x1;	
	res[1] = x2;
	res[2] = x3;
	
	
	return res;
}


//----------------------------------------------------------------------------------------------------------------------------------

int main()
{
	int lines   = 3;
	int columns = 3;
	data** matrix = read_matrix(lines, columns + 1);
	
	double* res = NULL;
	res = solve_line_syst3(matrix, lines);
	
	if (res == NULL)
	{
		printf("NO");
		return 0;
	}
	
	for (int i = 0; i < 3; i++)
	{
		printf("%lg\n", res[i]);
	}	

	destruct(matrix, lines);
	free (res   );
}
