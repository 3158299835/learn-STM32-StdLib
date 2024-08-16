#ifndef __W25Q64_H
#define __W25Q64_H

//初始化W25Q64
void W25Q64_Init(void);


/*厂商和设备ID号*/
typedef struct ID
{
    uint8_t MID;//8位厂商ID
    uint16_t DID;//16位设备ID
}ID;
extern ID W25Q64_ID;

//获取厂商和设备号ID
void W25Q64_ReadID(ID* Str);
//页编程
void W25Q64_PageProgram(uint32_t Address, uint8_t* DataArray,uint16_t Count);
//页擦除
void W25Q64_PageErase(uint32_t Address);
//读取
void W25Q64_ReadData(uint32_t Address, uint8_t* DataArray,uint32_t Count);
#endif
