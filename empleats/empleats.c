#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM 40
#define MAX_DIAS_MES 31 
#define MAX_CATEGORIA 40 
#define MAX_ADDRESS 100

#define BUFFER_SIZE (1<<20)

typedef struct 
{
  long long int NID;              /* Número d'identificació: clau d'ordenació */
  char Nom[MAX_NOM];  
  char Cognoms[MAX_NOM];  
  int  horesMes[MAX_DIAS_MES]; 
  char Categoria[MAX_CATEGORIA];
  unsigned int ptrClauForaneaDepartament;
  unsigned int ptrClauCategoria;
#ifdef EXTES     
  char Address[MAX_ADDRESS];
  char Nom_parella[MAX_NOM];
  char Cognoms_parella[MAX_NOM];
#endif
} Templeat;

typedef struct
{
	long long int NID;
	Templeat *data;
} Templeat_nids;

int compare(const void *p1, const void *p2)
{
    return ((Templeat_nids*) p1)->NID - ((Templeat_nids*) p2)->NID;
}

int main(int argc, char *argv[])
{
	Templeat *empleats, *empleats_def;
	Templeat_nids *ids;
	unsigned int N = 4000000, i;

	if (argc > 1) N = atoi(argv[1]);

	ids = (Templeat_nids *) malloc(N*sizeof(Templeat_nids));
	empleats = (Templeat *) malloc(N*sizeof(Templeat));
	empleats_def = (Templeat *) malloc(N*sizeof(Templeat));
	if (empleats == NULL) { fprintf(stderr, "Out of memory\n"); exit(0); }

	/* Random generation */
	for (i=0; i<N; i++) {
		empleats[i].NID = rand();
		empleats[i].Nom[0] = 'A' + ((i>>3) + (i<<2)) & 0x15;
		empleats[i].Cognoms[0] = 'a' + ((i>>2) + (i<<3)) & 0x15;
		empleats[i].horesMes[i % MAX_DIAS_MES] = i;
		empleats[i].Categoria[i % MAX_CATEGORIA] = (i << 2) * i;
		empleats[i].ptrClauForaneaDepartament = i<<10 + i<<14 + i>>3;
		empleats[i].ptrClauCategoria = i<<24 + i<< 18 + i<<10 + i>>2;
		ids[i].NID = empleats[i].NID;
		ids[i].data = &empleats[i];
#ifdef EXTES     
        empleats[i].Address[0] = 'A' + ((i>>4) + (i<<2)) & 0x15;
        empleats[i].Nom_parella[0] = 'a' + ((i>>5) + (i<<2)) & 0x15;
  		empleats[i].Cognoms_parella[0] = 'A' + ((i>>5) + (i<<3)) & 0x15;
#endif
	}

	qsort(ids, N, sizeof(Templeat_nids), compare);
	for (i=0; i < N; ++i) {
		empleats_def[i] = *(ids[i].data);
	}
	unsigned int N_blocks = N / BUFFER_SIZE;
	for (i=0; i<N_blocks*BUFFER_SIZE; i += BUFFER_SIZE){
		write (1, &empleats_def[i], BUFFER_SIZE*sizeof(Templeat));
	}
	write (1, &empleats_def[i], (N % BUFFER_SIZE)*sizeof(Templeat));
	return 0;
}
