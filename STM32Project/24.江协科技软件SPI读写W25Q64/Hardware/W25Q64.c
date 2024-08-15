#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
#include "W25Q64_Ins.h"
#include "MySPI.h"


/**
  * ��    ������ʼ��W25Q64
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void W25Q64_Init(void)
{
    MySPI_Init();
}





/********************/
/*ƴ��������ͨ��ʱ��*/
/********************/





/**
  * ��    �����鿴W25Q64�ĳ��̺ź��豸��
  * ��    ����ID* Str   �����ID�ṹ���ָ��
  * �� �� ֵ����
  * ע��������յڰ�λʱ��|=
  */
ID W25Q64_ID;//����豸ID�ŵĽṹ��
void W25Q64_ReadID(ID* Str)
{
    MySPI_Start();//��ʼ
    MySPI_WarpByte(W25Q64_JEDEC_ID);//���Ͷ�ȡ�豸��ָ�����ֵ��Ҫ
    Str->MID = MySPI_WarpByte(W25Q64_DUMMY_BYTE);//���ճ���ID �ӻ��������豸�š�����ֵ���
    Str->DID = MySPI_WarpByte(W25Q64_DUMMY_BYTE);//�����豸ID�߰�λ
    Str->DID <<= 8;//�ѽ��յ������ݷŵ��߰�λ
    Str->DID |= MySPI_WarpByte(W25Q64_DUMMY_BYTE);//�����豸ID�Ͱ�λ
    MySPI_Stop();//ֹͣ
}

/**
  * ��    ����дʹ��
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void W25Q64_WriteEnable(void)
{
    MySPI_Start();//��ʼ
    MySPI_WarpByte(W25Q64_WRITE_ENABLE);//����
    MySPI_Stop();//ֹͣ
}

/**
  * ��    ����дʧ��
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void W25Q64_WriteDisable(void)
{
    MySPI_Start();//��ʼ
    MySPI_WarpByte(W25Q64_WRITE_DISABLE);//����
    MySPI_Stop();//ֹͣ
}

/**
  * ��    �����ȴ�æ����
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void W25Q64_WaitBusy(void)
{
    MySPI_Start();//��ʼ
    MySPI_WarpByte(W25Q64_READ_STATUS_REGISTER_1);  //����
    
    uint32_t TimeOut = 100000;
    while((MySPI_WarpByte(W25Q64_DUMMY_BYTE)&0x01) == 0x01)    //��ȡ״̬�Ĵ���1��Busyλ�Ƿ�Ϊ1,Ϊ1��ȴ�
    {
        TimeOut--;
        if(TimeOut == 0)
        {
            break;  //��ʱ�˳�
        }
    }
    MySPI_Stop();   //ֹͣ
}

/**
  * ��    ����ҳ���
  * ��    ����Address       Ҫд���Ǹ�ҳ��ַ
              *DataArray    �洢�ֽ����õ�����
              Count         һ��д������ֽ�
  * �� �� ֵ����
  * ע�����һ��ֻ��д�����0-256���ֽ�
  */
void W25Q64_PageProgram(uint32_t Address, uint8_t* DataArray,uint16_t Count)//(0-256,����Ҫ16λ)
{
    W25Q64_WaitBusy();
    //��ǰ�ȴ������º�ȴ����ȵȴ����˳����Ƚϱ��ա� ��ǰ�ȴ�������������£��ٽ�ȥ��Ч�ʸߣ�
    
    W25Q64_WriteEnable();//дʹ�ܣ�ÿ��дʱ��Ҫ��дʹ�ܣ�
    
    MySPI_Start();//��ʼ
    MySPI_WarpByte(W25Q64_PAGE_PROGRAM);//����ҳ���ָ��
    MySPI_WarpByte(Address >> 16 );
    MySPI_WarpByte(Address >> 8 );//������ֻ�ܽ���8λ�����Զ�������
    MySPI_WarpByte(Address >> 0);//����ҳ��ַ
    uint16_t i = 0;
    for(i = 0; i < Count; i++)
    {
        MySPI_WarpByte(DataArray[i]);//����Count������ĵ�iλ
    }
    MySPI_Stop();//ֹͣ
}

/**
  * ��    ����ҳ����
  * ��    ����Address       Ҫ������һҳ
  * �� �� ֵ����
  * ע�������С�Ĳ�����λ��4kb 1����
  */
void W25Q64_PageErase(uint32_t Address)
{
    W25Q64_WaitBusy();
    //��ǰ�ȴ������º�ȴ����ȵȴ����˳����Ƚϱ��ա� ��ǰ�ȴ�������������£��ٽ�ȥ��Ч�ʸߣ�
    
    W25Q64_WriteEnable();//дʹ�ܣ�ÿ��дʱ��Ҫ��дʹ�ܣ�
    
    MySPI_Start();//��ʼ
    MySPI_WarpByte(W25Q64_SECTOR_ERASE_4KB);//����ҳ���ָ��
    MySPI_WarpByte(Address >> 16 );
    MySPI_WarpByte(Address >> 8 );//���͵�ַ
    MySPI_WarpByte(Address >> 0);
    MySPI_Stop();//ֹͣ
}

/**
  * ��    ������ȡ����
  * ��    ����Address       Ҫ��ȡ����ַ
              *DataArray    �洢�ֽ����õ�����
              Count         һ�ζ�ȡ�����ֽ�
  * �� �� ֵ����
  * ע�������ȡ���������ƶ�ȡ
  */
void W25Q64_ReadData(uint32_t Address, uint8_t* DataArray,uint32_t Count)//��ȡû������
{
    W25Q64_WaitBusy();
    //��ǰ�ȴ������º�ȴ����ȵȴ����˳����Ƚϱ��ա� ��ǰ�ȴ�������������£��ٽ�ȥ��Ч�ʸߣ�
    
    MySPI_Start();//��ʼ
    MySPI_WarpByte(W25Q64_READ_DATA);//����ҳ���ָ��
    MySPI_WarpByte(Address >> 16 );
    MySPI_WarpByte(Address >> 8 );//������ֻ�ܽ���8λ�����Զ�������
    MySPI_WarpByte(Address >> 0);//����ҳ��ַ
    uint32_t i = 0;
    for(i = 0; i < Count; i++)
    {
        DataArray[i] = MySPI_WarpByte(W25Q64_DUMMY_BYTE);//����Count���ֽڣ��ŵ�����ĵ�iλ
    }
    MySPI_Stop();//ֹͣ
}



