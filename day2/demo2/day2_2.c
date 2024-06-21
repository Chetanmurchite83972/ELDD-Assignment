#include<linux/module.h>


// __init is a gcc attribute -- __attribute__((section(".init.text")))
//	internally creates a new section in .ko file and place initialization fn there.
//	this section is auto-deleted after insmod (initialization) for better memory utilization.

// called when module in loaded in kernel (insmod)


static __init int desd_init(void)
{
	printk(KERN_INFO "%s : desd_init : init is successful\n", THIS_MODULE->name);
	return 0;
}

// __exit is a gcc attribute -- __attribute__((section(".exit.text")))
//	internally creates a new section in .ko file and place de-initialization fn there.
//	this and all sections are deleted after rmmod (de-initialization).

// called when module in unloaded from kernel (rmmod)


static __exit void desd_exit(void)
{
	printk(KERN_INFO "%s : desd_init : exit is successful\n", THIS_MODULE->name);
}


// mark function as module initialization function
// internally it writes wrapper init_module()
module_init(desd_init);
// mark function as module de-initialization function
// internally it writes wrapper cleanup_module()
module_exit(desd_exit);

// license = GPL or BSD or Dual BSD/GPL
MODULE_LICENSE("GPL");
// module author information
MODULE_AUTHOR("DESD @ SUNBEAM");
// module information
MODULE_DESCRIPTION("This is eldd - desd module");


// MODULE_XYZ("...") --> MODULE_INFO(xyz, "...")
// 	creates .modinfo section in .ko file and place info there.
//	this info can be seen using "modinfo" command

// static fn/variables are accessible only in current source file.
// In LKMP/LDD programming, conventionally all fns/vars limited to a file are declared static.









