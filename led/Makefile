KERN_DIR = /home/huangwenxi/linux-2.6.22.6  
PWD = $(shell pwd)
all:  
	make -C $(KERN_DIR) M=$(PWD) modules   
	arm-linux-gcc -o led_test led_test.c
  
clean:  
	make -C $(KERN_DIR) M=`pwd` modules clean  
	rm -rf modules.order  
  
obj-m += led_drv.o  
