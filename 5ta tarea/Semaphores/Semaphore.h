#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include "Tools.h"


class Semaphore
{
    public:
        Semaphore(){};
        virtual ~Semaphore(){};
        virtual void wait()=0;
        virtual void signal()=0;
    protected:
    private:
};

class C_Semaphore : public Semaphore
{
	public:
        C_Semaphore (int value);
        virtual ~C_Semaphore ();
        void wait();
        void signal();
    protected:
        sem_t *semaphore;
};

class My_Semaphore : public Semaphore
{
	public:
        My_Semaphore (int value);
        virtual ~My_Semaphore ();
        void wait();
        void signal();
    protected:
        int value, wake;
        Mutex *mutex;
        Conditional_Variable *condition_variable;
};

#endif // SEMAPHORE_H
