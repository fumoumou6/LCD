#include "Lcd_Driver.h"
#include "stm32h7xx_hal.h"


//********************************************************************************

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

//********************************************************************************


//STM32���İ�����
//�⺯���汾����

//�����Գ���ʹ�õ���ģ��SPI�ӿ�����
//�����ɸ��Ľӿ�IO���ã�ʹ����������4 IO������ɱ���Һ��������ʾ

/******************************************************************************
�ӿڶ�����Lcd_Driver.h�ڶ��壬����ݽ����޸Ĳ��޸���ӦIO��ʼ��LCD_GPIO_Init()

//  ----------------------------------------------------------------
// VCC  ��5V��3.3v��Դ
// GND  ��Դ��
// D1   ��PB15��SDI��
// D0   ��PB13��SCL��
// CS   ��PB12 Ƭѡ    
// RST  ��PB14 ϵͳ��λ
// DC   ��PB1  ����/����  
// BLK  ��PB0 �������    
// ----------------------------------------------------------------

//	#define LCD_SDI        	//PB15
//	#define LCD_SCL        	//PB13
//	#define LCD_CS        	//PB12
//	#define LCD_SDO     		//PB14 
//	#define LCD_RS         	//PB1
//	#define LCD_BLK         //PB0    	
*******************************************************************************/

/**************************************************************************************

��������: void LCD_GPIO_Init(void)

��������: Һ��IO��ʼ������
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

//Һ��IO��ʼ������
void LCD_GPIO_Init(void)
{
#if USE_SOFESPI == 1
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();					          //����PBʱ��


    GPIO_Initure.Pin=GPIO_PIN_0 |GPIO_PIN_1 | GPIO_PIN_12| GPIO_PIN_13| GPIO_PIN_14| GPIO_PIN_15;	//PB
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		    //�������
    GPIO_Initure.Pull=GPIO_PULLUP;         			    //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     	     	//��ʼ��

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	  //PB0��1
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	  //PB1��1
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);	//PB12��1
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);	//PB13��1
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);	//PB14��1
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);	//PB15��1
#else
    MX_SPI2_Init();
#endif
		LCD_BLK_SET;//��������
		LCD_BLK_CLR;//�رձ���
		LCD_BLK_SET;//��������
      
}


/****************************************************************************
* ��    �ƣ�void  SPIv_WriteData(u8 Data)
* ��    �ܣ�STM32_ģ��SPIдһ���ֽ����ݵײ㺯��
* ��ڲ�����Data
* ���ڲ�������
* ˵    ����STM32_ģ��SPI��дһ���ֽ����ݵײ㺯��


//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

****************************************************************************/
void  SPI_WriteData(u8 Data)
{
#if USE_SOFESPI == 1
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)
	  LCD_SDA_SET; //�������
      else LCD_SDA_CLR;

      LCD_SCL_CLR;
      LCD_SCL_SET;
      Data<<=1;
	}
#else
    HAL_SPI_Transmit(&hspi2, &Data, 1, 0xff);
#endif
}


/****************************************************************************
* ��    �ƣ�void Lcd_WriteIndex(u8 idx)
* ��    �ܣ�д ST7735S �������Ĵ�����ַ
* ��ڲ�����idx   �Ĵ�����ַ
* ���ڲ�������
* ˵    ��������ǰ����ѡ�п��������ڲ�����
* ���÷�����Lcd_WriteIndex(0x00);

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

****************************************************************************/
void Lcd_WriteIndex(u8 Index)
{
   
   //SPI д����ʱ��ʼ
   LCD_CS_CLR;
   LCD_RS_CLR;  //д������
   SPI_WriteData(Index);
   LCD_CS_SET;
}

/****************************************************************************
* ��    �ƣ�void Lcd_WriteData(u8 dat)
* ��    �ܣ�д ST7735S �Ĵ�������
* ��ڲ�����dat     �Ĵ�������
* ���ڲ�������
* ˵    �����������ָ����ַд�����ݣ�����ǰ����д�Ĵ�����ַ���ڲ�����
* ���÷�����Lcd_WriteData(0x30)

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

****************************************************************************/
void Lcd_WriteData(u8 Data)
{
   
   LCD_CS_CLR;
   LCD_RS_SET;   //д������
   SPI_WriteData(Data);
   LCD_CS_SET; 
}


/****************************************************************************
* ��    �ƣ�void Lcd_WriteReg(u8 Index,u8 Data)
* ��    �ܣ�

//д�Ĵ�������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

****************************************************************************/

void Lcd_WriteReg(u8 Index,u8 Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}

