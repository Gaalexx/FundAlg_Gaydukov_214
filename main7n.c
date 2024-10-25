#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>

typedef double (*bin_callback)(double x);

double binary_search(double a, double b, double epsilon, bin_callback func){
    double right = b;
    double left = a;
    double mid = 0;

    while(right - left >= (epsilon / 10)){
        mid = (left + right) / 2.0;
        if(func(mid) > 0){
            right = mid;
        }
        else{
            left = mid;
        }
    }
    return mid;
}

double uravn(double x){
    return 10 * x + 3.0 * x + 143;
}

int main(){
    printf("%f\n", binary_search(-1000, 5000, 0.000001, uravn));
}