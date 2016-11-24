#include "Philosophers.h"

Philosophers::Philosophers(int amount)
{
    //ctor
    this->amount_of_philosohers = amount;
    initializa_Philosophers(amount);
    next_taken =0;
}

void Philosophers::initializa_Philosophers(int amount)
{
    //Semaphore * temp[amount];
    chups_sticks = new Semaphore*[5];
    for(int i = 0; i < amount; i ++){
        chups_sticks[i] = new C_Semaphore(1);
    }
    //this->chups_sticks = temp;
}

Philosophers::~Philosophers()
{
    //dtor
}

void Philosophers::eat(Philosophers *parent, int index){
    int plate_porcentage=100;
    do
    {
        printf("Philosopher #%d is waiting for 2 chosticks\n",index);
        fflush(stdout);
        chups_sticks[index]->wait();
        printf("Philosopher #%d is waiting for 1 chosticks, got his, waiting for chopstick #%d\n",index, (index+1)%amount_of_philosohers);
        fflush(stdout);
        chups_sticks[(index+1)%amount_of_philosohers]->wait();
        printf("Philosopher #%d gots it, ready to eat\n",index);
        fflush(stdout);

            if(plate_porcentage>0){
                plate_porcentage -=10;
                printf("Philosopher #%d has eaten, his plate porcentage is %d\n",index,plate_porcentage);
                fflush(stdout);
                sleep(5);
            }
        chups_sticks[index]->signal();
        chups_sticks[(index+1)%amount_of_philosohers]->signal();
        //parent->next_taken = (parent->next_taken+1)%amount_of_philosohers;
        printf("Philosopher #%d is thinking\n",index);
        fflush(stdout);
        sleep(7);
    }while(plate_porcentage>0);
    printf("Philosopher #%d has finised, his plate porcentage is %d\n",index, plate_porcentage);
    fflush(stdout);
}

void Philosophers::exec(){
    thread *commensals[amount_of_philosohers];
    int index;

    for(index=0; index<amount_of_philosohers; index++)
    {
        commensals[index] = new thread(&Philosophers::eat, this,this,index);
    }

    pthread_exit(NULL);
}
