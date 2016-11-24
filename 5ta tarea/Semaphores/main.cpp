#include <iostream>
#include "ProducerConsumer.h"
#include "RW.h"
#include "Philosophers.h"
using namespace std;

int main()
{
    cout << "Syncing process with semaphores!" << endl;
    ProducerConsumer *pc = new ProducerConsumer();
    pc->exec();

    //RW *rw = new RW();
    //rw->exec();
    //Philosophers * p = new Philosophers(4);
    //p->exec();
    return 0;
}
