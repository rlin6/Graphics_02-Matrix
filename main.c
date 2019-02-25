#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *m1;
  struct matrix *m2;
  struct matrix *m3;

  edges = new_matrix(4, 4);
  m1 = new_matrix(4,4);
  m2 = new_matrix(4,2); 
  m3 = new_matrix(4,4);

  printf("\nTesting add_edge. Adding (1,2,3) and (4,5,6) m2 is created only 4 x 2 to test growth. m2 =\n");
  add_edge(m2, 1, 2, 3, 4, 5, 6);
  print_matrix(edges);

  printf("\nTesting ident. m1 =\n");
  ident(m1);
  print_matrix(m1);

  printf("\nTesting matrix multiplication m1 * m2 =\n");
  matrix_mult(m1, m2);
  print_matrix(m2);

  printf("\nTesting matrix multiplication m3 =\n");
  add_edge(m3, 1, 2, 3, 4, 5, 6);
  add_edge(m3, 7, 8, 9, 10, 11, 12);
  print_matrix(m3);
  
  printf("\nTesting matrix multiplication m3 * m2 =\n");
  
  matrix_mult(m3, m2);
  print_matrix(m2);

  free_matrix(m1);
  free_matrix(m2);
  free_matrix(m3);


  color c;
  c.red = 0;
  c.green = 0;
  c.blue = MAX_COLOR;

  clear_screen(s);

  for (int i = 0; i < 1000; i++) {
    add_edge(edges, 100 + cos(M_PI * i) + i, 200 + sin(M_PI * i) - i, 0, 300 + cos(M_PI * i) - i, 400 + sin(M_PI * i) + i, 0);
  }

  draw_lines(edges, s, c);

  free_matrix(edges);

  save_extension(s, "matrix.png");
  display(s); 
}  
