#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void tail(int fd, int x)
{
  int i, n, p, l=0;

 if((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
	if(buf[i] == '\n'){l++;if(l>=x){p=i+1;}}
    }

    for(;p<=n;p++){
        if(buf[p]!='\n'){printf(1,"%c",buf[p]);}
        else{printf(1,"\n");}
      }
    }

  if(n < 0){printf(1, "tail: read error\n");exit();}
}

int main(int argc, char *argv[])
{
  int fd, i, x=10;
  char c[512];
  char *num_str = c;

 if(argc <= 1){tail(0, 10);exit();} i=1;

 if(argv[1][0]=='-'){ 
    strcpy(c,argv[1]);
    num_str=num_str+1;
    x= atoi(num_str);
    if(argc <= 2){tail(0,x);exit();}i=2;
 }

 for(; i < argc; i++){
       if((fd = open(argv[i], 0)) < 0){
       printf(1, "tail: cannot open %s\n", argv[i]);
       exit();}
     tail(fd,x);
    }
 close(fd);
 exit();
}
