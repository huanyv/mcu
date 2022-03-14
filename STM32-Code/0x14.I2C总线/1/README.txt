模拟 I2C 通信协议，往E2PROM里写数据 ， 通过数码管显示，PA9按键控制 


SCL --- PB1
SDA --- PB0




数码管 
数据口位选：PB高8位
段选：38译码器 A PB2	B PB3	C PB4

E2PROM的 读取和写入 都在 key.c 中




