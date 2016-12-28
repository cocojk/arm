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
	{ 0x6f469b01, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x351615a3, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x6240f504, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x69ff6259, __VMLINUX_SYMBOL_STR(add_disk) },
	{ 0xb9b23e22, __VMLINUX_SYMBOL_STR(blk_queue_max_hw_sectors) },
	{ 0x68ffba43, __VMLINUX_SYMBOL_STR(blk_queue_make_request) },
	{ 0xdb8ded4f, __VMLINUX_SYMBOL_STR(blk_alloc_queue) },
	{ 0xc8685f13, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x512a7548, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x44aa0c6f, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xfc55a1fc, __VMLINUX_SYMBOL_STR(kill_bdev) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7543099434F54728D0CC2BC");
