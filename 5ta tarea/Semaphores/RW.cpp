#include "RW.h"
#include <stdio.h>
#include <string.h>
RW::RW()
{
    //ctor
    sem_write = new C_Semaphore(1);
    strcpy(data, "nothing");
}

RW::~RW()
{
    //dtor
}

void *RW::writer(RW *parent, const char* msg, int times){
    int i = 0;
    while(i<times)
    {
        printf("Waiting to write %s\n", msg);
        fflush(stdout);
        parent->sem_write->wait();
        i++;
        strcpy(parent->data, msg);
        printf("Writer wrote %s for the %d time\n", parent->data, i);
        fflush(stdout);
        parent->sem_write->signal();
        sleep(2);
    }
    printf("Writer writing %s end\n", msg);
    fflush(stdout);
    return NULL;

}

void *RW::reader(RW* parent, int index, int reading_sleep_time){
    while(1){
        printf("reader #%d got: %s\n",index, parent->data);
        sleep(1);
    }
    return NULL;
}

void RW::exec(){
    int number_of_readers = 5;
    thread *readers[number_of_readers];
    int index;

    for(index=0; index<number_of_readers; index++)
    {
        readers[index] = new thread(&RW::reader, this,this,index,1);
    }

    thread *writer1 = new thread(&RW::writer,this,this,"Hola",5);
    thread *writer2 = new thread(&RW::writer,this,this,"Como",4);
    thread *writer3 = new thread(&RW::writer,this,this,"Estas",3);

    //join_threads(producers,NP);
    //join_threads(consumers, NC);

    pthread_exit(NULL);
}
