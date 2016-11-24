#ifndef TOOLS_H
#define TOOLS_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
using namespace std;
void perror_exit(char *s);

class Mutex
{
    public:
        Mutex();
        void lock();
        void unlock();
        virtual ~Mutex();
        pthread_mutex_t* mutex;
};

class Conditional_Variable
{
    public:
        Conditional_Variable();
        void wait(Mutex *mutex);
        void signal();
        virtual ~Conditional_Variable();
    private:
        pthread_cond_t * conditional_variable;
};

#endif
