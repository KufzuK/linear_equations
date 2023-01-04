#include "systems.h"


int main()
{
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	
	
	
	int lines   = 0;

	scanf("%d \n", &lines);
	
	if (lines < 1)
		return 0;

	data** matrix = read_matrix(lines, lines + 1);

	
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


	#ifndef Cramer
		
	printf("right answers");

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

	gettimeofday(&stop, NULL);
	printf("time %lu микросекунд \n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	
	return 0;
}
