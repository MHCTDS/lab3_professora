#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Limitei o valor maximo para 100 para ficar mais justo para a GPU

int main(int argc, char*argv[]) {
   float* vetor_A; //vetor que será gerada
   float* vetor_B;
   long int n; //qtde de elementos do vetor
   float elem; //valor gerado para incluir no vetor
   double produto=0; //soma total dos elementos gerados
   int fator=1; //fator multiplicador para gerar números negativos
   FILE * descritorArquivo; //descritor do arquivo de saida
   size_t ret; //retorno da funcao de escrita no arquivo de saida

   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao> <nome arquivo saida>\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);

   //aloca memoria para o vetor
   vetor_A = (float*) malloc(sizeof(float) * n);
   vetor_B = (float*) malloc(sizeof(float) * n);
   if(!(vetor_A || vetor_B)) {
      fprintf(stderr, "Erro de alocao da memoria do vetor\n");
      return 2;
   }

   //preenche o vetor A com valores float aleatorios
   srand(time(NULL));
   for(long int i=0; i<n; i++) {
        elem = (rand() % 100)/3.0 * fator;
        vetor_A[i] = elem; //acumula o elemento na soma total
        fator*=-1;
   }

   //preenche o vetor B com valores float aleatorios
   for(long int i=0; i<n; i++) {
        elem = (rand() % 100)/3.0 * fator;
        vetor_B[i] = elem; //acumula o elemento na soma total
        fator*=-1;
   }

   //Calcula o produto dos vetores 
   for(long int i=0; i<n; i++) {
        produto+=vetor_A[i]*vetor_B[i];
   }

   //escreve o vetor no arquivo
   //abre o arquivo para escrita binaria
   descritorArquivo = fopen(argv[2], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   //escreve a dimensao dos vetores
   ret = fwrite(&n, sizeof(long int), 1, descritorArquivo);

   //escreve os elementos do vetor A
   ret = fwrite(vetor_A, sizeof(float), n, descritorArquivo);
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo: vetor A\n");
      return 4;
   }

   //escreve os elementos do vetor B
   ret = fwrite(vetor_B, sizeof(float), n, descritorArquivo);
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo; vetor B\n");
      return 4;
   }

   //escreve o produto vetorial
   ret = fwrite(&produto, sizeof(double), 1, descritorArquivo);

   fclose(descritorArquivo);
   free(vetor_A);
   free(vetor_B);

   return 0;
} 
