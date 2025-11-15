#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	
	if (argc < 2){
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}

	int count;
	char ch;
	for (int i = 1; i < argc; i ++){
		FILE *fp = fopen(argv[i], "r");
		
		while(fread(&count,sizeof(int),1,fp) == 1 && fread(&ch,sizeof(char),1,fp) == 1){
		
		for (int j = 0; j < count; j++){
			fwrite(&ch,sizeof(char),1,stdout);
		}

	}

        	
		fclose(fp);
	}
	exit(0);

}
