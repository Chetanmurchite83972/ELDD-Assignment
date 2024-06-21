#include<linux/module.h>
#include<linux/init.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/gpio.h>
#include<linux/uaccess.h>
#include<linux/interrupt.h>

#define LED_GPIO 49
#define SWITCH_GPIO 115

static int bbb_gpio_open(struct inode *,struct file *);
static int bbb_gpio_close(struct inode *,struct file *);
static int bbb_gpio_read(struct file *,char *,size_t,loff_t *);
static int bbb_gpio_write(struct file *, const char *,size_t,loff_t *);

#define MAX 32
static int led_state;
static int major;
static dev_t devno;
static struct class *pclass;
static struct cdev cdev;
static int irq;
static struct file_operation bbb_gpio_fops = {
    .owner = THIS_MODULE,
    .open = bbb_gpio_open,
    .release = bbb_gpio_open,
    .read = bbb_gpio_read,
    .write = bbb_gpio_write
};

static irqreturn_t switch_isr(int irq, void *param){
    led_state = !led_state;
    gpio_set_value(LED_GPIO, led_state);
    printk(KERN_INFO "%s: switch_isr() called.\n",THIS_MODULE->name);
    return IRQ_HANDLED;
}


static __init int bbb_gpio_init(void){
    int ret,minor;
    struct device *pdevice;

    printk(KERN_INFO "%s: bbb_gpio_init() called.\n",THIS_MODULE->name);

    //allocation
    ret = alloc_chrdev_region(&devno,0,1,"bbb_gpio");
    if(ret != 0){
        printk(KERN_ERR "%s: alloc_chrdev_region() failed.\n",THIS_MODULE->name);
        goto alloc_chrdev_region_failed;
    }
    major = MAJOR(devno);
    minor = MINOR(devno);
    printk(KERN_INFO "%s: alloc_chrdev_region() allocated device number %d/%d.\n",THIS_MODULE->name,major,minor);

    //class create
    pclass = class_create(THIS_MODULE,"bbb_gpio_class");
    if(IS_ERR(pclass)){
        printk(KERN_ERR "%s: class_create() failed.\n".THIS_MODULE->name);
        ret = -1;
        goto class_create_failed;
    }
    printk(KERN_INFO "%s: class_create() created device class.\n",THIS_MODULE->name);

    //device create
    pdevice = device_create(pclass,NULL,devno,NULL,"bbb_gpio%d",0);
    if(IS_ERR(pdevice)){
        printk(KERN_ERR "%s: device_create() failed.\n",THIS_MODULE->name);
        ret = -1;
        goto device_create_failed;
    }
    printk(KERN_INFO "%s: device_create() created device file.\n",THIS_MODULE->name);

    //cdev 
    cdev_init(&cdev,&bbb_gpio_fops);
    ret = cdev_add(&cdev, devno, 1); 
    if(ret != 0){
        printk(KERN_ERR "%s: cdev_add() failed to add cdev in kernel db.\n",THIS_MODULE->name);
        goto cdev_add_failed;
    }  
    printk(KERN_INFO "%s: cdev_add() added device in kernel db.\n",THIS_MODULE->name);

    bool valid = gpio_is_valid(LED_GPIO);
    if(!valid){
        printk(KERN_ERR "%s: GPIO pin %d exist.\n",THIS_MODULE->name,LED_GPIO);
        ret = -1;
        goto gpio_invalid;
    }
    printk(KERN_INFO "%s: GPIO pin %d exists.\n",THIS_MODULE->name,LED_GPIO);
    
    ret = gpio_request(LED_GPIO, "bbb-led");
    if(ret != 0){
        printk(KERN_ERR "%s: GPIO pin %d is busy.\n",THIS_MODULE->name,LED_GPIO);
        goto gpio_invalid;
    }
    printk(KERN_INFO "%s: GPIO pin %d acquired.\n",THIS_MODULE->name,LED_GPIO);
    
    led_state = 1;
    ret = gpio_direction_output(LED_GPIO,led_state);
    if(ret != 0){
        printk(KERN_ERR "%s: GPIO pin %d direction not set.\n",THIS_MODULE->name,LED_GPIO);
        goto gpio_direction_failed;
    }
    printk(KERN_INFO "%s: GPIO pin %d direction set to OUTPUT.\n",THIS_MODULE->name,LED_GPIO);

    valid = gpio_is_valid(SWITCH_GPIO);
    if(!valid){
        printk(KERN_ERR "%s: GPIO pin %d direction set to OUTPUT.\n",THIS_MODULE->name,LED_GPIO);
        ret = -1;
        goto switch_gpio_invalid;
    }
    printk(KERN_INFO "%s: GPIO pin %d is busy.\n",THIS_MODULE->name,SWITCH_GPIO);

    ret = gpio_direction_input(SWITCH_GPIO);
    if(ret != 0){
        printk(KERN_ERR "%s: GPIO pin %d direction not set.\n",THIS_MODULE->name,SWITCH_GPIO);
        goto swi
    }
    
}





static __exit void bbb_gpio_exit(void){
    printk(KERN_INFO "%s: bbb_gpio_exit() called.\n",THIS_MODULE->name);
    free_irq(irq, NULL);
    printk(KERN_INFO "%s: GPIO pin %d ISR released.\n",THIS_MODULE->name,SWITCH_GPIO);
    gpio_free(SWICH_GPIO);
    

}

module_init(bbb_gpio_init);
module_exit(bbb_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chetan Murchite");
MODULE_DESCRIPTION("Simple bbb_gpio driver with kfifo as device.");