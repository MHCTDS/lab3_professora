Exercicio 1 do lab 3

Alem da atividade em c, tambem fiz um programa em CUDA para comparacao de velocidade com gpu, embora nao leiam do mesmo arquivo.

Foram testados 3 tamanhos diferentes: mil entradas, 1 milhao de entradas e 1 bilhao de entradas

No caso da cpu, testarei com 1, 4 e 16 threads. Eu queria usar mapeamento de cache em c++, ja que provavelmente diminuiria drasticamente o numero de page faults e talvez aumentasse a velocidade de 10 a 100 vezes se for igual a gpu, mas isso foge do escope da entrega.

Eu tenho como CPU uma ryzen 7 9800x3d, com 8 nucleos e 16 threads e 96 gigabytes de memoria RAM.

No caso da da GPU, usarei 256 threads por bloco disponivel na gpu, dividindo igualmente os vetores em blocos de processamento.

Eu tenho como GPU uma rtx 5070ti

A cpu retorna um arquivo sqllite com metricas para analise de perfomance, mas nao colocarei aqui para nao poluir demais o repositorio.

o arquivo de figures inclui fotos do retorno dos programes de cpu e gpu.
