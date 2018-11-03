#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>


int main()
{
	char pathname[] = "Catalog1";
	int mode = 0777;
	mkdir (pathname, mode);

	int change_dir;
	change_dir = chdir (pathname);

	int file;
	mode_t mode_files = S_IRWXU|S_IRGRP|S_IROTH;
	int flags = O_RDONLY|O_CREAT|O_EXCL;

	char filenames[][6] = {{'f','i','l','e','1', '\0'}, {'f','i','l','e','2', '\0'},{'f','i','l','e','3', '\0'}};
	for (char (*cf)[6] = filenames; cf < filenames + 3; cf++)
	{
		file = open(*cf, flags, mode_files);
		if (file < 0)
		{
			printf("I cann't create file '%s'. This file already exists.\n", *cf);
			exit (1);
		}	 
		if (close(file) != 0)
		{
			printf("Cannot close created file with descriptor %d\n", file);
			exit(1);
		}
	}
	DIR *dp = NULL;
	dp = opendir(".");
	if (dp==NULL)
	{
		printf("Cannot open current directory.Problem: %s\n", strerror (errno));
		exit(0);
	}
	struct dirent *fid_ptr = NULL;
	struct dirent fid;
	int fileD = 0;
	char file_link[PATH_MAX+1];
	fileD = readdir_r(dp,&fid, &fid_ptr);

	while (fid_ptr != NULL)
	{
		struct stat fid_info;
		if ( (strncmp(fid.d_name, ".", PATH_MAX) == 0)||(strncmp(fid.d_name, "..", PATH_MAX) == 0))
		{
			fileD = readdir_r(dp, &fid, &fid_ptr);
			continue;
		}	
//		strncpy (file_link, pathname, PATH_MAX);
//		strncat (file_link, "/", PATH_MAX);
//		strncat (file_link, fid.d_name, PATH_MAX);
		mode_t val;
		char acs[11];
		strncpy (file_link, fid.d_name, PATH_MAX);
		if (lstat(file_link, &fid_info) == 0)
		{	
			mode_t val;
			val = (fid_info.st_mode  & ~S_IFMT);
			acs[0] = (S_ISDIR(fid_info.st_mode)) ? 'd' : '-';
			acs[0] = (S_ISCHR(fid_info.st_mode)) ? 'b' : acs[0];
			acs[0] = (S_ISBLK(fid_info.st_mode)) ? 'c' : acs[0];
			acs[0] = (S_ISFIFO(fid_info.st_mode)) ? 'p' : acs[0];

			acs[1] = (val & S_IRUSR) ? 'r' : '-';
			acs[2] = (val & S_IWUSR) ? 'w' : '-';
			acs[3] = (val & S_IXUSR) ? 'x' : '-';

			acs[4] = (val & S_IRGRP) ? 'r' : '-';
			acs[5] = (val & S_IWGRP) ? 'w' : '-';
			acs[6] = (val & S_IXGRP) ? 'x' : '-';

			acs[7] = (val & S_IROTH) ? 'r' : '-';
			acs[8] = (val & S_IWOTH) ? 'w' : '-';
			acs[9] = (val & S_IXOTH) ? 'x' : '-';
			acs[10] = '\0';
			
			struct passwd *usr = getpwuid (fid_info.st_uid);
			struct group *gr = getgrgid (fid_info.st_gid);


			printf("%s   %s   %ld   %s   %s\n", acs, fid.d_name,
					fid_info.st_size, usr->pw_name, gr->gr_name);
		}
		else
			printf ("Error statting %s: %s\n", file_link, strerror(errno));
		fileD = readdir_r(dp, &fid, &fid_ptr);
	}

	closedir (dp);
// rmdir (pathname);
	exit (0);

}

