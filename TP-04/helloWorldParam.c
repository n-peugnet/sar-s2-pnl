#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_DESCRIPTION("Module \"hello word\" pour noyau linux");
MODULE_AUTHOR("Nicolas Peugnet, LIP6");
MODULE_LICENSE("GPL");

static char *whom = "Nicolas";
module_param(whom, charp, 0660);
static int howmany = 1;
module_param(howmany, int, 0660);

static int __init hello_init(void)
{
	int i;

	for (i = 0; i < howmany; i++)
		pr_info("(%d) Hello, %s\n", i, whom);
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	pr_info("Goodbye, %s\n", whom);
}
module_exit(hello_exit);
