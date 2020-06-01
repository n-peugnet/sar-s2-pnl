#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/dcache.h>
#include <linux/rculist_bl.h>

MODULE_DESCRIPTION("A kernel module to try the sysfs");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

static int weasel_init(void)
{
	int size = 1 << d_hash_shift;
	struct hlist_bl_node *node;
	struct dentry *dentry;
	int count = 0;
	struct hlist_bl_head *i;

	pr_info("weasel module loaded\n");
	pr_info("dentry hashtable addr: %p\n", dentry_hashtable);
	pr_info("dentry hashtable size: %d\n", size);
	for (i = dentry_hashtable; i < dentry_hashtable + size; i++) {
		hlist_bl_for_each_entry_rcu(dentry, node, i, d_hash) {
			count++;
			/* pr_info("%s\n", dentry->d_name.name); */
		}
	}
	pr_info("count=%d\n", count);
	return 0;
}

static void weasel_exit(void)
{
	pr_info("weasel module unloaded\n");
}

module_init(weasel_init);
module_exit(weasel_exit);
