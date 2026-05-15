#include <stdio.h>
#include "hri2.h"

int main() {
    float c[2] = {4,3};
    float power[2];
    float magnitude;

    // Function calls.
    magnitude = absolute_complex(c);
    power_complex(c, power);

    // Output.
    printf("\nMagnitude = %.2f\n", magnitude);
    printf("Power (Square) = %.2f + %.2fi\n",
           power[0], power[1]);

    return 0;
}