
#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
tail(int fd, char* filepath, int x)
{
  int n, m, count;
  char *p, *q;
  memset(buf, 0, sizeof(char)*1024);
  if((fd = open(filepath, 0)) < 0){
    printf(1, "tail: cannot open %s\n", filepath);
    exit();
  }
  m = 0;
  count = 0;
  while((n = read(fd, buf+m, sizeof(buf)-m)) > 0){
    m += n;
    p = buf;
    while((q = strchr(p, '\n')) != 0){
      *q = 0;
      p = q+1;
      count++;
    }
    if(p == buf)
      m = 0;
    if(m > 0){
      m -= p - buf;
      memmove(buf, p, m);
    }
  }
  close(fd);

  if((fd = open(filepath, 0)) < 0){
    printf(1, "tail: cannot open %s\n", filepath);
    exit();
  }
  if(count <= x)
  {
    while((n = read(fd, buf, sizeof(buf))) > 0)
      write(1, buf, n);
    if(n < 0){
      printf(1, "tail: read error\n");
    }
    return;
  }
  
  m = 0;
  while((n = read(fd, buf+m, sizeof(buf)-m)) > 0){
    m += n;
    p = buf;
    while((q = strchr(p, '\n')) != 0){     
      count--;
      if(count < x)
      {
        *q = '\n';
        write(1, p, q+1 - p);
      }
      *q = 0; 
      p = q+1;
    }
    if(p == buf)
      m = 0;
    if(m > 0){
      m -= p - buf;
      memmove(buf, p, m);
    }
  }

}



int main(int argc, char *argv[])
{
  int fd, i, x=10;
  char c[512];
  char *num_str = c;

 if(argc <= 1){tail(0,"",10);exit();} i=1;

 if(argv[1][0]=='-'){ 
    strcpy(c,argv[1]);
    num_str=num_str+1;
    x= atoi(num_str);
    if(argc <= 2){tail(0,"",x);exit();}i=2;
 }

 for(; i < argc; i++){
       if((fd = open(argv[i], 0)) < 0){
       printf(1, "head: cannot open %s\n", argv[i]);
       exit();}
     tail(fd,argv[i],x);
    }
 close(fd);
 exit();
}
