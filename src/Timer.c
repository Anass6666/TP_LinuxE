
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

#define DRIVER_AUTHOR "Christophe Barès"
#define DRIVER_DESC "Hello world Module"
#define DRIVER_LICENSE "GPL"


static struct timer_list my_timer;

static void my_timer_callback(struct timer_list *timer)
{
printk("%s called (%ld)\n", __func__, jiffies);
}
static int __init my_init(void)
{
int ret;
pr_info("%s: Timer module loaded\n", __func__);


timer_setup(&my_timer, my_timer_callback, 0);
pr_info("%s: Setup timer to fire in 2s (%ld)\n", __func__, jiffies);
ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(2000)); //le temps avant l'appel de la callback my_timer_callback()
if (ret) pr_err("%s: Timer firing failed\n", __func__);
return 0;
}
static void __exit my_exit(void)
{
int ret;
ret = del_timer(&my_timer);
if (ret)
pr_err("%s: The timer is still is use ...\n", __func__);
pr_info("%s: Timer module unloaded\n", __func__);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);


// #include <linux/module.h>
// #include <linux/kernel.h>
// #include <linux/init.h>
// #include <linux/uaccess.h>
// #include <linux/proc_fs.h>
// #include <linux/timer.h>

// #define DRIVER_AUTHOR "Christophe Barès"
// #define DRIVER_DESC "Hello world Module"
// #define DRIVER_LICENSE "GPL"
// #define TAILLE 100
// #define INTERVALLE 100



// int hello_init(void)
// {
	// printk(KERN_INFO "Hello world!\n");

	// return 0;
// }

// void hello_exit(void)
// {
	// printk(KERN_ALERT "Bye bye...\n");
// }



// module_init(hello_init);
// module_exit(hello_exit);

// MODULE_LICENSE(DRIVER_LICENSE);
// MODULE_AUTHOR(DRIVER_AUTHOR);
// MODULE_DESCRIPTION(DRIVER_DESC);