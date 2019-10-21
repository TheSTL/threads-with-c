/**
 * Condition variables program.
 * Ashu Deshwal (c) 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *function1();
void *function2();
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
int condition = 0;

int main()
{
    pthread_t thread1, thread2;
    int threadError1, threadError2;

    threadError1 = pthread_create(&thread1, NULL,
    &function1, NULL);


    if (threadError1) {
    printf("Thread creation failed: %d\n",threadError1);
    }

    threadError2 = pthread_create(&thread2, NULL,
    &function2, NULL);

    if (threadError2) {
    printf("Thread creation failed %d\n", threadError2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(EXIT_SUCCESS);

    return 0;
}


void *function1() {
    pthread_mutex_lock( &lock );
    printf("Thread1 Lock mutex\n");
    while(!condition) {
      printf("I'm waiting for Thread2 to send me signal.\n");
      printf("Thread1 Unlock mutex\n");
      pthread_cond_wait( &condition_var, &lock );
    }
    printf("Thread2 send me signal.\n");
    pthread_mutex_unlock( &lock );
    printf("Thread1 Unlock mutex\n");

}


void *function2() {
    pthread_mutex_lock( &lock );
    printf("Thread2 Lock mutex\n");

    condition = 1;

    pthread_cond_signal( &condition_var );
    printf("Send signal to thread1\n");

    for(int i = 0 ; i < 10000; i++);

    pthread_mutex_unlock( &lock ); // until mutex unlock, thread1 will not start working because thread1 need to lock mutex.
    printf("Thread2 Unlock mutex\n");
}

