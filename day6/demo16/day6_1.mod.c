#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xeebba815, "__class_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x2682110c, "device_create" },
	{ 0x5943b701, "cdev_init" },
	{ 0xe1173f12, "cdev_add" },
	{ 0x6f915e6e, "device_destroy" },
	{ 0xbff14d94, "class_destroy" },
	{ 0x70e69df1, "cdev_del" },
	{ 0xf3d7e125, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0B850D33AFD358CDD6B0009");