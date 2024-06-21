obj-m = splitfile.o
splitfile-objs = day3_1a.o day3_1b.o day3_1c.o

modules:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
