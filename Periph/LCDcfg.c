#include "lcdcfg.h"
#include "MDR1986VE1T.h"

//--- Clock configuration ---
void ClkConfig2()
{
        MDR_RST_CLK->HS_CONTROL = 0x00000001;                       //HSE - On; Osc mode On
        while((MDR_RST_CLK->CLOCK_STATUS&0x04)!=0x04);      //Wait until HSE not ready
        MDR_EEPROM->CMD = 0;
        MDR_RST_CLK->CPU_CLOCK = 0x00000102;                        //CPU Clock = HSE (16MHz)
        MDR_RST_CLK->PER_CLOCK |= 1<<24;                            //clock of PORTD On
}

