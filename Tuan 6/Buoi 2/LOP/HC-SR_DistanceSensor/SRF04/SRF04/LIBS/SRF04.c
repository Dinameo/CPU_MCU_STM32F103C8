#include "main.h"
#include "SRF04.h"


double SRF04_DistanceCalc(uint16_t Echo_cnt) {
	double time_measure_us = Echo_cnt*TICK;
	return (double) (time_measure_us*V_SOUND)/2.0;
}
void SRF04_SendTrig(SRF04Cnf_t* SRF04, TIM_HandleTypeDef* htim) {
	
	HAL_GPIO_WritePin(SRF04->TRI_Port, SRF04->TRI_Pin, GPIO_PIN_SET);
	__HAL_TIM_SetCounter(htim, 0);
	while(__HAL_TIM_GetCounter(htim) < 20);
	HAL_GPIO_WritePin(SRF04->TRI_Port, SRF04->TRI_Pin, GPIO_PIN_RESET);
}
double SRF04_GetDistance(SRF04Cnf_t* SRF04, TIM_HandleTypeDef* htim) {
	while(HAL_GPIO_ReadPin(SRF04->ECH_Port, SRF04->ECH_Pin) == GPIO_PIN_RESET);
	__HAL_TIM_SetCounter(htim, 0);
	while(HAL_GPIO_ReadPin(SRF04->ECH_Port, SRF04->ECH_Pin) == GPIO_PIN_SET);
	uint16_t Echo_cnt = __HAL_TIM_GetCounter(htim);
	double Distance = SRF04_DistanceCalc(Echo_cnt);
	return Distance;
}
