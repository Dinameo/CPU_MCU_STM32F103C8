#ifndef __SRF04_H
#define __SRF04_H

#include "main.h"

#define FCLK		(double) 8												// MHz
#define PSC			(double) 3
#define TICK 		(double) ((PSC+1)/FCLK)					// us
#define V_SOUND	(double) 0.0343									// (cm/us)


typedef struct {
	GPIO_TypeDef* ECH_Port;
	GPIO_TypeDef* TRI_Port;
	
	uint16_t ECH_Pin;
	uint16_t TRI_Pin;
} SRF04Cnf_t;
double SRF04_DistanceCalc(uint16_t Echo_cnt);
void SRF04_SendTrig(SRF04Cnf_t* SRF04, TIM_HandleTypeDef* htim);
double SRF04_GetDistance(SRF04Cnf_t* SRF04, TIM_HandleTypeDef* htim);
#endif