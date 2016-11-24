#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include "Semaphore.h"
#include <thread>
#include <unistd.h>

class Philosophers
{
    public:
        Philosophers(int amount);
        void exec();
        virtual ~Philosophers();
    protected:
    private:
        int amount_of_philosohers;
        int next_taken;
        Semaphore **chups_sticks;
        void eat(Philosophers * parent, int index);
        void initializa_Philosophers(int amount);
};

#endif // PHILOSOPHERS_H
