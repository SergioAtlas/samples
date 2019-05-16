
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
 #include "main.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_LED': LED thread
 *---------------------------------------------------------------------------*/
 

void mainThread (void const *argument);                             // thread function
osThreadId tid_mainThread;                                          // thread id
osThreadDef (mainThread, osPriorityNormal, 1, 0);                   // thread object

void btnThread (void const *argument);                             // thread function
osThreadId tid_btnThread;                                          // thread id
osThreadDef (btnThread, osPriorityNormal, 1, 0);                   // thread object

void blueThread (void const *argument);                             // thread function
osThreadId tid_blueThread;                                          // thread id
osThreadDef (blueThread, osPriorityNormal, 1, 0);                   // thread object

//void orangeThread (void const *argument);                             // thread function
//osThreadId tid_orangeThread;                                          // thread id
//osThreadDef (orangeThread, osPriorityNormal, 1, 0);                   // thread object

void thread_accel ();                             // thread function
//osThreadId tid_accel_thread;                                          // thread id
//osThreadDef (thread_accel, osPriorityNormal, 1, 0);                   // thread object

enum val_E {																			//	????????????
	Thread_BLue_LED=0xf,														// 	???????????
	Thread_Orange_LED,															
};

uint8_t FlagBtnStatus = 0;												// assignt controller for button 
uint8_t is_system_in_DII = 0;											// assignt controller for state 2
uint8_t thread_type;															// assignt controller name of thread
volatile uint8_t reduce_crossing=0;								// assignt controller to reduce the timing in accelerometer
uint8_t is_it_first=1;														// vluue as a controller
	

int Init_Thread (void) {

  tid_mainThread = osThreadCreate (osThread(mainThread), NULL);		//mainThread thread it initialize the grean and blue LED
  if (!tid_mainThread) return(-1);
  
	tid_btnThread = osThreadCreate (osThread(btnThread), NULL);			//button thread it change the value of FLAGSTATUS
  if (!tid_btnThread) return(-1);
return(0);
}
#define cyle 25									//counter of 25 secounds
#define reduced 15							//counter of 15 secounds

void mainThread (void const *argument) {
uint8_t ii=0;
  while (1) 
	{
		LED_set(GREEN,ON);					// call the fucntion tu turn LED on 	
		LED_set(BLUE,ON);						//call the function to turn the LED off
		
		if(FlagBtnStatus == 1)			// check if the button has been pressed 
		{
			LED_set(GREEN,OFF);				//turn the green LED off
			LED_set(ORANGE,ON);				//turn the orange LED on
			osDelay(2000);						//wait two 2 secounds
			LED_set(ORANGE,OFF);			//turn the orange LED off
			LED_set(RED,ON);					// turn the red LED on
			osDelay(1000);						// delay for 0.1 secoudns
			thread_type =  Thread_BLue_LED;
			tid_blueThread = osThreadCreate (osThread(blueThread), NULL); // it call the blueThread for 25 secounds or 15 
 
			is_system_in_DII = 1;					// it declare the state 2 is on 
			
			for (ii=0; ii < 25 ;ii++){		
				if (ii < 2 ) {
					reduce_crossing = 0;			//it detect the if the button was pressed
				}
			if ((reduce_crossing) == 1 && (ii  < 15) && (is_it_first == 1))  //the ii 
				{
					is_it_first =0;
					ii +=10;
					reduce_crossing = 0;
				}				
			osDelay(1000);
			}
			 
			is_it_first =1;
			is_system_in_DII =0;
			LED_set(RED,OFF);
			thread_type =  Thread_Orange_LED; 
			osDelay(5000);
			
			osThreadTerminate(tid_blueThread);
			LED_set(ORANGE,OFF);
			LED_set(BLUE,ON);
			LED_set(GREEN,ON);
			FlagBtnStatus = 0;
			osDelay(15000);
		}
	}
}
void btnThread (void const *argument) {

  while (1) 
	{
		if(BTN_read == PRESSED)									// if its not press FlagBtnStatus =0
		{		
			FlagBtnStatus = 1;										// statu change 
		}					
	}
}
void blueThread (void const *argument) {

  while (1) 
	{
		
		if (thread_type == Thread_BLue_LED ) { 		// it ask if the blue blinking thread is on 
    Single_WriteI2C(0x1c,0x71); 							//call the fucntion to beep on
	   		
		LED_set(BLUE,ON);													// function of LED ON
		thread_accel();														//call fucntion accelrometer to see any cahnge in the accelerometer value
		osDelay(100);															//delay 		
		Single_WriteI2C(0x1c,0x00); 							//call the fucntion to set the beep off	
		LED_set(BLUE,OFF);												//fucntion blue LED off
		thread_accel();														//call fucntion accelrometer to see any cahnge in the accelerometer value
		osDelay(100);															//delay 
		thread_accel();														//call fucntion accelrometer to see any cahnge in the accelerometer value
		}
		//if the thread orange is activated the sequence activate LED orange on and 
		//blue LED is on after 0.1 sec LED blue is off for 3 times and the ORANGE LED off
		else if (thread_type == Thread_Orange_LED)
			
			{
		LED_set(ORANGE,ON);
		LED_set(BLUE,ON);
		osDelay(100);
		LED_set(BLUE,OFF);
		osDelay(100);
		LED_set(BLUE,ON);	
		osDelay(100);
		
		LED_set(ORANGE,OFF);
		LED_set(BLUE,OFF);
		osDelay(100);	
		LED_set(BLUE,ON);
		osDelay(100);
		LED_set(BLUE,OFF);
		osDelay(100);
		}
	}
}
 




