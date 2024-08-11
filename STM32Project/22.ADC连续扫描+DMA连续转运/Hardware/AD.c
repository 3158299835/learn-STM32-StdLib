#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];//�������ڴ��ADת�������ȫ������


void AD_Init(void)
{
    //����GPIOAʱ�ӡ�ADC1����ʱ�ӡ�DMA�����ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    //����ADCԤ��Ƶ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M
    
    //����PA0
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //���ù���ͨ��
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);//����������1��λ�ã�����Ϊͨ��0
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);//����������2��λ�ã�����Ϊͨ��1
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);//����������3��λ�ã�����Ϊͨ��2
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);//����������4��λ�ã�����Ϊͨ��3
    
    //��ʼ��ADC
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;     //�Ƿ�����ת������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //�Ҷ���
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //�ⲿ��������
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;      //ģʽ:����ADCģʽ
    ADC_InitStructure.ADC_NbrOfChannel = 4;         //��4��ͨ��
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;   //�Ƿ�ɨ��ģʽ����
    ADC_Init(ADC1,&ADC_InitStructure);
    
    
    /*ADCʹ��֮ǰ ��ʼ����DMA*/
    //��ʼ��DMA����
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//Դ����ַ
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���֣�16λ
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//Դ��ַ�Ƿ���������
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;//Ŀ�����ַ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//Ŀ���� �ֽ�
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//Ŀ�ĵط�����:��
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//���䷽�� 1-�洢�������衣2-���赽 �洢��
    DMA_InitStructure.DMA_BufferSize = 4;//���������   ��4��
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ָ����װ����ѭ��
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //�Ƿ�ʹ���������  ��
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//ѡ�����ȼ�
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);//Ӳ��������ADC1 ��Ӳ��������ͨ��1 ���Բ��ܱ�
    //ʹ��DMA
    DMA_Cmd(DMA1_Channel1, ENABLE);
    
    //����ADC��DMA�����
    ADC_DMACmd(ADC1, ENABLE);

    //����ADC1
    ADC_Cmd(ADC1, ENABLE);
    
    //У׼  
    ADC_ResetCalibration(ADC1); //��λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1) == SET) //�ȴ���λУ׼���
    ADC_StartCalibration(ADC1); //��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1) == SET); //�ȴ�У׼���
    
    //�������ADC
     ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}























