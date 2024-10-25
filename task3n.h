#include <stdio.h>
#include <ctype.h>
#include <string.h> //без strstr и strncmp
#include <stdarg.h>

int search_in_file(char* str, char* buf){ //доделать для слово\nслова
    FILE* dtr = fopen(buf, "r");
    if(dtr == NULL){
        return 0;
    }
    int len = strlen(str);
    printf("File %s:\n", buf);
    char ch = ' ';
    int flag_eq = 0;
    int enter_cnt = 1, num_of_sym = 1, iteration = 0, found_strs = 0;
    do
    {
        ch = fgetc(dtr);
        iteration++;
        num_of_sym++;
        if(ch == '\n' || ch == '\r'){
            num_of_sym = 1;
            enter_cnt++;
        }
        
        if(str[0] == ch){
            int n_iter = iteration;
            int i = 1;
            flag_eq = 1;
            while (ch != EOF || str[i] != ch || str[i] != '\0' || i != len)
            {
                ch = fgetc(dtr);
                //char str_i = str[i];
                if(str[i] != ch  && !(str[i] == '\n' && ch == '\r')){ 
                    fseek(dtr, iteration, SEEK_SET);
                    flag_eq = 0;
                    break;
                }
                i++;
                if(i == len){
                    break;
                }
            }
            if(flag_eq){
                printf("\tString: %d\tNumber: %d\n", enter_cnt, num_of_sym - 1);
                found_strs++;
                //num_of_sym++;
                fseek(dtr, iteration, SEEK_SET);
                flag_eq = 0;
            }
            else{
                fseek(dtr, iteration, SEEK_SET);
            }
        }
    } while (ch != EOF);
    if(!found_strs){
        printf("\tNo strings found\n");
    }
    fclose(dtr);
}

int search(char* str, int f_number, ...){
    va_list list;
    va_start(list, f_number);
    char* buf;
    for (int i = 0; i < f_number; i++)
    {
        char* buf = va_arg(list, char*);
        search_in_file(str, buf);
    }
    va_end(list);    
}
