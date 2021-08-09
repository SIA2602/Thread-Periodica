#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <cstring>
#include <pthread.h>
#include <signal.h>
 
std::mutex iomutex;
void f(int num)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    sched_param sch;
    int policy; 
    pthread_getschedparam(pthread_self(), &policy, &sch);
    std::lock_guard<std::mutex> lk(iomutex);
    std::cout << "Thread " << num << " is executing at priority "
              << sch.sched_priority << '\n';
}
 
int main()
{
    std::thread t1(f, 1);  
 
    sched_param sch;    

    //Para comportamento periodico no Linux
    sigset_t alarm_sig;
	sigemptyset(&alarm_sig); //Initialize a set to contain no signals
	sigaddset(&alarm_sig, SIGALRM); //Add a signal to a set
	sigprocmask(SIG_BLOCK, &alarm_sig, NULL);//Add the signals pointed to by set to the thread mask.
    
    int policy; 
    pthread_getschedparam(t1.native_handle(), &policy, &sch);
    sch.sched_priority = 20; //de 1 a 99
    
    if (pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch)) {
        std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
    }
 
    t1.join();
}