/****************************************************************************
* ��    �ƣ�void LCD_WriteData_16Bit(uint16_t Data)
* ��    �ܣ�

//��Һ����дһ��16λ����

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

****************************************************************************/


void LCD_WriteData_16Bit(uint16_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//д���8λ����
	 SPI_WriteData(Data); 			//д���8λ����
   LCD_CS_SET; 
}



/****************************************************************************
* ��    �ƣ�void Lcd_Reset(void)
* ��    �ܣ�

//Һ������λ����

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

****************************************************************************/



void Lcd_Reset(void)
{
	  LCD_RST_Clr;
      HAL_Delay(100);
	  LCD_RST_Set;
      HAL_Delay(100);
}


//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;



/****************************************************************************
* ��    �ƣ�void LCD_SetParam(void)
* ��    �ܣ�

//����LCD����
//������к�����ģʽ�л�

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

****************************************************************************/


void LCD_SetParam(void)
{ 	
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//ʹ�ú���	  
	lcddev.dir=1;//����
	lcddev.width=280;
	lcddev.height=240;
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;			
	Lcd_WriteReg(0x36,0xA0);

#else//����
	lcddev.dir=0;//����				 	 		
	lcddev.width=240;
	lcddev.height=280;
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;	
	Lcd_WriteReg(0x36,0xC0);
#endif
}


/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�,Y_IncMode��ʾ������y������x
����ֵ����

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

*************************************************/
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{
#if USE_HORIZONTAL==1	//ʹ�ú���
	
/*	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end);*/

	x_start = x_start + TFT_COLUMN_OFFSET,x_end=x_end+ TFT_COLUMN_OFFSET;
    Lcd_WriteIndex(0x2a);     //Column address set
    Lcd_WriteData(x_start>>8);    //start column
    Lcd_WriteData(x_start);
    Lcd_WriteData(x_end>>8);    //end column
    Lcd_WriteData(x_end);
    y_start = y_start + TFT_LINE_OFFSET;
    y_end=y_end+ TFT_LINE_OFFSET;
    Lcd_WriteIndex(0x2b);     //Row address set
    Lcd_WriteData(y_start>>8);    //start row
    Lcd_WriteData(y_start);
    Lcd_WriteData(y_end>>8);    //end row
    Lcd_WriteData(y_end);
	
#else

    x_start = x_start + TFT_COLUMN_OFFSET,x_end=x_end+ TFT_COLUMN_OFFSET;
    Lcd_WriteIndex(0x2a);     //Column address set
    Lcd_WriteData(x_start>>8);    //start column
    Lcd_WriteData(x_start);
    Lcd_WriteData(x_end>>8);    //end column
    Lcd_WriteData(x_end);
    y_start = y_start + TFT_LINE_OFFSET;
    y_end=y_end+ TFT_LINE_OFFSET;
    Lcd_WriteIndex(0x2b);     //Row address set
    Lcd_WriteData(y_start>>8);    //start row
    Lcd_WriteData(y_start);
    Lcd_WriteData(y_end>>8);    //end row
    Lcd_WriteData(y_end);
//    Lcd_WriteIndex(0x2C);     //Memory write
#endif
	
	Lcd_WriteIndex(0x2c); //��ʼд��GRAM

}

/*************************************************
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

*************************************************/
void Lcd_SetXY(u16 x,u16 y)
{
  	//Lcd_SetRegion(x,y,x,y);
 #if USE_HORIZONTAL==1	//ʹ�ú���	

	  Lcd_SetRegion(x+1,y+2,x+1,y+2);
	#else		
	  Lcd_SetRegion(x+2,y+1,x+2,y+1);
	#endif
}

	
/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	//Lcd_SetRegion(x,y,x+1,y+1);
 #if USE_HORIZONTAL==1	//ʹ�ú���	
	
  Lcd_SetRegion(x+1,y+2,x+2,y+3);
	
	#else	
	
	Lcd_SetRegion(x+2,y+1,x+3,y+2);

	#endif
	Lcd_WriteData(Data>>8);
	Lcd_WriteData(Data);

}    

/*****************************************
 �������ܣ���TFTĳһ�����ɫ                          
 ���ڲ�����color  ����ɫֵ                                 
******************************************/
//unsigned int Lcd_ReadPoint(u16 x,u16 y)
//{
//  unsigned int Data;
//  Lcd_SetXY(x,y);
//  Lcd_WriteData(Data);
//  return Data;
//}



/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

