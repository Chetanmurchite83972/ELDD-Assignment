#include<linux/module.h>
#include<linux/kfifo.h>

struct kfifo mykfifo;

static __init int mykfifo_init(void)
{
	char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char digits[] = "0123456789";

	//1. allocate memory to the array inside kfifo
	int ret = kfifo_alloc(&mykfifo, 32, GFP_KERNEL);
	if(ret < 0)
	{
		printk(KERN_INFO "%s : kfifo_alloc() is failed\n", THIS_MODULE->name);
		return -1;
	}

	printk(KERN_INFO "%s : Size of mykfifo = %u\n", THIS_MODULE->name, kfifo_size(&mykfifo));
	printk(KERN_INFO "%s : Length of mykfifo = %u\n", THIS_MODULE->name, kfifo_len(&mykfifo));
	printk(KERN_INFO "%s : Avail of mykfifo = %u\n", THIS_MODULE->name, kfifo_avail(&mykfifo));
	
	printk(KERN_INFO "%s : is empty = %d\n", THIS_MODULE->name, kfifo_is_empty(&mykfifo));
	printk(KERN_INFO "%s : is full = %d\n", THIS_MODULE->name, kfifo_is_full(&mykfifo));
	
	kfifo_in(&mykfifo, alphabets, strlen(alphabets));
	
	printk(KERN_INFO "%s : Size of mykfifo = %u\n", THIS_MODULE->name, kfifo_size(&mykfifo));
	printk(KERN_INFO "%s : Length of mykfifo = %u\n", THIS_MODULE->name, kfifo_len(&mykfifo));
	printk(KERN_INFO "%s : Avail of mykfifo = %u\n", THIS_MODULE->name, kfifo_avail(&mykfifo));
	
	printk(KERN_INFO "%s : is empty = %d\n", THIS_MODULE->name, kfifo_is_empty(&mykfifo));
	printk(KERN_INFO "%s : is full = %d\n", THIS_MODULE->name, kfifo_is_full(&mykfifo));

	kfifo_in(&mykfifo, digits, strlen(digits));
	
	printk(KERN_INFO "%s : Size of mykfifo = %u\n", THIS_MODULE->name, kfifo_size(&mykfifo));
	printk(KERN_INFO "%s : Length of mykfifo = %u\n", THIS_MODULE->name, kfifo_len(&mykfifo));
	printk(KERN_INFO "%s : Avail of mykfifo = %u\n", THIS_MODULE->name, kfifo_avail(&mykfifo));
	
	printk(KERN_INFO "%s : is empty = %d\n", THIS_MODULE->name, kfifo_is_empty(&mykfifo));
	printk(KERN_INFO "%s : is full = %d\n", THIS_MODULE->name, kfifo_is_full(&mykfifo));
	return 0;
}

static __exit void mykfifo_exit(void)
{
	int ret;
	char str[4];
	printk(KERN_INFO "%s : kfifo_exit() is called\n", THIS_MODULE->name);
	
	printk(KERN_INFO "%s : Data from mykfifo : \n", THIS_MODULE->name);
	while(!kfifo_is_empty(&mykfifo))
	{
		ret = kfifo_out(&mykfifo, str, sizeof(str));
		printk(KERN_INFO "%s : %s \n", THIS_MODULE->name, str);
	}

	kfifo_free(&mykfifo);
	printk(KERN_INFO "%s : kfifo_free() is successful\n", THIS_MODULE->name);
}

module_init(mykfifo_init);
module_exit(mykfifo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Devendra Dhande");
MODULE_DESCRIPTION("This is module to test / use kfifo");












