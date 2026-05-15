#include<stdio.h>

void add_complex(float c1[], float c2[], float res[]){
    res[0] = c1[0] + c2[0];
    res[1] = c1[1] + c2[1];
}

void mul_complex(float c1[], float c2[], float res[]){
    res[0] = c1[0]*c2[0] - c1[1]*c2[1];
    res[1] = c1[0]*c2[1] + c1[1]*c2[0];
}