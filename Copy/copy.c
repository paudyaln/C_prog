/******************************************************
 *FILENAME: copy.c
 *DES:
 *	Copy content of one file to another
 *
 *Author: Nischal Paudyal
 *2019
 **********************************************************/
#include <stdio.h>
#include <x86_64-linux-gnu/sys/types.h>
#include <x86_64-linux-gnu/sys/stat.h>
#include <x86_64-linux-gnu/sys/fcntl.h>
#include <x86_64-linux-gnu/sys/syscall.h>
#define PERMS 0666

main(){
  char *infile;
  char *outfile;
  int input, output, n;
  char buf[BUFSIZ];

  printf("Enter Source file path: ");
  gets(&infile);

  if ((input = open(infile, O_RDONLY, S_IRUSR)) == -1)
      fprintf(stderr,"cp: can't open %s", infile);
      printf("input ok\n");

  printf("Enter destination file path: ");
  gets(&outfile);

  if ((output = creat(outfile, PERMS)) == -1)
      fprintf(stderr, "cp: can't create %s", outfile, PERMS);
  printf("output ok\n");

  while ((n = read(input, buf, BUFSIZ)) > 0)
      if (write(output, buf, n) != n)
       fprintf("cp: write error on file %s", outfile);
  close(output);
  return 0;
  }
