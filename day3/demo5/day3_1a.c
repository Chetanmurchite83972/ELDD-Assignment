#include<linux/module.h>
#include "file.h"

static __init int desd_init(void)
{
	my_function();
	my_var = 20;
	printk(KERN_INFO "%s : desd_init() : my_var = %d\n",THIS_MODULE->name, my_var);
	printk(KERN_INFO "%s : desd_init() : state = %d\n",THIS_MODULE->state);
	printk(KERN_INFO "%s : desd_init() : init is successfully completed\n",THIS_MODULE->name);
	return 0;
}

module_init(desd_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chetan Murchite");
MODULE_DESCRIPTION("This is split module");
	
