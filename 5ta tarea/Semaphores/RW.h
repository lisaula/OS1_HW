#ifndef RW_H
#define RW_H
#include "Semaphore.h"
#include <thread>
#include <unistd.h>
class RW
{
    public:
        RW();
        virtual ~RW();
        void exec();
    protected:
    private:
        Semaphore *sem_write;
        char data[1024];
        void *writer(RW *parent, const char* msg, int times);
        void *reader(RW *parent, int,int);

};

#endif // RW_H
