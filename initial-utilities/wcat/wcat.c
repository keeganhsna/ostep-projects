#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	if (argc < 2){
		exit(0);
	}

	for (int i = 1; i < argc; i++){
	char *str = argv[i];
	FILE *fp = fopen(str,"r");
	
	if (fp == NULL){
		printf("wcat: cannot open file\n");
		exit(1);
	}
	char buffer[256];

	while(fgets(buffer,sizeof(buffer),fp) != NULL){
			printf("%s",buffer);
	}
	
	fclose(fp);
	}
	exit(0);
}

