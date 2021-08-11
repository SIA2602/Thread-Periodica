/*  Referencias:
    https://en.cppreference.com/w/cpp/thread/thread/native_handle
    https://pubs.opengroup.org/onlinepubs/7908799/xsh/signal.h.html
    https://github.com/csimmonds/periodic-threads/blob/master/timer.c
    https://2net.co.uk/tutorial/periodic_threads
*/
# include "thread.h"
 
int main(int argc, char **argv)
{          
    unsigned int periodo = atoi(argv[1]); //Periodo da thread periodica
    unsigned int cargaCPU = atoi(argv[2]); //Carga da CPU

    // Sinal que sera enviado do timer Posix para implementar comportamento periodico da thread
    // SIGALRM: Alarm clock.
    sigset_t alarm_sig;
    sigemptyset(&alarm_sig); //Initialize a set to contain no signals
    sigaddset(&alarm_sig, SIGALRM); //Add a signal to a set
    sigprocmask(SIG_BLOCK, &alarm_sig, NULL);//Add the signals pointed to by set to the thread mask.

    myThread *myPeriodicThread = new myThread;

    sched_param sch; //objeto que ira definir o grau de prioridade para thread 
    int policy; // location where the function can store the scheduling policy
    std::thread threadPeriodica(&myThread::periodicThread, myPeriodicThread, periodo, cargaCPU);  //criando thread 
    pthread_getschedparam(threadPeriodica.native_handle(), &policy, &sch); //Ref.: http://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/p/pthread_getschedparam.html
    sch.sched_priority = atoi(argv[3]); //prioridade de 1 a 99
    
    //Estabelencendo politica de escalonamento para a thread para SCHED_FIFO
    if (pthread_setschedparam(threadPeriodica.native_handle(), SCHED_FIFO, &sch)) {
        std::cout << "Falha ao setar politica de escalonamento: " << std::strerror(errno) << '\n';
    }
 
    threadPeriodica.join();
}
