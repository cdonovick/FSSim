#include<getopt.h>
#include "input_gen.h"
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

char * itoa(char *buf, int value) {
    sprintf(buf, "%d", value);
    return buf;
}


void use(){
    fprintf(stderr, " Memory generaton everything starts at 50.  [-u <use>] [-i <instructions>]  [-r <reads>] [-w <writes>] [-t <touch>] [-g <grow>] [-d <delete>] [-l <loaclity>] [-s <size>] [-a <rAnge] \n ");
}


int main(int argc, char **argv){
    params p;
    int c;
    int n = 0;
    opterr=0;

    while((c=getopt(argc,argv,"uA:L:P:R:D:")) != -1){
        switch(c){
            case 'u':
                use();
                exit(1);	
            case 'i':
                n = atoi(optarg);
                if(n >0){
                    p.instructions = n;
                }
                else{
                    perror("number of instructions cannot be negative");
                }
                break;
            case 'r':
                n = atoi(optarg);
                if(n >= 0){
                    p.read = n;
                }
                else{
                    perror("number of reads cannot be negative");
                }
                break;  
            case 'w':
                n = atoi(optarg);
                if(n >= 0){
                    p.write = n;
                }
                else{
                    perror("number of writes cannot be negative");
                }
                break;  
            case 't':
                n = atoi(optarg);
                if(n >= 0){
                    p.touch = n;
                }
                else{
                    perror("touch cannot be negative");
                }
                break;
            case 'g':
                n = atoi(optarg);
                if(n >= 0){
                    p.grow = n;
                }
                else{
                    perror("grow cannot be less than 0");
                }
                break;
            case 'd':
                n = atoi(optarg);
                if(n >= 0){
                    p.del = n;
                }
                else{
                    perror("delete cannot be less than 0");
                }
                break;
            case 'l':
                n = atoi(optarg);
                if(n >= 0){
                    p.locality = n;
                }
                else{
                    perror("locality cannot be negative. Choose a number out of 100");
                }
                break;
            case 's':
                n = atoi(optarg);
                if(n >= 0){
                    p.size = n;
                }
                else{
                    perror("size cannot be negative. Choose a number out of 100");
                }
                break;
            case 'a':
                n = atoi(optarg);
                if(n >= 0){
                    p.range = n;
                }
                else{
                    perror("range cannot be negative. Choose a number out of 100");
                }
                break;
            case '?':
                fprintf(stderr, "Unknown argument: -%c \n", optopt);
                use();
                return -1;  
        }
    }

    input_gen a(p);
    a.generate();
}

