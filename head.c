#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void head(int fd, int x)
{
  int i, n;
  int l;

  l = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0 && l<x)
  {

    for(i=0;i<=n && l<x;i++)
    {
      if(buf[i]!='\n')
      {
      	printf(1,"%c",buf[i]);
      }
      else
      {
      	printf(1,"\n");
      	l++;
      }
    }
  }

  if(n < 0)
  {
    printf(1, "head: read error\n");
    exit();
   }
}

int main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1)
  {
    head(0, 10);
    exit();
  }

  else if(argc==2)

  {
    for(i=1; i < argc; i++)
      {
        if((fd = open(argv[i], 0)) < 0){
          printf(1, "head: cannot open %s\n", argv[i]);
          exit();
        }
        head(fd,10);
        close(fd);
      }
  }


  else if(argc==3)
  {
    char c[512];
    strcpy(c,argv[1]);
    char *num_str = c;
    num_str=num_str+1;
    int x= atoi(num_str);


    for(i=2; i < argc; i++)
    {
      if((fd = open(argv[i], 0)) < 0){
        printf(1, "head: cannot open %s\n", argv[i]);
        exit();
      }
      head(fd,x);
      close(fd);
    }
  }

  else
  {
    printf(1,"head: syntax error");
  }
    exit();
  
}
