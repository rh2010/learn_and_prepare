#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <strings.h>
#include <string.h>

#define PIT_DIR "pit_files"

void initialize(void)
{
	int ret =0;
	/* Create a dir which will contain the PIT-Files */
	ret = mkdir(PIT_DIR, 0775);
	if (ret == -1) {
		perror("Dir creation failed");
		if (errno == EEXIST) {
		// Nothing .. 
		} else {
			assert(0);
		}
	} else {
		printf("Created dir %s\n", PIT_DIR);
	}

}

void remove_all_files(char *dir_name)
{
	DIR *dir;
	struct dirent *ent;
	int ret = 0;
	char filename[256];

	assert(dir_name != NULL);

	printf("in remove_all_files\n");
	dir = opendir(dir_name);
	if (dir) {
		while ((ent = readdir(dir)) != NULL) {
			printf("File: %s", ent->d_name);
			if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0) || (strstr(ent->d_name, "."))) {
				printf("\t Skipping \n");
				continue;
			}
			bzero(filename, sizeof(filename));
//			snprintf(filename, 256, "pit_files/%s", ent->d_name);
			snprintf(filename, 256, "%s/%s", dir_name, ent->d_name);
			printf("\t Deleting %s\n", filename);
			ret = remove(filename);
			if (ret == -1) {
				perror("Removing dir failed");
			}
		}
		closedir(dir);
	} else { // dir is NULL
		printf("Could not open dir: %s\n", dir_name);
		perror("Error opening dir");
	}

}
void uninitialize(void)
{
	int ret = 0;

try_again:
	ret = rmdir(PIT_DIR);
	if (ret == -1) {
		perror("Removing dir failed");
		if (errno == ENOTEMPTY) {
			remove_all_files(PIT_DIR);
			goto try_again;		
		} else {
			assert(0);
		}
	}
//	perror("Remove error: ");
	assert(ret == 0);
}

int main (void)
{
	char c;
	initialize();

	scanf("%c", &c);
	uninitialize();
	return 0;
}
