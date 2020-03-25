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
#define N 160

float stop_timer();
pthread_barrier_t barrier;
int *arg;
void start_timer();
int a[N][N], b[N][N], c[N][N];
typedef struct _workRange{	
	int tid;
	int start;
	int end;
}workRange;
typedef struct _workRange *WorkRange;
WorkRange *winfo;

void * worker(void *arg){
	const int tid=*(int*)arg;
	//printf("TID is %i\n", tid);
	for(int i = winfo[tid]->start; i <= winfo[tid]->end; i++)
		for(int j=0; j < N; j++){
			c[i][j]=0;
			for(int k=0; k<N; k++)
				c[i][j]+=a[i][k]*b[k][j];
		}
	
	//printf("job is finished%i\n", tid);
	pthread_barrier_wait(&barrier);	
}



int main(int argc, char * argv[]){	
	if(argc<2){
		printf("Enter number of threads: like ./param_mm 16\n");
		return 1;
  }	
	int ptNum=atoi(argv[1]);	
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++){
			a[i][j]=1;
			b[i][j]=1;
		}
	 	
	pthread_barrier_init(&barrier,NULL,ptNum+1);
	pthread_t child[ptNum];
	
	winfo= calloc(ptNum, sizeof(WorkRange));	
	for(int i=0;i<ptNum;i++){
		winfo[i]= calloc(1, sizeof(struct _workRange));		
		winfo[i]->tid=i;
		winfo[i]->start= i * (N/ptNum);
		winfo[i]->end=((i+1)*(N/ptNum))-1;
		printf("tid= %i, start=%i, end=%i\n",winfo[i]->tid ,winfo[i]->start,winfo[i]->end );
	}
	start_timer();	
	for(int i=0;i<ptNum;i++){		
		//(child+sizeof(pthread_t)*i)
		if(pthread_create(&child[i],NULL,worker,&winfo[i]->tid ) != 0)
			printf("Cannot create pthread \n");    
		
	}

	pthread_barrier_wait(&barrier);	
	printf("Total time consumption is : %f\n", stop_timer());
	printf("To see whether result is correct write 1 as a second argument like: ./para_mm 16 1\n");
	
	/* to see the output matrix to make sure the multiplication is done correctly*/
	if( argc>2 && atoi(argv[2])){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				printf("%i ",c[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}


