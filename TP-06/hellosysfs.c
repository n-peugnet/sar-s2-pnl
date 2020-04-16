#include <linux/module.h>
#include <linux/kernel.h>

#define NAME_LENGTH 10

MODULE_DESCRIPTION("A kernel module to try the sysfs");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

static char name[NAME_LENGTH];

static ssize_t hello_show(struct kobject *kobj, struct kobj_attribute *attr,
		      char *buf)
{
	return sprintf(buf, "Hello %s!\n", name);
}

static ssize_t hello_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t count)
{
	size_t len = NAME_LENGTH;

	return strlcpy(name, buf, min(len, count + 1));
}

static struct kobj_attribute hello_kobj = __ATTR_RW(hello);

static int hellosysfs_init(void)
{
	strncpy(name, "sysfs", 6);
	pr_info("hellosysfs module loaded\n");
	return sysfs_create_file(kernel_kobj, &hello_kobj.attr);
}

static void hellosysfs_exit(void)
{
	sysfs_remove_file(kernel_kobj, &hello_kobj.attr);
	pr_info("hellosysfs module unloaded\n");
}

module_init(hellosysfs_init);
module_exit(hellosysfs_exit);
