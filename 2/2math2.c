#include <math.h>
#include "hri2.h"

// Function to find magnitude of complex number.
float absolute_complex(float c[]) {
    return sqrt((c[0] * c[0]) + (c[1] * c[1]));
}

// Function to square a complex number.
void power_complex(float c[], float result[]) {
    result[0] = (c[0] * c[0]) - (c[1] * c[1]);
    result[1] = 2 * c[0] * c[1];
}