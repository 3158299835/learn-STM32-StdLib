#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"
#include "W25Q64_Ins.h"
#include "MySPI.h"


/**
  * 函    数：初始化W25Q64
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void W25Q64_Init(void)
{
    MySPI_Init();
}





/********************/
/*拼接完整的通信时序*/
/********************/





/**
  * 函    数：查看W25Q64的厂商号和设备号
  * 参    数：ID* Str   存放了ID结构体的指针
  * 返 回 值：无
  * 注意事项：接收第八位时是|=
  */
ID W25Q64_ID;//存放设备ID号的结构体
void W25Q64_ReadID(ID* Str)
{
    MySPI_Start();//起始
    MySPI_WarpByte(W25Q64_JEDEC_ID);//发送读取设备号指令。返回值不要
    Str->MID = MySPI_WarpByte(W25Q64_DUMMY_BYTE);//接收厂商ID 从机发来的设备号。发送值随便
    Str->DID = MySPI_WarpByte(W25Q64_DUMMY_BYTE);//接收设备ID高八位
    Str->DID <<= 8;//把接收到的数据放到高八位
    Str->DID |= MySPI_WarpByte(W25Q64_DUMMY_BYTE);//接收设备ID低八位
    MySPI_Stop();//停止
}

/**
  * 函    数：写使能
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void W25Q64_WriteEnable(void)
{
    MySPI_Start();//起始
    MySPI_WarpByte(W25Q64_WRITE_ENABLE);//发送
    MySPI_Stop();//停止
}

/**
  * 函    数：写失能
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void W25Q64_WriteDisable(void)
{
    MySPI_Start();//起始
    MySPI_WarpByte(W25Q64_WRITE_DISABLE);//发送
    MySPI_Stop();//停止
}

/**
  * 函    数：等待忙函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void W25Q64_WaitBusy(void)
{
    MySPI_Start();//起始
    MySPI_WarpByte(W25Q64_READ_STATUS_REGISTER_1);  //发送
    
    uint32_t TimeOut = 100000;
    while((MySPI_WarpByte(W25Q64_DUMMY_BYTE)&0x01) == 0x01)    //读取状态寄存器1的Busy位是否为1,为1则等待
    {
        TimeOut--;
        if(TimeOut == 0)
        {
            break;  //超时退出
        }
    }
    MySPI_Stop();   //停止
}

/**
  * 函    数：页编程
  * 参    数：Address       要写入那个页地址
              *DataArray    存储字节所用的数组
              Count         一次写入多少字节
  * 返 回 值：无
  * 注意事项：一次只能写入最多0-256个字节
  */
void W25Q64_PageProgram(uint32_t Address, uint8_t* DataArray,uint16_t Count)//(0-256,所以要16位)
{
    W25Q64_WaitBusy();
    //事前等待。（事后等待是先等待再退出，比较保险。 事前等待可以先做别的事，再进去。效率高）
    
    W25Q64_WriteEnable();//写使能（每次写时都要先写使能）
    
    MySPI_Start();//起始
    MySPI_WarpByte(W25Q64_PAGE_PROGRAM);//发送页编程指令
    MySPI_WarpByte(Address >> 16 );
    MySPI_WarpByte(Address >> 8 );//（接收只能接收8位。会自动舍弃）
    MySPI_WarpByte(Address >> 0);//发送页地址
    uint16_t i = 0;
    for(i = 0; i < Count; i++)
    {
        MySPI_WarpByte(DataArray[i]);//发送Count个数组的第i位
    }
    MySPI_Stop();//停止
}

/**
  * 函    数：页擦除
  * 参    数：Address       要擦除那一页
  * 返 回 值：无
  * 注意事项：最小的擦除单位。4kb 1扇区
  */
void W25Q64_PageErase(uint32_t Address)
{
    W25Q64_WaitBusy();
    //事前等待。（事后等待是先等待再退出，比较保险。 事前等待可以先做别的事，再进去。效率高）
    
    W25Q64_WriteEnable();//写使能（每次写时都要先写使能）
    
    MySPI_Start();//起始
    MySPI_WarpByte(W25Q64_SECTOR_ERASE_4KB);//发送页编程指令
    MySPI_WarpByte(Address >> 16 );
    MySPI_WarpByte(Address >> 8 );//发送地址
    MySPI_WarpByte(Address >> 0);
    MySPI_Stop();//停止
}

/**
  * 函    数：读取数据
  * 参    数：Address       要读取个地址
              *DataArray    存储字节所用的数组
              Count         一次读取多少字节
  * 返 回 值：无
  * 注意事项：读取可以无限制读取
  */
void W25Q64_ReadData(uint32_t Address, uint8_t* DataArray,uint32_t Count)//读取没有限制
{
    W25Q64_WaitBusy();
    //事前等待。（事后等待是先等待再退出，比较保险。 事前等待可以先做别的事，再进去。效率高）
    
    MySPI_Start();//起始
    MySPI_WarpByte(W25Q64_READ_DATA);//发送页编程指令
    MySPI_WarpByte(Address >> 16 );
    MySPI_WarpByte(Address >> 8 );//（接收只能接收8位。会自动舍弃）
    MySPI_WarpByte(Address >> 0);//发送页地址
    uint32_t i = 0;
    for(i = 0; i < Count; i++)
    {
        DataArray[i] = MySPI_WarpByte(W25Q64_DUMMY_BYTE);//接收Count个字节，放到数组的第i位
    }
    MySPI_Stop();//停止
}



