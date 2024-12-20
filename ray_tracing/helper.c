#include "helper.h"

#include <stdlib.h>

const double PI = 3.1415926535897932385;

double degrees_to_radians(double degrees)
{
    return (degrees * PI) / 180.0;
}

double random_double()
{
    // Random double in 0 <= n < 1
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

double random_double_in_range(double min, double max)
{
    return min + ((max - min) * random_double());
}