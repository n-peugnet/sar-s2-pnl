#! /bin/bash

if [ -z $1 ]
then
	echo "usage: ./qemu-run-externKernel-virtfs.sh <shared-folder>"
	exit 1
fi

# Fixer les variables avec les chemins de vos fichiers
HDA="-drive file=pnl-tp.img,format=raw"
HDB="-drive file=myHome.img,format=raw"
SHARED=$1
KERNEL=linux/arch/x86/boot/bzImage

# Linux kernel options
CMDLINE="root=/dev/sda1 rw console=ttyS0 kgdboc=ttyS1 "

FLAGS="--enable-kvm "
VIRTFS+=" --virtfs local,path=${SHARED},mount_tag=share,security_model=passthrough,id=share "

exec qemu-system-x86_64 ${FLAGS} \
     ${HDA} ${HDB} \
     ${VIRTFS} \
     -net user -net nic \
     -serial mon:stdio \
     -serial tcp::1234,server,nowait \
     -boot c -m 2G \
     -kernel "${KERNEL}" -append "${CMDLINE}"