#define SENSITIVITY 500		// define the sencityvy value of the X, Y ,Z of the acceerometer
void thread_accel ( ) {
	//Declares the variable to store the z-axis MS 8-bits in
	uint8_t X_Reg_H; //Declares the variable to store the x-axis MS 8-bits in
	uint8_t Y_Reg_H; //Declares the variable to store the y-axis MS 8-bits in 
	uint8_t Z_Reg_H; //Declares the variable to store the z-axis MS 8-bits in
	int16_t X_accn;  //Declares the variable to store the X value in a 16 bit value
	uint8_t X_Reg_L;  //Declares the variable to store the x-axis MS 8-bits in
	uint8_t Y_Reg_L;	//Declares the variable to store the y-axis MS 8-bits in
	uint8_t Z_Reg_L;  //Declares the variable to store the z-axis MS 8-bits in
	int16_t Y_accn;   //declare the variable to store the Y axis in a 16 bit value 
	int16_t Z_accn;		//declare the variable to store the Z_axis in a 16 bit value
	uint16_t ii;
	
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) == SET){ // accelerometer setting the accelerometer to detect
	
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);				// get any change on accelerometer 
		 	X_Reg_H =  ReadSPI(SPI_Params ,0x29);       //function to send the value to read the 
			//read 2	
	 		X_Reg_L =  ReadSPI(SPI_Params ,0x28);       //function to send the value to read the 
			X_accn=(X_Reg_H<<8)|X_Reg_L;								//add the value of 
			
			//Read 3
			Y_Reg_H =  ReadSPI(SPI_Params ,0x2B);				
			Y_Reg_L =  ReadSPI(SPI_Params ,0x2A);
			Y_accn=(Y_Reg_H<<8)|Y_Reg_L;
			
			
			Z_Reg_H =  ReadSPI(SPI_Params ,0x2D);				
			Z_Reg_L =  ReadSPI(SPI_Params ,0x2C);
			Z_accn=(Z_Reg_H<<8)|Z_Reg_L;

			if(Y_accn < -SENSITIVITY){ // Check to see if the acceleration value is positive or negative - the acceleration is a signed 16-bit number so the MSB of the upper 8-bits (register H) is the sign bit: 1 is negative, 0 is positive. Refer to the C Programming guide or Bits – Bytes - Logic Functions (Negative numbers) document if you are unclear about this.
       reduce_crossing =1;
			}
			else if(Y_accn > SENSITIVITY){

		  reduce_crossing = 1;
			}
			else{

 
			}
				
			if((X_accn < -SENSITIVITY)){ // Check to see if the acceleration value is positive or negative - the acceleration is a signed 16-bit number so the MSB of the upper 8-bits (register H) is the sign bit: 1 is negative, 0 is positive. Refer to the C Programming guide or Bits – Bytes - Logic Functions (Negative numbers) document if you are unclear about this.
      reduce_crossing=1;
			}
			else if(X_accn > SENSITIVITY){
      reduce_crossing = 1;
			}
			else{
 
			} 
			// Check to see if the acceleration value is positive or negative - the acceleration is a signed 16-bit 
			//number so the MSB of the upper 8-bits (register H) is the sign bit: 1 is negative, 0 is positive.
			//Refer to the C Programming guide or Bits – Bytes - Logic Functions (Negative numbers) 
			//document if you are unclear about this.
     
			if((Z_accn < -SENSITIVITY)){ 
      reduce_crossing=1;
			}
			else if(Z_accn > SENSITIVITY){	
      reduce_crossing = 1;
			}
			else{
 
			} 
			
			
    }
  }



