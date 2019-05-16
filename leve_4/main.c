 


#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_i2s.h"

extern 
	int Init_Thread(void);
extern osThreadId tid_Thread_LED;
 // Declarations
SPI_HandleTypeDef SPI_Params; // Declares the structure handle for the parameters of SPI1

void LED_initialize(void);  // initialize the configuration of the LED
void BTN_initialize(void);	// initialize the configuration for the button 
void initSpi(void);					// initialize the configuration of the psi
 

void Sys_init(void);				// initialize the system configuration 
void Init_accel(void) ;			// initialize the accelerometre
static void Error_Handler(void);	// errors
////////////////////////
void trythis( void);		
//////////////////////////////////
void I2C1_Init(void);					/// initialize the I2C

#ifdef RTE_CMSIS_RTOS_RTX

extern uint32_t os_time;     //declare the value for timer

uint32_t HAL_GetTick(void) { 
  return os_time; 
}
#endif

/**
  * System Clock Configuration
  */
void SystemClock_Config(void) {

	#ifdef STM32F401xC
  
	RCC_OscInitTypeDef RCC_OscInitStruct;		// ????????????
  RCC_ClkInitTypeDef RCC_ClkInitStruct;   // ???????????/

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();				

  /* The voltage scaling allows optimizing the power consumption when the
     device is clocked below the maximum system frequency (see datasheet). */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 |
                                RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
#else 
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
 

#endif
	 
}

static void Error_Handler(void)
{
  while(1)
  {
	
  }
}

/**
  * Main function
  */
//thread accelerometer get 
extern void thread_accel (void);					
int main (void) {

	
	
  osKernelInitialize();                     /* initialize CMSIS-RTOS          */

  HAL_Init();                               /* Initialize the HAL Library     */

  SystemClock_Config();                     /* Configure the System Clock     */
  Sys_init();																// call the function 
 
  LED_initialize();													// call the function 
  BTN_initialize();													// call the function
////////////////
//I2C1_Init();																// initialize the i2ci
/////////////////////////	
  Init_Thread();                       			// Create LED thread              */

  osKernelStart();                          // start thread execution         */
 

  while (1) {
//    while (Buttons_GetState() & 1U);        /* Wait while holding USER button */
 //   osSignalSet(tid_Thread_LED, 1U);        /* Signal LED thread              */
 //   osDelay(500);                           /* Wait 500ms                     */
		osDelay(1000);
  }
}



/// new code Soffar :
// initially the GPIOA
void BTN_initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOA_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
}
//initial the port A
void LED_initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitTypeDef GPIO_InitStruct_A;
	__GPIOD_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	GPIO_InitStruct_A.Pin = GPIO_PIN_4;
	GPIO_InitStruct_A.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_A.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct_A.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStruct_A);
	
}
// this fucntion ste the LED on and off
void LED_set(uint32_t LED, GPIO_PinState value)
{
	HAL_GPIO_WritePin(GPIOD, LED, value);			//fucntion fund in the stm32f4xx_hal_gpio
}




