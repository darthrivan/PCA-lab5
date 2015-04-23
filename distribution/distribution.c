#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/times.h>


#define MAX_POS (1<<22) 



void distribution_sort(unsigned int *S, unsigned int *D, int n, int bits)
{

   unsigned int max_value = (1<<bits)-1;
   unsigned int shift = (sizeof(unsigned int)<<3)-bits;
   static unsigned int index[MAX_POS]; 
   unsigned int i, j, tmp, tmpp;


   for (i=0;i<max_value;i++) 
      index[i] = 0;

   /* Histograma de valors pels bits log2(MAX_POS) més baixos */
   for(i = 0;i<n; i++) 
   {
     j = (S[i]>>shift);
     index[j] = index[j]+1;
   }

   tmp = index[0];
   index[0] = 0;
   for (i=0; i<max_value; i++) 
   {
      tmpp = tmp + index[i];
      tmp  = index[i+1];
      index[i+1] = tmpp;
   }

   for(i = 0; i<n; i++) 
   {
      j = ((S[i]>>shift));
      D[index[j]] = S[i];
      index[j] = index[j]+1;
   }

}

#define N 1000000
#define BITS 4
typedef enum {RANDOM, GOINGUP} Tdistribution;
#define SYNTAX_EXECUTION "Usage: exec n dist_bits distribution (1=GOINGUP)\n" 

int main(int argc, char *argv[])
{

  unsigned int *D;
  unsigned int *S;
  unsigned int n, i;
  int bits;
  Tdistribution  dist;
  int tmp;
  struct rusage start;
  struct rusage end;


  if (argc == 4)
  {
      n =atoi(argv[1]);
      bits = atoi(argv[2]);
      tmp = atoi(argv[3]);
      if (tmp == 1) dist = GOINGUP;
      else dist=RANDOM;
  }
  else 
  {
      printf(SYNTAX_EXECUTION);
      exit(0);
  }

  D = (unsigned int *)malloc(sizeof(unsigned int)*n);
  S = (unsigned int *)malloc(sizeof(unsigned int)*n);

  if (dist==RANDOM)
  { 
    for (i=0; i<n; i++) 
    { 
     S[i] = random();
    }
  }
  else
  {
    for (i=0; i<n; i++) 
    { 
     if (i&1)
         S[i] = i;
     else 
         S[i] = n-i;
    }
  }

  getrusage(RUSAGE_SELF,&start);

  distribution_sort(S, D, n, bits);

  getrusage(RUSAGE_SELF,&end);
  float user_seconds = (float) (end.ru_utime.tv_sec-start.ru_utime.tv_sec) + ((float)(end.ru_utime.tv_usec-start.ru_utime.tv_usec))/1000000.0;
  float system_seconds = (float) (end.ru_stime.tv_sec-start.ru_stime.tv_sec) + ((float)(end.ru_stime.tv_usec-start.ru_stime.tv_usec))/1000000.0;
  fprintf(stdout, "%f %f\n", user_seconds, system_seconds);

  return 0;
}


