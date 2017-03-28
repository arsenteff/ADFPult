#include "cpu.h"
#include "MDR1986VE1T.h"
#include "MDR32F9Qx_rst_clk.h"


void
CPU_Initialization( void )
{
  MDR_RST_CLK->HS_CONTROL = 0x00000001;                               //HSE - On; Osc mode On
  while( ( MDR_RST_CLK->CLOCK_STATUS & 0x04 ) != 0x04 );              //Wait until HSE not ready

  MDR_RST_CLK->CPU_CLOCK = 0x00000102;                                //CPU Clock = множитель*xMHz

  MDR_RST_CLK->PLL_CONTROL = ( (CFG_CPU_PLL_MULL-1) << 8 ) | ( 1 << 2 );       //PLL CPU On;
  while( ( MDR_RST_CLK->CLOCK_STATUS & 0x02 ) != 0x02 );              //wait until PLL CPU not ready

  RST_CLK_PCLKcmd ( RST_CLK_PCLK_EEPROM, ENABLE );
  MDR_EEPROM->CMD = (( CFG_CPU_QUARTZ_MHZ * CFG_CPU_PLL_MULL ) / 25 ) << 3;                                           //Delay = 0

  MDR_RST_CLK->CPU_CLOCK = 0x00000106;                                //CPU Clock = множитель*xMHz
}


#include "core_cm1.h"

void HardFault_Handler(void)
{
  //__asm("MRS R0, MSP");

  //top of stack is in R0. It is passed to C-function.
  //__asm("BL (Hard_fault_handler_c)");

  /* Go to infinite loop when Hard Fault exception occurs */
  //PRINTF("HardFault - It requires a reboot.");
  //NVIC_SystemReset();
  while ( 1 );
}

void Hard_fault_handler_c(unsigned int* hardfault_args)
{
   unsigned int stacked_r0;
   unsigned int stacked_r1;
   unsigned int stacked_r2;
   unsigned int stacked_r3;
   unsigned int stacked_r12;
   unsigned int stacked_lr;
   unsigned int stacked_pc;
   unsigned int stacked_psr;

   stacked_r0 = ((unsigned long) hardfault_args[0]);
   stacked_r1 = ((unsigned long) hardfault_args[1]);
   stacked_r2 = ((unsigned long) hardfault_args[2]);
   stacked_r3 = ((unsigned long) hardfault_args[3]);

   stacked_r12 = ((unsigned long) hardfault_args[4]);
   stacked_lr = ((unsigned long) hardfault_args[5]);
   stacked_pc = ((unsigned long) hardfault_args[6]);
   stacked_psr = ((unsigned long) hardfault_args[7]);

   /* Go to infinite loop when Hard Fault exception occurs */
   while (1);
}
