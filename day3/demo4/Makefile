obj-m = splitfile.o
splitfile-objs = day3_2.o day3_2b.o

modules:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
