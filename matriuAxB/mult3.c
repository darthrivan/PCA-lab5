#include <stdio.h>
#include <stdlib.h>

#define N 2048

int n;

int C[N][N];
int A[N][N];
int B[N][N];


#ifndef _BLOCK_SIZE_
   #define BLOCK_SIZE 1024
#else
   #define BLOCK_SIZE _BLOCK_SIZE_
#endif


void mult3(int C[][N], int B[][N], int A[][N], int n)
{
  int i,j,k,r;

  for ( k=0 ; k < n; k++ )
  {
    for ( j=0 ; j < n; j++ )
    {
      r = B[k][j];
      for ( i=0 ; i < n ; i++ )
         C[i][j] += A[i][k]*r;
    }
  }
}

void init(int A[][N], int n)
{

  int i,j;

  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      A[i][j] = i+j;

}

int main(int argc, char *argv[])
{


  if (argc > 1) n = atoi(argv[1]); else n = N;

  init( A, n);
  init( B, n);
  init( C, n);
  

  mult3(C,B,A,n); 

  write(1, C, sizeof(C));
  return 0;
}
