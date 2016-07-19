/*
 * sensors.c
 *
 *  Created on: Apr 10, 2014
 *      Author: raraujo
 */

#include "chip.h"
#include "fixedptc.h"
#include "sensors.h"
#include "config.h"
#include "motors.h"
#include "EDVS128_LPC43xx.h"
#include "mpu9105.h"
#include "extra_pins.h"
#include "sdcard.h"
#include "xprintf.h"
#include "utils.h"
#include <stdbool.h>
#include "itd.h"

#define ADC_ACCURACY						(10)

#define MOTOR_DRIVER_CURRENT1_SENSOR_PORT	(4)
#define MOTOR_DRIVER_CURRENT1_SENSOR_PIN	(1)
#define MOTOR_DRIVER_CURRENT2_SENSOR_PORT	(4)
#define MOTOR_DRIVER_CURRENT2_SENSOR_PIN	(3)

#define ADC0_CHANNEL						(2)
#define ADC1_CHANNEL						(3)
#define ADC2_CHANNEL						(4)
#define ADC3_CHANNEL						(5)
#define ADC4_CHANNEL						(6)
#define ADC5_CHANNEL						(7)


uint32_t sensorsEnabledCounter;
struct sensorTimer sensorsTimers[MAX_SENSORS];
volatile uint8_t sensorRefreshRequested;

volatile uint32_t lastEventCount = 0;
#if USE_SDCARD
volatile uint32_t lastByteCount = 0;
volatile uint32_t lastEventRecordedCount = 0;
#endif

static ADC_CLOCK_SETUP_T adcConfig;
struct sensorTimer * enabledSensors[MAX_SENSORS];

#define XCORR
//#define FFT
// Buffers for the left and right microphone signals
#ifdef FFT
COMPLEX left0[BUFFER_MAX_SIZE];
COMPLEX right0[BUFFER_MAX_SIZE];
COMPLEX left1[BUFFER_MAX_SIZE];
COMPLEX right1[BUFFER_MAX_SIZE];
#endif

#ifdef XCORR
uint16_t left0[BUFFER_MAX_SIZE];
uint16_t right0[BUFFER_MAX_SIZE];
uint16_t left1[BUFFER_MAX_SIZE];
uint16_t right1[BUFFER_MAX_SIZE];
#endif
extern const int16_t lag_limit;
uint16_t buf_length = 0;
uint8_t buf_flag = 0;  // indicating whether buffer0 or buffer 1 is used
int8_t process_flag = -1;  // flag for processing the buf data

uint8_t stream_adc_flag = 0;  // flag for sending adc through serial towards matlab

/**
 * The Systick handler is used for a lot more tasks than sensor timing.
 * It also provides a timer for decaying for the motor velocity, motor control
 * and second timer used for the LED blinking and Retina event rate.
 */
