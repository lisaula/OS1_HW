#include "Semaphore.h"


C_Semaphore::C_Semaphore(int value)
{
    //ctor
    this->semaphore = new sem_t();
    int n = sem_init(semaphore, 0, value);
    if (n != 0) {
        perror_exit("sem_init failed");
    }
}

C_Semaphore::~C_Semaphore()
{
    //dtor
    delete semaphore;
}

void C_Semaphore::wait()
{
    int n = sem_wait(semaphore);
    if (n != 0) perror_exit("semaphore wait failed");
}

void C_Semaphore::signal()
{
    int n = sem_post(semaphore);
    if (n != 0) perror_exit("sem_post failed");
}

My_Semaphore::My_Semaphore(int value)
{
    //ctor
    this->value = value;
    wake = 0;
    mutex = new Mutex();
    condition_variable = new Conditional_Variable();
}

My_Semaphore::~My_Semaphore()
{
    //dtor
    delete mutex;
    delete condition_variable;
}

void My_Semaphore::wait()
{
    mutex->lock();
    value--;

    if (value < 0) {
    do {
      condition_variable->wait(mutex);
    } while (wake < 1);
    wake--;
    }
    mutex->unlock();

}

void My_Semaphore::signal()
{
    mutex->lock();
    value++;

    if (value <= 0) {
        wake++;
        condition_variable->signal();
    }
    mutex->unlock();

}
