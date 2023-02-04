#include "systems.h"


int main()
{
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	//srand(time(NULL));
	
	
	int lines   = 0;

	scanf("%d \n", &lines);
	
	if (lines < 1)
		return 0;

	ready_mat* matr = read_matrix(lines, lines + 1);

	
	#ifdef Cramer
	double* res1 = NULL;
	res1 = solve_line_syst3(matrix, lines);
	
	if (res1 == NULL)
	{
		printf("NO");
		//return 0;
	}
	else
	{
		printf("first option\n");	
	

		for (int i = 0; i < lines; i++)
		{
			printf("%lg\n", res1[i]);
		}
	}

	free(res1);

	#endif

	/*
	#ifndef Cramer
		
	printf("right answers\n");

	double** mat = to_diagonal(matrix, lines);
	if (mat == NULL)
	{
		printf ("NO, everything bad. Either too many equtions, or no real sollution\n");
		///case of n equations for n - 1 variables will be considered later
		return 0;
	}
	
	double* res2 = solve_diagonal(mat, lines);	

	destruct(matrix, lines);
	

	for (int i = 0; i < lines; i++)
	{
		printf("%lg\n", res2[i]);
	}

	free(res2);
	#endif    // diagonal
*/


/*
	//ready_mat* matr = init_matrix(4);
	ready_mat* matr = init_matrix(4);
	//printf("%d", matr->lines);
	printf("\n");
	
	print_matrix2(matr);

	printf("\n");
	change_matrix(matr);
	printf("\n");
	print_matrix (matr->matr_ptr, matr->lines, matr->columns);
	
	destruct(matr->matr_ptr, matr->lines);
	free(matr);	
*/

	solve_syst(matr);
//	print_mass(matr->sollution, matr->lines);
	//destruct

	/*for (int i = 0; i < matr->lines; i++)
	{
		printf("%lg \n", matr->sollution[i]);
	}*/

	print_vline(matr->sollution, matr->lines);

	gettimeofday(&stop, NULL);
	printf("time %lu микросекунд \n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	
	return 0;
}
