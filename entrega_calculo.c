#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 
#include "timer.h"

short int nthreads; //numero de threads 
long int global_n; //tamanho do vetor
float* vetor_A; // primeiro vetor armazenado no arquivo
float* vetor_B; // segundo vetor armazenado no arquivo

void* produto_vetor(void* args){
    long int tid= (long int) args;
    long int fim;
    double res=0,*ret;

    fim=(tid+1)*(global_n/nthreads);
    if (tid==nthreads-1) fim=global_n;

    for(long int i=(tid)*(global_n/nthreads);i<fim;i++){
        res+=vetor_A[i]*vetor_B[i];
    }

    ret = (double*) malloc(sizeof(float));
    if (ret!=NULL) *ret = res;
    else printf("--ERRO: malloc() thread\n");


    pthread_exit((void*) ret);
}

int main(int argc, char *argv[]){
    FILE *arq; //arquivo de entrada
    size_t ret; //retorno da funcao de leitura no arquivo de entrada
    double produto=0; //resultado do produto concorrente
    double produto_linear; //resultado do produto sem concorrencia
    double* retorno; //retorno das threads
    pthread_t *tid_sistema; //vetor de identificadores das threads no sistema
    double time1,time2; // retornar tempos

    if(argc < 3) { printf("Use: %s <arquivo de entrada> <numero de threads> \n", argv[0]); exit(-1); }

    //resgatando n do arquivo
    arq = fopen(argv[1], "rb");
    if(arq==NULL) { printf("--ERRO: fopen()\n"); exit(-1); }

    ret = fread(&global_n, sizeof(long int), 1, arq);
    if(!ret) {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
        return 3;
    }

    //aloca espaco de memoria e carrega o vetor A
    vetor_A = (float*) malloc (sizeof(float) * global_n);
    if(vetor_A==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
    ret = fread(vetor_A, sizeof(float), global_n, arq);
    if(ret < global_n) {
        fprintf(stderr, "Erro de leitura dos elementos do vetor\n");
        return 4;
    }

    //aloca espaco de memoria e carrega o vetor B
    vetor_B = (float*) malloc (sizeof(float) * global_n);
    if(vetor_B==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
    ret = fread(vetor_B, sizeof(float), global_n, arq);
    if(ret < global_n) {
        fprintf(stderr, "Erro de leitura dos elementos do vetor\n");
        return 4;
    }

    //carrega produto linear
    ret = fread(&produto_linear, sizeof(double), 1, arq);
    if(!ret) {
        fprintf(stderr, "Erro de leitura do resultado linear \n");
        return 3;
    }

    //le o numero de threads da entrada do usuario 
    nthreads = atoi(argv[2]);
    //limita o numero de threads ao tamanho do vetor
    if(nthreads>global_n) nthreads = global_n;

    //aloca espaco para o vetor de identificadores das threads no sistema
    tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if(tid_sistema==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }

    //calculando produto
    GET_TIME(time1);
    for (long int i=0;i<nthreads;i++){
        if (pthread_create(&tid_sistema[i], NULL, produto_vetor, (void*) i)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }

    for (long int i=0;i<nthreads;i++){
        if (pthread_join(tid_sistema[i], (void *) &retorno)) {
            printf("--ERRO: pthread_join()\n"); exit(-1);
        }
        produto += *retorno;
    }
    GET_TIME(time2);

    printf("produto concorrente %lf\n",produto);
    printf("tempo gastado%lf\n\n",time2-time1);

    printf("produto linear %lf\n",produto_linear);

    printf("porcentagem de variacao %lf\n",(produto_linear-produto)/produto_linear);

    free(retorno);
    free(vetor_A);
    free(vetor_B);
    fclose(arq);

    return 0;
}