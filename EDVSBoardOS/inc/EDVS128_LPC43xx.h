#ifndef DVS_H_
#define DVS_H_

#include <stdint.h>
#include "config.h"

// ***************************************************************************** modes
#define EDVS_MODE_DEFAULT			EDVS_MODE_INTERNAL

enum EDVS_MODE {
	EDVS_MODE_INTERNAL,				//  2 Bytes/event
	EDVS_MODE_MASTER_ARMED,			//  variable timestamp
	EDVS_MODE_MASTER_RUNNING,		//  variable timestamp
	EDVS_MODE_SLAVE					//  4 Bytes/event
};

// ***************************************************************************** data formats
#define EDVS_DATA_FORMAT_DEFAULT			EDVS_DATA_FORMAT_BIN

#define EDVS_DATA_FORMAT_BIN				 0					//  2 Bytes/event


/*
 * These definitions are to be used with the processingMode variable.
 * The first byte is left to be used as a bitfield with the first bit being
 * used to mark whether or not events should be stream.
 * The following 3 bytes are used as a counter for the numbers of tasks which need to
 * process the events.
 *
 * The reason for this added complexity comes from the possibility of disabling tasks that process
 * events like the SD card recording.
 *
 */
#define EDVS_STREAM_EVENTS					(1<<0)
#define EDVS_PROCESS_EVENTS					(1<<8)

#define DVS_EVENTBUFFER_SIZE_BITS		((uint32_t) 12)
#define DVS_EVENTBUFFER_SIZE		  	(((uint32_t) 1)<<DVS_EVENTBUFFER_SIZE_BITS)
#define DVS_EVENTBUFFER_MASK		  	(DVS_EVENTBUFFER_SIZE - 1)

struct eventRingBuffer {
	uint32_t eventBufferTimeLow[DVS_EVENTBUFFER_SIZE]; /* 4 byte timestamp ring buffer*/
	uint16_t eventBufferA[DVS_EVENTBUFFER_SIZE]; /* events address ring buffer*/
	uint32_t ringBufferLock; /* Lock to notify the M0 that the M4 core is accessing the ring buffer */
	uint32_t eventBufferWritePointer; /* the write pointer for the ring buffer */
	uint32_t eventBufferReadPointer; /* the read pointer for the ring buffer */
	uint32_t currentEventRate; /* the retina event rate per second */
};

extern volatile struct eventRingBuffer events;

#define SYNCHRONIZATION_PORT		(2)
#define SYNCHRONIZATION_PIN			(4)
#define SYNCHRONIZATION_CHANNEL		(0)

#define TIMER_CAPTURE_CHANNEL 		(1)
#define EVENT_PORT					(3)
#define PIN_ALL_ADDR            ((uint32_t) 0x00007FFF)// all 15 address bits from DVS
#define BIAS_diffOn			 8
#define BIAS_diff			 9
#define BIAS_foll			10
#define BIAS_Pr				11

//BIAS seetings

#define BIAS_DEFAULT				0			// "BIAS_DEFAULT"

/**
 * It initializes the Retina chip, by pushing the default bias levels,
 * initializing the GPIO and the timer which is used to capture events.
 */
extern void DVS128ChipInit(void);

/**
 * It initializes Timer1 in order for capture to be possible.
 */
extern void DVS128InitTimer(void);

/**
 * Return a bias value
 * @param biasID Bias identifier, it should be between 0 and 12
 * @return the bias value or 0 if biasID is invalid
 */
extern uint32_t DVS128BiasGet(uint32_t biasID);

/**
 * It set a bias value
 * @param biasID Bias identifier, it should be between 0 and 12
 * @param biasValue the new bias values, should be smaller than 0xFFFFFF
 */
extern void DVS128BiasSet(uint32_t biasID, uint32_t biasValue);

/**
 * It loads the bias array with a default set of values.
 * There are currently 6 available.
 * @param biasSetID a value between 0 and 5
 */
extern void DVS128BiasLoadDefaultSet(uint32_t biasSetID);

/**
 * It flushs the bias value array to the Retina chip.
 * @param multiplier each bais value is mulplied by this value before being sent to the
 *        retina chip, it should usually be 1.
 */
extern void DVS128BiasFlush(uint32_t multiplier);

/**
 * It enables or disables the streaming of retina events through the UART.
 * @param flag ENABLE or DISABLE
 */
static inline void DVS128FetchEventsEnable(uint8_t flag) {
	if (flag) {
		eDVSProcessingMode |= EDVS_STREAM_EVENTS;
	} else {
		eDVSProcessingMode &= ~EDVS_STREAM_EVENTS;
	}
}

/**
 * It enables or disables the streaming of retina events through the UART.
 * @param flag ENABLE or DISABLE
 */
static inline void DVS128SetMode(enum EDVS_MODE mode) {
	eDVSProcessingMode = mode;
}

#endif