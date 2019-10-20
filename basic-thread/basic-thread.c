/**
 * Basic thread program.
 * Vaclav Bohac (c) 2011
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *showMessage(void *ptr);

void *showMessage(void *ptr ) {
    const char * messages = (char *) ptr;
    printf("%s\n", messages);
}

int main()
{
    pthread_t thread1, thread2;
    const char * message1 = "Thread 1 is saying..";
    const char * message2 = "Thread 2 is saying..";
    int createThread1Error, createThread2Error;

    createThread1Error = pthread_create(&thread1, NULL,
    showMessage,(void *) message1);

    if (createThread1Error) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n",createThread1Error);
        exit(EXIT_FAILURE);
    }

    createThread2Error = pthread_create(&thread2, NULL,
    showMessage,(void *) message2);

    if (createThread2Error) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n",createThread2Error);
        exit(EXIT_FAILURE);
    }
    printf("In main function\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(EXIT_SUCCESS);

    return 0;
}