void SysTick_Handler(void) {  // now the systick handler function is called every 1/50000 second
	static uint16_t second_timer = 0;
	static uint16_t data_left = 0;
	static uint16_t data_right = 0;
	static uint32_t debug_timer = 0;
	//static uint16_t data0,data1;
#if USE_PUSHBOT
	static uint16_t one_k_hertz_timer = 0;
	static uint16_t ten_hertz_timer = 0;
	if (++ten_hertz_timer >= 5000) {  // 100
		ten_hertz_timer = 0;
		if (motor0.controlMode & DECAY_MODE) {
			if (motor0.decayCounter == 0) {
				if (motor0.controlMode & DIRECT_MODE) {
					if (motor0.requestedWidth != 0) {
						motor0.requestedWidth = (motor0.requestedWidth * 90) / 100;
						updateMotorWidth(0, motor0.requestedWidth);
					}
				} else {
					if (motor0.requestedVelocity > 0) {
						motor0.requestedVelocity--;
					} else if (motor0.requestedVelocity < 0) {
						motor0.requestedVelocity++;
					}
				}
			} else {
				motor0.decayCounter--;
			}
		}
		if (motor1.controlMode & (DECAY_MODE)) {
			if (motor1.decayCounter == 0) {
				if (motor1.controlMode & DIRECT_MODE) {
					if (motor1.requestedWidth != 0) {
						motor1.requestedWidth = (motor1.requestedWidth * 90) / 100;
						updateMotorWidth(1, motor1.requestedWidth);
					}
				} else {
					if (motor1.requestedVelocity > 0) {
						motor1.requestedVelocity--;
					} else if (motor1.requestedVelocity < 0) {
						motor1.requestedVelocity++;
					}
				}
			} else {
				motor1.decayCounter--;
			}
		}
	}
	if(one_k_hertz_timer == 50){
		one_k_hertz_timer = 0;
		if (motor0.controlMode & VELOCITY_MODE) {
			motor0.updateRequired = 1;
		}
		if (motor1.controlMode & VELOCITY_MODE) {
			motor1.updateRequired = 1;
		}
	}
#endif
	if (++second_timer >= 50000) { //1000
		lastEventCount = events.currentEventRate;
#if USE_SDCARD
		lastByteCount = sdcard.bytesWrittenPerSecond;
		lastEventRecordedCount = sdcard.eventsRecordedPerSecond;
#endif
		__DSB(); //Ensure it has been saved
		events.currentEventRate = 0;
#if USE_SDCARD
		sdcard.bytesWrittenPerSecond = 0;
		sdcard.eventsRecordedPerSecond = 0;
#endif

		second_timer = 0;
		toggleLed0 = 1;
	}
	// send left&right channel adc values through serial
	if(++debug_timer >= 1000){
		debug_timer = 0;
		if(stream_adc_flag){
			if (Chip_ADC_ReadValue(LPC_ADC1, ADC1_CHANNEL, &data_left) == SUCCESS){
				if (Chip_ADC_ReadValue(LPC_ADC1, ADC5_CHANNEL, &data_right) == SUCCESS){
					xprintf("L%uR%u\r\n", data_left, data_right);
				}
			}
		}
	}
/*
	//GET adc value every 1/50000 second
	// only when both channels successfully get the data that we increase the buf length
	//if(++debug_timer >= 100){
		//xputs("1\n");
		//debug_timer = 0;
		if(!buf_flag){
			//xputs("22\n");
			if(Chip_ADC_ReadValue(LPC_ADC1, ADC1_CHANNEL, &left0[buf_length]) == SUCCESS){  // &left0[buf_length].real
				//xputs("in1\n");
				if(Chip_ADC_ReadValue(LPC_ADC1, ADC5_CHANNEL, &right0[buf_length]) == SUCCESS){
					//xprintf("   %d\n", data0);
					//left0[buf_length].real = data0;
					//right0[buf_length].real = data1;

					if(++buf_length == BUFFER_MAX_SIZE){
						buf_length = 0;
						buf_flag = !buf_flag;
						process_flag = 0;
						//xputs(">>>>>");
					}
				}
			}
		}else{
			//xputs("333\n");
			if(Chip_ADC_ReadValue(LPC_ADC1, ADC1_CHANNEL, &left1[buf_length]) == SUCCESS){
				//xputs("in2\n");
				if(Chip_ADC_ReadValue(LPC_ADC1, ADC5_CHANNEL, &right1[buf_length]) == SUCCESS){
					//xprintf("   %d\n", data0);
					//left1[buf_length].real = data0;
					//right1[buf_length].real = data1;
					if(++buf_length == BUFFER_MAX_SIZE){
						buf_length = 0;
						buf_flag = !buf_flag;
						process_flag = 1;
						//xputs("<<");
					}
				}
			}
		}
	//}
	 */


	/*
	for (int i = 0; i < sensorsEnabledCounter; ++i) {
		if (--enabledSensors[i]->counter == 0) {
			enabledSensors[i]->counter = enabledSensors[i]->reload;
			enabledSensors[i]->triggered = 1;
			sensorRefreshRequested = 1;
		}
	}
	*/
}

STATIC INLINE void printADCRead(uint8_t sensorId, uint8_t channel) {
	uint16_t data;
	if (Chip_ADC_ReadValue(LPC_ADC1, channel, &data) == SUCCESS) {
		xprintf("-S%d %u\n", sensorId, data);
	} else {
		xprintf("-S%d -1\n", sensorId);
	}
}

void batteryInit() {
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC1, 1, ENABLE);
}

#define VBAT_DIVISOR		(11)
void batteryReport() {
	uint16_t adcRead;
	if (Chip_ADC_ReadValue(LPC_ADC1, 1, &adcRead) == SUCCESS) {
		uint32_t data = (adcRead * 2800 * VBAT_DIVISOR) >> 10; //divide by 1024
		xprintf("-S0 %u\n", data);
	} else {
		xputs("-S0 -1\n");
	}
}

