/*
 * Conway's Game of Life
 *
 * Serial version
 *
 * written by: Curt Lewis
 * date: 2020-05-18
 *
 * An exercise "assigned" on CI_TUTOR Introduction to MPI
 * https://www.citutor.org/content.php?cid=1295
 *
 * Added ncurses to visualize
 *
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

void print_matrix(int **, int, int, int, int);
void init_matrix(int **, int, int, int);

/*
 * Prints an m x n matrix
*/
void print_matrix(int **mat, int i_beg, int i_end, int j_beg, int j_end) {

  int i, j;
  char c;

  for(i = i_beg; i < i_end; i++) {
    for(j = j_beg; j < j_end; j++) {
      if ( mat[i][j] ) {
        c = '*';
      } else {
        c = ' ';
      }
      mvprintw(i, j, "%c ",c);
    }
    mvprintw(i, j, "\n");
  }

  return; 
}

/*
 * Initialize a matrix to the given value, val
*/
void init_matrix(int **mat, int val, int ni, int nj) {
  
  int i, j;

  for(i = 0; i < ni; i++) {
    for(j = 0; j < nj; j++) {
      mat[i][j] = val;
    }
  }
  
}

int main() {

  int i, j, g;
  int NI = 24;                  // row size of game board
  int NJ = 48;                  // col size of game board
  int ni = NI + 2;              // row size including ghost cells 
  int nj = NJ + 2;              // col size including ghost cells
  int value;                    // number of neighbors for a given cell
  const int STEPS = 100;        // number of "generations"
  time_t t;                     // used to seed random number

  // old and new will be ni x nj matrices 
  int ** old;
  int ** new;

  // ncurses functions
  initscr();
  curs_set(0);
  noecho();

  // allocate rows
  old = malloc( ni * sizeof( int * ));
  new = malloc( ni * sizeof( int * ));

  // allocate the columns for each row
  for(i = 0; i < ni; i++) {
    old[i] = malloc( nj * sizeof( int ));
    new[i] = malloc( nj * sizeof( int ));
  }

  init_matrix(new, 0, ni, nj);

  // 1st define NI x NJ matrix (i.e. the inside matrix)
  // and initialize cells to either 0 or 1.
  srand( (unsigned) time(&t) );
  for(i = 1; i <= NI; i++ ) {
    for( j = 1; j <= NJ; j++ ) {
      old[i][j] = rand() & 1;
    }
  }

  // run thru the generations
  for(g = 0; g < STEPS; g++) {
    
    // set the "ghost" cells equal to their corresponding "current" cell value

    // the corner positions:
    old[0][0] = old[NI][NJ];
    old[0][nj-1] = old[NI][1];
    old[ni-1][nj-1] = old[1][1];
    old[ni-1][0] = old[1][NJ];

    // set the top and bottom ghost rows 
    for(j = 1; j < nj; j++) {
      old[0][j] = old[NI][j];
      old[ni-1][j] = old[1][j];
    }

    // set the 1st and last ghost columns
    for(i = 1; i < ni; i++) {
      old[i][0] = old[i][NJ];
      old[i][nj-1] = old[i][1];
    }

    for(i = 1; i < ni - 1; i++) {
      for( j = 1; j < nj - 1; j++ ) {
        // sum up all the neighbors
        value = old[i-1][j-1] + old[i-1][j] + old[i-1][j+1] + // upper neighbors
                old[i][j-1] + old[i][j+1] +                   // side neighbors
                old[i+1][j-1] + old[i+1][j] + old[i+1][j+1];  // bottom neighbors

        switch( value ) {
          case 3:
            new[i][j] = 1;
            break;

          case 2:
            new[i][j] = old[i][j];
            break;

          default:
            new[i][j] = 0;
        }

      }
    }

    print_matrix(new, 1, ni - 1, 1, nj - 1);
    mvprintw(i + 2, 0, "Generation %d of %d", (g + 1), STEPS);
    refresh();
    sleep(1);

    // for the next generation "old" now equals "new"
    for(i = 0; i < ni; i++) {
      for(j = 0; j < nj; j++) {
        old[i][j] = new[i][j];
      }
    }
  
  }

  // all generations are done 
  // ncurses wait for user to press a key
  getch();
  endwin();

  return 0;
}
