#include "Tools.h"

void perror_exit(char *s)
{
  perror(s);
  exit(-1);
}

Mutex::Mutex(){
    mutex = new pthread_mutex_t();
    int n = pthread_mutex_init(mutex, NULL);
    if (n != 0) perror_exit("make_lock failed");
}

Mutex::~Mutex(){
    //dtor
    delete mutex;
}
void Mutex::lock()
{
  int n = pthread_mutex_lock(mutex);
  if (n != 0) perror_exit("lock failed");
}

void Mutex::unlock()
{
  int n = pthread_mutex_unlock(mutex);
  if (n != 0) perror_exit("unlock failed");
}


Conditional_Variable::Conditional_Variable(){
    this->conditional_variable = new pthread_cond_t();
    int n = pthread_cond_init(conditional_variable, NULL);
    if (n != 0) perror_exit("make_cond failed");
}

Conditional_Variable::~Conditional_Variable(){
    delete conditional_variable;
}
void Conditional_Variable::wait(Mutex *mutex)
{
  int n = pthread_cond_wait(conditional_variable, mutex->mutex);
  if (n != 0) perror_exit("cond_wait failed");
}

void Conditional_Variable::signal()
{
  int n = pthread_cond_signal(conditional_variable);
  if (n != 0) perror_exit("cond_signal failed");
}
