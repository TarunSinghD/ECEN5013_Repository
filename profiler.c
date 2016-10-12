
#include "profiler.h"
#include "MKL25Z4.h"
#include "uart0.h"
#include "main.h"
#include "data.h"
#define TEMP_BUFFER_LENGTH 40
uint8_t temp_buffer[TEMP_BUFFER_LENGTH];

void init_profiler(void)
{
	//Step 1: Clock config
	// Internal Clock and Enable it(MCGIRCLK)
    MCG_C1 |= MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;
    // Fast internal clock mode
    MCG_C2 |= MCG_C2_IRCS_MASK;
    // CLock gate enable for timer1
    SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
    // MCGIRCLK as timer source clock
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(3);

    //Step 3: Disable timer counter  and set CPWMS=0 (up counter mode)
    TPM1_SC =0;

    //Step 4: Timer1 config
    //Set MOD value for timer1 (max value)
    TPM1_MOD = MOD_VAL;
    //prescaler to divide by 1
    TPM1_SC |= TPM_SC_PS(0);

    //Global interrupt enable
	 __enable_irq();
	 //Enable at NVIC
	 NVIC_EnableIRQ(TPM1_IRQn);
	 //Enable timer overflow interrupt
	 TPM1_SC |= TPM_SC_TOIE_MASK;
}

void start_time(void)
{
	//run counter
    TPM1_SC |= TPM_SC_CMOD(1);
}

volatile uint16_t overflow_count=0;
void end_time(void)
{
	uint32_t counter_val=0;
	float clk_time;
	TPM1_SC &= ~TPM_SC_CMOD(1);		//stop counter

	counter_val = TPM1_CNT;
	clk_time = counter_val/T1CLK; //clock

	if(overflow_count !=0)
	{
		clk_time = clk_time + ((MOD_VAL/T1CLK)*overflow_count);
		//overflow_count = 0;
	}

	char arr1[] = {"\r\nExecution Time (Usec):"};
	my_ftoa(clk_time, temp_buffer, 4);
	log_string_param(arr1, string_length(arr1), temp_buffer, string_length(temp_buffer));
	char arr2[] = {"\r\nClock cycles:"};
	my_itoa(temp_buffer, counter_val, 10);
	log_string_param(arr2, string_length(arr2), temp_buffer, string_length(temp_buffer));
	char arr3[] = {"\r\noverflow count:"};
	my_itoa(temp_buffer, overflow_count, 10);
	log_string_param(arr3, string_length(arr3), temp_buffer, string_length(temp_buffer));
	overflow_count = 0;
}

void TPM1_IRQHandler(void)
{
	if(TPM1_SC & TPM_SC_TOF_MASK)
	{
		overflow_count++;					//keep count of oveflow
		TPM1_SC |= TPM_SC_TOF_MASK;			//clear the tof bit by writing 1
	}
}
