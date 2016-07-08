#ifndef __ITD_H
#define __ITD_H
#include <stdint.h>


typedef struct{
	uint16_t real;
	uint16_t imag;
}COMPLEX;

#define SOUND_SPEED   	(343)
#define LAG_LIMIT   	(15)      // = mic_distance / soundspeed * ADC_FREQ
#define PI				(3.14)
#define FFT_LENGTH		(256)

int8_t itd(void);
int fft(COMPLEX *x, uint32_t N);
int ifft(COMPLEX *x, uint32_t N);


const float cos_tb[] = {  // žŤśČ(PI PI/2 PI/4 PI/8 PI/16 ... PI/(2^k))
-1.000000, 0.000000, 0.707107, 0.923880, 0.980785, 0.995185 , 0.998795, 0.999699, 0.999925, 0.999981,
0.999995, 0.999999, 1.000000, 1.000000, 1.000000, 1.000000 , 1.000000, 1.000000, 1.000000, 1.000000,
1.000000,
};

const float sin_tb[] = {  // žŤśČ(PI PI/2 PI/4 PI/8 PI/16 ... PI/(2^k))
0.000000, 1.000000, 0.707107, 0.382683, 0.195090, 0.098017 , 0.049068, 0.024541, 0.012272, 0.006136,
0.003068, 0.001534, 0.000767, 0.000383, 0.000192, 0.000096 , 0.000048, 0.000024, 0.000012, 0.000006,
0.000003,
};

#endif
