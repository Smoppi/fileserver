#include <stdio.h>
#include <stdlib.h>

char main( int argc, unsigned char *argv[] )
{
  unsigned char file_name[4096];
  unsigned char buffer[4096];
  unsigned int n;
  unsigned int m;
  unsigned char *keyword = argv[2];
  unsigned char end[27] = "--------- THE END ---------";
  FILE * fp;


  if(argc!=3) return 1;
  if(!keyword[0]) return 2;

  for(m=0;keyword[m];m++) if(keyword[m] >= 97 && keyword[m] <= 124) keyword[m] -= 32;

  printf("Keyword: %s<br>", keyword);

  fp = fopen(argv[1], "r");

  while(1)
  {
    nextrow:;
    fgets(buffer, 4096, fp);
    // if buffer[28] is a null character
    if(!buffer[28])
    {
      for(n=26;n;n--)
        if(buffer[n] != end[n]) break;
      if(!n)
      {
        printf("<br>End of results.\n");
        return 0;
      }
    }

    for(n=0,m=0;buffer[n];n++,m++)
    {
      if(buffer[n] == 47)
      {
        m=-1;
        continue;
      }
      file_name[m] = buffer[n];
    }
    file_name[m] = 0;

    for(n=0;file_name[n];n++)
      if(file_name[n] >= 97 && file_name[n] <= 124)
        file_name[n] -= 32;

    for(n=0,m=0;file_name[n];n++)
    {
      if(file_name[n] == keyword[m])
        for(m=1,n++;keyword[m];m++,n++)
          if(keyword[m] != file_name[n]) break;
      if(!keyword[m])
      {
        printf("<a href = \"lataus.php?dir=%s\">%s</a><br>\n", &buffer[1], &buffer[1]);
        goto nextrow;
      }
    }
  }
  return 3;
}
