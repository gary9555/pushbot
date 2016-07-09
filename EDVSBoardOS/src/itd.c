#include "itd.h"
#include <stdint.h>
#include <math.h>
#include "sensors.h"


static const uint8_t sft  = BUFFER_MAX_SIZE / 2;
static const uint8_t lag_limit = MIC_DIST / SOUND_SPEED * ADC_FREQ;

static int8_t abs(int8_t num);
static void conjugate(COMPLEX *x, uint16_t length);
static void max_index(COMPLEX *x, uint16_t lengt, int * max, int8_t * max_idx);
static float norm(COMPLEX *x, uint16_t length);
static uint32_t floor_log2_32(uint32_t x);
int ones_32(uint32_t n);

#define CONJ_REAL(left, right, i)   \
    (left[i].real*right[i].real \
     + left[i].imag*right[i].imag)

#define CONJ_IMAG(left, right, i)   \
    (left[i].real*right[i].imag \
     - left[i].imag*right[i].real)

int8_t itd(){

	// fft(x)
	int8_t angle;
	COMPLEX *left;
	COMPLEX *right;
	int8_t lag;

	if(process_flag == 0){
		left=left0;
		right=right0;
	}
	else{
		left=left1;
		right=right1;
	}

	fft(left,BUFFER_MAX_SIZE);
	fft(right,BUFFER_MAX_SIZE);

	float normvalue = norm(left,BUFFER_MAX_SIZE) * norm(right,BUFFER_MAX_SIZE);

	//
	for(uint16_t i=0; i<BUFFER_MAX_SIZE;i++){
		left[i].real = CONJ_REAL(left, right, i) / normvalue;
		left[i].imag = CONJ_IMAG(left, right, i) / normvalue;
	}

	//
	ifft(left,BUFFER_MAX_SIZE);

	// get the lag value
	int max_pos, max_neg;
	int8_t lag_pos,lag_neg;

	COMPLEX * temp1 = &left[0];
	COMPLEX * temp2 = &left[BUFFER_MAX_SIZE-lag_limit];
	max_index(temp1, lag_limit+1, &max_pos, &lag_pos);
	max_index(temp2, lag_limit  , &max_neg, &lag_neg);

	if(max_pos >= max_neg){
		lag = lag_pos;
	}else{
		lag = lag_neg - lag_limit;
	}

	float est_diff = lag * SOUND_SPEED / ADC_FREQ;

	if(est_diff != 0){
	    //angle = (PI/2 - atan((0.01/est_diff^2-1) / (0.01/est_diff^2-1+est_diff^2/4-0.05^2)^0.5))/PI*180;
	    angle = (HALF_PI - atan(sqrt( 0.01/est_diff*est_diff - 1)));
	    if(est_diff < 0)
	        angle = -angle;
	}else{
	    angle = 0;
	}

	return angle;
}

int fft(COMPLEX *x, uint32_t N)
{
	int i,j,l,k;
	static uint32_t M = 0;
    static uint32_t ND4 = 0;
	static float sR,sI,tR,tI,uR,uI;


    /* Separate even and odd */
    M = N >> 1;
    for (i=0; i<M; i++) {
        x[i].real = x[i<<1].real;
        x[i].imag = x[(i<<1)+1].real;
    }

    /* N/2 points FFT */
    fft(x, M);

    /* Even/Odd frequency domain decomposition */
    ND4 = N >> 2;
    for (i=1; i<ND4; i++) {
        j = M - i;
        k = i + M;
        l = j + M;
        x[k].real = (x[i].imag + x[j].imag) / 2;
        x[l].real = x[k].real;
        x[k].imag = -(x[i].real - x[j].real) / 2;
        x[l].imag = -x[k].imag;
        x[i].real = (x[i].real + x[j].real) / 2;
        x[j].real = x[i].real;
        x[i].imag = (x[i].imag - x[j].imag) / 2;
        x[j].imag = -x[i].imag;
    }
    x[N-ND4].real = x[ND4].imag;
    x[M].real = x[0].imag;
    x[N-ND4].imag = 0;
    x[M].imag = 0;
    x[ND4].imag = 0;
    x[0].imag = 0;

    /* Complete last stage FFT */
    uR = 1;
    uI = 0;
    //k = floor_log2_32(M);
    //sR = cos_tb[k]; //cos(PI / M);
    //sI = -sin_tb[k];  // -sin(PI / M)
    sR = cos(PI / M);
    sI = -sin(PI / M);

    for (i=0; i<M; i++) {   /* loop for each sub DFT */
        k = i + M;
        tR = x[k].real * uR - x[k].imag * uI;
        tI = x[k].real * uI + x[k].imag * uR;
        x[k].real = x[i].real - tR;
        x[k].imag = x[i].imag - tI;
        x[i].real += tR;
        x[i].imag += tI;

        tR = uR;
        uR = tR * sR - uI * sI;
        uI = tR * sI + uI *sR;
    } /* Next i */

	return 0;
}

int ifft(COMPLEX *x, uint32_t N)
{
	int k = 0;

    /* Make frequency domain symmetrical */
	for (k=(N>>1)+1; k<N; k++) {
        x[k].real = x[N-k].real;
		x[k].imag = -x[N-k].imag;
	}

    /* Add real and imag parts together */
    for (k=0; k<N; k++) {
        x[k].real += x[k].imag;
    }

	fft(x, N);    /* using FFT */

	for (k=0; k<N; k++) {
		x[k].real = (x[k].real + x[k].imag) / N;
		x[k].imag = 0;
	}

	return 0;
}

static int8_t abs(int8_t num){
	if(num<0)
		num = -num;
	return num;
}

static void max_index(COMPLEX *x, uint16_t length, int * max, int8_t * max_idx){
	*max = 0;
	for(uint16_t i=0;i<length;i++){
		if(abs((x+i)->real) > *max){
			*max = abs((x+i)->real);
			*max_idx = i;
		}
	}
	return;
}

static void conjugate(COMPLEX *x, uint16_t length){
	for(uint16_t i=0; i<length; i++)
		x[i].imag = -x[i].imag;
}

static float norm(COMPLEX *x, uint16_t length){
	float sum = 0;
	for(uint8_t i = 0; i<length; i++){
		sum += x[i].real*x[i].real + x[i].imag*x[i].imag;
	}
	return sqrt(sum);
}

static uint32_t floor_log2_32(uint32_t x)
{
    x |= (x>>1);
    x |= (x>>2);
    x |= (x>>4);
    x |= (x>>8);
    x |= (x>>16);

    return (ones_32(x>>1));
}

int ones_32(uint32_t n)
{
    unsigned int c =0 ;
    for (c = 0; n; ++c)
    {
        n &= (n - 1) ; // clear the lowest bit 1
    }
    return c ;
}
