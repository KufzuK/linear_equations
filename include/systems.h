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
	double* sollution;

	int         lines;
	int       columns;
	int           det;

} ready_mat;

struct  matrix_info;

typedef struct matrix_info       info;



/// here general functions: ***************************************************
ready_mat* read_matrix(int n, int m);

void print_matrix(ready_mat* matr);

void destruct_2d(double** matrix, int lines);

void destruct(ready_mat* matr);

ready_mat* copy_mat(ready_mat* matr);

void print_vline(double* column, int lines);

//void print_column(double* column, int lines)
///                         ***************************************************






/// general function for matrixes as structures

void print_matrix2(ready_mat* matr);
///                          **************************************************




/// for determinant:        ***************************************************


ready_mat* to_triangle(ready_mat* matr);

#if(0)
double triangle_det(ready_mat* matr);
#endif

///                         ***************************************************








/// for Ghauss              ***************************************************     

ready_mat* triangle_expanded(ready_mat* matr);


ready_mat* to_diagonal      (ready_mat* matr);


double* solve_diagonal		(ready_mat* matr);


void solve_syst             (ready_mat* matr);
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

ready_mat* expand_mat(ready_mat* matr, int except);


double det_expanded(ready_mat* matr, int except);


double* solve_line_syst3(double** matrix, int lines);





#endif   // STACK.H
