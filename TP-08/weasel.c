#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/dcache.h>
#include <linux/rculist_bl.h>

MODULE_DESCRIPTION("A kernel module to try the sysfs");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

#define MODULE_NAME "weasel"
#define WHOAMI "whoami"

static struct proc_dir_entry *proc_parent;
static struct proc_dir_entry *proc_file;

static ssize_t whoami_read(struct file *f, char *buf, size_t len, loff_t *off)
{
	char *text = "I'm a weasel!\n";

	return simple_read_from_buffer(buf, len, off, text, 16);
}

static const struct file_operations proc_file_fops = {
	.owner = THIS_MODULE,
	.read = whoami_read,
};

static void print_dentry_info(void)
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
}

static int __init weasel_init(void)
{
	proc_parent = proc_mkdir(MODULE_NAME, NULL);
	proc_file = proc_create(WHOAMI, 0444, proc_parent, &proc_file_fops);
	print_dentry_info();
	return 0;
}

static void __exit weasel_exit(void)
{
	remove_proc_subtree(MODULE_NAME, NULL);
	pr_info("weasel module unloaded\n");
}

module_init(weasel_init);
module_exit(weasel_exit);
