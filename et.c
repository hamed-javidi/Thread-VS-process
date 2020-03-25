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
#include <pthread.h>

float stop_timer();
void start_timer();

char *buf;
int size;

void foo(){
	/*for(int i=0;i<size; i+=4096){
      buf[i]='a'; 
    }*/
	buf[0]='a';
}

int main(int argc, char * argv[]){   
  
  if(argc<2){
	printf("Enter an argument: like ./et_crt 1024\n");
	return 1;
  }
  size=atoi(argv[1])* 1024;
  buf= calloc(size, sizeof(char));
  pthread_t child1;  
  start_timer();
  
  if(pthread_create(&child1,NULL,(void *)foo,NULL) != 0){
    printf("Cannot create pthread \n");    
  }
  
  pthread_join(child1 , NULL);
  float st=stop_timer();
  printf("Total time consumption of Pthread is : %f\n", st );  
  return 0;
}


