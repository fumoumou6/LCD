#ifndef _Lcd_Driver_H
#define _Lcd_Driver_H



#include "stm32h7xx_hal.h"

#include "spi.h"
/**************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	



#define u8 uint8_t
#define u16 uint16_t

//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	 wramcmd;		//��ʼдgramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ��	 
}_lcd_dev; 	

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����


#define RED  	  0xf800
#define GREEN	  0x07e0
#define BLUE 	  0x001f
#define WHITE	  0xffff
#define BLACK	  0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111



/////////////////////////////////////�û�������///////////////////////////////////	 
//֧�ֺ��������ٶ����л���֧��8/16λģʽ�л�
#define USE_HORIZONTAL  	1	    //�����Ƿ�ʹ�ú��� 		0,��ʹ��.  1,ʹ��.
//ʹ��ģ��SPI��Ϊ����
#define USE_SOFESPI 0               //�����Ƿ�ʹ�����spi       0,��ʹ��.  1,ʹ��.

/**************************************************************************************/

//����LCD�ĳߴ�

#if USE_HORIZONTAL == 1	//ʹ�ú���
#define X_MAX_PIXEL	        280
#define Y_MAX_PIXEL	        240
#else
#define X_MAX_PIXEL	        240
#define Y_MAX_PIXEL	        280
#endif

//Һ�����ƿ���1�������궨��
#if USE_SOFESPI == 1
#define	LCD_SDA_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET) 	   //PB15��1 
#define	LCD_SCL_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)	     //PB13��1
#endif

#define	LCD_CS_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)	     //PB12��1
#define LCD_RST_Set  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET)	   //PB14��1
#define	LCD_RS_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET)		   //PB1��1
#define	LCD_BLK_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET) 	     //PB0��1 


//Һ�����ƿ���0�������궨��
#if USE_SOFESPI == 1
#define	LCD_SDA_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET)  	  //PB15��0 //DIN
#define	LCD_SCL_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)	    //PB13��0 //CLK
#endif

#define	LCD_CS_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)	   	//PB12��0/CS
#define LCD_RST_Clr  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET)	  //PB14��0 //RES
#define	LCD_RS_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET)		 	//PB1��0 //DC
#define	LCD_BLK_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)  	  //PB0��0 //DIN

#if USE_HORIZONTAL==1	//ʹ�ú���

#define TFT_COLUMN_OFFSET 20
#define TFT_LINE_OFFSET 0

#else
#define TFT_COLUMN_OFFSET 0
#define TFT_LINE_OFFSET 20

#endif

void LCD_GPIO_Init(void);//��ʼ��IO��
void  SPI_WriteData(u8 Data);//STM32_ģ��SPIдһ���ֽ����ݵײ㺯��
void LCD_WriteData_16Bit(uint16_t Data);//��Һ����дһ��16λ����

void Lcd_WriteIndex(u8 Index);//д�������Ĵ�����ַ
void Lcd_WriteData(u8 Data);//  д�Ĵ�������
void Lcd_WriteReg(u8 Index,u8 Data);////д�Ĵ�������

u16 Lcd_ReadReg(u8 LCD_Reg);

void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
//unsigned int Lcd_ReadPoint(u16 x,u16 y);














#endif










/**************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/**************************************************************************************/



