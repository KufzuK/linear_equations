#ifndef SYSTEM_H
#define	SYSTEM_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>


typedef double data;


typedef struct ready_matrix
{
	double** matr_ptr;
	double*  line_ptr;

	int         lines;
	int       columns;
	int           det;

} ready_mat;

struct  matrix_info;

typedef struct matrix_info       info;



/// here general functions: ***************************************************
data** read_matrix(int n, int m);

void print_matrix(data** matrix, int n, int m);

void destruct(double** matrix, int lines);

double** copy_mat(double** matrix, int lines, int columns);

///                         ***************************************************






/// general function for matrixes as structures

void print_matrix2(ready_mat* matr);
///                          **************************************************




/// for determinant:        ***************************************************


double** to_triangle(data** matrix, int n);

double triangle_det(double** matrix, int n);


///                         ***************************************************








/// for Ghauss              ***************************************************     

double** triangle_expanded(double** matrix, int lines);


double** to_diagonal(double** matrix, int lines);


double* solve_diagonal(double** matrix, int lines);

///                         *************************************************** 








/// for tests               ***************************************************



ready_mat* create_blank_matrix(int lines, int columns);

ready_mat* init_matrix(int lines);

void feel_diagonal(ready_mat* matr);

void rand_line_change(ready_mat* matr);

void change_matrix(ready_mat* matr);


///                         *************************************************** 







/// for Cramer              ***************************************************
// functions for calculating the determinant are required.

double** expand_mat(double** matrix, int lines, int except);


double det_expanded(double** matrix, int lines, int except);


double* solve_line_syst3(double** matrix, int lines);





#endif   // STACK.H
