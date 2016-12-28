#!/bin/bash
exec qemu-system-arm -M versatilepb -s -S -m 128M -kernel output/images/zImage -serial stdio -append "console=ttyAMA0 root=/dev/nfs nfsroot=10.0.2.2:/srv/nfs/busybox rw ip=10.0.2.15::10.0.2.1:255.255.255.0 init=/sbin/init"
