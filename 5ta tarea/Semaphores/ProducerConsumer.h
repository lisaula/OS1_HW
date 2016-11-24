#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H
#include "Semaphore.h"

#include <thread>
#include <unistd.h>

#define BUFF_SIZE   5           /* total number of slots */
#define NP          1           /* total number of producers */
#define NC          3           /* total number of consumers */
#define NITERS      4           /* number of items produced/consumed */


class ProducerConsumer
{
    public:
        ProducerConsumer();
        virtual ~ProducerConsumer();
        void exec();
    protected:
        void * producer(ProducerConsumer *parent, int index);
        void * consumer(ProducerConsumer *parent, int index);
    private:
        void join_threads(thread *array[], int size);
        int buf[BUFF_SIZE];   /* shared var */
        int in;               /* buf[in%BUFF_SIZE] is the first empty slot */
        int out;              /* buf[out%BUFF_SIZE] is the first full slot */
        Semaphore *full;           /* keep track of the number of full spots */
        Semaphore *empty;          /* keep track of the number of empty spots */
        // use correct type here
        pthread_mutex_t *mutex;          /* enforce mutual exclusion to shared data */
};

#endif // PRODUCERCONSUMER_H
