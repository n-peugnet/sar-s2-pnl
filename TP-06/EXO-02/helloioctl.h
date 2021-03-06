#include <asm/ioctl.h>

#pragma once
#define MAGIC_NUM 'N'
#define DEV_NAME "hello"
#define SIZE_WHO 10
#define SIZE_MSG 20
#define HELLO _IOR(MAGIC_NUM, 1, int)
#define WHO   _IOW(MAGIC_NUM, 2, int)

static int helloioctl_init(void);
static void helloioctl_exit(void);
