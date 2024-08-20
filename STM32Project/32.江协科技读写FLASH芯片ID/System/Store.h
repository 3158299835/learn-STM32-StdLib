#ifndef __STORE_H
#define __STORE_H

//对外声明保存最后一页的SRAM数组
extern uint16_t Store_Data[];

//初始化
void Store_Init(void);
//把SRAM数组写入FLASH
void Store_Save(void);
//清除FLASH（除了标志位）
void Store_Clear(void);

#endif