/////////////accelorometer
void Sys_init(void) {
	
GPIO_InitTypeDef GPIOA_Params;			 								// give the structure the for the parameters of GPIOA
GPIO_InitTypeDef GPIOE_Params;
GPIO_InitTypeDef GPIOD_Params;											// give structure for parameters of GPIOE
GPIO_InitTypeDef GPIOE_Params_I;
	// Code to initialise the SPI
RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 								// enable the SPI1

SPI_Params.Instance = SPI1; 												// Selects which SPI interface to use
SPI_Params.Init.Mode = SPI_MODE_MASTER; 						// Sets the STM32F407 to act as the master
SPI_Params.Init.NSS = SPI_NSS_SOFT; 								// Sets the slave to be controlled by software
SPI_Params.Init.Direction = SPI_DIRECTION_2LINES; 	// Sets the SPI to full-duplex
SPI_Params.Init.DataSize = SPI_DATASIZE_8BIT; 			// Sets the data packet size to 8-bit
SPI_Params.Init.CLKPolarity = SPI_POLARITY_HIGH; 		// Sets the idle polarity for the clock line to high
SPI_Params.Init.CLKPhase = SPI_PHASE_2EDGE; 				// Sets the data line to change on the second transition of the clock line
SPI_Params.Init.FirstBit = SPI_FIRSTBIT_MSB;				// Sets the transmission to MSB first 
SPI_Params.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; // Sets the clock prescaler to divide the main APB2 clock (previously set to 84MHz) by 32 to give a SPI clock of 2.625MHz, which is less the maximum value of 10MHz for the SPI.

HAL_SPI_Init(&SPI_Params); // Configures the SPI using the specified parameters
// Code to initialise pins 5-7 of GPIOA
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //Enable the clock for GPIOA

GPIOA_Params.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_4; // Selects pins 5,6 and 7
GPIOA_Params.Alternate = GPIO_AF5_SPI1; 					//Selects alternate function 5 which corresponds to SPI1
GPIOA_Params.Mode = GPIO_MODE_AF_PP; 							//Selects alternate function push-pull mode
GPIOA_Params.Speed = GPIO_SPEED_FAST; 						//Selects fast speed3
GPIOA_Params.Pull = GPIO_NOPULL; 									//Selects no pull-up or pull-down activation
HAL_GPIO_Init(GPIOA, &GPIOA_Params); 							// Sets GPIOA into the modes specified in GPIOA_Params

// Code to initialise pin 3 of GPIOE
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; 							//Enable the clock for GPIOE
GPIOE_Params.Pin = GPIO_PIN_3; 										// Selects pin 3
GPIOE_Params.Mode = GPIO_MODE_OUTPUT_PP; 					//Selects normal push-pull mode
GPIOE_Params.Speed = GPIO_SPEED_FAST; 						//Selects fast speed
GPIOE_Params.Pull = GPIO_PULLUP; 									//Selects pull-up activation

HAL_GPIO_Init(GPIOE, &GPIOE_Params); // Sets GPIOE into the modes specified in GPIOE_Params


GPIOE_Params_I.Pin=GPIO_PIN_0;
GPIOE_Params_I.Mode=GPIO_MODE_IT_RISING;
GPIOE_Params_I.Speed=GPIO_SPEED_FAST;
HAL_GPIO_Init(GPIOE, &GPIOE_Params_I);

GPIOE->BSRR = GPIO_PIN_3; //Sets the serial port enable pin CS high (idle)
__HAL_SPI_ENABLE(&SPI_Params); //Enable the SPI
// Initialize GPIO Port for LEDs
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable Port D clock
GPIOD->MODER |= GPIO_MODER_MODER15_0; // Port D.14 output - red LED
GPIOD->MODER |= GPIO_MODER_MODER14_0; // Port D.12 output - green LED
GPIOD->MODER |= GPIO_MODER_MODER13_0; // Port D.14 output - red LED
GPIOD->MODER |= GPIO_MODER_MODER12_0;
	Init_accel();
}

void Init_accel(void) {
	
  	uint8_t read_reg;
	///write reg 4
	WriteSPI(SPI_Params ,0x83, 0x20);// from : 0x33 to 0x63

	// read_reg =  ReadSPI(SPI_Params ,0x20);
	///write reg_5
	 WriteSPI(SPI_Params ,0x20 ,0x24); // full scale 
	// read_reg =  ReadSPI(SPI_Params ,0x20);
	//Write Reg 3
	 WriteSPI(SPI_Params ,0xC8, 0x23);
	// read_reg =  ReadSPI(SPI_Params ,0x23);
	
}
 

	
	

