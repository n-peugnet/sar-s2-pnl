#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "helloioctl.h"

int main(void)
{
	char buf[SIZE_MSG];
	int fd;
	int ret;

	fd = open("/dev/hello", O_RDWR);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	ret = ioctl(fd, WHO, "beer");

	ret = ioctl(fd, HELLO, buf);
	printf("return: %d, buf: %s\n", ret, buf);
}
