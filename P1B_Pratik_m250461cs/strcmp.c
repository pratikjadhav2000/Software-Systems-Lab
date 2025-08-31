#include<stdio.h>
#include<string.h>

int main(){

    char *str1 = "ABCDdfsdf";
    char *str2 = "ABCcz";

    printf("%d\n",strcmp(str1,str2));

    return 0;
}