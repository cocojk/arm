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
	{ 0x96cec1da, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x932344a8, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0x167e7f9d, __VMLINUX_SYMBOL_STR(__get_user_1) },
	{ 0x44aa0c6f, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc3aaf0a9, __VMLINUX_SYMBOL_STR(__put_user_1) },
	{ 0x9bc64027, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x58b9c658, __VMLINUX_SYMBOL_STR(try_module_get) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "5B19E88449B1B065E0E66DB");
