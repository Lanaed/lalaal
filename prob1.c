#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
 char pathname[] = "Catalog1";
 printf ("%s\n", pathname);
 int mode = 0777;
 mkdir (pathname, mode);
/* DIR *dp;
 dp = opendir(pathname);
 if (dp==NULL)
 {
	printf("Sorry, I can't open the directory %s\n", pathname);
	exit (1);
 }*/
 int change_dir;
 change_dir = chdir (pathname);

 int file;
 mode_t mode_files = S_IRWXU|S_IRGRP|S_IROTH;
 int flags = O_RDONLY|O_CREAT|O_EXCL;

 char filename[] = "";
 char filename1[] = "file1";
 char filename2[] = "file2";
 char filename3[] = "file3"; 
 for (int i = 0; i<3; i++)
 {
 	switch (i)
 	{
 		case 0:
			*filename = *filename1;
			printf ("%s", filename);
			break;
		case 1:
			*filename = *filename2;
			printf ("%s", filename);
			break;
		case 2:
			*filename = *filename3;
			printf ("%s", filename);
			break;
	}
 	file = open(filename, flags, mode_files);
	 if (file < 0)
 	{
 		printf("I cann't create file '%s'. This file already exists.\n", filename);
 		exit (1);
 	}	 
	 if (close(file) != 0)
 	{
 		printf("Cannot close created file with descriptor %d\n", file);
 		exit(1);
 	}
 }
// closedir (dp);
// rmdir (pathname);
 exit (0);

}

