#include <stdio.h>
#include <stdlib.h>

#define N 1024 

int n;

int C[N][N];
int A[N][N];
int B[N][N];


void mult2(int C[][N], int B[][N], int A[][N], int n)
{

  int i,j,k;
  int r;

  for ( k=0 ; k < n; k++ )
  {


    for ( i=0 ; i < n; i++ )
    {
      r = A[i][k];
      for ( j=0 ; j < n ; j++ )
         C[i][j] += r*B[k][j];
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
  

  mult2(C,B,A,n); 

  write(1, C, sizeof(C));
  return 0;
}
