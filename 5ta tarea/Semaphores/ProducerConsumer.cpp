#include "ProducerConsumer.h"

ProducerConsumer::ProducerConsumer()
{
    //ctor
    in=0;               /* buf[in%BUFF_SIZE] is the first empty slot */
    out=0;              /* buf[out%BUFF_SIZE] is the first full slot */
    full = new My_Semaphore(0);           /* keep track of the number of full spots */
    empty= new My_Semaphore(BUFF_SIZE);          /* keep track of the number of empty spots */
        // use correct type here
    mutex = new pthread_mutex_t();
    pthread_mutex_init(mutex, NULL);
}

ProducerConsumer::~ProducerConsumer()
{
    //dtor
}

void * ProducerConsumer::producer(ProducerConsumer * parent, int index){
    int i=0, item;
    while(1)
    {
        item = i;
        i++;
        parent->empty->wait();
        /* If another thread uses the buffer, wait */
        pthread_mutex_lock(parent->mutex);
        int pos = parent->in;
        parent->buf[pos] = item;
        parent->in = (parent->in+1)%BUFF_SIZE;
        printf("[Producer #%d] Produced pizza in the position %d\n", index,pos);
        fflush(stdout);
        /* Release the buffer */
        pthread_mutex_unlock(parent->mutex);
        /* Increment the number of full slots */
        parent->full->signal();

        /* Interleave  producer and consumer execution */
        //if (i % 2 == 1)
        sleep(1);
    }
    return NULL;
}

void * ProducerConsumer::consumer(ProducerConsumer *parent, int index){
    int i, item;
    for (i=NITERS; i > 0; i--) {
        parent->full->wait();
        pthread_mutex_lock(parent->mutex);
        item=i;
        int pos =parent->out;
        item=parent->buf[pos];
        parent->out = (parent->out+1)%BUFF_SIZE;
        printf("[Consumer #%d] Consumed pizza of the position %d\n", index,pos);
        fflush(stdout);
        /* Release the buffer */
        pthread_mutex_unlock(parent->mutex);
        /* Increment the number of full slots */
        parent->empty->signal();

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}
void ProducerConsumer::join_threads(thread *array[], int size){
    for(int i =0; i < size;i++){
        array[size]->join();
    }
}
void ProducerConsumer::exec(){
    thread *producers[NP], *consumers[NC];
    int index;

    for (index = 0; index < NP; index++)
    {
        /* Create a new producer */
        producers[index] = new thread(&ProducerConsumer::producer,this,this,index);
    }
    /*create a new Consumer*/
    for(index=0; index<NC; index++)
    {
        consumers[index] = new thread(&ProducerConsumer::consumer, this,this,index);
    }

    //join_threads(producers,NP);
    //join_threads(consumers, NC);

    pthread_exit(NULL);
}
