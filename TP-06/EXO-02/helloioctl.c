#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "helloioctl.h"

MODULE_DESCRIPTION("A kernel module to try the ioctl");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

static int major;
static const struct file_operations fops = {};

static int helloioctl_init(void)
{
	major = register_chrdev(0, NAME, &fops);
	pr_info("helloioctl module loaded with major %d\n", major);
	return 0;
}

static void helloioctl_exit(void)
{
	unregister_chrdev(major, NAME);
	pr_info("helloioctl module unloaded\n");
}

module_init(helloioctl_init);
module_exit(helloioctl_exit);
