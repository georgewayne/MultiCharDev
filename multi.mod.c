#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x121e492e, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xf8e6f2e6, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x27c252bb, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x7d0f5419, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x8bfe7e2c, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0xbfbf8b33, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xf166edc9, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x6618bd41, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x901bfa3a, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xa46a84db, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C91188B58251AA4B12F9D2C");
