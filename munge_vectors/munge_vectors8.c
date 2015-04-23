#include <stdio.h>
#include <stdlib.h>
#include "clock.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define N_ITER (1<<12)


void Munge8( void *data, uint32_t size ) {
    int j;
    uint8_t *data8 = (uint8_t*) data;
    uint8_t *data8End = data8 + size;
    double cyc, cyc_min;
    
  start_counter();
  for (j=0; j<N_ITER; j++) {

    data8 = (uint8_t*) data;
    while( data8 != data8End ) {
        *data8++ = -*data8;
    }

  }
  cyc = get_counter()/N_ITER;
  printf("%.2f\n", cyc);
//  printf("Normalized %.2f\n", cyc/(float)(data8End-(uint8_t*)data));
}

void Munge16( void *data, uint32_t size ) {
    int j;
    uint16_t *data16 = (uint16_t*) data;
    uint16_t *data16End = data16 + (size >> 1); /* Divide size by 2. */
    uint8_t *data8 = (uint8_t*) data16End;
    uint8_t *data8End = data8 + (size & 0x00000001); /* Strip upper 31 bits. */
    
  for (j=0; j<N_ITER; j++) {
    while( data16 != data16End ) {
        *data16++ = -*data16;
    }
    while( data8 != data8End ) {
        *data8++ = -*data8;
    }
  }
}

void Munge32( void *data, uint32_t size ) {
    int j;
    uint32_t *data32 = (uint32_t*) data;
    uint32_t *data32End = data32 + (size >> 2); /* Divide size by 4. */
    uint8_t *data8 = (uint8_t*) data32End;
    uint8_t *data8End = data8 + (size & 0x00000003); /* Strip upper 30 bits. */
    
  for (j=0; j<N_ITER; j++) {
    while( data32 != data32End ) {
        *data32++ = -*data32;
    }
    while( data8 != data8End ) {
        *data8++ = -*data8;
    }
  }
}

void Munge64( void *data, uint32_t size ) {
    int j;
    double *data64 = (double*) data;
    double *data64End = data64 + (size >> 3); /* Divide size by 8. */
    uint8_t *data8 = (uint8_t*) data64End;
    uint8_t *data8End = data8 + (size & 0x00000007); /* Strip upper 29 bits. */
    
  for (j=0; j<N_ITER; j++) {
    while( data64 != data64End ) {
        *data64++ = -*data64;
    }
    while( data8 != data8End ) {
        *data8++ = -*data8;
    }
  }
}



#define MAX_DATOS (2*1024*1024)



int main()
{
  char *buffer = (char *)malloc(MAX_DATOS+64);
  char *buffer_tmp;
  

  int alignment=0;


  buffer = buffer+(64-((unsigned int)buffer%64));
  for (alignment=0; alignment<=64; alignment++)
  {
     buffer_tmp = buffer+alignment;
     printf("%d\t",alignment);
     Munge8( (void *)buffer_tmp, MAX_DATOS-alignment );
  }


  return 0;
}

