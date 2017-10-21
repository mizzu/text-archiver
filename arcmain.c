#include "arc.h"

void main(int argc, char * argv[])
{
	int flag = 0;
	if((strcmp(argv[1], "-c")) == 0) // checks the command line args
	{
		if(argc < 4)
		{
			fprintf(stderr, "Wrong number of command line args for -c\n");
			fflush(stderr);
			exit(1);
		}
		flag = 1; // sets a flag depending on the arg
	} else if((strcmp(argv[1], "-x")) == 0) {
		if(argc != 3)
		{
			fprintf(stderr, "Wrong number of command line args for -x\n");
			fflush(stderr);
			exit(1);
		}
		flag = 2;
	} else if((strcmp(argv[1], "-p")) == 0) {
		if(argc != 4)
		{
			fprintf(stderr, "Wrong number of command line args for -p\n");
			fflush(stderr);
			exit(1);
		}
		flag = 3;
	}
	else
	{
		fprintf(stderr, "Invalid flag\n"); // checks for flag
		fflush(stderr);
		exit(1);
	}
	switch(flag)
	{ // depending on the flag, will go to corresponding function
		case 1: createArc(argv, argc);
				break;
		case 2: unArc(argv[2]);
				break;
		case 3: lsArc(argv[3], argv[2]);
				break;
	}
}
