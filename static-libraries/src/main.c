#include <stdio.h>

#include "libcircle.h"
#include "libsquare.h"

int main() {
    float radius = 5.0;
    printf("The area of a circle with radius %f is %f\n", radius, area_circle(radius));
    printf("The area of a square with side %f is %f\n", radius, area_square(radius));
    return 0;
}