#include "arc.h"

void lsArc(char * name, char * prefix)
{
	FILE * arc;
	if((arc = fopen(name, "rb")) == NULL) // if it fails to open/create the output it will exit
	{	
			fprintf(stderr, "Could not open archive file\n");
			fflush(stderr);
			exit(1);
	}
	unsigned char n; // one byte for number of files
	fread(&n, 1, 1, arc); // reads it in
	unsigned char lstr[255]; // arrays to hold info for corresponding files
	char * strs[255];
	unsigned int fsize[255];
	int i = 0;
	for(i = 0; i < n; i++)
	{
		fread(&(lstr[i]), 1, 1, arc); // goes through each one
		strs[i] = malloc(lstr[i]+1);
		if(strs[i] == NULL)
		{
			fprintf(stderr, "Could not malloc string for archive\n"); // mallocs the string for the array
			fflush(stderr);
			exit(1);
		}		
		fread(strs[i], lstr[i], 1, arc); // reads string
		strs[i][lstr[i]] = '\0'; // adds null terminating
		fread(&(fsize[i]), 4, 1 , arc); // reads size
	}
	fclose(arc); // closes
	char * strc;
	for(i = 0; i < n; i++)
	{
		if((strc = strstr(strs[i], prefix)) != NULL) // goes through each string in array
		{
			printf("File:'%s'; Size:'%u' \n", strs[i], fsize[i]);
		} // uses strstr to find if there is a match
	}
}