#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>

int to_n_ns(double num, int sys){
    if(sys < 2 || sys > 36){
        return 0;
    }
    else if(sys != 2){
        int size = 4, cnt = 0;
        char* prec_nums = (char*)malloc(sizeof(char) * size);
        prec_nums[cnt++] = '0';
        prec_nums[cnt++] = '.';
        int iter = 0;
        while(num > 0.0000001 && iter < 15){
            num *= sys;
            if(size - 1 == cnt){
                char* prec_nums_n = (char*)realloc(prec_nums, size * 2);
                if(prec_nums_n == NULL){
                    free(prec_nums);
                    return 0;
                }
                prec_nums = prec_nums_n;
                size *= 2;
            }
            int num_i = (int)num;
            prec_nums[cnt++] = num_i < 10? '0' + num_i: 'A' + num_i - 10;
            num -= num_i;
            iter++;
        }
        prec_nums[cnt++] = '\0';
        if(iter == 14){
            printf("%s\n", prec_nums);
            free(prec_nums);
            return 0;
        }
        printf("%s\n", prec_nums);
        free(prec_nums);
        return 1;
    }
    else{
        int size = 4, cnt = 0;
        char* prec_nums = (char*)malloc(sizeof(char) * size);
        prec_nums[cnt++] = '0';
        prec_nums[cnt++] = '.';
        int iter = 0;
        while(num > 0.00000001 && iter < 15){
            num *= 2;
            if(size - 1 == cnt){
                char* prec_nums_n = (char*)realloc(prec_nums, size * 2);
                if(prec_nums_n == NULL){
                    free(prec_nums);
                    return 0;
                }
                prec_nums = prec_nums_n;
                size *= 2;
            }
            int num_i = (int)num;
            prec_nums[cnt++] = num_i + '0';
            num -= num_i;
            iter++;
        }
        prec_nums[cnt++] = '\0';
        
        if(iter == 14){
            printf("%s\n", prec_nums);
            free(prec_nums);
            return 0;
        }
        printf("%s\n", prec_nums);
        free(prec_nums);
        return 1;
    }
}

int arePeriodic(int sys, int num, ...){
    va_list list;
    va_start(list, num);
    double arg;
    for (int i = 0; i < num; i++)
    {
        arg = va_arg(list, double);
        printf("%d\n", to_n_ns(arg, sys));
    }
    va_end(list);
}

int main(){
    arePeriodic(2, 2, 0.5, 0.125);
}