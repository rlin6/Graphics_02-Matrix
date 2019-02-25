/*==========================================
  A matrix will be a 4xN array of doubles
  Each row will represent an [x, y, z, 1] point.
  For multiplication purposes, consider the rows like so:
  x0  x1      xn
  y0  y1      yn
  z0  z1  ... zn
  1  1        1
  ==========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m

print the matrix such that it looks like
the template in the top comment
*/
void print_matrix(struct matrix *m) {
  for (int r = 0; r < m->rows; r++) {
    for (int c = 0; c < m->cols; c++) {  //iterate through each row and column
      printf("%0.2f ", m->m[r][c]);  //print double value in that spot up to 2 decimals
    }
    printf(" \n");  //move to next line
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  for (int r = 0; r < m->rows; r++) {
    for (int c = 0; c < m->cols; c++) {  //iterates through each row and column 
      if (r == c) {  //if on the diagonal, set to 1
	      m->m[r][c] = 1;
      }
      else {  //otherwise turn to 0 
	      m->m[r][c] = 0;  
      }
    }
  }
}

/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b

multiply a by b, modifying b to be the product
a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {

  struct matrix *temp = new_matrix(a->rows,b->cols);
  
  for (int r = 0; r < temp->rows; r++) {  //first row of dot products
    int dot = 0;  
    for (int x = 0; x < b->rows; x++) {
      for (int c = 0; c < a->cols; c++) {  //iterate through each row and column
	      dot += (a->m[r][c]) * (b->m[c][x]);  //get the dot product for that spot 
      }
      temp->m[r][x] = dot;  //set the new value
      dot = 0;  //reset dot product
    }
  }
  copy_matrix(temp,b);  //change b into the new matrix
}

/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}
