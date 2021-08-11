# include "thread.h"

void myThread::periodicThread(unsigned int periodo, unsigned int cargaCPU)
{
    sigset_t alarm_sig; //The sigset_t data type is used to represent a signal set(conjunto de sinais linux)

    sched_param parametro;
    sched_getparam(0, &parametro); //Prioridade recebida
    std::cout<< "Prioridade da Thread: " << parametro.sched_priority << std::endl;
    
    sigemptyset(&(alarm_sig)); //preenche a máscara como vazia (sem nenhum sinal) 
    int signo = SIGALRM; //Alarme
    sigaddset(&(alarm_sig), signo); //acrescenta o sinal signo à máscara
    
    timer_t timer_id; // armazena valores de tempo
    int ret;
    ret = timer_create(CLOCK_REALTIME, NULL, &timer_id); //criando temporizador ( tipo relogio,,id do temporizador é apontado por timer_id)
    if (ret == -1)
	return;

    struct itimerspec alarm;   //estrutura que contem 2 estruturas(it_interval e it_value) que guardam o novo valor inicial para o cronômetro e o novo intervalo para o cronômetro (dentro de duas struct timespec: tv_sec e tv_nsec)
    struct itimerspec value;  
    alarm.it_interval.tv_sec = periodo/1000; //periodo da thread em segundos
    alarm.it_interval.tv_nsec = periodo*1000000;// periodo da thread em nano segundos
    alarm.it_value.tv_sec = periodo/1000; // tempo da primeira ativação em segundos
    alarm.it_value.tv_nsec = periodo*1000000; //tempo da primeira ativação em nano segundos
    
    unsigned int loop = 30000/periodo;
    ret = timer_settime(timer_id, 0, &alarm, NULL); //arma temporizador
    

    while(loop>0) 
    {
	
        sigwait(&(alarm_sig), &signo); // Wait for the next SIGALRM

        for(unsigned int i=0;i<cargaCPU*1000;i++){} //Carga recebida

        timer_gettime(timer_id, &value);//Tempo restante para acabar o periodo
        std::cout << loop << "  " << value.it_value.tv_nsec << std::endl; //tempo de resposta da tarefa
        
        ret = timer_getoverrun(timer_id);//Verifica perda de timer

        if(ret > 0)
        std::cout << "\t" << ret << " timer perdido!" << std::endl;
        
        loop--;	
    }
    
    ret = timer_delete(timer_id); //Deleta o timer criado	

    return;
}