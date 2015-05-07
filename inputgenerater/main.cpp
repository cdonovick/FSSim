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
	fprintf(stderr, " Memory generaton everything starts at 50.  [-u <use>] [-i <instructions>]  [-w <%reads/writes>] [-s <avg file size>] [-r range in file size] [-l <loaclity>]\n ");
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
                    p.i = n;
                }
				else{
					perror("number of instructions cannot be negative");
				}
                break;
			case 'w':
				n = atoi(optarg);
				if(n >= 0){
					p.rw = n;
				}
				else{
					perror("number of reads/writes cannot be negative");
				}
				break; 
			case 's':
				n = atoi(optarg);
                if(n >= 0){
					p.s = n;
				}
				else{
					perror("file size avg cannot be negative");
				}
				break;
			case 'r':
				n = atoi(optarg);
                if(n >= 0){
					p.r = n;
				}
				else{
					perror("range cannot be less than 0");
			    }
				break;
	    		case 'l':
				n = atoi(optarg);
                if(n >= 0){
					p.l = n;
				}
				else{
					perror("locality cannot be negative. Choose a number out of 100");
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

