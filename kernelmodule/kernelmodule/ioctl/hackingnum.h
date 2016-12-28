#ifndef __HACK_NUM__
#define __HACK_NUM__

#define NUM             2
#define NUM_VM_AREA_PROBE   0
#define NUM_TASK_STRUCT_VMADDRESS   1

extern void (*hack[NUM]) (long pid);
void vm_area_probe (long pid);
void task_struct_vmaddress (long pid);

#endif
