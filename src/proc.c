
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>



#define TAILLE 100
char message[TAILLE]; // buffer de taille TAILLE
static int param;
module_param(param, int, 0);
MODULE_PARM_DESC(param,"Un parametre de ce module");

ssize_t fops_read(struct file *file, char __user * buffer, size_t count, loff_t * ppos)
{
int errno=0;
int copy;
if (count > TAILLE) count=TAILLE; //une condition pour localiser la fin de caractères dans le fichier
if ((copy=copy_to_user(buffer, message, strlen(message)+1))) // lire le contenu de la table message[]
errno = -EFAULT;
printk(KERN_INFO "message read, %d, %p\n", copy, buffer); // afficher ce qui a été lu sur la table
return count-copy;
}
ssize_t fops_write(struct file * file, const char __user * buffer,size_t count, loff_t * ppos)
{
int len = count;
if (len > TAILLE) len = TAILLE; //vérifier si c'est la bonne taille
printk(KERN_INFO "Recieving new messag\n");
if (copy_from_user(message, buffer, count)) { // scanner ce qui a été saisi par l'utilisateur
return -EFAULT;
}
message[count] = '\0'; // indiquer la fin des caracteres dans le fichier
//size_of_message = strlen(message);
printk(KERN_INFO "New message : %s\n", message); // afficher le message saisi par l’utilisateur
return count;
}
struct file_operations proc_fops; // creation d’une structure
int hello_init(void)
{
printk(KERN_INFO "Hello world!\n");
printk(KERN_DEBUG"Le parametre est = %d \n", param);
proc_create("procHello", 0666,NULL,&proc_fops); //création d'une entrée (fichier) dans /proc/ avec comme nom : "procHello", droits :0666 lire ecrire pour tout les utilisateurs, et structure : proc_fops
proc_fops.read = fops_read; // lire le message écris dans le fichier
proc_fops.write = fops_write; // ecrire un message dans le fichier
return 0;
}
void hello_exit(void)
{
printk(KERN_ALERT "Bye bye...\n");
remove_proc_entry("procHello", NULL);
}
module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);



