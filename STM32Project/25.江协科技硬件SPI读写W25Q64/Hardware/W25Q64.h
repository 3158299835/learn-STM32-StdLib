#ifndef __W25Q64_H
#define __W25Q64_H

//��ʼ��W25Q64
void W25Q64_Init(void);


/*���̺��豸ID��*/
typedef struct ID
{
    uint8_t MID;//8λ����ID
    uint16_t DID;//16λ�豸ID
}ID;
extern ID W25Q64_ID;

//��ȡ���̺��豸��ID
void W25Q64_ReadID(ID* Str);
//ҳ���
void W25Q64_PageProgram(uint32_t Address, uint8_t* DataArray,uint16_t Count);
//ҳ����
void W25Q64_PageErase(uint32_t Address);
//��ȡ
void W25Q64_ReadData(uint32_t Address, uint8_t* DataArray,uint32_t Count);
#endif
