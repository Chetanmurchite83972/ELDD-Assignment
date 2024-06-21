#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>
#include<linux/init_task.h>
#include<asm/current.h>


static __init int kern_list_init(void)
{
	// init_task	-->> pcb of init process
	// tasks	-->> process list

	struct task_struct *trav;

	printk(KERN_INFO "%s : kern_list_init is called\n", THIS_MODULE->name);
	
/*	
	list_for_each_entry(trav, &init_task.tasks, tasks)
	{
		printk(KERN_INFO "%s : pid = %d, cmd = %s\n", THIS_MODULE->name, trav->pid, trav->comm);
	}
*/	

	list_for_each_entry(trav, &current->tasks, tasks)
	{
		printk(KERN_INFO "%s : pid = %d, cmd = %s\n", THIS_MODULE->name, trav->pid, trav->comm);
	}
	
	printk(KERN_INFO "%s : kern_list_init is completed\n", THIS_MODULE->name);

	return 0;
}

static __exit void kern_list_exit(void)
{
	printk(KERN_INFO "%s : kern_list_exit is completed\n", THIS_MODULE->name);
}

module_init(kern_list_init);
module_exit(kern_list_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CM");
MODULE_DESCRIPTION("This is module to use/test kernel linked list");
