void WriteSPI(SPI_HandleTypeDef SPI_Params ,uint8_t data, uint8_t addr) {
	/* Start SPI transmission */
	GPIOE->BSRR = GPIO_PIN_3<<16;
	
/* Add read bit */
//	addr = (0x80) | addr ;
	
	/* Send address */
	HAL_SPI_Transmit(&SPI_Params,&addr,1,1000);
	//TM_SPI_Send(LIS302DL_LIS3DSH_SPI, addr);
	/* Send data */
	HAL_SPI_Transmit(&SPI_Params,&data,1,1000);
//	TM_SPI_WriteMulti(LIS302DL_LIS3DSH_SPI, data, count);
	
	/* Stop SPI transmission */
  GPIOE->BSRR = GPIO_PIN_3;
}

uint8_t ReadSPI(SPI_HandleTypeDef SPI_Params ,uint8_t addr) {
	/* Start SPI transmission */
	
	uint8_t empty_data = 0x00;
  uint8_t reg_val;
	GPIOE->BSRR = GPIO_PIN_3<<16;
	
/* Add read bit */
	addr |= 0x80;
	
	/* Send address */
	HAL_SPI_Transmit(&SPI_Params,&addr,1,1000);
	//TM_SPI_Send(LIS302DL_LIS3DSH_SPI, addr);
	/* Send data */
	HAL_SPI_Receive(&SPI_Params,&empty_data,1,1000);
//	TM_SPI_WriteMulti(LIS302DL_LIS3DSH_SPI, data, count);
	
	/* Stop SPI transmission */
  GPIOE->BSRR = GPIO_PIN_3;
	reg_val = *SPI_Params.pRxBuffPtr;
	return (reg_val);
}



 
 

 



 
I2C_HandleTypeDef hi2c1;
void I2C1_Init()
{
 
    HAL_StatusTypeDef I2C_State; 																// declare State handle
    GPIO_InitTypeDef GPIO_InitStruct; 													// Declares the structure handle for the parameters of the reset pin on GPIOE
 
	
	
     __GPIOB_CLK_ENABLE(); 																			// here we enable clock for port B
     GPIO_InitStruct.Pin = GPIO_PIN_6;
     GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;                   	 //GPIO_MODE_OUTPUT_PP
     GPIO_InitStruct.Pull = GPIO_NOPULL;                         //GPIO_PULLUP
     GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
     GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;              		 //GPIO_MODE_OUTPUT_PP
     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


     GPIO_InitStruct.Pin = GPIO_PIN_9; 														//SDA for I2c Protocol
     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);											//


     __I2C1_CLK_ENABLE(); 																			  //I2C1 clock anbling 
     __I2C1_FORCE_RESET();																				//restar the I2C1
     __I2C1_RELEASE_RESET(); 																			// start


     hi2c1.Instance = I2C1;
     hi2c1.Init.ClockSpeed = 100000; 													// datasheet audio
     hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
     hi2c1.Init.OwnAddress1 = 0xEE;
     hi2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
     hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
     hi2c1.Init.OwnAddress2     = 0;
     hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
     hi2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLED;
     HAL_I2C_Init(&hi2c1);

 //   __HAL_I2S_ENABLE(&I2S_Params);

    GPIOD->BSRR |= GPIO_PIN_4; 																		//Sets the reset pin of CS43L22 high
		
}

void Single_WriteI2C(uint8_t REG_Address,uint8_t REG_data)				
{
    uint8_t TxData[2] = {REG_Address,REG_data};
    HAL_StatusTypeDef i;
    uint8_t j=0;
//I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout
    HAL_I2C_Master_Transmit(&hi2c1,0x94,(uint8_t*)TxData,2,4000);  //it get the I2C_Chandle , the dev adress and pdata, size , time_out
}

uint8_t rec_data;
//READ THE VALUE RECORDER 
void Single_ReadI2C(void)
{
     
    HAL_StatusTypeDef i;
    uint8_t j=0;

    //HAL_I2C_Master_Transmit(&hi2c1,0x94,(uint8_t*)TxData,2,4000);
		HAL_I2C_Master_Receive(&hi2c1, 0x94, &rec_data,1, 1000); 			//	get the I2C_handle, dv addres, data , size , time out 
}


 