*************************************************/
void Lcd_Clear(u16 Color)               
{	
   unsigned int i,m;

#if USE_HORIZONTAL==1	//ʹ�ú���	

   //Lcd_SetRegion(2,1,X_MAX_PIXEL+1,Y_MAX_PIXEL);
	 Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
	
   Lcd_WriteIndex(0x2C);
	
 	for(i=0;i<Y_MAX_PIXEL;i++)
    for(m=0;m<X_MAX_PIXEL;m++)
    {
        Lcd_WriteData(Color>>8);
        Lcd_WriteData(Color);
    } 
		
	
#else	
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
	
//   Lcd_WriteIndex(0x2C);
	
 	for(i=0;i<Y_MAX_PIXEL;i++)
    for(m=0;m<X_MAX_PIXEL;m++)
    {	
	  	Lcd_WriteData(Color>>8);
			Lcd_WriteData(Color);
    } 
		
#endif	
		
}



/*************************************************
��������void Lcd_Init(void)
���ܣ�Һ������ʼ������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

*************************************************/

void Lcd_Init(void)
{

	
	  LCD_GPIO_Init();//ʹ��ģ��SPI  ��ʼ��IO�ӿ�

	  Lcd_Reset();    //��λҺ����


		Lcd_WriteIndex(0x11);//Sleep exit 
		
		HAL_Delay(200);
			
		Lcd_WriteIndex(0xB1); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteIndex(0xB2); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteIndex(0xB3); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x05); 
		Lcd_WriteData(0x3C); 
		Lcd_WriteData(0x3C); 
		//------------------------------------End ST7735S Frame Rate---------------------------------// 
		Lcd_WriteIndex(0xB4); //Dot inversion 
		Lcd_WriteData(0x03);
        //--------------ST7789V Power setting---------------//
        Lcd_WriteIndex(0xBB);//VCOM
        Lcd_WriteData(0x3F);

        Lcd_WriteIndex(0xC0); //Power control
        Lcd_WriteData(0x2c);

        Lcd_WriteIndex(0xC2);		//VDV and VRH Command Enable
        Lcd_WriteData(0x01);

        Lcd_WriteIndex(0xC3);			//VRH Set
        Lcd_WriteData(0x0F);		//4.3+( vcom+vcom offset+vdv)

        Lcd_WriteIndex(0xC4);			//VDV Set
        Lcd_WriteData(0x20);				//0v

        Lcd_WriteIndex(0xC6);				//Frame Rate Control in Normal Mode
        Lcd_WriteData(0X01);			//111Hz

        Lcd_WriteIndex(0xd0);				//Power Control 1
        Lcd_WriteData(0xa4);
        Lcd_WriteData(0xa1);

        Lcd_WriteIndex(0xE8);				//Power Control 1
        Lcd_WriteData(0x03);

        Lcd_WriteIndex(0xE9);				//Equalize time control
        Lcd_WriteData(0x09);
        Lcd_WriteData(0x09);
        Lcd_WriteData(0x08);
        Lcd_WriteIndex(0xC5); //VCOM
        Lcd_WriteData(0x1A);
        Lcd_WriteIndex(0x36); //MX, MY, RGB mode
        Lcd_WriteData(0xC0);
		//------------------------------------ST7735S Gamma Sequence---------------------------------// 
        Lcd_WriteIndex(0xE0); //Set Gamma
        Lcd_WriteData(0xD0);
        Lcd_WriteData(0x05);
        Lcd_WriteData(0x09);
        Lcd_WriteData(0x09);
        Lcd_WriteData(0x08);
        Lcd_WriteData(0x14);
        Lcd_WriteData(0x28);
        Lcd_WriteData(0x33);
        Lcd_WriteData(0x3F);
        Lcd_WriteData(0x07);
        Lcd_WriteData(0x13);
        Lcd_WriteData(0x14);
        Lcd_WriteData(0x28);
        Lcd_WriteData(0x30);

        Lcd_WriteIndex(0XE1); //Set Gamma
        Lcd_WriteData(0xD0);
        Lcd_WriteData(0x05);
        Lcd_WriteData(0x09);
        Lcd_WriteData(0x09);
        Lcd_WriteData(0x08);
        Lcd_WriteData(0x03);
        Lcd_WriteData(0x24);
        Lcd_WriteData(0x32);
        Lcd_WriteData(0x32);
        Lcd_WriteData(0x3B);
        Lcd_WriteData(0x14);
        Lcd_WriteData(0x13);
        Lcd_WriteData(0x28);
        Lcd_WriteData(0x2F);
		//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
		Lcd_WriteIndex(0x3A); //65k mode 
		Lcd_WriteData(0x05);
        Lcd_WriteIndex(0x21); 		//����
		Lcd_WriteIndex(0x29); //Display on

    LCD_SetParam();//����LCD����	 

}




























/**************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/**************************************************************************************/









