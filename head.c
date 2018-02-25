#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void head(int fd, int x)
{
  int i, n, l=0;

  while((n = read(fd, buf, sizeof(buf))) > 0 && l<x)
  {
    for(i=0;i<=n && l<x;i++)
    {
      if(buf[i]!='\n'){printf(1,"%c",buf[i]);}
      else{printf(1,"\n");l++;}
    }
  }

  if(n < 0){printf(1, "head: read error\n");exit();}
}

int main(int argc, char *argv[])
{
  int fd, i, x=10;
  char c[512];
  char *num_str = c;

 if(argc <= 1){head(0, 10);exit();}
 i=1;
 if(argv[1][0]=='-'){
    
    strcpy(c,argv[1]);
    num_str=num_str+1;
    x= atoi(num_str);
    if(argc <= 2){head(0,x);exit();}
    i=2;
 }

 for(; i < argc; i++)
    {
       if((fd = open(argv[i], 0)) < 0){
          printf(1, "head: cannot open %s\n", argv[i]);
          exit();}
       head(fd,x);
    }
 close(fd);
 exit();
}
