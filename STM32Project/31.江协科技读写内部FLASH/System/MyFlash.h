#ifndef __MYFLASH_H
#define __MYFLASH_H

//¶Á³ö×Ö
uint32_t MyFLASH_ReadWord(uint32_t Address);
//¶Á³ö°ë×Ö
uint16_t MyFLASH_ReadHalfWord(uint32_t Address);
//¶Á³ö×Ö½Ú
uint8_t MyFLASH_ReadByte(uint32_t Address);

//Çå³ýËùÓÐÒ³
void MyFLASH_EraseAllPages(void);
//Çå³ýÄ³Ò³
void MyFLASH_ErasePage(uint32_t PageAddress);

//±àÐ´×Ö
void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data);
//±àÐ´°ë×Ö
void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

#endif