void ADC0Init() {
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC1, 2, ENABLE);
}
void ADC0Report() {
	printADCRead(1, 2);
}
void ADC1Init() {
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC1, 3, ENABLE);
}
void ADC1Report() {
	printADCRead(2, 3);
}

void ADC2Init() {
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC1, 4, ENABLE);
}
void ADC2Report() {
	printADCRead(3, 4);
}
void ADC3Init() {
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC1, 5, ENABLE);
}
void ADC3Report() {
	printADCRead(4, 5);
}
void ADC4Init() {
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC1, 6, ENABLE);
}
void ADC4Report() {
	printADCRead(5, 6);
}
void ADC5Init() {
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC1, 7, ENABLE);
}
void ADC5Report() {
	printADCRead(6, 7);
}

void MotorPWMReport() {
	xprintf("-S%d %d %d %d %d\n", PWM_SIGNALS, getMotorWidth(MOTOR0), getMotorWidth(MOTOR1), getMotorDutycycle(MOTOR0),
			getMotorDutycycle(MOTOR1));
}

void MotorCurrentsInit() {
	Chip_SCU_PinMuxSet(MOTOR_DRIVER_CURRENT1_SENSOR_PORT, MOTOR_DRIVER_CURRENT1_SENSOR_PIN, SCU_MODE_INACT | FUNC7);
	Chip_SCU_PinMuxSet(MOTOR_DRIVER_CURRENT2_SENSOR_PORT, MOTOR_DRIVER_CURRENT2_SENSOR_PIN, SCU_MODE_INACT | FUNC7);
	LPC_SCU->ENAIO[0] |= 0x3; //Enable Analog function on these GPIO pins.
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING); //This must be before the burst cmd
	Chip_ADC_SetBurstCmd(LPC_ADC0, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC0, 0, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC0, 1, ENABLE);
}
#define AMPLIFIER_GAIN		(46454ULL) //(1+100k/2.2k)*10
#define SENSE_RESISTOR		(10ULL)
void MotorCurrentsReport() {
	uint16_t motor0, motor1;
	uint64_t motor0Current = -1;
	uint64_t motor1Current = -1;
	if (Chip_ADC_ReadValue(LPC_ADC0, 0, &motor0) == SUCCESS) {
		motor0Current = ((motor0 * 2800ULL * AMPLIFIER_GAIN * SENSE_RESISTOR) >> 10) / 1000ULL;
	}
	if (Chip_ADC_ReadValue(LPC_ADC0, 1, &motor1) == SUCCESS) {
		motor1Current = ((motor1 * 2800ULL * AMPLIFIER_GAIN * SENSE_RESISTOR) >> 10) / 1000ULL;
	}
	xprintf("-S%d %u %u\n", MOTOR_CURRENTS, motor0Current, motor1Current);
}

void EventCountReport() {
#if USE_SDCARD
	xprintf("-S%d %d %d %d\n", EVENT_RATE, lastEventCount, lastEventRecordedCount, lastByteCount);
#else
	xprintf("-S%d %d\n", EVENT_RATE, lastEventCount);
#endif
}

