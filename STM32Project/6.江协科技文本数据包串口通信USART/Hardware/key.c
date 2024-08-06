#include "key.h"
#include "stm32f10x.h"

//��ʼ��GPIO
//����1 2�ǵ͵�ƽ��⡣����ģʽ����Ϊ��������
void KEY_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��APB2���ߵ�GPIOC ʱ��
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_0;//KEY 1  2 ��Ӧ����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��GPIOB 11  0����
    
}




//�������
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t Key_up = 1;//��ʼ��keyup = 1��δ������
    if(mode == 1)
    {
        Key_up = 1;//�����������������ģʽ����ô��ǿ�ƶ�����һ��״̬Ϊδ������
    }
    if(Key_up && (KEY1||KEY2))//��һ��δ�����£�����KEY1��2���¡���ô����Ч
    {
        Delay_ms(10);//ȥ����
        Key_up = 0;//��ֵΪ0,��ǰ���
        if     (KEY1)
        {
            return 1;
        }
        else if(KEY2)
        {
            return 2;
        }    
        }
    else if(KEY1 == 0 && KEY2 == 0)
    {
        Key_up = 1;//δ�����£���ô��ֵΪ1�����δ�����¡�
    }
    return 0;
}
