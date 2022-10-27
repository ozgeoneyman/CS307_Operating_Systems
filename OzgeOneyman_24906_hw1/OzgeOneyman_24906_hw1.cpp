/* OZGE ONEYMAN 24906 HW1*/

#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdio.h>   /* for printf fn */

using namespace std;

vector <vector <int> > M (2, vector<int> (50,0)); /* A global matrix, row=2 col=50, and cells equal to zero */

int remainingSeats = 100;
int turn = 0;

/* Function for printing matrix */
void printSeats(){

	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[0].size(); j++)
		{
			printf("%d ",M[i][j]);
		}
		printf("\n");
	}
	
}

void * reservationAgency1(void *)
{
	while(true)
	{

	  int x = rand() % 2; /* Two random numbers for row and column */
	  int y = rand() % 50;

	  while(turn != 0) {}

	  printf("Agency 1 Entered Critical Region \n");

	  if(M[x][y] == 0)   /* checking the cells */
	  {
	  	M[x][y] = 1;
	  	int seatNumber = x*50+y;
	  	printf("Seat Number %d is reserved by Agency 1 \n", seatNumber+1); /* plus one bec. row and col nums start from zero */
	  	remainingSeats--;
	  }
	  
	  printf("Agency 1 Exit Critical Region \n\n");
	  
	  turn = 1;

	  if(remainingSeats == 0)
	  {
	  	pthread_exit(0);  /* it ends the thread */
	  }

	}

}


void * reservationAgency2(void *)
{
	while(true)
	{

	  int x = rand() % 2; /* Two random numbers for row and column */
	  int y = rand() % 50;

	  while(turn != 1) {}

	  printf("Agency 2 Entered Critical Region \n");

	  if(M[x][y] == 0)  /* checking the cells */
	  {
	  	M[x][y] = 2;
	  	int seatNumber = x*50+y;
	  	printf("Seat Number %d is reserved by Agency 2 \n", seatNumber+1); /* plus one bec. row and col nums start from zero */
	  	remainingSeats--;
	  }
	  
	  printf("Agency 2 Exit Critical Region \n\n");

	  turn = 0;

	  if(remainingSeats == 0)
	  {
	  	pthread_exit(0);  /* it ends the thread */
	  }

	}

}

int main(){

    srand((unsigned) time(NULL));   /* for generating similar random nums */

	pthread_t TravelAgency1, TravelAgency2;
	
	pthread_create (&TravelAgency1, NULL, reservationAgency1, NULL);
	pthread_create (&TravelAgency2, NULL, reservationAgency2, NULL);

	pthread_join(TravelAgency1, NULL);
	pthread_join(TravelAgency2, NULL);

	  	
  	printf("No seats Left \n\n");
  	printf("Plane is full: \n\n");
  	printSeats();    /* print the plane */

	return 0;
}
