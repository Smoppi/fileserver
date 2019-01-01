#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *frandom;
  int m;
  if(argc>=2)
  {
    frandom = fopen("/dev/urandom", "r");
    if(frandom == NULL) {
      perror("Error in opening /dev/urandom");
      return(-1);
    }
    for(m=atoi(argv[1]);m;m--)
      printf("%c", 32+fgetc(frandom)%95);
    fclose(frandom);
    if(argc != 3)
      printf("\n");
    return 1;
  }
  return 0;
}
