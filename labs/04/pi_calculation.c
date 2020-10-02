//Omar Alejandro Balboa Lara
//A00825034
//Lab04
//Link to the graphic: https://docs.google.com/document/d/1DWtpStIKstbufmgs6wdJh5gaJgrOTmb8jtCX96GW5v8/edit

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


#define POINTS 10000
#define SEED 35791246

double numerator;
double denominator;
double pi;
int num_threads; //number of threads to create
long points_per_thread; //point for each thread
long inside = 0;

void *monteCarlo(void *t_id){
	double x;
	double y;
	double z;
	int *count = (int *)malloc(sizeof(int)); //num of points in 1st quadrant of unit circle
	int i;
	
	//initialize random numbers
	*count =0;
	//unsigned int random = rand();
	srand(SEED);
	for(i = 0; i < points_per_thread; i++){
	
		//create random number between 0 and 1
		double xrandom_number;
		double yrandom_number;
		xrandom_number = rand() / ((double)(unsigned) RAND_MAX +1);
		x = xrandom_number;
		yrandom_number = rand() / ((double)(unsigned) RAND_MAX +1);
		y = yrandom_number;
		z = pow(x,2) + pow(y,2);
		
		if(z <= 1){
			*count += 1;
		}
	}
	
	pthread_exit((void *) count);
}

int main(int argc, const char *argv[]){
	//starts the clock
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	//If the user does not give the number of threads
	if(argc != 2){
		printf("Threads were not specified\n");
		return 1;
	}
	
	num_threads=atoi(argv[1]);
	//If the user does not give a number higher than 0
	if(num_threads == 0){
		printf("Number of threads has to be greater than 0 \n");
		return 0;
	}
	
	points_per_thread = POINTS/num_threads; //Look for the amount of points for each thread
	pthread_t threads[num_threads];
	
	for(int t = 0; t < num_threads; t++){
		if(pthread_create(&threads[t], NULL, monteCarlo, (void *)(intptr_t) t)){
			printf("ERROR CREATING THREADS \n");
			return 1;
		}
	}
	
	void *count_thread;
	
	for(int t = 0; t < num_threads; t++){
		pthread_join(threads[t], &count_thread);
		inside += * (long *) count_thread;
	}
	
	numerator = (4.00 * (double)inside );
	denominator = ((double)points_per_thread * num_threads);
	pi = numerator / denominator;
	printf("PI: %f \n", pi);

	//ends the clock	
	end = clock();
	cpu_time_used = ((double)(end - start)) /  CLOCKS_PER_SEC;
	printf("Time used with %d threads is %f \n",num_threads, cpu_time_used);
	
	return 0;
}
