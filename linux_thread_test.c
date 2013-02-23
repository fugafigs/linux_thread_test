#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define TRIES 1025

void *run(void *args)
{
    sleep(10);
}

int create_thread(void)
{
    pthread_t thread;

    return pthread_create(&thread, NULL, &run, NULL);
}

int create_process(void)
{
    pid_t pid;

    pid = fork();
    switch (pid) { 
    case -1 : 
        return -1;
    case 0 : /* child process */    
        sleep(10);
        _exit(0);
        break;
    }

    return 0;
}

int main(int argc, char *argv[]) 
{
    int i;
    int ret;

    for (i = 0; i < TRIES; i++) {
        if (i % 10) {  /* creates thread */
            ret = create_thread();
            printf("%-4dth try : pthread_create() returns : %-2d, %s\n", 
                   i, ret, strerror(ret)); 
        }
        else {        /* creates process */
            ret = create_process();
            printf("%-4dth try : fork()           returns : %-2d, %s\n", 
                   i, ret, strerror(errno)); 
        }
    }

    return 0;
}