void sensorsInit(void) {
	Chip_ADC_Init(LPC_ADC0, &adcConfig);
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_NO_START, ADC_TRIGGERMODE_RISING);
	Chip_ADC_Init(LPC_ADC1, &adcConfig);
	Chip_ADC_SetStartMode(LPC_ADC1, ADC_NO_START, ADC_TRIGGERMODE_RISING);

	sensorRefreshRequested = 0;
	sensorsEnabledCounter = 0;
	for (int i = 0; i < MAX_SENSORS; ++i) {
		enabledSensors[i] = NULL;
		sensorsTimers[i].initialized = false;
		sensorsTimers[i].triggered = false;
		sensorsTimers[i].reload = 0;
		sensorsTimers[i].counter = 0;
		sensorsTimers[i].position = -1;
		sensorsTimers[i].init = NULL;
		sensorsTimers[i].refresh = NULL;

	}
	sensorsTimers[BATTERY].init = batteryInit;
	sensorsTimers[BATTERY].refresh = batteryReport;
	sensorsTimers[ADC0].init = ADC0Init;
	sensorsTimers[ADC0].refresh = ADC0Report;
	sensorsTimers[ADC1].init = ADC1Init;
	sensorsTimers[ADC1].refresh = ADC1Report;
	sensorsTimers[ADC2].init = ADC2Init;
	sensorsTimers[ADC2].refresh = ADC2Report;
	sensorsTimers[ADC3].init = ADC3Init;
	sensorsTimers[ADC3].refresh = ADC3Report;
	sensorsTimers[ADC4].init = ADC4Init;
	sensorsTimers[ADC4].refresh = ADC4Report;
	sensorsTimers[ADC5].init = ADC5Init;
	sensorsTimers[ADC5].refresh = ADC5Report;
	sensorsTimers[MOTOR_CURRENTS].init = MotorCurrentsInit;
	sensorsTimers[MOTOR_CURRENTS].refresh = MotorCurrentsReport;
	sensorsTimers[PWM_SIGNALS].refresh = MotorPWMReport;
	sensorsTimers[EVENT_RATE].refresh = EventCountReport;

	// initialize channel 4 and 5 for the microphone values
	ADC1Init(); // left
	ADC5Init(); // right

	//uint32_t load = Chip_Clock_GetRate(CLK_MX_MXCORE) / 1000 - 1;
	uint32_t load = Chip_Clock_GetRate(CLK_MX_MXCORE) / ADC_FREQ - 1;
	if (load > 0xFFFFFF) {
		load = 0xFFFFFF;
	}
	SysTick->LOAD = load;
	SysTick->CTRL |= 0x7;	// enable the Systick, bit 0 is enable, bit 1 is
							// interrupt/polling choice, bit 2 selects the core clock/external clock
							// thus 0x07 = 0b111 (enabled, interrupt mode, core clock)
}

void enableSensors(uint32_t mask, uint8_t flag, uint32_t period) {
	for (int i = 0; i < MAX_SENSORS; ++i) {
		if (mask & (1 << i)) {
			enableSensor(i, flag, period);
		}
	}
}

void enableSensor(uint8_t sensorId, uint8_t flag, uint32_t period) {
	if (sensorId >= MAX_SENSORS) {
		return;
	}
	if (sensorsTimers[sensorId].refresh == NULL) {
		return;
	}
	SysTick->CTRL &= ~0x1;	//disable the Systick
	if (flag) {
		if (sensorsTimers[sensorId].position == -1) {
			sensorsTimers[sensorId].counter = period;
			sensorsTimers[sensorId].reload = period;
			enabledSensors[sensorsEnabledCounter++] = &sensorsTimers[sensorId];
			sensorsTimers[sensorId].position = sensorsEnabledCounter - 1;
			if (!sensorsTimers[sensorId].initialized) {
				sensorsTimers[sensorId].initialized = true;
				if (sensorsTimers[sensorId].init != NULL) {
					sensorsTimers[sensorId].init();
				}
			}
		} else {
			sensorsTimers[sensorId].reload = period;	//Update the period
		}
	} else {
		if (sensorsTimers[sensorId].position != -1) {
			//if removing the last one, no need to iterate or do anything besides reducing the counter
			if (sensorsTimers[sensorId].position != sensorsEnabledCounter - 1) {
				for (int i = sensorsTimers[sensorId].position; i < sensorsEnabledCounter; ++i) {
					enabledSensors[i] = enabledSensors[i + 1];
				}
			}
			sensorsTimers[sensorId].position = -1;
			sensorsTimers[sensorId].triggered = 0;
			sensorsEnabledCounter--;
		}
	}
	SysTick->CTRL |= 0x1;	//enable the Systick
}

void getSensorsOutput(uint32_t mask) {
	for (int i = 0; i < MAX_SENSORS; ++i) {
		if (mask & (1 << i)) {
			if (!sensorsTimers[i].initialized) {
				sensorsTimers[i].initialized = true;
				if (sensorsTimers[i].init != NULL) {
					sensorsTimers[i].init();
				}
				timerDelayUs(100);	//Wait for a read on just initialized hardware ( only applicable to ADC)
			}
			if (sensorsTimers[i].refresh != NULL) {
				sensorsTimers[i].refresh();
			}
		}
	}
}
