#include <thread>
#include <iostream>
#include <chrono>
#include <cstring>
#include <pthread.h>
#include <signal.h> 
#include <time.h>
#include <unistd.h>

class myThread{
    public:	
        void periodicThread(unsigned int periodo, unsigned int cargaCPU);

};
