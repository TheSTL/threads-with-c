/**
 * Prevent Deadlock program.
 * Ashu Deshwal (c) 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *function1();
void *function2();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int counter1 = 0, counter2 = 0;

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

    printf("Counter value after threads:\ncounter1: %d, counter2: %d\n", counter1,counter2);
    exit(EXIT_SUCCESS);

    return 0;
}

void *function1() {
    int lockError = pthread_mutex_trylock( &mutex1 );
    if (lockError) {
    fprintf(stderr, "Mutex1 LockError code : %d\n", lockError);
    }
    else {
    counter1++;
    function2();
    printf("Thread1 increase counter value %d\n", counter1);
    pthread_mutex_unlock( &mutex1 );
    }
}

void *function2() {
    int lockError = pthread_mutex_trylock( &mutex2  );
    if (lockError) {
    fprintf(stderr, "Mutex2 LockError code : %d\n", lockError);
    }
    else {
    counter2++;
    function1();
    printf("Thread2 increase counter value %d\n", counter2);
    pthread_mutex_unlock( &mutex2 );
    }
}

