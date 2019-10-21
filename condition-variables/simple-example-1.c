/**
 * Condition variables program.
 * Ashu Deshwal (c) 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *function1();
void *function2();
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
int counter = 0, run1 = 0, run2 = 0;

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

    printf("Counter value after threads: %d\n", counter);
    printf("No of loop in thread1 %d\nNo of loop in thread2 %d\n",run1, run2);
    exit(EXIT_SUCCESS);

    return 0;
}


void *function1() {

    for(;;){
        pthread_mutex_lock( &count_mutex );
        run1++;

        pthread_cond_wait( &condition_var, &count_mutex);

        counter++;
        printf("Thread1 increase counter value %d\n", counter);
        pthread_mutex_unlock( &count_mutex );
        if (counter>=10) return(NULL);
    }
}


void *function2() {

    for(;;) {

        pthread_mutex_lock( &count_mutex );
            run2++;
        if ( counter<3 || counter>7 ) {
           pthread_cond_signal( &condition_var );
        }
        else {
          counter++;
          printf("Thread2 increase counter value %d\n", counter);
        }

        pthread_mutex_unlock( &count_mutex );

        if (counter>=10) return(NULL);

    }
}

