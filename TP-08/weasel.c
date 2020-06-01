#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/dcache.h>
#include <linux/rculist_bl.h>

MODULE_DESCRIPTION("A kernel module to try the sysfs");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

#define MODULE_NAME "weasel"
#define FILE_WHOAMI "whoami"
#define FILE_LIST "list"

static struct proc_dir_entry *parent;
static struct proc_dir_entry *file_whoami;
static struct proc_dir_entry *file_list;

/*********************** whoami *******************************/

static ssize_t whoami_read(struct file *f, char *buf, size_t len, loff_t *off)
{
	char *text = "I'm a weasel!\n";

	return simple_read_from_buffer(buf, len, off, text, 16);
}

static const struct file_operations file_whoami_fops = {
	.owner = THIS_MODULE,
	.read = whoami_read,
};

/************************** functions *****************************/

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

static void seq_print_dentries(struct seq_file *s)
{
	int size = 1 << d_hash_shift;
	struct hlist_bl_node *node;
	struct dentry *dentry;
	struct hlist_bl_head *i;

	for (i = dentry_hashtable; i < dentry_hashtable + size; i++) {
		hlist_bl_for_each_entry_rcu(dentry, node, i, d_hash) {
			seq_dentry(s, dentry, "");
			seq_puts(s, "\n");
		}
	}
}

/************************* list *****************************/

static int list_seq_show(struct seq_file *s, void *v)
{
	seq_print_dentries(s);
	return 0;
}

static int list_open(struct inode *inode, struct file *file)
{
	return single_open(file, list_seq_show, file->private_data);
}

static const struct file_operations file_list_fops = {
	.owner   = THIS_MODULE,
	.open    = list_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

/**************************** init ***************************/

static int __init weasel_init(void)
{
	parent = proc_mkdir(MODULE_NAME, NULL);
	file_whoami = proc_create(FILE_WHOAMI, 0444, parent, &file_whoami_fops);
	file_list = proc_create(FILE_LIST, 0444, parent, &file_list_fops);
	print_dentry_info();
	return 0;
}

/**************************** exit ****************************/

static void __exit weasel_exit(void)
{
	remove_proc_subtree(MODULE_NAME, NULL);
	pr_info("weasel module unloaded\n");
}

module_init(weasel_init);
module_exit(weasel_exit);
