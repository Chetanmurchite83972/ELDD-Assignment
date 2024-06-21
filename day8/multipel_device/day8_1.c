#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<device.h>
#include<cdev.h>
#include<linux/kfifo.h>
#include<linux/slab.h>



static __init int pchar_init(void){
	int ret,minor,i;
	struct device *pdevice;
	sev_t devno;

	printk(KERN_INFO "%s: pchar_init() called.\n",THIS_MODULE->name);

	device = (struct pchar_device*)kmalloc(devcnt * sizeof(struct pchar_device),GFP_KERNEL);
	if(device == NULL){
		ret = -ENOMEM;
		printk(KERN_ERR "%s: kmalloc() failed to allocate devices private struct memory.\n",THIS_MODULE->name);
		goto devices_kmallocc_failed;
	}
	printk(KERN_INFO "%s: kmalloc() allocated devices private struct memory.\n",THIS_MODULE->name);

	for(i=0; i<devcnt; i++){
		ret = kfifo_alloc(&devices[i].buf,MAX,GFP_KERNEL);
		if(ret != 0){
			printk(KERN_ERR "%s: kfifo_alloc() failed for device %d.\n",THIS_MODULE->name,i);
			goto kfifo_alloc_failed;
		}
		printk(KERN_ERR "%s: kfifo_alloc() successfully created %d device.\n",THIS_MODULE->name,devcnt);
	}

	ret = alloc_chrdev_region(&devno, 0, devcnt, "pchar");
	if(ret != 0){
		printk(KERN_ERR "%s: alloc_chrdev_region() failed.\n",THIS_MODULE->name,devcnt);
		goto alloc_chrdev_region_failed;
	}
	major = MAJOR(devno);
	minor = MINOR(devno);
	printk(KERN_INFO "%s: alloc_chrdev_region() allocated device number %d/%d.\n",THIS_MODULE->name);
	pclass = class_create("pchar_class");
    if(IS_ERR(pclass)) {
        printk(KERN_ERR "%s: class_create() failed.\n", THIS_MODULE->name);
		ret = -1;
		goto class_create_failed;
	}
	printk(KERN_ERR "%s: class_create() created device class.\n",THIS_MODULE->name);

	for(i=0; i<devcnt; i++) {
		devno = MKDEV(major, i);
		pdevice = device_create(pclass,NULL,devno,NULL,"pchar%d",i);
		if(IS_ERR(pdevice)){
			printk(KERN_ERR "%s: device_create() failed for device %d.\n",THIS_MODULE->name,i);
			ret = -1;
			goto device_create_failed;
		}
	}
	printk(KERN_INFO "%s: device_create() created device files.\n",THIS_MODULE->name);
	for(i=0; i<devcnt)

		


