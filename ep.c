/*Hamed Javidi
2738776
Date of creation: 2/6/2020
Date of modification 2/11/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

float stop_timer();
void start_timer();

int main(int argc, char * argv[]){
  pid_t cpid; 
  int status; 
  
	
  if(argc<2){
	printf("Enter an argument: like ./ep_crt 1024\n");
	return 1;
  }
		
  int size=atoi(argv[1])* 1024;
  char *buf= calloc(size, sizeof(char));
    
  start_timer();
  cpid=fork();
  if(cpid<0){
    printf("fork error\n");
    exit(1);
  }
  if(cpid==0){ //child
    for(int i=0;i<size; i+=1024){
      buf[i]='a'; 
    }
    exit(status);
  }
  else{ //parent
    waitpid(cpid,&status,0);
	float st=stop_timer();
    printf("Total time consumption is : %f\n",st);
  }  
return 0;
}


