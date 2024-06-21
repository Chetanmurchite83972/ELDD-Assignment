#include <linux/module.h>		// ksrc/include/linux/module.h

// this is initialisation function   -- will be called at time of insmod
int init_module(void)
{
	// this msg will be written into kernel log file
	printk(KERN_INFO "hello : init_module : Hello DESD @ SUNBEAM\n");
	// successful completion of initilisation for this module
	return 0;
}

// this is deinitialisation function   -- will be called at time of rmmod
void cleanup_module(void)
{
	// this msg will be written into kernel log file
	printk(KERN_INFO "hello : cleanup_module : Bye bye DESD @ SUNBEAM\n");
}

MODULE_INFO(license, "GPL");
MODULE_INFO(author, "Chetan Murchite");
MODULE_INFO(description, "This is hello module for desd @ sunbeam");











