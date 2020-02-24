#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_DESCRIPTION("Module pour modifier lister les superblocks");
MODULE_AUTHOR("Nicolas Peugnet, LIP6");
MODULE_LICENSE("GPL");

void iter_handler(struct super_block *sb, void *arg)
{
    pr_info("%d", sb->s_dev);
}

static int __init hello_init(void)
{
	pr_info("Hello, show_sb\n");
    iterate_supers(iter_handler, NULL);
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	pr_info("Goodbye, show_sb\n");
}
module_exit(hello_exit);

