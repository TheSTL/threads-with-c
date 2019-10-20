/**
 * Without Mutex program.
 * Ashu Deshwal (c) 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *functionC();
int counter = 0;

int main()
{
    pthread_t thread1, thread2;
    int threadError1, threadError2;

    threadError1 = pthread_create(&thread1, NULL,
    &functionC, NULL);

    if (threadError1) {
    printf("Thread creation failed: %d\n",threadError1);
    }

    threadError2 = pthread_create(&thread2, NULL,
    &functionC, NULL);

    if (threadError2) {
    printf("Thread creation failed %d\n", threadError2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Counter value after threads: %d\n", counter);
    exit(EXIT_SUCCESS);

    return 0;
}

void *functionC() {
    counter++;
    printf("Threads increase counter value %d\n", counter);
}
