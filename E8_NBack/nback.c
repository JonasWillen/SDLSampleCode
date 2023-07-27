#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nback.h"

void fillInAMatch(int nBackString[], int size, int combinations, int nback);
void fillInAllEmty(int nBackString[], int size, int combinations, int nback);


void createNBackString(int nBackString[], int size, int combinations, int procentMatch, int nback){
    
    srand((unsigned)time(NULL));

    for(int i = 0; i<size; i++){
        nBackString[i] = 0;
    }

    int matches = (int) size*procentMatch/100;

    for(int i = 0; i<matches; i++){
        fillInAMatch(nBackString, size, combinations, nback);
    }

    fillInAllEmty(nBackString, size, combinations, nback);  

}

void fillInAMatch(int nBackString[], int size, int combinations, int nback){
    
    int value = 1 + rand() % combinations;

    int test = 0;
    while(test == 0){
        int possition = rand() % size;
        if((possition+nback < size) && nBackString[possition]== 0 && nBackString[possition+nback] == 0){
            nBackString[possition] = value;
            nBackString[possition+nback] = value;
            test = 1;
        }
    }
}

void fillInAllEmty(int nBackString[], int size, int combinations, int nback){
    for(int i = 0; i< size; i++){
        if(nBackString[i] == 0){  
            int test = 0;
            int foo, bar;
            while(test == 0){
                int value = 1 + rand() % combinations;
                foo = 0;
                bar = 0; 
                if(i-nback > 0){
                    if (nBackString[i-nback] != value){
                        foo = 1;
                    }  
                }else{
                    foo = 1;
                }

                if(i+nback < size){
                    if(nBackString[i+nback] != value){
                        bar = 1;
                    }  
                }else{
                    bar = 1;
                }

                if(foo == 1 && bar == 1){
                    test = 1;
                    nBackString[i] = value;
                }
                    
            }
        }
        
    }
}