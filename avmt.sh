#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 2 ]; then
	echo "Usage: avmt host | guest | setup | send msg | unzip-ramdisk | zip-ramdisk"
	exit 1
fi

if [ $1 == "host" ]; then
	emulator -no-boot-anim -shell -no-window -kernel ./guest-os/arch/arm/boot/zImage -ramdisk $ANDROID_IMG/ramdisk.img -show-kernel -avd host
fi

if [ $1 == "guest" ]; then
	emulator -no-boot-anim -shell -no-window -kernel ./host-os/arch/arm/boot/zImage -ramdisk guest-os-ramdisk.img -show-kernel -avd guest
fi

if [ $1 == "setup" ]; then
	cd tcp
	make
	make install
	cd ..
	adb -s emulator-5556 forward tcp:7000 tcp:7000
fi

if [ $1 == "send" ]; then
	adb -s emulator-5554 shell /data/client $2
fi	

if [ $1 == "unzip-ramdisk" ]; then
	mkdir ramdisk
	cd ramdisk
	gunzip -c ../your-ramdisk-file | cpio -i
	cd ..
fi

if [ $1 == "zip-ramdisk" ]; then
	cd ramdisk
	find . | cpio -o -H newc | gzip > ../guest-os-ramdisk.img
	cd ..
fi
