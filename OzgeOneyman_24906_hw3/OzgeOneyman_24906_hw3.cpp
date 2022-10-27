

// OZGE ONEYMAN 24906

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <queue>
#include <semaphore.h>
using namespace std;

#define NUM_THREADS 10
#define MEMORY_SIZE 150

struct node
{
    int id;
    int size;
};


queue<node> myqueue; // shared que
pthread_mutex_t sharedLock = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_t server; // server thread handle
sem_t semlist[NUM_THREADS]; // thread semaphores

int thread_message[NUM_THREADS]; // thread memory information
char  memory[MEMORY_SIZE]; // memory size





void my_malloc(int thread_id, int size)
{
    //This function will add the struct to the queue
    node newqueue;
    newqueue.id = thread_id;
    newqueue.size = size;
    pthread_mutex_lock(&sharedLock);
    myqueue.push(newqueue);
    pthread_mutex_unlock(&sharedLock);
    
}

void * server_function(void *)
{
    //This function should grant or decline a thread depending on memory size.
    int start=0;
    int numofthreads=0;
    bool numofthreads_check = false;
    
    
    while (numofthreads_check == false) {
        if (myqueue.empty() == false) {
            pthread_mutex_lock(&sharedLock);
            numofthreads= numofthreads +1;
            node temp = myqueue.front();
            myqueue.pop();
                
            if (start + temp.size >= MEMORY_SIZE){
                thread_message[temp.id]=-1;
            }
            else if (start + temp.size < MEMORY_SIZE) {
                int newstart= start + temp.size + 1;
                thread_message[temp.id] = start;
                start = newstart;
            }
                sem_post(&(semlist[temp.id]));
                pthread_mutex_unlock(&sharedLock);
            if (numofthreads == NUM_THREADS) {
                numofthreads_check = true;
            }
        }
    }
    return NULL;

}

void * thread_function(void * id)
{
    //This function will create a random size, and call my_malloc
    int size = rand() % ((MEMORY_SIZE/6) +1);
    int * my_id = (int *)id;
    
    my_malloc(*my_id,size);
    sem_wait(&(semlist[*my_id]));
    pthread_mutex_lock(&sharedLock);

    
    if(thread_message[*my_id] == -1)
    {
        printf("For Thread %d: There is not enough space. \n", *my_id);
    }
    else
    {
        if(*my_id == 0){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '0';
                i++;
            }
        }
        else if(*my_id == 1){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '1';
                i++;
            }
        }
        else if(*my_id == 2){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '2';
                i++;
            }
        }
        else if(*my_id == 3){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '3';
                i++;
            }
        }
        else if(*my_id == 4){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '4';
                i++;
            }
        }
        else if(*my_id == 5){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '5';
                i++;
            }
        }
        else if(*my_id == 6){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '6';
                i++;
            }
        }
        else if(*my_id == 7){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '7';
                i++;
            }
        }
        else if(*my_id == 8){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '8';
                i++;
            }
        }
        else if(*my_id == 9){
            
            int i=0;
            while (i<= size) {
                
                
                memory[thread_message[*my_id]+i] = '9';
                i++;
            }
        }

    }
    
   pthread_mutex_unlock(&sharedLock);
   return NULL;
    //Block
    //Then fill the memory with id's or give an error prompt
}

void init()
{
    pthread_mutex_lock(&sharedLock);    //lock
    for(int i = 0; i < NUM_THREADS; i++) //initialize semaphores
    {sem_init(&semlist[i],0,0);}
    for (int i = 0; i < MEMORY_SIZE; i++)    //initialize memory
      {char zero = '0'; memory[i] = zero;}
       pthread_create(&server,NULL,server_function,NULL); //start server
    pthread_mutex_unlock(&sharedLock); //unlock
}



void dump_memory()
{
 // You need to print the whole memory array here.
    int i = 0;
    while (i < MEMORY_SIZE)
    {
        cout<< memory[i] << " ";
        i++;
    }
}

int main (int argc, char *argv[])
 {

     int thread_id [NUM_THREADS] = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 };  //You need to create a thread ID array here

     init();    // call init
    
     pthread_t p0 , p1 , p2 , p3 , p4 , p5 , p6, p7, p8 , p9 ;
        //You need to create threads with using thread ID array, using pthread_create()

     pthread_create(&p0, NULL, thread_function, (void*)&thread_id[0]);
     pthread_create(&p1, NULL, thread_function, (void*)&thread_id[1]);
     pthread_create(&p2, NULL, thread_function, (void*)&thread_id[2]);
     pthread_create(&p3, NULL, thread_function, (void*)&thread_id[3]);
     pthread_create(&p4, NULL, thread_function, (void*)&thread_id[4]);
     pthread_create(&p5, NULL, thread_function, (void*)&thread_id[5]);
     pthread_create(&p6, NULL, thread_function, (void*)&thread_id[6]);
     pthread_create(&p7, NULL, thread_function, (void*)&thread_id[7]);
     pthread_create(&p8, NULL, thread_function, (void*)&thread_id[8]);
     pthread_create(&p9, NULL, thread_function, (void*)&thread_id[9]);


     //You need to join the threads
     pthread_join(p0, NULL);
     pthread_join(p1, NULL);
     pthread_join(p2, NULL);
     pthread_join(p3, NULL);
     pthread_join(p4, NULL);
     pthread_join(p5, NULL);
     pthread_join(p6, NULL);
     pthread_join(p7, NULL);
     pthread_join(p8, NULL);
     pthread_join(p9, NULL);
     
          
     dump_memory(); // this will print out the memory
     
     printf("\nMemory Indexes:\n" );
     for (int i = 0; i < NUM_THREADS; i++)
     {
         printf("[%d]" ,thread_message[i]); // this will print out the memory indexes
     }
     printf("\nTerminating...\n");
 }
