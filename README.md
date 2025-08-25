Exercicio 1 do lab 3

Alem da atividade em c, tambem fiz um programa em CUDA para comparacao de velocidade com gpu, embora nao leiam do mesmo arquivo.

Foram testados 3 tamanhos diferentes: mil entradas, 1 milhao de entradas e 1 bilhao de entradas

No caso da cpu, testarei com 1, 4 e 16 threads. Eu queria usar mapeamento de cache em c++, ja que provavelmente diminuiria drasticamente o numero de page faults e talvez aumentasse a velocidade de 10 a 100 vezes se for igual a gpu, mas isso foge do escope da entrega.

Eu tenho como CPU uma ryzen 7 9800x3d, com 8 nucleos e 16 threads e 96 gigabytes de memoria RAM.

No caso da da GPU, usarei 256 threads por bloco disponivel na gpu, dividindo igualmente os vetores em blocos de processamento.

Eu tenho como GPU uma rtx 5070ti

A gpu retorna um arquivo sqllite com metricas para analise de perfomance, mas nao colocarei aqui para nao poluir demais o repositorio.

o arquivo de figures inclui fotos do retorno dos programes de cpu e gpu.

Nenhum dos testes mostrou diferencas no calculo entre o programe concorrente e linear, talvez isso seja devido a alguma feature especial do meu chip.

A CPU gastou com 1k entradas:
0.000173 segundos com 1 thread, 0.000176 com 4 threads e 0.000367 segundos com 16 threads

Se observou uma piora no tempo de execucao com o aumento das threads. A teoria do porque seria o overhead da execucao de multiplas threads combinado com a incapacidade do processador de usar branch prediction corretamente com a paralelizacao piorar a perfomance

A CPU gastou com 1M entradas:
0.002516 segundos com 1 thread, 0.000763 com 4 threads e 0.000668 segundos com 16 threads

A perfomance melhorou em em ~4 vezes de 1 a 4 threads, mas teve uma melhora muito minima de 4 para 16

A CPU gastou com 1B entradas:
2.291970 segundos com 1 thread, 0.574209 com 4 threads e 0.148584 segundos com 16 threads

A perfomance melhorou em em ~4 vezes de 1 a 4 threads e de novo ~4 de 4 a 16 threads, finalmente chegando a uma quantidade de dados grande o suficiente para que o numero de threads fosse inversamente proporcional.

No caso da GPU tudo esta registrado em nanosegundos, 1 bilhonesino de segundo: 

Com 1k entradas demoru 1728 nanosegundos, com 1M de entradas demorou 10464 nanosegundos e com 1B de entradas demorou 12527521 nanosegundos, ou 0.012 segundos 

De 1k para 1M de entradas A GPU so gastou 6 vezes mais tempo, mesmo com um aumento de 1000 vezes nos dados. Porem, com 1B de netrads, a gpu demorou 1000 vezes mais, quase com o mesmo tempo de processamento da cpu.

Eu fiz alguns testes extras, e nao parece ter sido o caso de passar o limite do memoria da gpu. Eu teria que investigar o codigo e estudar mais para otimizar a execucao e voltar a ter ganhos de processamento, pois nao acho que a gpu, feita para processar matriz e vetores, deveria levar quase o mesmo tempo da cpu.
