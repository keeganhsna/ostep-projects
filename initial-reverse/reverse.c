#include <complex.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024

int main(int argc, char* argv[]){
	FILE *fp;
	FILE *out;	
	if (argc == 1){
		fp = stdin;
	} else if ( argc > 3){
		fprintf(stderr,"usage: reverse <input> <output>\n");
		exit(1);
	}
	if (argc > 1 ){
	fp = fopen(argv[1], "r");
	
	if (fp == NULL){
		fprintf(stderr,"reverse: cannot open file '%s'\n",argv[1]);
		exit(1);
	}
	}
	if (argc ==3 ){
		if(strcmp(argv[1],argv[2]) == 0){
		fprintf(stderr, "reverse: input and output file must differ\n");
		exit(1);}
		
		out = fopen(argv[2], "w");
		if (out == NULL){
			fprintf(stderr,"error: cannot open file '%s'",argv[2]);
			exit(1);
		}
		struct stat s1, s2;
		
    	if (stat(argv[1], &s1) == -1) {
        	perror("stat file1");
       	 exit(1);
    	}

    	if (stat(argv[2], &s2) == -1) {
        	perror("stat file2");
        	exit(1);
   	 }

    	if (s1.st_ino == s2.st_ino && s1.st_dev == s2.st_dev) {
        	fprintf(stderr,"reverse: input and output file must differ\n");
		exit(1);
    	}
	}
	

	char **lines;
	lines = malloc(sizeof(char *) * MORE_LINES);
	
	if (!lines){
		fprintf(stderr,"malloc failed\n");
		exit(1);
	}

	size_t total_lines = 0;
	size_t total_chars = 0;
	char c;

	do{
		c= fgetc(fp);
		if(ferror(fp)){
			printf("error reading file\n");
			exit(1);
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
		
	if (!lines[total_lines]){
		fprintf(stderr,"malloc failed\n");
		exit(1);
	}
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
		for (size_t i = total_lines; i >0; i --){
			fprintf(out,"%s",lines[i-1]);
		}
		fclose(out);
	}else{
		for (size_t i = total_lines; i >0; i--){
			fprintf(stdout,"%s",lines[i-1]);
		}
	}

	
	for (size_t i = total_lines; i >0; i --){
		free(lines[i-1]);}	
	
	free(lines);
	//free these
	fclose(fp);
	exit(0);
}
