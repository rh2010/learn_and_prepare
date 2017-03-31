#include "my_header.h"

#define INPUT_FILE "./ifile"
#define OUTPUT_FILE "./ofile"

#define MAGIC	0xdeadbeef
int
main(void)
{
	int ifd, ofd;
	bool ifile_opened = TRUE;
	bool ofile_opened = TRUE;

	ifd = open(INPUT_FILE, O_RDONLY);
	if (ifd == -1) {
		printf("Unable to open file %s, error:%s \n", INPUT_FILE, strerror(errno));
	}
	printf("Input file %s, opened!\n", INPUT_FILE);

	ofd = open(OUTPUT_FILE, (O_WRONLY|O_TRUNC));
	if (ofd == -1) {
		printf("Unable to open file %s, error:%s \n", OUTPUT_FILE, strerror(errno));
	}
	printf("Output file %s, opened!\n", OUTPUT_FILE);

	close(ofd);
	close(ifd);

	printf("Magic: [%#x] and [0x%x]\n", MAGIC, MAGIC);
	return (0);
}
