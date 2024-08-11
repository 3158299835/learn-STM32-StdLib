#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_size = 0;

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t size)
{
    MyDMA_size = size;
    //����DMA�����ʱ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    //��ʼ��DMA����
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;//Դ����ַ
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//Դ���
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//Դ��ַ�Ƿ�����
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;//Ŀ�����ַ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//Ŀ���� �ֽ�
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//Ŀ���Ƿ�����
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//���䷽�� 1-�洢�������衣2-���赽 �洢��
                    //��Ϊ���Ǻ���Ҫ�����Ǹ��������Ǹ��Ǵ洢����ѡ�ĸ����ⲻ��
    DMA_InitStructure.DMA_BufferSize = size;//���������  ���� 0 - 65535
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//ָ����װ���Ƿ�Ҫ��װ��ע�ⲻ��Ӧ���ڴ洢�����洢���� �����װģʽ
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable; //�Ƿ�ʹ���������  ��
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//ѡ�����ȼ�
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);//���������ͨ�����ѡ��
    //ʹ��DMA
    DMA_Cmd(DMA1_Channel1,DISABLE);//���������̹��������ǵ��ú�������
}

//���� �� ת��һ��
void MyDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1,DISABLE);//ʧ��
    DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_size);
    DMA_Cmd(DMA1_Channel1,ENABLE);//ʹ��
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET)//�ȴ�ת����ɱ�־λ
    DMA_ClearFlag(DMA1_FLAG_TC1);//�ֶ������־λ����������Զ����
    
    //GLȫ�ֱ�־λ��  TCת����ɱ�־λ��
    //HTת�˹����־λ��  TEת�˴����־λ
    
    //��GL�� �� ��Global����ȫ�֣�����д��
    //��TC�� �� ��Transfer Complete����ת����ɣ�����д��
    //��HT�� �� ��Half Transfer����ת�˹��룩����д��
    //��TE�� �� ��Transfer Error����ת�˴��󣩵���д��
}














