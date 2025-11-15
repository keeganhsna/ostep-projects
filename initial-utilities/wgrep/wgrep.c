#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	
	if (argc < 2){
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	char *str = argv[1];
	
	if (argc == 3){
	char *file = argv[2];
	FILE *fp = fopen(file,"r");
	
	if (fp == NULL){
		printf("wgrep: cannot open file\n");
		exit(1);
	}
	
	char *line = NULL;
	size_t len = 0;

	while(getline(&line,&len,fp) != -1){
		if (strstr(line,str) != NULL){
			printf("%s",line);
			
	}
	}
	fclose(fp);
	}
	
	if (argc == 2){
		char buffer[256];
		while (fgets(buffer,sizeof(buffer),stdin) != NULL) {
			if (strstr(buffer,str) != NULL){
			printf("%s",buffer);
			
	}
			
				}
	}
	
	exit(0);

}
