#ifndef __ITD_H
#define __ITD_H
#include <stdint.h>
#include "sensors.h"


#define XCORR
//#define FFT


typedef struct{
	float real;
	float imag;
}COMPLEX;

#define SOUND_SPEED   	(343)
#define LAG_LIMIT   	(15)      // = mic_distance / soundspeed * ADC_FREQ
#define PI				(3.14)
#define HALF_PI			(1.57)
#define FFT_LENGTH		(256)
#define MIC_DIST		(0.1)


int8_t itd(void);


#endif
