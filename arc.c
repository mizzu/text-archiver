#include "arc.h"

void unArc(char * name)
{
	FILE * arc;
	if((arc = fopen(name, "rb")) == NULL) // if it fails to open/create the output it will exit
	{	
			fprintf(stderr, "Could not open archive file\n");
			fflush(stderr);
			exit(1);
	}
	unsigned char n; // gets char
	fread(&n, 1, 1, arc); // reads in number of files
	unsigned char lstr[255];
	char * strs[255];
	unsigned int fsize[255]; // arrays for info of the file
	int i = 0;
	for(i = 0; i < n; i++)
	{
		fread(&(lstr[i]), 1, 1, arc); // reads str length
		strs[i] = malloc(lstr[i]+1); // mallocs string
		if(strs[i] == NULL)
		{
			fprintf(stderr, "Could not malloc string for archive\n");
			fflush(stderr);
			exit(1); // malloc check
		}		
		fread(strs[i], lstr[i], 1, arc); // reads string
		strs[i][lstr[i]] = '\0'; // adds null terminating
		fread(&(fsize[i]), 4, 1 , arc); // gets filesize
	}
	int fd = 0;
	int z = 0;
	char * buf;
	int cfd;
	for(i = 0; i < n; i++)
	{
		if((fd = open(strs[i], (O_CREAT | O_WRONLY), (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP))) < 0)
		{ // creates file, gives it write access, and user/group permissions
			fprintf(stderr, "Could not create file: '%s', fd:'%d'\n", strs[i], fd);
			fflush(stderr);
			exit(1); // if it cannot create the file it will exit
		}
			buf = malloc(fsize[i]+1); // creates a buffer for the size of the file
			fread(buf, fsize[i], 1, arc); // reads from archive the whole file
			buf[fsize[i]] = '\0'; // adds null terminating (for write)
			if((write(fd, buf, fsize[i])) != fsize[i])		// writes to to the file and checks
			{
				fprintf(stderr, "Could not write all contents to file\n");
				fflush(stderr);
				exit(1);
			}
			free(buf); // frees buf
		close(fd); // closes file
	} // onto the next
	fclose(arc); // closes the archive
}