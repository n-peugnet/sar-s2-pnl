#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched/task.h>
#include <linux/kthread.h>

MODULE_DESCRIPTION("A kernel module to monitor a task based on its pid");
MODULE_AUTHOR("Nicolas Peugnet <n.peugnet@free.fr>");
MODULE_LICENSE("GPL");

static pid_t target;
module_param(target, int, 0660);

struct task_monitor {
	struct pid *pid;
};

static struct task_monitor task_monitor;
static struct task_struct *monitor_thread;
static u_int16_t seconds = 5;

static void put_current_pid(void)
{
	if (task_monitor.pid != NULL)
		put_pid(task_monitor.pid);
}

static int monitor_pid(pid_t pid)
{
	struct pid *s_pid;
	int ret = 0;

	put_current_pid();
	s_pid = find_get_pid(pid);
	if (s_pid == NULL)
		return -1;
	task_monitor.pid = s_pid;
	pr_info("pid_t: %d, pid->level: %d\n", pid, s_pid->level);
	return ret;
}

static int monitor_fn(void *unused)
{
	struct task_struct *task;

	while (!kthread_should_stop()) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(seconds * HZ);
		if (task_monitor.pid == NULL)
			continue;
		task = get_pid_task(task_monitor.pid, PIDTYPE_PID);
		if (pid_alive(task)) {
			pr_info("pid %d usr %lld sys %lld", task->pid,
				task->utime / 1000000, task->stime / 1000000);
		}
		put_task_struct(task);
	}
	return 0;
}

static ssize_t taskmonitor_show(struct kobject *kobj,
				struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, 16, "target: %d\n", target);
}

static ssize_t taskmonitor_store(struct kobject *kobj,
				 struct kobj_attribute *attr, const char *buf,
				 size_t count)
{
	switch (*buf) {
	case 'r':
	default:
		monitor_pid(target);
		break;
	}
	return count;
}

static struct kobj_attribute hello_kobj = __ATTR_RW(taskmonitor);

static int taskmonitor_init(void)
{
	int err;

	err = sysfs_create_file(kernel_kobj, &hello_kobj.attr);
	if (err)
		return err;
	monitor_pid(target);
	monitor_thread = kthread_run(monitor_fn, NULL, "monitor_fn");
	pr_info("taskmonitor module loaded\n");
	return 0;
}

static void taskmonitor_exit(void)
{
	if (monitor_thread)
		kthread_stop(monitor_thread);
	sysfs_remove_file(kernel_kobj, &hello_kobj.attr);
	put_current_pid();
	pr_info("taskmonitor module unloaded\n");
}

module_init(taskmonitor_init);
module_exit(taskmonitor_exit);
