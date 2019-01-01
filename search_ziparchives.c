#include <stdio.h>
#include <stdlib.h>

char main( int argc, char *argv[] )
{
  char *archive_name = calloc(4096, sizeof(char));
  char *buffer = calloc(4096, sizeof(char));
  size_t n;
  size_t m;
  size_t l;
  char c;
  char *keyword = argv[2];
  char archive_word = 65; // A
  char lines2 = 101; // e
  int kw_length;
  FILE * fp;

  if(argc!=3) return 0;

  for(m=0;keyword[m];m++)
    if(keyword[m] >= 97 && keyword[m] <= 124) keyword[m] -= 32;
  kw_length=m-1;

  printf("Keyword: %s<br>", keyword);

  fp = fopen(argv[1], "r");

  while(1)
  {
    archive_end:;
    c=fgetc(fp);
    if(c==-1) // EOF
    {
      printf("\nEnd of search results.\n");
      return 1;
    }
    if(c == archive_word)
    {
      fgets(archive_name, 4096, fp);
      while(1)
      {
        nextrow:;
        if(fgets(buffer, 4096, fp))
        {
          for(n=0;buffer[n];n++);
          if(buffer[0] == lines2)
            goto archive_end;
          else
          {
            for(;n;n--)
            {
              if(buffer[n] >= 97 && buffer[n] <= 124) buffer[n] -= 32;
              if(buffer[n] == keyword[0])
              {
                for(m=kw_length;m; m--)
                {
                  if(buffer[n+m] >= 97 && buffer[n+m] <= 124) buffer[n+m] -= 32;
                  if(buffer[n+m] != keyword[m]) break;
                }
                if(!m)
                {
                  printf("Archive: <a href = \"lataus.php?dir=%s\">%s</a><br>", archive_name, archive_name);
                  printf("%s<br>", buffer);
                  goto nextrow;
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
