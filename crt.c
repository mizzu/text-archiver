#include "arc.h"

void createArc(char * args[], int argc)
{
	unsigned char n = argc - 3;
	FILE* arch; // creates a file pointer to open the binary file
	if((arch = fopen(args[2], "w")) == NULL) // if it fails to open/create the output it will exit
	{	
			fprintf(stderr, "Could not create archive file\n");
			fflush(stderr);
			exit(1);
	}
	fwrite(&n, 1, 1, arch); // writes the number of files
	struct stat * hfs = malloc(sizeof(struct stat));
	unsigned int size;
	int i = 3;
	unsigned char l;
	while(i < argc) // until the end of the files list (starting at the first)
	{
		if((stat(args[i], hfs)) < 0)
		{
			fprintf(stderr, "Could not get stat for file: '%s'\n", args[i]);
			fflush(stderr);
			perror("stat");
			continue; // if it can't open stat it will go to the next one
		}
		size = hfs->st_size; // gets size
		l = strlen(args[i]); // gets the string lenth
		fwrite(&l, 1, 1, arch);
		fwrite(args[i], l, 1, arch);
		fwrite(&size, 4, 1, arch); // write the length of name, name, and size
		i++; // goes to next arg
	}
	i = 3; // resets i
	int fd = 0; // file descriptor
	char buf[1];
	unsigned int count = 0;
	while(i < argc) // again while not end of args
	{
		if((fd = open(args[i], O_RDONLY)) < 0) // if it can't open the file it continues
		{
			fprintf(stderr, "Could not open file: '%s'\n", args[i]);
			fflush(stderr);
			i++;
			continue;
		}
		while((read(fd, buf, 1)) > 0) //reads each char one by one and writes it
		{
			fwrite(buf, 1, 1, arch);
		}
		close(fd); // closes file
		i++; // onto the next
	}
	fclose(arch); // closes the archive
}