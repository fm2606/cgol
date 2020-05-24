# Conway's Game of Life

An exercised "assigned" in CI Tutor for learning MPI programming:  https://www.citutor.org/content.php?cid=1295

cgol.c -- rough draft that prints out matrix as 1's and 0's.  It doesn't use ncurses and just uses printf to print matrices to the screen

cgol_nc.c -- using cgol.c as base adds ncurses to print out the game board.  Replaces 1s with asterisks and spaces for 0s.

compile:\
gcc -o cgol cgol.c -lncurses\
or\
gcc -o cgol_nc cgol_nc.c -lncurses\
