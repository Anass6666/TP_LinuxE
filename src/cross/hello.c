
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/uaccess.h>


#define DRIVER_AUTHOR "Christophe Barès"
#define DRIVER_DESC "Hello world Module"
#define DRIVER_LICENSE "GPL"
#define TAILLE 100
#define INTERVALLE 100


static int param;
module_param(param, int, 0);
MODULE_PARM_DESC(param, "Un parametre de ce module"); //définir la variable param en tant que parametre du module

int hello_init(void)
{
printk(KERN_INFO "Hello world!\n");
printk(KERN_DEBUG"Le parametre est = %d \n", param); //affichage du parametre
return 0;
}

void hello_exit(void)
{
printk(KERN_ALERT "Bye bye...\n");
}
module_init(hello_init);
module_exit(hello_exit);
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