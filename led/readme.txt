./led_test on
./led_test off
功能：
1：主设备号自动分配
1：会class_device_creat()四个设备，次设备号分别是0,1,2,3

测试：
./led_test leds on|off
./led_test led1 on|off
./led_test led2 on|off
./led_test led3 on|off