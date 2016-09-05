//Interface for numerical program
//Using alglib for functions

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "interpolation.h"

using namespace alglib;

using namespace std;

int main(int argc, char **argv)
{
    real_1d_array x = "[-1.0,-0.5,0.0,+0.5,+1.0]";
    real_1d_array y = "[+1.0,0.25,0.0,0.25,+1.0]";
    real_1d_array d1;
    real_1d_array d2;

    spline1dgriddiff2cubic(x, y, d1, d2);

    printf("%s\n", d1.tostring(3).c_str()); // EXPECTED: [-2.0, -1.0, 0.0, +1.0, +2.0]
    printf("%s\n", d2.tostring(3).c_str()); // EXPECTED: [ 2.0,  2.0, 2.0,  2.0,  2.0]

    return 0;
}
