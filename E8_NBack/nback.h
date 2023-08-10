#ifndef nback_h
#define nback_h
// createNBackString takes an integer array of size, input variables are the array, its size, 
// number of diffrent combinatations as a integer, procentesith so 20 equals 20% match
// nback is number of steps between matches. 

typedef struct nback_type *Nback;

Nback create(int size, int combinations, int procentMatch, int nback);
int getIndexOf(Nback s, int index);

#endif