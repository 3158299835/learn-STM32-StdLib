#ifndef __STORE_H
#define __STORE_H

//���������������һҳ��SRAM����
extern uint16_t Store_Data[];

//��ʼ��
void Store_Init(void);
//��SRAM����д��FLASH
void Store_Save(void);
//���FLASH�����˱�־λ��
void Store_Clear(void);

#endif
