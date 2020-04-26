#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "helloioctl.h"

MODULE_DESCRIPTION("A kernel module to try the ioctl");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

static int major;
static char who[SIZE_WHO] = "ioctl";
static char buf[SIZE_MSG];

static long hello_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	size_t not_copied;

	switch (cmd) {
	case HELLO:
		pr_info("HELLO cmd");
		sprintf(buf, "Hello %s!\n", who);
		not_copied = copy_to_user((char *)arg, buf, SIZE_MSG);
		break;
	case WHO:
		pr_info("WHO cmd");
		not_copied = copy_from_user(who, (char *)arg, SIZE_WHO);
		break;
	default:
		return -ENOTTY;
	}
	return not_copied;
}

static const struct file_operations fops = {
	.unlocked_ioctl = hello_ioctl
};

static int helloioctl_init(void)
{
	major = register_chrdev(0, DEV_NAME, &fops);
	pr_info("helloioctl module loaded with major %d\n", major);
	return 0;
}

static void helloioctl_exit(void)
{
	unregister_chrdev(major, DEV_NAME);
	pr_info("helloioctl module unloaded\n");
}

module_init(helloioctl_init);
module_exit(helloioctl_exit);
