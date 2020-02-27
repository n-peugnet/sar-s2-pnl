#! /bin/bash

# Fixer les variables avec les chemins de vos fichiers
HDA="-drive file=pnl-tp.img,format=raw"
HDB="-drive file=myHome.img,format=raw"
KERNEL=linux/arch/x86/boot/bzImage

# Linux kernel options
CMDLINE="root=/dev/sda1 rw console=ttyS0 kgdbwait"
CMDLINE="$CMDLINE kgdboc=ttyS1"
# CMDLINE="$CMDLINE init=bin/bash"

FLAGS="--enable-kvm "

exec qemu-system-x86_64 ${FLAGS} \
     ${HDA} ${HDB} \
     -net user -net nic \
     -serial mon:stdio \
     -serial tcp::1234,server,nowait \
     -boot c -m 2G \
     -kernel "${KERNEL}" -initrd my_initramfs.cpio.gz -append "${CMDLINE}"

