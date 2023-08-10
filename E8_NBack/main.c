#include <stdio.h>  
#include "nback.h"

int main(){

    int size = 20;

    //int nBackString[size];

    //createNBackString(nBackString, size, 9, 20, 2);

    Nback s1;

    s1 = create(size, 9, 20, 2);


    for(int i=0; i<size-1; i++){
        printf("%d, ", getIndexOf(s1, i));
    }

    printf("%d \n", getIndexOf(s1, 19));

    return 0;
};