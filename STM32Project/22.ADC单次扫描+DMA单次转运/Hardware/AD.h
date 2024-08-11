#ifndef __AD_H
#define __AD_H

extern uint16_t AD_Value[4];

//初始化
void AD_Init(void);

//开启ADC一次，然后搬运出去一次
void AD_Getvalue(void);



#endif
