#include <linux/module.h>
#include <linux/kernel.h>

MODULE_DESCRIPTION("A kernel module to try the sysfs");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

static ssize_t hello_show(struct kobject *kobj, struct kobj_attribute *attr,
		      char *buf)
{
	return strlcpy(buf, "Hello sysfs!", 13);
}

static struct kobj_attribute hello_kobj = __ATTR_RO(hello);

static int hellosysfs_init(void)
{
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
