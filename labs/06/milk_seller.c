//Omar Alejandro Balboa Lara
//A00825034
//Lab06

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

int averageBottles = 0;
int totalBottles = 1000;
int bottlesSold = 0;
int seller[5];
int sellers=5;

int rando[5];
bool t[6] = {false,false,false,false,false,false};

pthread_mutex_t mutex;

void sellBottles(intptr_t *t_id){
	intptr_t t_id1 = (intptr_t)t_id;
	
	int sell=t_id1;
	for(int i=1; i<6 || t[sell]!=true; i++){
		if(rando[i-1]+seller[sell] <=200 && rando[i-1]!=0){
			seller[sell] += rando[i-1];
			bottlesSold += rando[i-1];
			rando[i-1] = 0;
			printf("Seller number %d: %d bottles \n", sell, seller[sell]);
			t[sell] = true;
			break;
		}
		t[sell]=true;	
	}	
}

void *threadFunc(void *i){
	intptr_t t_id = (intptr_t) i;
	
	pthread_mutex_lock(&mutex);

	if(bottlesSold < 1000 && t[t_id] == false){
		sellBottles((intptr_t *)t_id);
	}
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
}

void generateRandom(){
	for(int i=0; i<5; i++){
		rando[i] = (rand()%(200)+1);
	}	
}

int main(void){
	pthread_mutex_init(&mutex, NULL);
	srand(time(0));
	for(int j=0; j<5; j++){
		generateRandom();
		for(int x=1; x<=5; x++){
			t[x]=false;
		}
		printf("After the customer number %d each seller has sold: \n", j+1);
		pthread_t threads[sellers];
		
		for(int i =0; i<sellers; i++){
			pthread_create(&threads[i],NULL,threadFunc,(void *)(intptr_t)(i+1));		
		}
		
		for(int i=0; i<sellers; i++){
			pthread_join(threads[i],NULL);
			
		}
	printf("\n");
	}
	printf("Total amount of bottles sold for each seller: \n");
	for(int i=0; i<sellers; i++){
		printf("Seller %d: %d bottles \n",i+1, seller[i+1]);
	}
	averageBottles = bottlesSold/5;
	printf("\n");
	printf("Total of bottles sold is %d of %d in stock \n",bottlesSold, totalBottles);
	printf("The average number of bottles sold for each seller is %d \n", averageBottles);
	return 0;
}
