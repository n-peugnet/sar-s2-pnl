#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/pid.h>

MODULE_DESCRIPTION("A kernel module to monitor a task based on its pid");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

static pid_t target;
module_param(target, int, 0660);

static int monitor_pid(pid_t pid)
{
	struct pid *s_pid;
	int ret = 0;

	s_pid = find_get_pid(pid);
	if (s_pid == NULL) {
		ret = -1;
		goto monitor_pid_destructor;
	}
	pr_info("pid_t: %d, pid->level: %d\n", pid, s_pid->level);
monitor_pid_destructor:
	put_pid(s_pid);
	return ret;
}

static ssize_t taskmonitor_show(struct kobject *kobj,
				struct kobj_attribute *attr, char *buf)
{
	monitor_pid(target);
	return sprintf(buf, "Hello!\n");
}

static ssize_t taskmonitor_store(struct kobject *kobj,
				 struct kobj_attribute *attr, const char *buf,
				 size_t count)
{
	pr_info("Hello baby!");
	return count;
}

static struct kobj_attribute hello_kobj = __ATTR_RW(taskmonitor);

static int taskmonitor_init(void)
{
	pr_info("taskmonitor module loaded\n");
	return sysfs_create_file(kernel_kobj, &hello_kobj.attr);
}

static void taskmonitor_exit(void)
{
	sysfs_remove_file(kernel_kobj, &hello_kobj.attr);
	pr_info("taskmonitor module unloaded\n");
}

module_init(taskmonitor_init);
module_exit(taskmonitor_exit);
