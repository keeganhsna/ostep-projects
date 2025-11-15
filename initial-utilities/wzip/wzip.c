#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	
	if (argc < 2){
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}


	int count = 1;
	int curr, prev;
	int init = 0;
	for (int i = 1; i < argc; i ++){
		char *file = argv[i];

		FILE *fp = fopen(file,"r");

		if (fp == NULL){
			printf("wzip: cannot open file\n");
			exit(1);
		}
		


		while ((curr = fgetc(fp)) != EOF) {
			if(!init){
				prev = curr;
				count = 1;
				init = 1;
			}else if( curr == prev ) {
				count ++;
			}else{
				fwrite(&count,sizeof(int),1,stdout);
				fputc(prev,stdout);
				prev = curr;
				count = 1;

			}
		}
		fclose(fp);
	}
			if(init){
			fwrite(&count,sizeof(int),1,stdout);
				fputc(prev,stdout);
			}



        	
	exit(0);

}
