#ifndef __MYFLASH_H
#define __MYFLASH_H

//������
uint32_t MyFLASH_ReadWord(uint32_t Address);
//��������
uint16_t MyFLASH_ReadHalfWord(uint32_t Address);
//�����ֽ�
uint8_t MyFLASH_ReadByte(uint32_t Address);

//�������ҳ
void MyFLASH_EraseAllPages(void);
//���ĳҳ
void MyFLASH_ErasePage(uint32_t PageAddress);

//��д��
void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data);
//��д����
void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

#endif
