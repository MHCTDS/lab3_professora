#include <iostream>
#include <math.h>
// Nao vale a pena fazer esse calculo em gpu com so 4
// entao usei 1 milhao
// Demorou 6 mil nanosegundos para fazer a soma com 1 milhao
// O bottleneck e alocar isso tudo para a gpu, demorou 66 milhoes de nanosegundos
#define N 1000

__global__
void add(float *x,float *y,float *sum, int n) {

  int index=blockIdx.x*blockDim.x+threadIdx.x;
  int stride=blockDim.x*gridDim.x;
  for(int i=index; i<n;i+=stride){
    *sum+=x[i]+y[i];
  }
}

int main(){

  float *x,*y,*sum;

  cudaMallocManaged(&x,N*sizeof(float));
  cudaMallocManaged(&y,N*sizeof(float));
  cudaMallocManaged(&sum,sizeof(float));

  for(int i=0; i<N;i++){
    x[i]=1;
  }
  
  for(int i=0; i<N;i++){
    y[i]=1;
  }
  
  *sum=0;

  cudaMemPrefetchAsync(x,N*sizeof(float),0,0);
  cudaMemPrefetchAsync(y,N*sizeof(float),0,0);
  cudaMemPrefetchAsync(sum,sizeof(float),0,0);
  
  int blockSize = 256;
  int numBlocks=(N+blockSize-1)/blockSize;
  add<<<numBlocks,blockSize>>>(x,y,sum,N);

  cudaDeviceSynchronize();

  // Check for errors (all values should be 3.0f)
  std::cout << "final sum: " << sum << std::endl;

  cudaFree(x);
  cudaFree(y);
  cudaFree(sum);

  return 0;
}
