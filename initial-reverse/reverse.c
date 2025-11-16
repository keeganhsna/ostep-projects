#include <complex.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MORE_LINES 1024
#define MORE_CHARS 1024

int main(int argc, char* argv[]){
	FILE *fp;
	
	if (argc == 1){
		fp = stdin;
	}else if (argc ==2){

	fp = fopen("text.txt", "r");
	//FILE *fp = fopen("text.txt","r");
	
	if (fp == NULL){
		fprintf(stderr,"error: cannot open file '%s'",argv[1]);
		exit(1);
	}
	} else{
		fprintf(stderr,"usage: reverse <input> <output>");
		exit(1);
	}

	char **lines;
	lines = malloc(sizeof(char *) * MORE_LINES);
	
	size_t total_lines = 0;
	size_t total_chars = 0;
	char c;

	do{
		c= fgetc(fp);
		if(ferror(fp)){
			printf("error reading file\n");
			return 1;
		}
		if (feof(fp)){
			
			if (total_chars != 0){
			lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
			lines[total_lines][total_chars] = '\0';
			total_lines++;
			}

			break;
		}
		if (total_chars ==0){
			lines[total_lines] = malloc(MORE_CHARS);
		}
		lines[total_lines][total_chars] = c;
		total_chars ++;
		if (c == '\n'){
			lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
			lines[total_lines][total_chars] = '\0';
			total_lines++;
			total_chars = 0;

			if (total_lines % MORE_LINES == 0 ){
				size_t new_size = total_lines + MORE_LINES;
				lines = realloc(lines, sizeof(char *) * new_size);
			}
		}
		else if (total_chars % MORE_CHARS ==0){
			size_t new_size = total_chars + MORE_CHARS;
			lines[total_lines] = realloc(lines[total_lines], new_size);
		}
	}while (true);
	lines = realloc(lines, sizeof(char *) * total_lines);
	

	
	if (argc == 3){
		FILE *wfp = fopen(argv[2], "w");
		if (wfp == NULL){
			fprintf(stderr,"error: cannot open file '%s'",argv[2]);
			exit(1);
		}
		for (size_t i = total_lines-1; i >=0; i --){
			fprintf(wfp,"%s",lines[i]);
		}
		fclose(wfp);
	}

	for (size_t i = total_lines-1; i >=0; i --){
		printf("%s", lines[i]);
	}
	
	for (size_t i = total_lines-1; i >=0; i --){
		free(lines[i]);}	
	
	free(lines);
	//free these
	fclose(fp);
	return 0;
}
