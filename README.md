# Thread-Periodica
Trabalho Pratico 1 relativo a Thread Periódica para a disciplina de Sistemas de Tempo Real ministrada na UFSC Joinville.

## Conteudo do Projeto
- main.cpp (programa principal contendo as implementacoes)
- thread.cpp (implementacao dos metodos da classe para a thread periodica)
- thread.h (escopo da classe)
- Makefile (Makefile para executar a aplicacao)
- periodic_thread.pdf (pdf contendo a descricao do problema)

## Instrucoes
- Para compilar o programa basta digitar no terminal linux: make
- Para executar: sudo taskset -c 1 ./main periodo cargaCPU prioridade <br><br>
onde:<br>
    <b>periodo</b> eh o valor em ms<br>
    <b>cargaCPU</b> eh o fator de carga<br>
    <b>prioridade</b> eh o fator de prioridade da tarefa variando de 1 a 99<br>
