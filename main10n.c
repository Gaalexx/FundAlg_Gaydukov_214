#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

double polynomial(double x, int n, double** coefs, int pow_a){
    double res = /* pow_a == 0? */ (*coefs)[0];//: (*coefs)[0] * (n - pow_a + 1);
    (*coefs)[0] = res * (n);
    for (int i = 1; i < n + 1; i++)
    {
        res = res * x + /* pow_a == 0? */ (*coefs)[i];//: (*coefs)[i] * (n - pow_a );
        (*coefs)[i] = (*coefs)[i] * (n - i);//*= pow_a == 0? (*coefs)[i]: ((*coefs)[i] * (n - pow_a));
    }
    return res;
}

int Tailor_sum(double epsilon, double a, double** coef, int n, ...){
    va_list list;
    va_start(list, n);
    long long int fact = 1;
    *coef = (double*)malloc(sizeof(double) * (n + 1));
    if(*coef == NULL){
        return -1;
    }
    double* o_coef = (double*)malloc(sizeof(double) * (n + 1));
    if(o_coef == NULL){
        free(coef);
        return -1;
    }
    for (int i = 0; i < n + 1; i++)
    {
        o_coef[i] = va_arg(list, double);
    }
    va_end(list);
    *coef[0] = polynomial(a, n, &o_coef, 0);
    for (int i = 1; i < n + 1; i++)
    {
        fact *= i;
        (*coef)[i] = polynomial(a, n - i, &o_coef, i) / (double)fact;
    }
    
    free(o_coef);
    return 0;
}


int main(){
    double* coef;
    Tailor_sum(0.0000001, 1.0, &coef, 3, 5.0, 2.0, 3.0, 10.0);
    for (int i = 3; i >= 0; i--)
    {
        printf("%f\t", coef[i]);
    }
    printf("\n");
    free(coef);
    return 0;
}