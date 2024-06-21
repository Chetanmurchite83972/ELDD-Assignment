#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>

struct student
{
	int rollno;
	char name[20];
	int marks;
	struct list_head slist;
};


struct list_head slist;

static __init int kern_list_init(void)
{
	struct student *ptr = NULL, *st;
	struct list_head *pos;

	printk(KERN_INFO "%s : kern_list_init is called\n", THIS_MODULE->name);
	// initialize linke list
	INIT_LIST_HEAD(&slist);

	// allocate memory dynamically for first student
	ptr = kmalloc(sizeof(struct student), GFP_KERNEL);
	// fill student info into allocated memory
	ptr->rollno = 3;
	strcpy(ptr->name, "pqr");
	ptr->marks = 75;
	// add newly created node into linked list	
	list_add(&ptr->slist, &slist);

	// allocate memory dynamically for first student
	ptr = kmalloc(sizeof(struct student), GFP_KERNEL);
	// fill student info into allocated memory
	ptr->rollno = 1;
	strcpy(ptr->name, "abc");
	ptr->marks = 95;
	// add newly created node into linked list	
	list_add(&ptr->slist, &slist);

	// allocate memory dynamically for first student
	ptr = kmalloc(sizeof(struct student), GFP_KERNEL);
	// fill student info into allocated memory
	ptr->rollno = 5;
	strcpy(ptr->name, "xyz");
	ptr->marks = 65;
	// add newly created node into linked list	
	list_add(&ptr->slist, &slist);

	// allocate memory dynamically for first student
	ptr = kmalloc(sizeof(struct student), GFP_KERNEL);
	// fill student info into allocated memory
	ptr->rollno = 2;
	strcpy(ptr->name, "mno");
	ptr->marks = 80;
	// add newly created node into linked list	
	list_add(&ptr->slist, &slist);
	

	printk(KERN_INFO "%s : Students List : \n", THIS_MODULE->name);
	list_for_each(pos, &slist)
	{
		st = list_entry(pos, struct student, slist);
		printk(KERN_INFO "%s : name = %s, rollno = %d, marks = %d\n", THIS_MODULE->name, st->name, st->rollno, st->marks);
	}
	
	printk(KERN_INFO "%s : kern_list_init is completed\n", THIS_MODULE->name);

	return 0;
}

static __exit void kern_list_exit(void)
{
	struct list_head *pos, *n;
	struct student *st;

	printk(KERN_INFO "%s : kern_list_exit is called\n", THIS_MODULE->name);

	list_for_each_safe(pos, n, &slist)
	{
		st = list_entry(pos, struct student, slist);
		list_del(pos);
		kfree(st);
	}

	printk(KERN_INFO "%s : kern_list_exit is completed\n", THIS_MODULE->name);
}

module_init(kern_list_init);
module_exit(kern_list_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chetan Murchite");
MODULE_DESCRIPTION("This is module to use/test kernel linked list");

















