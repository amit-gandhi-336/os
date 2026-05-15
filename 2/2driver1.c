#include<stdio.h>
#include "hri1.h"

int main(){
    
    float c1[2] = {2,3};
    float c2[2] = {7,-2};
    float sum[2] = {0};
    float product[2] = {0};

    add_complex(c1,c2,sum);
    mul_complex(c1,c2,product);

    printf("Sum = %.2f + %.2fi\n",sum[0],sum[1]);
    printf("Product = %.2f + %.2fi\n",product[0],product[1]);
    
    return 0;
}

gcc -c complex.c → ar rcs libcomplex.a complex.o → gcc test.c -L. -lcomplex -o test

gcc -fPIC -shared -o libmath.so math.c → gcc test.c -L. -lmath -Wl,-rpath,. -o test