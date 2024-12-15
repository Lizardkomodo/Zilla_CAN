/*
 * Zilla_EVA_Wifi_Module.c
 *
 *  Created on: Nov 24, 2024
 *      Author: Benny
 */
#include "Zilla_EVA_Wifi_Module.h"
#include "stm32f1xx_hal_can.h"
extern CAN_HandleTypeDef hcan;

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t TxData[8];
static uint8_t RxData[8];
uint32_t TxMailbox;



int datacheck = 0;


void Zilla_CAN_Init() {
	HAL_CAN_Start(&hcan);
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void Zilla_CAN_ActivateNotification() {
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

}

void Zilla_CAN_Transmit(){
	TxHeader.DLC = 2; //Data length
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = 0x446;  //ID of device

	TxData[0] = 100;
	TxData[1] = 10;
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox);

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
	if (RxHeader.DLC == 2){
		datacheck = 1;
	}
}
