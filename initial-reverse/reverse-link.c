#include <complex.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct _node {
	char *content;
	struct _node *next;
}node;


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
	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	node *head = NULL;
	while((read = getline(&line,&len,fp))!=-1){
		node *np = malloc(sizeof(node));
		np->content = (char *) malloc(sizeof(char) * len);
		strcpy(np->content,line);
		np->next = head;
		head = np;
	}

	
	if (argc != 3){
		out= stdout;
	}
	
	node *temp = head;
	
	while(temp !=NULL){
		fprintf(out,"%s",temp->content);
		temp = temp->next;
	}

	if (argc ==3){
		fclose(out);
	}
	
	//free these
	fclose(fp);
	exit(0);
}
