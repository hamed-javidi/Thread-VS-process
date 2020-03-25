/*Hamed Javidi
2738776
Date of creation: 2/6/2020
Date of modification 2/11/2020
*/
#include <stdio.h>
#include<sys/time.h>
static struct timeval start_time,stop_time;

void start_timer(){	
	//unit in second
	gettimeofday(&start_time,(struct timezone*)NULL);
}
float stop_timer(){
	gettimeofday(&stop_time,(struct timezone*)NULL);
	float elapsed_sec= stop_time.tv_sec - start_time.tv_sec + (stop_time.tv_usec - start_time.tv_usec ) / 1000000.0;
	return elapsed_sec;
}


