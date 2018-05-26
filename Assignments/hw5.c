
#include "System_MKL25Z4.h"
#include "MKL25Z4.h"
#include <stdint.h>
uint32_t pre_interrupt=0,post_interrupt=0,difference=0;

void RED_LED_setup()	//Setup Red LED
{
	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB_BASE_PTR->PCR[18] = PORT_PCR_MUX(3);
	return;
}

void TPM_Init() //Setup TDM
{
	MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
	MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK; //Select fast internal clock
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable TPM2 clock
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);
	TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);	// divide 4 MHz by 2^7 = 128
	TPM2_BASE_PTR->MOD = (16384)-1;	//set the frequency 50 Hz
	TPM2_BASE_PTR->SC |= TPM_SC_TOIE_MASK;
	TPM2_BASE_PTR->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;	//Enable TPM Interrupt
	TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->MOD / 8; //Enable TPM Interrupt
	return;
}

void SysTick_Init() //Setup TDM
{
	SysTick-> CTRL = 0;
	SysTick-> LOAD = 0xFFFFFF;
	SysTick-> VAL = 0;
	SysTick-> CTRL = 7;
	return;
}

void TPM2_Handler()
{
	GPIOB_PTOR |= (1<<18); // Toggle Red LED
	post_interrupt = SysTick-> LOAD;
	difference=pre_interrupt-post_interrupt;
}

int main(void)
{
	TPM_Init();
	RED_LED_setup();
	SysTick_Init();
	pre_interrupt = SysTick-> LOAD;
	NVIC -> ISPR[0] = 1 << 19;
	return 0;
}

