
// STM32 Simple Calculator USART2 (Tx PA.2, Rx PA.3) STM32F4 Discovery - sourcer32@gmail.com
 
#include "stm32f4_discovery.h"
 
/**************************************************************************************/
 
void RCC_Configuration(void)
{
  /* --------------------------- System Clocks Configuration -----------------*/
  /* USART2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
 
  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}
 
/**************************************************************************************/
 
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  /*-------------------------- GPIO Configuration ----------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  /* Connect USART pins to AF */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);  // USART2_TX
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);  // USART2_RX
}
 
/**************************************************************************************/
 
void USART2_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
 
  /* USARTx configuration ------------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
  USART_Init(USART2, &USART_InitStructure);
 
  USART_Cmd(USART2, ENABLE);
}
 
/**************************************************************************************/
 
char USART_GetChar(void)
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET); // Wait for Full
 
  return((char)USART_ReceiveData(USART2));
}
 
/**************************************************************************************/
 
void USART_PutChar(char i)
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
 
  USART_SendData(USART2, i);
}
 
/**************************************************************************************/
 
void USART_PutString(char *s)
{
  while(*s)
    USART_PutChar(*s++);
}
 
/**************************************************************************************/
 
void USART_PutDecimal(int i)
{
  char str[16], *s;
  int n;
 
  s = str + sizeof(str); // Point to tail
 
  *--s = 0; // NUL
 
  if (i < 0) // Negative
  {
    n = 1;
    i = -i; // Negate
  }
  else
    n = 0;
 
  do
  {
    *--s = '0' + (char)(i % 10);
    i = i / 10;
  }
  while(i);
 
  if (n) // Add sign if negated
    *--s = '-';
 
  USART_PutString(s);
}
 
/**************************************************************************************/
 
void USART_Calc(void) // Simple Calculator from keystrokes
{
 // int accum, num;
 // char i;
 
 // accum = 0;
 // num = 0;
 
  while(1)
  {
    USART_SendData(USART2, 'A');
    USART_PutString("\r\n");
   /* i = USART_GetChar();
 
    if ((i >= '0') && (i <= '9')) // Decimal?
    {
      num = (num * 10) + (int)(i - '0'); // Load the number
    }
    else if (i == '+')
    {
      accum += num; // add
      num = 0; // clear
      USART_PutDecimal(accum);
      USART_PutString("\r\n");
    }
    else if (i == '-')
    {
      accum -= num; // subtract
      num = 0; // clear
      USART_PutDecimal(accum);
      USART_PutString("\r\n");
    }
    else if (i == '.') // Print current accumulator and number
    {
      USART_PutString("accum:");
      USART_PutDecimal(accum);
      USART_PutString(", num:");
      USART_PutDecimal(num);
      USART_PutString("\r\n");
    }*/
  }
}
 
/**************************************************************************************/
 
int main(void)
{
  RCC_Configuration();
 
  GPIO_Configuration();
 
  USART2_Configuration();
 
  //USART_Calc();
 
  while(1){
    USART_SendData(USART2, 'A');
    USART_PutString("\r\n");
  
}; // Don't want to exit
}

