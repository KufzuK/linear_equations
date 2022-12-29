#ifndef SYSTEM_H
#define	SYSTEM_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>


typedef double data;



struct matrix_info;
typedef struct matrix_info info;




/// here general functions: ***************************************************
data** read_matrix(int n, int m);

void print_matrix(data** matrix, int n, int m);

void destruct(double** matrix, int lines);

double** copy_mat(double** matrix, int lines, int columns);

///                         ***************************************************







/// for determinant:        ***************************************************


double** to_triangle(data** matrix, int n);

double triangle_det(double** matrix, int n);


///                         ***************************************************








/// for Ghauss              ***************************************************     

double** triangle_expanded(double** matrix, int lines);


double** to_diagonal(double** matrix, int lines);


double* solve_diagonal(double** matrix, int lines);

///                         *************************************************** 








/// for Cramer              ***************************************************
// functions for calculating the determinant are required.

double** expand_mat(double** matrix, int lines, int except);


double det_expanded(double** matrix, int lines, int except);


double* solve_line_syst3(double** matrix, int lines);





#endif   // STACK.H
