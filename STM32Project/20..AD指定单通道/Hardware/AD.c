#include "stm32f10x.h"                  // Device header





void AD_Init(void)
{
    //����GPIOAʱ�Ӻ�ADC1����ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    //����ADCԤ��Ƶ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M
    //����PA0
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //�ֶ���������������ͨ�����ﵽ�л���Ч��
    
    //��ʼ��ADC
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;     //�Ƿ�����ת������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //�Ҷ���
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //�ⲿ��������
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;      //ģʽ:����ADCģʽ
    ADC_InitStructure.ADC_NbrOfChannel = 1;         //ָ��ɨ��ģʽ���ü���ͨ��
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //�Ƿ�ɨ��ģʽ����
    ADC_Init(ADC1,&ADC_InitStructure);
    //����ADC1
    ADC_Cmd(ADC1,ENABLE);
    
    //У׼
    //��λУ׼���ȴ���λУ׼��ɡ���ʼУ׼���ȴ�У׼���
    ADC_ResetCalibration(ADC1); //��λУ׼
    while(ADC_GetResetCalibrationStatus(ADC1) == SET) //�ȴ���λУ׼���
    ADC_StartCalibration(ADC1); //��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1) == SET); //�ȴ�У׼���
}


uint16_t AD_Getvalue(uint8_t ADC_Channel)
{
    //���ù���ͨ����
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//����������1��λ�ã�����Ϊͨ��ADC_Channel
    //�������ת��
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//�ȴ�ת�����
    //��ȡת��ֵ
    return ADC_GetConversionValue(ADC1);
}






















