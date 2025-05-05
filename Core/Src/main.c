/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7789\st7789.h"
#include "stdbool.h"
#include "jogo.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
static const bool hearts[50][50] = {{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false,false,true,true,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false},
		{false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false},
		{false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
};
static const bool spades[50][50] = {{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false},
		{false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false},
		{false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,true,true,false,false,false,true,true,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,true,false,false,false,false,true,true,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,false,false,true,true,true,true,true,true,true,true,true,true,true,false,true,false,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
};
static const bool clubs[50][50] = {{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,true,true,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false},
		{false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,false,true,true,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,false,true,true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,true,false,false,false,false,true,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,true,false,false,false,false,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,true,true,true,true,false,true,true,true,true,true,false,true,true,true,true,true,true,true,true,false,true,true,true,true,false,false,true,true,true,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
};
static const bool diamonds[50][50] = {
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false},
		{false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false},
		{false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false},
		{false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false},
		{false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false},
		{false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false},
		{false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,true,true,false,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
		{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
};
static const uint16_t fundocarta[][(50*50/2)]  = {
  0x4eeb, 0x14f5, 0x51ec, 0x8eeb, 0x18f6, 0xd7f5, 0x39f6, 0xf8f5, 0x76ed, 0xb3f4, 0x96f5, 0x55ed, 0xf7f5, 0xf0eb, 0x59f6, 0x38f6, 0x8eeb, 0xd7f5, 0x59f6, 0x92ec, 0x14f5, 0x59f6, 0x55f5, 0x92f4, 0x18f6, 0x18f6, 0x92ec, 0x55f5, 0x59f6, 0x34f5, 0x92ec, 0x59f6, 0xd7f5, 0x8eeb, 0x38f6, 0x39f6, 0xd0eb, 0xf7f5, 0x55ed, 0x96f5, 0xb3f4, 0x76ed, 0x18f6, 0x39f6, 0xd7f5, 0x18f6, 0x6eeb, 0x51ec, 0x34f5, 0x4eeb,
  0x4deb, 0x31f4, 0x14f5, 0xf0eb, 0x34ed, 0x18f6, 0x59f6, 0x18f6, 0xb3ec, 0x92ec, 0x76f5, 0x14ed, 0x51ec, 0xb7f5, 0x35f5, 0x92f4, 0x18f6, 0xf4f4, 0xf4f4, 0x55f5, 0x55f5, 0x14f5, 0xd3ec, 0xb6f5, 0xb3f4, 0xb3f4, 0xb6f5, 0xd3ec, 0x14f5, 0x55f5, 0x55f5, 0xf4f4, 0xf4f4, 0x18f6, 0xb2f4, 0x35f5, 0xb7f5, 0x51ec, 0x14ed, 0x76f5, 0xb2ec, 0xb3ec, 0x18f6, 0x59f6, 0x18f6, 0x14ed, 0xd0eb, 0x14f5, 0x31f4, 0x4deb,
  0x4deb, 0x92f4, 0xf0eb, 0x6eeb, 0x55ed, 0x59f6, 0xb6ed, 0x79f6, 0xd3ec, 0x92ec, 0x55f5, 0x35ed, 0x96f5, 0x52ec, 0xf8f5, 0xb7f5, 0x31ec, 0x96f5, 0xf7f5, 0xb3f4, 0x35f5, 0xf7f5, 0x35f5, 0xf3f4, 0x96f5, 0xb6f5, 0xf3f4, 0x35f5, 0xf7f5, 0x35f5, 0xb3f4, 0xf7f5, 0x96f5, 0x31ec, 0xb7f5, 0xf8f5, 0x51ec, 0x96f5, 0x35ed, 0x55f5, 0x92ec, 0xd3ec, 0x79f6, 0xb6f5, 0x59f6, 0x55ed, 0x6eeb, 0xf0eb, 0x92f4, 0x4deb,
  0x4deb, 0xb3f4, 0xcfeb, 0x4eeb, 0x35ed, 0xf8f5, 0x9af6, 0xd7ed, 0xd3ec, 0x72ec, 0x55f5, 0x14ed, 0xdbf6, 0xafeb, 0x7af6, 0x9af6, 0x4eeb, 0x59f6, 0x79f6, 0xb3f4, 0xb6f5, 0x59f6, 0xb6f5, 0xf4f4, 0x39f6, 0x39f6, 0xf4f4, 0xb7f5, 0x59f6, 0xb7f5, 0xb3f4, 0x79f6, 0x59f6, 0x4deb, 0x9af6, 0x79f6, 0xafeb, 0xdbfe, 0x14ed, 0x55f5, 0x72ec, 0xd3ec, 0xd7ed, 0x9af6, 0xf8f5, 0x35ed, 0x4eeb, 0xcfeb, 0xb3f4, 0x4deb,
  0x4deb, 0x72f4, 0x92f4, 0xcfeb, 0x38f6, 0xf7f5, 0x59f6, 0x38f6, 0x76ed, 0xd3f4, 0xb6f5, 0x55ed, 0xcfeb, 0xf7f5, 0x55f5, 0xb3ec, 0x59f6, 0xb3ec, 0x55f5, 0x76f5, 0xf3ec, 0x96f5, 0xf4f4, 0x76f5, 0x34f5, 0x35f5, 0x76f5, 0xf4f4, 0xb6f5, 0xf3ec, 0x76f5, 0x55f5, 0xb3ec, 0x59f6, 0xb3ec, 0x55f5, 0xf7f5, 0xcfeb, 0x55ed, 0x96f5, 0xd3f4, 0x96ed, 0x38f6, 0x59f6, 0xf7f5, 0x38f6, 0xafeb, 0x92ec, 0x72f4, 0x4deb,
  0x4deb, 0x92f4, 0xf3f4, 0xcfeb, 0x35ed, 0x38f6, 0x59f6, 0x18f6, 0xd3ec, 0x92f4, 0x76f5, 0x14ed, 0x14f5, 0xd3ec, 0x96f5, 0x14f5, 0xf3ec, 0x55f5, 0x35f5, 0xd3ec, 0x55f5, 0x34f5, 0xd3f4, 0x35f5, 0xd3f4, 0xd3f4, 0x35f5, 0xb3ec, 0x34f5, 0x55f5, 0xd3ec, 0x35f5, 0x55f5, 0xd3ec, 0x14f5, 0x96f5, 0xd3ec, 0x14f5, 0x14ed, 0x76f5, 0xb2ec, 0xd3ec, 0x38f6, 0x59f6, 0x38f6, 0x35ed, 0xafeb, 0xf4f4, 0x92f4, 0x4deb,
  0x4deb, 0xb3f4, 0xcfeb, 0x6eeb, 0x75ed, 0x59f6, 0x96ed, 0x9af6, 0xf4ec, 0x72ec, 0x35f5, 0x34ed, 0x9af6, 0xf0eb, 0x79f6, 0x9af6, 0x8eeb, 0x38f6, 0x79f6, 0xd3f4, 0x96f5, 0x59f6, 0xb7f5, 0xf3f4, 0x59f6, 0x39f6, 0xf4f4, 0xb7f5, 0x59f6, 0x96f5, 0xd3f4, 0x79f6, 0x38f6, 0x8eeb, 0x7af6, 0x59f6, 0xf0eb, 0x9af6, 0x34ed, 0x35ed, 0x92ec, 0xf4ec, 0x9af6, 0x96ed, 0x59f6, 0x75ed, 0x4eeb, 0xcfeb, 0xb3f4, 0x4deb,
  0x4deb, 0x35f5, 0x10ec, 0x6eeb, 0x14ed, 0x18f6, 0xbaf6, 0xd7f5, 0xb3ec, 0x51ec, 0x34f5, 0x76ed, 0x10ec, 0x96f5, 0x96f5, 0x35f5, 0xd7f5, 0xd3ec, 0xf8f5, 0x76f5, 0xd3ec, 0x59f6, 0x75f5, 0x34f5, 0xd7f5, 0xd7f5, 0x34f5, 0x75f5, 0x59f6, 0xb3ec, 0x75f5, 0xf8f5, 0xd3ec, 0xd7f5, 0x34f5, 0x96f5, 0x96f5, 0x10ec, 0x76ed, 0x14f5, 0x51ec, 0xb3ec, 0xd7f5, 0xbaf6, 0x18f6, 0x14ed, 0x6eeb, 0x10ec, 0x35f5, 0x4deb,
  0x2deb, 0xf0eb, 0x76f5, 0x10ec, 0x38f6, 0xf8f5, 0x59f6, 0x39f6, 0x96ed, 0xd3f4, 0xb6f5, 0x72ec, 0x75f5, 0x14ed, 0x14f5, 0x92f4, 0x35ed, 0x76f5, 0x11ec, 0xf4ec, 0x18f6, 0xcfeb, 0x51ec, 0xf8f5, 0xcfeb, 0xcfeb, 0xf8f5, 0x51ec, 0xcfeb, 0xf8f5, 0xf4ec, 0x31ec, 0x76f5, 0x35ed, 0x92f4, 0x14f5, 0xf4ec, 0x76f5, 0x72ec, 0x96f5, 0xd3f4, 0x96ed, 0x39f6, 0x59f6, 0xf7f5, 0x39f6, 0xf0eb, 0x96f5, 0xf0eb, 0x2deb,
  0x4deb, 0x92f4, 0xf0eb, 0x8eeb, 0x55ed, 0x39f6, 0x59f6, 0x38f6, 0xf4ec, 0xb3f4, 0xb6f5, 0x75ed, 0x76f5, 0x10ec, 0x18f6, 0x18f6, 0xd0eb, 0x76f5, 0x79f6, 0xb3ec, 0xd3f4, 0x9af6, 0x76f5, 0x72ec, 0x59f6, 0x59f6, 0x72f4, 0x76f5, 0x9af6, 0xd3ec, 0xb3f4, 0x79f6, 0x76f5, 0xd0eb, 0x18f6, 0x18f6, 0x10ec, 0x75f5, 0x75ed, 0xb6f5, 0xb3f4, 0xf4ec, 0x38f6, 0x59f6, 0x39f6, 0x55ed, 0x8eeb, 0xf0eb, 0x92f4, 0x4deb,
  0x2deb, 0x72f4, 0xafeb, 0x4eeb, 0x75ed, 0x59f6, 0x96ed, 0x9af6, 0xf4ec, 0x72ec, 0x35f5, 0x55ed, 0x55f5, 0x35f5, 0xd7f5, 0xd7f5, 0x35f5, 0x96f5, 0x38f6, 0x96f5, 0x55f5, 0x79f6, 0xf7f5, 0x75f5, 0x59f6, 0x39f6, 0x55f5, 0xf7f5, 0x79f6, 0x55f5, 0x76f5, 0x38f6, 0x96f5, 0x35f5, 0xd7f5, 0xd7f5, 0x35f5, 0x55f5, 0x35ed, 0x35f5, 0x72ec, 0xf4ec, 0x9af6, 0x96ed, 0x79f6, 0x75ed, 0x4deb, 0xafeb, 0x92f4, 0x2deb,
  0x4deb, 0x51f4, 0x10ec, 0xafeb, 0xf4ec, 0x18f6, 0xbaf6, 0xd7f5, 0x92ec, 0x10ec, 0xd3f4, 0x72ec, 0x35f5, 0xf3ec, 0xf4f4, 0x92f4, 0x14ed, 0x55f5, 0x31ec, 0xf3ec, 0xd7f5, 0xf0eb, 0x72ec, 0xd7f5, 0xf0eb, 0xf0eb, 0xd7f5, 0x72ec, 0xf0eb, 0xd7f5, 0xf3ec, 0x31ec, 0x55f5, 0x14ed, 0x92f4, 0xf4f4, 0xf4ec, 0x55f5, 0x72ec, 0xb3ec, 0x31ec, 0x92ec, 0xd7f5, 0xbaf6, 0x18f6, 0xf4ec, 0xafeb, 0x10ec, 0x51f4, 0x4deb,
  0x2deb, 0xcfeb, 0x55f5, 0x10ec, 0x39f6, 0xf8f5, 0x59f6, 0x39f6, 0x96ed, 0xd3f4, 0xb6f5, 0xd7f5, 0x6eeb, 0x92f4, 0xb6f5, 0x55f5, 0xb3f4, 0x51ec, 0x9af6, 0x92f4, 0x8eeb, 0xfcf6, 0x35f5, 0xcfeb, 0x59f6, 0x59f6, 0xcfeb, 0x34f5, 0xfcf6, 0x8eeb, 0x92f4, 0x7af6, 0x51ec, 0xb2f4, 0x35f5, 0xb7f5, 0xb2f4, 0x8eeb, 0xd7ed, 0x96f5, 0xd3f4, 0x96ed, 0x59f6, 0x59f6, 0xf8f5, 0x39f6, 0xf0eb, 0x55f5, 0xcfeb, 0x2deb,
  0x4deb, 0x55f5, 0xf0eb, 0x4eeb, 0x96ed, 0x38f6, 0x59f6, 0x38f6, 0x14ed, 0xb3f4, 0xb6f5, 0xf3ec, 0xdbfe, 0x14f5, 0x38f6, 0x79f6, 0xf3f4, 0x7af6, 0x38f6, 0xd7f5, 0x79f6, 0x38f6, 0x59f6, 0x18f6, 0x79f6, 0x79f6, 0x18f6, 0x59f6, 0x38f6, 0x59f6, 0xd7f5, 0x38f6, 0x7af6, 0xf3f4, 0x79f6, 0x18f6, 0x14f5, 0xdbfe, 0xf4ec, 0xb6f5, 0xb3f4, 0x14ed, 0x38f6, 0x59f6, 0x38f6, 0x96ed, 0x4deb, 0xf0eb, 0x55f5, 0x4deb,
  0x4deb, 0xd3f4, 0xcfeb, 0x6eeb, 0x55ed, 0x59f6, 0x96ed, 0x9af6, 0xd3ec, 0x92ec, 0x76f5, 0xf4ec, 0x92ec, 0xd3ec, 0x55f5, 0xd3f4, 0xf4ec, 0xf4f4, 0x14f5, 0xd3ec, 0xf4ec, 0x34f5, 0xb3f4, 0x14f5, 0xd3f4, 0xd3f4, 0x14f5, 0xb3f4, 0x34f5, 0xf4f4, 0xd3ec, 0x14f5, 0xf4f4, 0xf4ec, 0xd3f4, 0x35f5, 0xd3ec, 0x92ec, 0xf4ec, 0x75f5, 0x92f4, 0xd3ec, 0x9af6, 0x96ed, 0x59f6, 0x55ed, 0x6eeb, 0xcfeb, 0xd3f4, 0x4deb,
  0x4deb, 0x92f4, 0x55f5, 0xcfeb, 0xf4ec, 0x18f6, 0x9af6, 0xf7f5, 0x92ec, 0x51ec, 0x14f5, 0x35ed, 0xf0eb, 0x35f5, 0x55f5, 0xd3f4, 0x75f5, 0xb3ec, 0x96f5, 0xf4f4, 0x92ec, 0xd7f5, 0xf4f4, 0xf3ec, 0x55f5, 0x55f5, 0xf3ec, 0xf4f4, 0xd7f5, 0x92ec, 0xf4f4, 0x96f5, 0xb3ec, 0x75f5, 0xd3f4, 0x55f5, 0x35ed, 0x10ec, 0x35ed, 0x14f5, 0x51ec, 0x92ec, 0xd7f5, 0x9af6, 0x18f6, 0xf4ec, 0xcfeb, 0x55f5, 0x92f4, 0x4deb,
  0x4eeb, 0xd3f4, 0x51ec, 0xafeb, 0x18f6, 0xf7f5, 0x59f6, 0x18f6, 0x76ed, 0xb3f4, 0x76f5, 0xd3ec, 0x9eff, 0xd3f4, 0x59f6, 0xbbf6, 0x72ec, 0xfbf6, 0x38f6, 0xb7f5, 0xdbfe, 0x18f6, 0x79f6, 0x38f6, 0x59f6, 0x59f6, 0x38f6, 0x79f6, 0x18f6, 0xdbf6, 0xb7f5, 0x38f6, 0xfbf6, 0x72ec, 0xbbf6, 0x59f6, 0xd3f4, 0x9eff, 0xd3ec, 0x75f5, 0xb3f4, 0x76ed, 0x18f6, 0x39f6, 0xf7f5, 0x18f6, 0xafeb, 0x51ec, 0xd3f4, 0x6eeb,
  0x2deb, 0x92f4, 0xafeb, 0x4eeb, 0x96ed, 0x18f6, 0x59f6, 0x18f6, 0x35ed, 0x92f4, 0x76f5, 0x75ed, 0x92ec, 0x51ec, 0xb7f5, 0x76f5, 0x31ec, 0xf4f4, 0x18f6, 0x72ec, 0x52ec, 0x39f6, 0x14f5, 0x51ec, 0xb7f5, 0xb7f5, 0x51ec, 0xf4f4, 0x39f6, 0x72ec, 0x92ec, 0x18f6, 0xf4f4, 0x31ec, 0x76f5, 0xb7f5, 0x51ec, 0x92ec, 0x55ed, 0x75f5, 0x92f4, 0x35ed, 0x18f6, 0x59f6, 0x18f6, 0x96ed, 0x4eeb, 0xafeb, 0x92f4, 0x2deb,
  0x4deb, 0x92f4, 0xf0eb, 0x8eeb, 0x55ed, 0x59f6, 0xd7f5, 0x79f6, 0xd3ec, 0xb3f4, 0x96f5, 0xf4ec, 0x92ec, 0x55f5, 0x35f5, 0xb3f4, 0xb6f5, 0x14f5, 0xd3f4, 0x14f5, 0x55f5, 0xd3f4, 0xb3ec, 0x96f5, 0x92f4, 0x92f4, 0x96f5, 0xb3ec, 0xd3f4, 0x55f5, 0x34ed, 0xd3f4, 0x14f5, 0xb6f5, 0xb3f4, 0x34f5, 0x55f5, 0x92ec, 0xf4ec, 0x96f5, 0xb3f4, 0xd3ec, 0x79f6, 0xd7f5, 0x59f6, 0x55ed, 0x6eeb, 0xf0eb, 0x92f4, 0x4deb,
  0x4deb, 0xf0eb, 0xf4f4, 0xf0eb, 0xf4ec, 0x18f6, 0x59f6, 0xf8f5, 0x92ec, 0x72ec, 0x55f5, 0x14ed, 0x18f6, 0xb3f4, 0x18f6, 0x38f6, 0x92ec, 0x18f6, 0x38f6, 0x55f5, 0xb7f5, 0x38f6, 0xd7f5, 0x75f5, 0x38f6, 0x18f6, 0x76f5, 0xd7f5, 0x38f6, 0xb7f5, 0x55f5, 0x38f6, 0x18f6, 0x92ec, 0x18f6, 0x18f6, 0xb3f4, 0x18f6, 0x14ed, 0x55f5, 0x92f4, 0x92ec, 0xf8f5, 0x59f6, 0x18f6, 0xf4ec, 0xf0eb, 0xf4f4, 0xf0eb, 0x4deb,
  0x4deb, 0x35f5, 0x31ec, 0x6eeb, 0xf8f5, 0xf7f5, 0x39f6, 0xf8f5, 0x75ed, 0x92ec, 0x75f5, 0x75ed, 0x96f5, 0xafeb, 0x59f6, 0x18f6, 0x4eeb, 0x76f5, 0x9af6, 0x51ec, 0xb2ec, 0xbaf6, 0x55f5, 0x31ec, 0x39f6, 0x39f6, 0x31ec, 0x55f5, 0xbaf6, 0x92ec, 0x51ec, 0x9af6, 0x96f5, 0x4eeb, 0x38f6, 0x39f6, 0xafeb, 0x96f5, 0x75ed, 0x55f5, 0xb2ec, 0x75ed, 0x18f6, 0x39f6, 0xd7f5, 0xf8f5, 0x6eeb, 0x31ec, 0x35f5, 0x4deb,
  0x2deb, 0x51f4, 0xafeb, 0x6eeb, 0xb7f5, 0xf8f5, 0x39f6, 0xf8f5, 0x35ed, 0x92f4, 0x76f5, 0xf3ec, 0xb3ec, 0x76ed, 0x34f5, 0x92f4, 0xd7f5, 0x34f5, 0xb2f4, 0x35f5, 0x96f5, 0x92f4, 0xb2ec, 0xd7f5, 0x51f4, 0x71f4, 0xd7f5, 0xb3ec, 0x92f4, 0x96f5, 0x35f5, 0xb3f4, 0x34f5, 0xd7f5, 0x92f4, 0x34f5, 0x76f5, 0xb3ec, 0xd3ec, 0x75f5, 0xb2ec, 0x55ed, 0xf8f5, 0x39f6, 0xf8f5, 0xb7f5, 0x6eeb, 0x8feb, 0x51f4, 0x2deb,
  0x4deb, 0xd3f4, 0x92f4, 0xafeb, 0x35ed, 0x38f6, 0xf7f5, 0x39f6, 0xb3ec, 0x92ec, 0x76f5, 0x55ed, 0x14f5, 0x14f5, 0xd7f5, 0x76f5, 0x14f5, 0x55f5, 0xd7f5, 0x34f5, 0x35f5, 0xf7f5, 0x55f5, 0x35f5, 0xb6f5, 0xb6f5, 0x35f5, 0x55f5, 0xf8f5, 0x35f5, 0x34f5, 0xd7f5, 0x55f5, 0x14f5, 0x76f5, 0xd7f5, 0x14f5, 0x14f5, 0x35ed, 0x75f5, 0x92ec, 0xb3ec, 0x39f6, 0xf8f5, 0x38f6, 0x34ed, 0x8feb, 0x92f4, 0xd3f4, 0x4deb,
  0x4deb, 0x72f4, 0xb3f4, 0xcfeb, 0x14ed, 0x18f6, 0x38f6, 0x18f6, 0x92ec, 0x72ec, 0x55f5, 0x35ed, 0x9af6, 0xafeb, 0x79f6, 0x7af6, 0x2deb, 0x18f6, 0x79f6, 0x92ec, 0x55f5, 0x79f6, 0x96f5, 0xb3f4, 0x39f6, 0x39f6, 0xb2f4, 0x96f5, 0x79f6, 0x55f5, 0x92f4, 0x79f6, 0x38f6, 0x2deb, 0x7af6, 0x79f6, 0xafeb, 0x7af6, 0x35ed, 0x55f5, 0x92f4, 0xb2ec, 0x18f6, 0x38f6, 0x38f6, 0x14ed, 0xcfeb, 0xd3f4, 0x72f4, 0x4deb,
  0x4deb, 0xb2f4, 0xcfeb, 0x6eeb, 0xd7f5, 0xf7f5, 0x39f6, 0xf8f5, 0x55ed, 0x92f4, 0x76f5, 0x34ed, 0x92ec, 0x76f5, 0x75f5, 0xd3f4, 0xb7f5, 0x14f5, 0x35f5, 0x35f5, 0x35f5, 0x35f5, 0xf3f4, 0x96f5, 0xf4f4, 0xf4f4, 0x96f5, 0xf3ec, 0x55f5, 0x35f5, 0x35f5, 0x35f5, 0x14f5, 0xb7f5, 0xd3f4, 0x55f5, 0x76f5, 0x92ec, 0x34ed, 0x76f5, 0xb3f4, 0x55ed, 0xf8f5, 0x39f6, 0xf7f5, 0xd7f5, 0x6eeb, 0xcfeb, 0xb3f4, 0x4deb,
  0x4deb, 0x92f4, 0xcfeb, 0x6eeb, 0xd7f5, 0xf7f5, 0x39f6, 0xf8f5, 0x55ed, 0x92ec, 0x76f5, 0x14ed, 0x92ec, 0x76f5, 0x55f5, 0xd3f4, 0xb7f5, 0x14f5, 0x34f5, 0x35f5, 0x35f5, 0x35f5, 0xf3f4, 0x96f5, 0xf3f4, 0xf3f4, 0x96f5, 0xd3f4, 0x35f5, 0x35f5, 0x35f5, 0x35f5, 0x14f5, 0xb7f5, 0xd3f4, 0x55f5, 0x76f5, 0x92ec, 0x14ed, 0x76f5, 0xb3f4, 0x55ed, 0xf8f5, 0x39f6, 0xf7f5, 0xd7f5, 0x6eeb, 0xcfeb, 0xb2f4, 0x4deb,
  0x4deb, 0x72f4, 0xb3f4, 0xcfeb, 0x14ed, 0x18f6, 0x38f6, 0x18f6, 0x92ec, 0x92ec, 0x55f5, 0x35ed, 0x7af6, 0xafeb, 0x79f6, 0x7af6, 0x4deb, 0x18f6, 0x79f6, 0x92ec, 0x55f5, 0x79f6, 0x96f5, 0xb3f4, 0x39f6, 0x39f6, 0xb3f4, 0x96f5, 0x79f6, 0x55f5, 0x92ec, 0x79f6, 0x18f6, 0x2deb, 0x7af6, 0x79f6, 0xafeb, 0x7af6, 0x35ed, 0x55f5, 0x92ec, 0x92ec, 0x18f6, 0x38f6, 0x18f6, 0x14ed, 0xcfeb, 0xd3f4, 0x72f4, 0x4deb,
  0x4deb, 0xd3f4, 0x92f4, 0xafeb, 0x34ed, 0x38f6, 0xf7f5, 0x59f6, 0xb3ec, 0x92ec, 0x55f5, 0x55ed, 0x14f5, 0x14f5, 0xd7f5, 0x76f5, 0x14f5, 0x55f5, 0xd7f5, 0x34f5, 0x35f5, 0xf8f5, 0x55f5, 0x35f5, 0xb6f5, 0xb7f5, 0x35f5, 0x55f5, 0xf8f5, 0x35f5, 0x34f5, 0xd7f5, 0x55f5, 0x14f5, 0x76f5, 0xd7f5, 0x14f5, 0x14f5, 0x55ed, 0x55f5, 0x92f4, 0xb3ec, 0x39f6, 0xf8f5, 0x38f6, 0x35ed, 0x8feb, 0xb2f4, 0xd3f4, 0x4deb,
  0x2deb, 0x51f4, 0x8feb, 0x6eeb, 0xb7f5, 0xf8f5, 0x39f6, 0xf8f5, 0x55ed, 0x92ec, 0x76f5, 0xd3ec, 0xb3ec, 0x76f5, 0x34f5, 0x92f4, 0xb7f5, 0x34f5, 0x92f4, 0x35f5, 0x96f5, 0x92ec, 0xb2ec, 0xd7f5, 0x51ec, 0x51f4, 0xd7f5, 0xb3ec, 0x92f4, 0x96f5, 0x35ed, 0xb2f4, 0x34f5, 0xd7f5, 0x92f4, 0x34f5, 0x76f5, 0xb3ec, 0xd3ec, 0x75f5, 0xb2f4, 0x55ed, 0xf8f5, 0x39f6, 0xf8f5, 0xb7f5, 0x6eeb, 0x8feb, 0x51f4, 0x2deb,
  0x4deb, 0x35f5, 0x31ec, 0x6eeb, 0xf8f5, 0xf7f5, 0x39f6, 0xf8f5, 0x75ed, 0x92ec, 0x75f5, 0x76ed, 0x96f5, 0xafeb, 0x39f6, 0x18f6, 0x6eeb, 0x76f5, 0x9af6, 0x51ec, 0xb2ec, 0xbaf6, 0x55f5, 0x31ec, 0x38f6, 0x39f6, 0x31ec, 0x55f5, 0xbaf6, 0x92ec, 0x51ec, 0x9af6, 0x96f5, 0x6eeb, 0x18f6, 0x39f6, 0xafeb, 0x76f5, 0x76ed, 0x55f5, 0x92ec, 0x75ed, 0x18f6, 0x39f6, 0xd7f5, 0xf8f5, 0x6eeb, 0x31ec, 0x35f5, 0x4deb,
  0x4deb, 0xf0eb, 0xf4f4, 0xf0eb, 0x14ed, 0x18f6, 0x59f6, 0x18f6, 0x92ec, 0x92ec, 0x75f5, 0x14ed, 0x38f6, 0xb3f4, 0x18f6, 0x38f6, 0x92ec, 0x18f6, 0x38f6, 0x55f5, 0xb7f5, 0x38f6, 0xd7f5, 0x76f5, 0x18f6, 0x18f6, 0x75f5, 0xd7f5, 0x38f6, 0xd7f5, 0x55f5, 0x38f6, 0x18f6, 0x92ec, 0x38f6, 0x18f6, 0xb3f4, 0x38f6, 0x14ed, 0x55f5, 0x92f4, 0x92ec, 0xf8f5, 0x59f6, 0x18f6, 0xf4ec, 0xf0eb, 0xf4f4, 0xf0eb, 0x4deb,
  0x4deb, 0x92f4, 0x10ec, 0x8eeb, 0x55ed, 0x59f6, 0xd7ed, 0x79f6, 0xd3ec, 0xb3f4, 0x96f5, 0xf3ec, 0x92ec, 0x55f5, 0x34f5, 0xb3f4, 0x96f5, 0x14f5, 0xd3f4, 0x14ed, 0x55f5, 0xd3f4, 0xb3f4, 0x96f5, 0x92f4, 0x92f4, 0x96f5, 0xb3f4, 0xd3f4, 0x55f5, 0x34f5, 0xd3f4, 0x14f5, 0x96f5, 0xb3f4, 0x34f5, 0x55f5, 0x92ec, 0xf3ec, 0x96f5, 0xb3f4, 0xd3ec, 0x79f6, 0xd7f5, 0x59f6, 0x55ed, 0x6eeb, 0xf0eb, 0x92f4, 0x4deb,
  0x2deb, 0x92f4, 0xafeb, 0x6eeb, 0x96ed, 0x18f6, 0x59f6, 0x18f6, 0x35ed, 0x92ec, 0x75f5, 0x75ed, 0x92ec, 0x51ec, 0xb7f5, 0x76f5, 0x51ec, 0xf4f4, 0x18f6, 0x92ec, 0x71ec, 0x39f6, 0x14f5, 0x51ec, 0xb7f5, 0xb7f5, 0x51ec, 0x14f5, 0x39f6, 0x72ec, 0x92ec, 0x18f6, 0xf4f4, 0x51ec, 0x75f5, 0xb7f5, 0x51ec, 0x92ec, 0x75ed, 0x75f5, 0x92f4, 0x35ed, 0x18f6, 0x59f6, 0x18f6, 0x96ed, 0x4eeb, 0xafeb, 0x92f4, 0x2deb,
  0x6eeb, 0xd3f4, 0x51ec, 0xafeb, 0x38f6, 0xf7f5, 0x59f6, 0x18f6, 0x76ed, 0xb2ec, 0x76f5, 0xd3ec, 0x9eff, 0xd3f4, 0x59f6, 0xbbf6, 0x72ec, 0xfbf6, 0x39f6, 0xb7f5, 0xdbf6, 0xf8f5, 0x79f6, 0x38f6, 0x59f6, 0x59f6, 0x38f6, 0x79f6, 0x18f6, 0xdbfe, 0xb7f5, 0x39f6, 0xfbf6, 0x72ec, 0xdbf6, 0x59f6, 0xd3ec, 0x9eff, 0xd3ec, 0x75f5, 0xb3f4, 0x76ed, 0x18f6, 0x39f6, 0xf7f5, 0x18f6, 0xafeb, 0x51ec, 0xd3f4, 0x6eeb,
  0x4deb, 0x92f4, 0x55f5, 0xcfeb, 0xf4ec, 0x18f6, 0x9af6, 0xf7f5, 0x92ec, 0x72ec, 0x35f5, 0x35ed, 0x10ec, 0x34f5, 0x55f5, 0xd3f4, 0x55f5, 0xb3ec, 0x96f5, 0xf4f4, 0x92ec, 0xb7f5, 0xf4f4, 0xd3ec, 0x55f5, 0x55f5, 0xd3ec, 0xf4f4, 0xd7f5, 0x92ec, 0xf4f4, 0x96f5, 0xb3ec, 0x55f5, 0xf3f4, 0x55f5, 0x34ed, 0x10ec, 0x35ed, 0x35f5, 0x72ec, 0x92ec, 0xf7f5, 0x9af6, 0x18f6, 0xf4ec, 0xcfeb, 0x55f5, 0x92f4, 0x4deb,
  0x4deb, 0xd3f4, 0xcfeb, 0x6eeb, 0x55ed, 0x59f6, 0x96ed, 0x9af6, 0xd3ec, 0xb2f4, 0x96f5, 0xf4ec, 0x92ec, 0xd3ec, 0x55f5, 0xd3f4, 0xf4ec, 0xf4f4, 0x14f5, 0xd3ec, 0xf4f4, 0x34f5, 0xb3ec, 0x14f5, 0xd3f4, 0xd3f4, 0x14f5, 0xb3f4, 0x34f5, 0xf4f4, 0xd3ec, 0x14f5, 0xf4f4, 0xf4ec, 0xd3f4, 0x35f5, 0xd3ec, 0x92ec, 0xf4ec, 0x96f5, 0xb3f4, 0xf3ec, 0x9af6, 0xb6ed, 0x59f6, 0x55ed, 0x6eeb, 0xcfeb, 0xd3f4, 0x4deb,
  0x4deb, 0x55f5, 0xf0eb, 0x4eeb, 0x76ed, 0x39f6, 0x59f6, 0x38f6, 0x14ed, 0xb3f4, 0x96f5, 0xf4ec, 0xdbfe, 0x14f5, 0x18f6, 0x79f6, 0xf3f4, 0x7af6, 0x38f6, 0xd7f5, 0x79f6, 0x38f6, 0x59f6, 0x18f6, 0x79f6, 0x79f6, 0x18f6, 0x59f6, 0x38f6, 0x79f6, 0xd7f5, 0x38f6, 0x7af6, 0xd3ec, 0x79f6, 0x38f6, 0x14f5, 0xdbf6, 0xf3ec, 0x96f5, 0xb3f4, 0x14ed, 0x38f6, 0x59f6, 0x38f6, 0x96ed, 0x4eeb, 0xf0eb, 0x35f5, 0x4deb,
  0x2deb, 0xafeb, 0x55f5, 0x10ec, 0x39f6, 0xf8f5, 0x59f6, 0x59f6, 0x96ed, 0xd3f4, 0x96f5, 0xd7f5, 0x8eeb, 0x92f4, 0xb7f5, 0x55f5, 0x92f4, 0x51ec, 0x9af6, 0x92ec, 0x8eeb, 0xfbf6, 0x35f5, 0xafeb, 0x59f6, 0x59f6, 0xcfeb, 0x34f5, 0x1cf7, 0x8eeb, 0x92ec, 0x7af6, 0x51ec, 0x92f4, 0x55f5, 0xb7f5, 0x92f4, 0x8eeb, 0xd7f5, 0x96f5, 0xd3f4, 0x96ed, 0x59f6, 0x59f6, 0xf8f5, 0x39f6, 0xf0eb, 0x55f5, 0xafeb, 0x2deb,
  0x4deb, 0x51f4, 0x10ec, 0xafeb, 0xf4ec, 0x18f6, 0xbaf6, 0xd7f5, 0x92ec, 0x11ec, 0xd3ec, 0x72ec, 0x35f5, 0xf4ec, 0xf4f4, 0x92f4, 0x14ed, 0x55f5, 0x31ec, 0xf3ec, 0xd7f5, 0xf0eb, 0x72ec, 0xd7f5, 0xf0eb, 0xf0eb, 0xd7f5, 0x72ec, 0xf0eb, 0xd7f5, 0xf3ec, 0x31ec, 0x55f5, 0x14ed, 0x92f4, 0xf4f4, 0xf4ec, 0x35f5, 0x72ec, 0xd3ec, 0x31ec, 0x92ec, 0xd7f5, 0xbaf6, 0x18f6, 0xf4ec, 0xafeb, 0x10ec, 0x51ec, 0x4deb,
  0x2deb, 0x92f4, 0xafeb, 0x4eeb, 0x75ed, 0x79f6, 0x96ed, 0x9af6, 0xf4ec, 0x72ec, 0x55f5, 0x35ed, 0x55f5, 0x35f5, 0xd7f5, 0xd7f5, 0x35f5, 0x96f5, 0x38f6, 0x96f5, 0x55f5, 0x79f6, 0xf7f5, 0x75f5, 0x59f6, 0x59f6, 0x55f5, 0xd7f5, 0x79f6, 0x55f5, 0x96f5, 0x38f6, 0x96f5, 0x35f5, 0xd7f5, 0xf7f5, 0x35f5, 0x55f5, 0x55ed, 0x55f5, 0x92ec, 0xf4ec, 0x9af6, 0x96ed, 0x79f6, 0x76ed, 0x4deb, 0xafeb, 0x72f4, 0x2deb,
  0x4deb, 0x92f4, 0xf0eb, 0x8eeb, 0x55ed, 0x39f6, 0x59f6, 0x38f6, 0xf4ec, 0xb3f4, 0xb7f5, 0x75ed, 0x76f5, 0x10ec, 0x38f6, 0x18f6, 0xcfeb, 0x76f5, 0x79f6, 0xb2f4, 0xd3f4, 0x9af6, 0x76f5, 0x72ec, 0x59f6, 0x59f6, 0x72ec, 0x76f5, 0x9af6, 0xd3f4, 0xb2f4, 0x79f6, 0x96f5, 0xcfeb, 0x18f6, 0x38f6, 0x10ec, 0x76f5, 0x75ed, 0xb6f5, 0xb3f4, 0xf4ec, 0x38f6, 0x59f6, 0x39f6, 0x75ed, 0x8eeb, 0xf0eb, 0x92f4, 0x4deb,
  0x2deb, 0xf0eb, 0x96f5, 0x10ec, 0x38f6, 0xf8f5, 0x59f6, 0x39f6, 0x96ed, 0xd3f4, 0xb6f5, 0x72ec, 0x55f5, 0x14ed, 0x14f5, 0x92f4, 0x35ed, 0x76f5, 0x31ec, 0xf4ec, 0x18f6, 0xcfeb, 0x51ec, 0xf8f5, 0xcfeb, 0xcfeb, 0xf8f5, 0x51ec, 0xd0eb, 0xf8f5, 0xf4ec, 0x31ec, 0x76f5, 0x35ed, 0x92f4, 0x14f5, 0x14ed, 0x75f5, 0x72ec, 0x96f5, 0xd3f4, 0x96ed, 0x39f6, 0x59f6, 0xf8f5, 0x39f6, 0xf0eb, 0x96f5, 0xf0eb, 0x2deb,
  0x4deb, 0x35f5, 0x10ec, 0x6eeb, 0x14ed, 0x18f6, 0xbaf6, 0xd7f5, 0xb3ec, 0x51ec, 0x14f5, 0x76ed, 0x11ec, 0x96f5, 0x96f5, 0x34f5, 0xd7f5, 0xd3ec, 0xf7f5, 0x76f5, 0xd3ec, 0x59f6, 0x76f5, 0x35f5, 0xd7f5, 0xd7f5, 0x35f5, 0x75f5, 0x59f6, 0xb3ec, 0x75f5, 0xf7f5, 0xd3ec, 0xd7f5, 0x34f5, 0x96f5, 0x96f5, 0x30ec, 0x75ed, 0x14f5, 0x51ec, 0xb3ec, 0xd7ed, 0xbaf6, 0x18f6, 0x14ed, 0x6eeb, 0x10ec, 0x35f5, 0x4deb,
  0x4deb, 0xb3f4, 0xcfeb, 0x6eeb, 0x75ed, 0x59f6, 0x96ed, 0x9af6, 0xf4ec, 0x72ec, 0x35f5, 0x34ed, 0x9af6, 0xd0eb, 0x79f6, 0x9af6, 0x8eeb, 0x38f6, 0x79f6, 0xb3f4, 0x96f5, 0x59f6, 0xb7f5, 0xf3f4, 0x39f6, 0x39f6, 0xf3f4, 0xb7f5, 0x59f6, 0x96f5, 0xb3f4, 0x79f6, 0x38f6, 0x6eeb, 0x7af6, 0x79f6, 0xf0eb, 0x9af6, 0x34ed, 0x35f5, 0x72f4, 0xf4ec, 0x9af6, 0x96ed, 0x59f6, 0x75ed, 0x4eeb, 0xcfeb, 0xb3f4, 0x4deb,
  0x4deb, 0x92f4, 0xf3f4, 0xcfeb, 0x35ed, 0x38f6, 0x59f6, 0x38f6, 0xd3ec, 0x92f4, 0x96f5, 0x14ed, 0x14f5, 0xd3ec, 0x96f5, 0x14f5, 0xf3ec, 0x55f5, 0x35f5, 0xd3ec, 0x55f5, 0x34f5, 0xd3ec, 0x35f5, 0xd3f4, 0xf3f4, 0x35f5, 0xd3ec, 0x35f5, 0x55f5, 0xd3ec, 0x35f5, 0x55f5, 0xd3ec, 0x14f5, 0x96f5, 0xd3ec, 0x14f5, 0x14ed, 0x76f5, 0xb3f4, 0xd3ec, 0x38f6, 0x59f6, 0x38f6, 0x35ed, 0xafeb, 0xf4f4, 0x92f4, 0x4deb,
  0x4deb, 0x72f4, 0x92ec, 0xcfeb, 0x38f6, 0xf7f5, 0x59f6, 0x38f6, 0x76ed, 0xd3f4, 0xb6f5, 0x55ed, 0xcfeb, 0xf7f5, 0x55f5, 0xb3ec, 0x59f6, 0xd3ec, 0x55f5, 0x76f5, 0xf4ec, 0x96f5, 0xf4f4, 0x76f5, 0x34f5, 0x34f5, 0x76f5, 0xf4f4, 0x96f5, 0xf4ec, 0x76f5, 0x55f5, 0xb3f4, 0x59f6, 0xb3ec, 0x55f5, 0xf7f5, 0xcfeb, 0x55ed, 0x96f5, 0xd3f4, 0x96ed, 0x38f6, 0x59f6, 0xf7f5, 0x38f6, 0xcfeb, 0x92f4, 0x72f4, 0x4deb,
  0x4deb, 0xb3f4, 0xcfeb, 0x4eeb, 0x35ed, 0xf8f5, 0x9af6, 0xd7ed, 0xd3ec, 0x72ec, 0x55f5, 0x14ed, 0xdbf6, 0xafeb, 0x7af6, 0x9af6, 0x4eeb, 0x59f6, 0x79f6, 0xb3f4, 0xb6f5, 0x59f6, 0xb6f5, 0xf3f4, 0x39f6, 0x39f6, 0xf4f4, 0xb6f5, 0x59f6, 0xb6f5, 0xb3f4, 0x79f6, 0x59f6, 0x4deb, 0x9af6, 0x7af6, 0xafeb, 0xdbf6, 0x14ed, 0x35f5, 0x72ec, 0xd3ec, 0xd7ed, 0x9af6, 0xf8f5, 0x35ed, 0x4eeb, 0xcfeb, 0xb3f4, 0x4deb,
  0x4deb, 0x92f4, 0xf0eb, 0x6eeb, 0x55ed, 0x59f6, 0xb6ed, 0x79f6, 0xd3ec, 0x92f4, 0x55f5, 0x35ed, 0x96f5, 0x72ec, 0xf8f5, 0xd7f5, 0x51ec, 0x96f5, 0xf7f5, 0xb3f4, 0x35f5, 0xf7f5, 0x35f5, 0xf3f4, 0xb6f5, 0xb6f5, 0xf3f4, 0x35f5, 0xf7f5, 0x35f5, 0xb3f4, 0xf7f5, 0x96f5, 0x31ec, 0xd7f5, 0xf8f5, 0x71ec, 0x96f5, 0x35ed, 0x55f5, 0x92f4, 0xd3ec, 0x7af6, 0xb6ed, 0x59f6, 0x55ed, 0x6eeb, 0xd0eb, 0x92f4, 0x4deb,
  0x4deb, 0x31f4, 0x14f5, 0xf0eb, 0x34ed, 0x18f6, 0x59f6, 0x18f6, 0xb3ec, 0x92f4, 0x76f5, 0x14ed, 0x51ec, 0xb7f5, 0x35f5, 0x92f4, 0x18f6, 0xf4f4, 0xf4f4, 0x55f5, 0x55f5, 0x14f5, 0xd3ec, 0xb6f5, 0xb3ec, 0xb3f4, 0xb7f5, 0xd3ec, 0x14f5, 0x55f5, 0x55f5, 0xf4f4, 0xf4f4, 0x18f6, 0x92ec, 0x35f5, 0xb7f5, 0x51ec, 0x14ed, 0x76f5, 0xb3f4, 0xb3ec, 0x18f6, 0x59f6, 0x18f6, 0x34ed, 0xd0eb, 0x14f5, 0x31f4, 0x4deb,
  0x4eeb, 0x14f5, 0x31ec, 0x8eeb, 0x18f6, 0xf7f5, 0x59f6, 0x18f6, 0x76ed, 0xb3f4, 0x96f5, 0x55ed, 0xf7f5, 0xf0eb, 0x39f6, 0x38f6, 0x8eeb, 0xd7f5, 0x59f6, 0x92ec, 0x14f5, 0x59f6, 0x55f5, 0x92ec, 0x18f6, 0x18f6, 0x92f4, 0x55f5, 0x59f6, 0x14f5, 0x92ec, 0x59f6, 0xd7f5, 0x8eeb, 0x38f6, 0x39f6, 0xefeb, 0xd7f5, 0x55ed, 0x96f5, 0xd3f4, 0x76ed, 0x18f6, 0x39f6, 0xd7f5, 0x18f6, 0x6eeb, 0x51ec, 0x14f5, 0x4eeb
};
static const int16_t minion1[]  = {
	0xc118, 0xe220, 0xe230, 0x0231, 0x0231, 0xe230, 0x0231, 0xe130, 0xe228, 0xc218, 0xc218, 0xe210, 0xe210, 0xe210, 0xe210, 0xc118, 0xc118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa110, 0xa118, 0x8118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0xa118, 0x8110, 0xe218, 0xc218, 0xa110, 0x8110, 0x6010, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 
	0xc118, 0x8118, 0x0229, 0x4339, 0x4341, 0x2239, 0x4339, 0x4339, 0x2231, 0xe220, 0xe218, 0xe218, 0x0219, 0x0219, 0x0219, 0x0219, 0x0219, 0x0219, 0xe218, 0xe218, 0xc218, 0xe218, 0xc218, 0xc218, 0xc110, 0x8110, 0x8110, 0x8110, 0x8110, 0x8110, 0xa118, 0xc118, 0xc218, 0xe218, 0xc218, 0xc118, 0xc118, 0xc118, 0xc218, 0x0221, 0xe218, 0xc118, 0xa110, 0x8110, 0x6008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 
	0x8110, 0xa118, 0xa120, 0xa120, 0xc120, 0xc128, 0xc128, 0xc128, 0xa120, 0x6010, 0x6010, 0x8110, 0x8110, 0xa118, 0xa110, 0xa110, 0xa118, 0xa118, 0x8110, 0x6010, 0x8110, 0x8118, 0x8118, 0x8118, 0x6010, 0x6010, 0x8010, 0x6010, 0x6010, 0x6010, 0x8118, 0xa120, 0xa120, 0x8118, 0x8110, 0x8110, 0x8110, 0x8110, 0x8110, 0xa110, 0x6010, 0x8118, 0xa118, 0x8118, 0xa118, 0x8118, 0x6010, 0x6010, 0x8118, 0xa118, 0xa118, 0x6010, 0x4008, 0x4008, 0x8110, 0xa210, 0x6110, 0x8118, 0xa120, 0xa120, 
	0x8118, 0xa120, 0xc128, 0xe130, 0xe130, 0x0139, 0x2241, 0x4241, 0xe130, 0x8018, 0x6010, 0x6010, 0x6010, 0x8118, 0xa118, 0xa120, 0xa118, 0x8118, 0xa118, 0xa120, 0xc128, 0xc128, 0xc120, 0xa120, 0xa120, 0xa120, 0x8118, 0x8110, 0x8118, 0xc128, 0xe130, 0xe130, 0xe130, 0xe130, 0xc128, 0xa120, 0x8118, 0x8118, 0xa118, 0x8118, 0x8110, 0x8118, 0x8118, 0x6010, 0x6010, 0x6010, 0x8118, 0xc120, 0xc128, 0xa120, 0x8118, 0x6010, 0x6010, 0x6010, 0x8110, 0x8110, 0x8118, 0x8118, 0xe128, 0x2239, 
	0x4010, 0xa120, 0xc128, 0xe130, 0x0239, 0x2241, 0x4249, 0x4249, 0x0239, 0x8118, 0x4010, 0x8118, 0xe128, 0x0229, 0x8441, 0x465a, 0xe551, 0x6341, 0xe230, 0x8118, 0x8118, 0x0231, 0x2231, 0xc120, 0xa120, 0xc120, 0xc120, 0x8118, 0x8118, 0xc128, 0xc128, 0xc128, 0xe130, 0x0139, 0x2239, 0x0239, 0xe128, 0xc128, 0xe128, 0xe128, 0xc128, 0xc128, 0xa120, 0x8118, 0xc120, 0x8249, 0x436a, 0x6372, 0x627a, 0x4272, 0xc259, 0x2239, 0xc128, 0xc128, 0xc128, 0xc120, 0xc120, 0xe130, 0x6249, 0x6251, 
	0xa120, 0xa120, 0xc128, 0xe130, 0x2239, 0x0231, 0x0239, 0x2239, 0x6249, 0x236a, 0x0393, 0x64a3, 0xc38a, 0xe682, 0x10bd, 0x8cb4, 0x4793, 0x446a, 0xc351, 0x2239, 0xc120, 0xc128, 0xa120, 0xa120, 0xa120, 0xa120, 0x8118, 0x8010, 0xa118, 0x2139, 0x0262, 0xc38a, 0x449b, 0xc6ab, 0xe9ab, 0x6793, 0xc582, 0x666a, 0x097b, 0x4662, 0x2239, 0xa120, 0xa120, 0x2139, 0x4272, 0x2272, 0x2272, 0x2272, 0x0362, 0xe459, 0xc451, 0x6349, 0x6341, 0x8349, 0x2239, 0xa120, 0x6010, 0xa120, 0xc128, 0xe130, 
	0xa120, 0xe130, 0xa120, 0xe130, 0x0241, 0xe130, 0x2239, 0xe261, 0x8282, 0xc392, 0xc292, 0x2272, 0xc351, 0xac8b, 0x36d6, 0x0fc5, 0xc9a3, 0x8cbc, 0xe782, 0xc451, 0x8251, 0x6249, 0xe130, 0xa120, 0xa120, 0xa120, 0xe128, 0x6141, 0x026a, 0x827a, 0xa382, 0x637a, 0x8993, 0x8eb4, 0x8eb4, 0x0ca4, 0xeb9b, 0xcfb4, 0x6dac, 0xaa9b, 0xc872, 0x0229, 0xc128, 0xa251, 0xa259, 0x8151, 0x4141, 0x8349, 0x055a, 0xa76a, 0x0883, 0x4662, 0x055a, 0xe87a, 0x4662, 0x0231, 0xa120, 0xe130, 0xc130, 0xc128, 
	0xa259, 0xc128, 0x8118, 0xa120, 0x8118, 0xe130, 0x026a, 0x427a, 0x8282, 0xa28a, 0x8382, 0xe782, 0xa76a, 0x6a83, 0xf5d5, 0xaeb4, 0x6472, 0x2ab4, 0x09b4, 0xa351, 0xa351, 0xc259, 0x8251, 0xe130, 0x8118, 0x8120, 0xc128, 0x4241, 0x4249, 0x6249, 0x2141, 0xa86a, 0x4ea4, 0xaeb4, 0xaebc, 0xcb9b, 0xa772, 0xaebc, 0xefc4, 0xe782, 0x456a, 0x8441, 0xa120, 0xe128, 0xc128, 0xe130, 0xe138, 0x4241, 0x6241, 0x6241, 0x466a, 0x2562, 0x6249, 0x4662, 0xc451, 0xe130, 0xe130, 0x2239, 0x0239, 0xe130, 
	0x6249, 0xc128, 0xa120, 0x8118, 0x8018, 0x2139, 0xc261, 0xe261, 0xc261, 0x8151, 0x4241, 0x876a, 0x8762, 0x255a, 0x297b, 0x0ca4, 0xe8ab, 0x06b4, 0x449b, 0x2462, 0x2241, 0xc128, 0xe230, 0xe130, 0xc128, 0xc128, 0xc128, 0xe128, 0xe130, 0x0139, 0x2139, 0xe459, 0xe459, 0x0883, 0x6db4, 0x8db4, 0x0ba4, 0x498b, 0x0ba4, 0x2cac, 0x8993, 0xe451, 0x4241, 0xc128, 0x2241, 0xa259, 0xc261, 0x026a, 0x2272, 0xe261, 0xe261, 0x026a, 0x026a, 0xa259, 0x0131, 0xa120, 0xc128, 0xe130, 0xe138, 0xa128, 
	0x4339, 0xa118, 0xa120, 0xa120, 0xc128, 0x0139, 0x0139, 0xe128, 0xe130, 0x6249, 0x4272, 0x0393, 0xa382, 0x226a, 0x0362, 0x0462, 0x4562, 0x6472, 0xc482, 0x048b, 0x2239, 0x2239, 0x2239, 0x0239, 0x0131, 0xc130, 0x0139, 0xa251, 0x8251, 0x026a, 0x4272, 0x4272, 0x2272, 0x2372, 0xc482, 0x659b, 0x84ab, 0x63a3, 0x649b, 0xa5ab, 0x04bc, 0x0462, 0xe361, 0x6372, 0x8251, 0xc259, 0xe261, 0x2272, 0x8282, 0xc28a, 0xe392, 0x0393, 0x239b, 0xa382, 0x0139, 0x8120, 0xe130, 0x0139, 0x6249, 0xa259, 
	0x4339, 0xa120, 0xc128, 0x0239, 0x0131, 0xa128, 0xc128, 0x2141, 0xe261, 0x8282, 0x23a3, 0xc3b3, 0x03c4, 0xe3bb, 0x63a3, 0x0393, 0x2393, 0x04bc, 0x63cc, 0x43c4, 0x4239, 0x0883, 0x0239, 0xe138, 0xe130, 0x0131, 0x236a, 0x239b, 0xc261, 0x026a, 0x627a, 0xa28a, 0x239b, 0x83ab, 0xc4b3, 0xe5bb, 0x05bc, 0x86cc, 0x85cc, 0x03bc, 0x83d4, 0x6372, 0xc38a, 0x026a, 0x8251, 0xa259, 0xe261, 0x2272, 0x6282, 0xc48a, 0xe682, 0xe77a, 0x8672, 0x0462, 0xe130, 0x8118, 0xe130, 0x0139, 0x0139, 0x2241, 
	0xe128, 0x2239, 0x6341, 0x0139, 0xe130, 0xc130, 0x2141, 0x8251, 0xe261, 0x8282, 0x239b, 0xc3b3, 0x43cc, 0x85cc, 0x26bc, 0x07b4, 0x85a3, 0x869b, 0x837a, 0x63cc, 0x4249, 0x4a8b, 0x0139, 0xe138, 0xe130, 0xe130, 0xc259, 0x8382, 0x026a, 0x026a, 0x627a, 0xc28a, 0x63ab, 0x659b, 0x6893, 0xca9b, 0xe782, 0x0ca4, 0x8993, 0x8251, 0x63cc, 0x038b, 0xe359, 0x6249, 0x4241, 0x6249, 0xc259, 0x026a, 0x627a, 0x2272, 0x6249, 0xc128, 0xe130, 0x226a, 0x4139, 0x8118, 0xc128, 0xe130, 0xe130, 0x0139, 
	0x4241, 0x8341, 0xc87a, 0xe138, 0xe130, 0xc128, 0x0139, 0x6249, 0x8259, 0x2272, 0x039b, 0xc3b3, 0x44c4, 0x439b, 0xc269, 0xe369, 0x6993, 0x2cac, 0xa482, 0x63cc, 0x0262, 0xa449, 0x4241, 0xe130, 0xc128, 0x0131, 0x8251, 0xe269, 0x226a, 0x8251, 0x4272, 0xe292, 0x83ab, 0x4272, 0xe138, 0xe138, 0xe140, 0xe130, 0xe130, 0x2272, 0xa3d4, 0x0362, 0xa120, 0x0231, 0x4241, 0x2239, 0x2239, 0x8249, 0xc259, 0xc259, 0x2139, 0x0239, 0xc382, 0x84ab, 0xa251, 0x8118, 0xa120, 0xc120, 0xc120, 0xc120, 
	0x0231, 0x6341, 0xaa93, 0x4241, 0xe130, 0xc128, 0xc128, 0x0239, 0x2239, 0x8249, 0x0362, 0xc482, 0x64a3, 0x04bc, 0x65c4, 0xe9d4, 0xe9d4, 0xc7d4, 0x64cc, 0x63cc, 0xa482, 0xe359, 0xc451, 0xa120, 0x8118, 0xe128, 0x4241, 0x8251, 0xc261, 0xc259, 0xc259, 0x637a, 0x63ab, 0xe3bb, 0x627a, 0x6159, 0x8259, 0x6251, 0xa259, 0x23bc, 0x04bc, 0x4239, 0xa120, 0x2141, 0x6251, 0x8251, 0xa259, 0xa259, 0xc259, 0x8251, 0x2231, 0x4331, 0x265a, 0x6662, 0xa349, 0x2241, 0x0239, 0xe128, 0xe228, 0xe220, 
	0x0231, 0xa351, 0x6a8b, 0x8449, 0xc128, 0xc128, 0xc128, 0x2239, 0x4249, 0x8251, 0x2272, 0xc38a, 0x6472, 0x2462, 0xc672, 0x2783, 0x688b, 0x8893, 0x8893, 0x688b, 0x2462, 0x43a3, 0x278b, 0xa120, 0x8118, 0xc128, 0x0239, 0x4249, 0x8259, 0x026a, 0xe261, 0xc351, 0xa382, 0xa3b3, 0xe3bb, 0xa3ab, 0xa4ab, 0x83a3, 0xc4b3, 0xc4b3, 0xa57a, 0x8118, 0x8118, 0x2239, 0x4249, 0x6251, 0xa259, 0x026a, 0x0262, 0xa449, 0xc541, 0xc541, 0x074a, 0x074a, 0x2331, 0xc128, 0xe130, 0xe130, 0xc120, 0xa118, 
	0x4239, 0x4239, 0x4662, 0x2231, 0xa120, 0xc120, 0xe128, 0x4241, 0x6249, 0x6249, 0xe551, 0xc772, 0x8572, 0x0452, 0x475a, 0xc96a, 0xa86a, 0xc96a, 0xe96a, 0xe972, 0xc541, 0x8249, 0xa38a, 0xe261, 0xc128, 0xc128, 0xe230, 0x4339, 0xc451, 0x0262, 0x427a, 0x0262, 0x255a, 0x6662, 0xa572, 0xe682, 0xc67a, 0xe872, 0x685a, 0x4852, 0xc549, 0xc128, 0xc128, 0xe120, 0xe228, 0x2231, 0x8249, 0xc251, 0xa349, 0xe541, 0x064a, 0xe641, 0x274a, 0x074a, 0x2331, 0xc128, 0xe128, 0xc120, 0xc120, 0x6010, 
	0x0229, 0x0229, 0xa441, 0x4662, 0xc120, 0xc128, 0xc128, 0x2241, 0x4249, 0xa86a, 0x55ad, 0xfbe6, 0x919c, 0xae83, 0x7094, 0x6c73, 0x919c, 0x2f94, 0x5094, 0x2f8c, 0x508c, 0x308c, 0x8862, 0xb1a4, 0x8d7b, 0x2f8c, 0x6d73, 0x6d73, 0x13a5, 0xcd83, 0x8b83, 0xac83, 0x58d6, 0xf3a4, 0x308c, 0xb29c, 0xea62, 0x75b5, 0x308c, 0xd7bd, 0xa639, 0x0f8c, 0xef83, 0xe641, 0x308c, 0xee83, 0x6d73, 0xae7b, 0xee83, 0x508c, 0xf39c, 0x2b6b, 0x4852, 0x8539, 0xc220, 0x8118, 0xa120, 0xa120, 0x8118, 0x8118, 
	0x2329, 0x0221, 0x4331, 0xc772, 0xe130, 0xe128, 0xe128, 0x0231, 0x2239, 0x0a73, 0x55ad, 0x4c6b, 0x274a, 0x95b5, 0x54ad, 0xb6bd, 0x7df7, 0xce7b, 0x79d6, 0x7df7, 0xf7c5, 0x5def, 0x6d73, 0xdbde, 0x8d73, 0x38ce, 0x1ce7, 0x99d6, 0x13a5, 0x8e73, 0x34ad, 0x95b5, 0x7ef7, 0x13a5, 0x13a5, 0xdade, 0xf7c5, 0xbade, 0x2b6b, 0x1ce7, 0x484a, 0xbef7, 0x17c6, 0x13a5, 0x3ce7, 0xf7c5, 0xfbe6, 0x38c6, 0xd29c, 0x0f84, 0x7194, 0x0742, 0xc120, 0xa118, 0x8118, 0xa118, 0xa118, 0xc120, 0xc128, 0xc128, 
	0xe220, 0x6008, 0xa118, 0xa441, 0x8118, 0x4010, 0x8110, 0xc220, 0xe228, 0x895a, 0x75b5, 0xfbe6, 0x13a5, 0xf7bd, 0xf7c5, 0x54ad, 0x5def, 0xce7b, 0x79d6, 0x79d6, 0x38ce, 0x5def, 0x4d6b, 0x38ce, 0xa95a, 0x9ef7, 0x1ce7, 0x99d6, 0x96b5, 0x7194, 0xb6bd, 0xf7c5, 0x7ef7, 0x13a5, 0x79ce, 0x5def, 0x17c6, 0x79d6, 0x308c, 0x3cef, 0x284a, 0x7def, 0x58ce, 0x508c, 0x1ce7, 0xf7c5, 0x58ce, 0xf3a4, 0x38ce, 0x55ad, 0xae7b, 0xe641, 0xe128, 0xe128, 0xa120, 0x6010, 0x6110, 0x6110, 0xa120, 0xa118, 
	0xc120, 0x6010, 0x8110, 0x6439, 0xc220, 0x4008, 0x6110, 0xc120, 0xc120, 0x2329, 0x4852, 0x0b63, 0x6952, 0xca5a, 0xeb62, 0x895a, 0x0b63, 0x274a, 0xca5a, 0xef83, 0xf7c5, 0xf3a4, 0x2429, 0x074a, 0x8439, 0xa962, 0x4852, 0x274a, 0x074a, 0xe641, 0x0742, 0xe741, 0x284a, 0x8531, 0xe741, 0x6852, 0x4752, 0x475a, 0x2752, 0x895a, 0x6431, 0x0742, 0xe741, 0x4431, 0x4852, 0x6852, 0xc962, 0x895a, 0x885a, 0x074a, 0xa539, 0x2331, 0x0231, 0xc128, 0x8110, 0x4008, 0x8110, 0x6010, 0x8118, 0x8118
  };
  static const int16_t minion2[]  = {
	0xe210, 0xe218, 0xc110, 0xc118, 0xe218, 0xe218, 0xe218, 0xe210, 0xc210, 0xe210, 0xe218, 0xe218, 0xe210, 0xe210, 0xe210, 0xc110, 0xc118, 0xc118, 0xc118, 0xc110, 0xc110, 0xc110, 0xc118, 0xc110, 0xc110, 0xc110, 0xc110, 0xc110, 0xa110, 0xc110, 0xc118, 0xc118, 0xc110, 0xc110, 0xc110, 0xc118, 0xc118, 0xc118, 0xc118, 0xc118, 0xa110, 0xe218, 0xe218, 0xc110, 0xa110, 0x6110, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 
	0x0219, 0xe220, 0x0229, 0x0231, 0x2231, 0x0231, 0x0229, 0x0229, 0xe220, 0xe218, 0xe218, 0xe218, 0x0219, 0x0219, 0x0219, 0xe218, 0xe218, 0xe218, 0xe218, 0xe218, 0xe218, 0xe218, 0xe218, 0xc218, 0xc118, 0xc118, 0xa110, 0x8110, 0x8110, 0xc120, 0xe128, 0xe128, 0xe128, 0xe120, 0xe220, 0xc118, 0xc218, 0xc218, 0xe218, 0x0221, 0xe218, 0xc118, 0xa118, 0xa110, 0x6008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 0x4008, 
	0xc118, 0xc128, 0x0231, 0x4241, 0x2239, 0x4241, 0x6341, 0x0231, 0xc120, 0x6110, 0x6010, 0xa110, 0xa110, 0xa110, 0xa118, 0xa118, 0xa110, 0xa110, 0xa110, 0x8110, 0x8110, 0x8110, 0x8110, 0xa118, 0x8110, 0x6110, 0x6010, 0x8110, 0xc120, 0xe128, 0xc128, 0xc128, 0xc128, 0xe128, 0xa120, 0x8110, 0xa110, 0x8110, 0x8110, 0xc110, 0x8110, 0xa118, 0x8110, 0x6008, 0x6008, 0x6008, 0x6010, 0x6010, 0x6010, 0x6010, 0x6010, 0x6110, 0x6010, 0x4008, 0x8110, 0xc210, 0x6108, 0x6110, 0x2239, 0xa251, 
	0xa118, 0xa120, 0x2339, 0xa449, 0x6341, 0x4241, 0x8341, 0x4241, 0x0231, 0x8118, 0x6010, 0xa118, 0x0129, 0x4139, 0x4139, 0x0131, 0xc120, 0xc120, 0xc120, 0xa118, 0x6010, 0x8110, 0x6010, 0x6010, 0x6010, 0x6010, 0x6010, 0x6010, 0x6010, 0x6010, 0x8118, 0x8118, 0x8120, 0xa120, 0xa118, 0xc120, 0xc120, 0xa118, 0xa118, 0x8118, 0x8110, 0x8110, 0x8118, 0x6010, 0x8110, 0x8118, 0xa120, 0xe128, 0x0131, 0xe128, 0xc120, 0xa118, 0x8118, 0x8110, 0x8110, 0xa118, 0xa120, 0x4241, 0x4249, 0x2141, 
	0x6010, 0x8118, 0xc128, 0x0231, 0x2239, 0x0139, 0xe130, 0xe130, 0xc128, 0xe128, 0xc251, 0xa382, 0x439b, 0x83a3, 0x83ab, 0x64a3, 0x847a, 0xc86a, 0x097b, 0xc451, 0x4241, 0xe128, 0xa120, 0xa120, 0xa120, 0x8118, 0x8118, 0x8118, 0x8018, 0x8118, 0xa120, 0xa120, 0xc128, 0xc128, 0xc128, 0xe128, 0x0231, 0xc128, 0xc120, 0xc128, 0xc128, 0xc120, 0x8118, 0x8118, 0xa120, 0xa251, 0x236a, 0x637a, 0x627a, 0x627a, 0x2272, 0x8249, 0xe128, 0xc128, 0xc128, 0xc120, 0xa120, 0xa120, 0x8120, 0x8118, 
	0x8118, 0xa120, 0xc128, 0xc130, 0xe138, 0x2239, 0x2241, 0x4241, 0xa259, 0x637a, 0xe392, 0x039b, 0x43a3, 0x84ab, 0x63a3, 0xe261, 0x4662, 0xf5cd, 0x4fcd, 0x0aac, 0x446a, 0x8349, 0x0231, 0xc120, 0xa120, 0xa120, 0xa120, 0xa120, 0xe128, 0x4239, 0xc259, 0xa382, 0x449b, 0xa6a3, 0xa89b, 0x278b, 0xa57a, 0x2562, 0xa76a, 0x055a, 0x2239, 0xa120, 0xa120, 0xc128, 0x226a, 0x2272, 0x2272, 0x4272, 0x2272, 0x0362, 0xe459, 0xa351, 0x6341, 0x4341, 0x0239, 0xc120, 0xc128, 0xe130, 0xe130, 0xe130, 
	0x4141, 0xc128, 0xa128, 0xe130, 0x0141, 0x4241, 0x6249, 0xa259, 0x0272, 0x6282, 0xa28a, 0xa28a, 0xa282, 0xa382, 0x0783, 0x045a, 0xe972, 0x15d6, 0x0ca4, 0x6993, 0xedc4, 0xe359, 0xa349, 0x0231, 0xc128, 0xa120, 0xc128, 0x6141, 0x0262, 0x627a, 0xa382, 0x837a, 0x488b, 0x6eac, 0x8eb4, 0x0ca4, 0x0c9c, 0x10bd, 0x6eb4, 0xcb9b, 0xa772, 0xe228, 0xe128, 0x6249, 0xa259, 0x8151, 0x6149, 0xc351, 0xe559, 0xc449, 0xa772, 0x8672, 0xc451, 0x2562, 0x666a, 0x4339, 0xe130, 0x0139, 0x4241, 0x6249, 
	0x627a, 0xc261, 0xc128, 0xe130, 0x0139, 0x0239, 0x4241, 0x8249, 0x6249, 0x2141, 0x0139, 0xe128, 0xe128, 0x0239, 0x2a7b, 0x465a, 0xe549, 0x6a8b, 0x0783, 0x4372, 0x2ed5, 0x8472, 0xe459, 0x4241, 0xa120, 0xc120, 0x8249, 0x026a, 0x026a, 0xa259, 0x4241, 0x4662, 0xac8b, 0xafb4, 0xcfbc, 0xaa9b, 0x8a93, 0x51c5, 0xefc4, 0xc77a, 0x498b, 0xe551, 0x8120, 0xa120, 0x8020, 0x8020, 0xa120, 0x2239, 0xa449, 0x6341, 0xe87a, 0x6a8b, 0xe459, 0xc772, 0x0983, 0x6341, 0xc128, 0xe128, 0x2241, 0xc359, 
	0x2239, 0x0231, 0xc128, 0xe130, 0x2141, 0xc128, 0xa120, 0xa120, 0xc128, 0x0139, 0x8151, 0x026a, 0xa282, 0x0393, 0xe38a, 0xe361, 0xa351, 0xe451, 0x456a, 0x659b, 0xc4ab, 0x0362, 0xa349, 0x0231, 0xc128, 0xc128, 0x0239, 0xe130, 0xe130, 0x0131, 0x2139, 0xa351, 0x055a, 0x4983, 0x8eb4, 0x6db4, 0xcb9b, 0x698b, 0x0ca4, 0x0cac, 0x688b, 0xe451, 0x8341, 0xe128, 0xc128, 0x0139, 0x8251, 0x026a, 0x226a, 0xc259, 0xa259, 0xc259, 0xa259, 0xa259, 0x2239, 0xc128, 0xe130, 0x0139, 0x0141, 0x8251, 
	0x4339, 0x8341, 0xa120, 0xe130, 0x0139, 0xe130, 0xe130, 0x0139, 0x4249, 0xa259, 0x427a, 0xe29a, 0x83b3, 0x04bc, 0x44c4, 0x439b, 0x026a, 0xa351, 0xa351, 0xe359, 0x446a, 0x045a, 0x8349, 0x0239, 0xe130, 0xc128, 0xe130, 0x4141, 0xa259, 0x026a, 0x4272, 0x4272, 0x2272, 0x2372, 0xc582, 0x469b, 0x85a3, 0x439b, 0x249b, 0x84ab, 0xe4b3, 0x045a, 0xc451, 0x2239, 0x0131, 0x8251, 0xe261, 0x2272, 0x8282, 0xa28a, 0xc38a, 0xe392, 0x039b, 0xe392, 0x4141, 0x8120, 0xc130, 0x0139, 0x0139, 0x2241, 
	0x8439, 0x6339, 0xa449, 0xa451, 0x0139, 0xe138, 0xe130, 0x0139, 0x6251, 0xa259, 0x2272, 0xe292, 0xa3b3, 0x43cc, 0x83cc, 0x04bc, 0xa4ab, 0x0393, 0xe38a, 0xa4ab, 0x63cc, 0x2883, 0x2241, 0xe138, 0xe130, 0x0139, 0xa251, 0xa259, 0xc261, 0x026a, 0x627a, 0xa28a, 0x039b, 0x83ab, 0xa4b3, 0xe4b3, 0x05bc, 0x66cc, 0x85cc, 0x23c4, 0x63cc, 0x436a, 0x2362, 0xa282, 0xa259, 0xa259, 0xc261, 0x2272, 0x6282, 0xc38a, 0x068b, 0x068b, 0x068b, 0xa47a, 0x2139, 0x8118, 0xc120, 0xe130, 0xe130, 0x0139, 
	0xe130, 0x8349, 0x0ca4, 0x0883, 0x0139, 0xe138, 0xe130, 0x0139, 0x4249, 0x4249, 0xc259, 0x837a, 0x439b, 0x24c4, 0x64cc, 0xc48a, 0x4572, 0x6572, 0x857a, 0xa251, 0x63a3, 0x498b, 0x4241, 0xe130, 0xe130, 0x4241, 0xc382, 0x837a, 0xc261, 0x2272, 0x627a, 0xc28a, 0x63a3, 0x659b, 0x689b, 0xeaa3, 0xa99b, 0x4cac, 0xaa9b, 0xc261, 0x63cc, 0x439b, 0x837a, 0x0262, 0x4241, 0x6249, 0xc259, 0x026a, 0x427a, 0x627a, 0xc259, 0x0231, 0xe228, 0xc259, 0x4139, 0x8118, 0xa120, 0xc128, 0xc120, 0xc120, 
	0x2241, 0x2562, 0xaebc, 0xaa9b, 0x0139, 0xe138, 0xe130, 0xe128, 0xe230, 0x0231, 0x4239, 0x8349, 0x2462, 0xa47a, 0xa4ab, 0x45c4, 0x2bd5, 0x90d5, 0xacbc, 0x4241, 0x2239, 0x255a, 0x4241, 0xe130, 0xc128, 0x0131, 0xe261, 0xa382, 0xe261, 0xc259, 0x627a, 0xe292, 0x83ab, 0x627a, 0x0139, 0xe138, 0xe140, 0xe138, 0xe130, 0xc259, 0x83d4, 0xa382, 0xc120, 0x0131, 0x2241, 0x2239, 0x2231, 0x6241, 0xe261, 0x2272, 0x8249, 0xc128, 0x8249, 0xe38a, 0xc251, 0xa118, 0xa120, 0xe128, 0xe220, 0xe220, 
	0x0231, 0xc449, 0x8dbc, 0xcb9b, 0x2239, 0xe130, 0xc128, 0x0139, 0x6249, 0xa259, 0xc261, 0xe261, 0xa282, 0x0393, 0x8472, 0x866a, 0xe67a, 0x0362, 0x2239, 0xe130, 0xe130, 0xc128, 0x0231, 0xa120, 0xa120, 0xe128, 0x6249, 0xa259, 0xe261, 0xa251, 0xc259, 0x8382, 0x63ab, 0xa3ab, 0x427a, 0x4151, 0x6251, 0x4251, 0x8251, 0xe3b3, 0x23c4, 0x8349, 0xa120, 0x0139, 0x6251, 0x6251, 0xa259, 0xa259, 0xa251, 0x6249, 0xe228, 0x0229, 0xe549, 0x475a, 0xa351, 0x4241, 0x2239, 0xe128, 0xa120, 0xa118, 
	0x0231, 0xc351, 0xab9b, 0x666a, 0xe128, 0xc128, 0xa120, 0x0139, 0x6251, 0xa259, 0x026a, 0x2272, 0x026a, 0x627a, 0x239b, 0x2493, 0x84a3, 0x637a, 0x4241, 0x2231, 0xc128, 0x0239, 0x055a, 0xa120, 0xa118, 0x0231, 0x4249, 0x6249, 0xa259, 0x026a, 0xe261, 0xe359, 0xc38a, 0xa3b3, 0xc3b3, 0x63a3, 0x84ab, 0x439b, 0xa3ab, 0xc4b3, 0xe482, 0xa118, 0x6118, 0x0239, 0x4249, 0x6251, 0xa259, 0x026a, 0x0262, 0x8341, 0xa441, 0xa539, 0xe641, 0x2752, 0x4339, 0xc128, 0xe130, 0xe130, 0xe128, 0xa120, 
	0x6241, 0x4241, 0x8762, 0xe228, 0x8118, 0x8118, 0x8018, 0x0131, 0x6251, 0xc359, 0x866a, 0xe77a, 0x446a, 0xa349, 0xc451, 0x0583, 0xa572, 0x0652, 0xa541, 0xe649, 0x0231, 0x2362, 0x8349, 0x8341, 0xe228, 0xe128, 0x0139, 0x8349, 0xe459, 0x026a, 0x2272, 0xe261, 0x055a, 0x866a, 0xe57a, 0x0583, 0xe582, 0x087b, 0x8862, 0x4852, 0xa541, 0xc128, 0xc128, 0xc120, 0xe120, 0x2231, 0x6249, 0xc259, 0xc351, 0xc541, 0x274a, 0xe641, 0x074a, 0x4852, 0x6339, 0xe128, 0xe128, 0xc128, 0xc120, 0x8118, 
	0x0229, 0x0229, 0xe551, 0xe551, 0xa120, 0xa120, 0xc120, 0x0231, 0x4241, 0x2a73, 0xb6bd, 0xbade, 0xce83, 0x6c73, 0x919c, 0xea62, 0x7094, 0x0f8c, 0xad7b, 0x2f8c, 0xce83, 0x308c, 0x4c6b, 0x4f94, 0xca62, 0xef83, 0x8d7b, 0xce83, 0x13ad, 0x0e8c, 0x2e94, 0xcd8b, 0x34ad, 0x34ad, 0x7094, 0x7194, 0x4c6b, 0x55ad, 0xf3a4, 0xf7c5, 0x895a, 0x0f8c, 0xee83, 0x6852, 0x308c, 0xad7b, 0xad73, 0x8d73, 0xee83, 0x5094, 0x55ad, 0x8d7b, 0x6852, 0x064a, 0x0229, 0x8118, 0xa120, 0x8120, 0x8118, 0x8118, 
	0x2321, 0x0221, 0x6339, 0xa772, 0xe130, 0xe128, 0xe128, 0xe228, 0x0229, 0x8d7b, 0xb6bd, 0x2c6b, 0xe741, 0x75b5, 0x9ad6, 0x75b5, 0x3cef, 0x14a5, 0x9ad6, 0x1be7, 0x508c, 0x9ef7, 0x95b5, 0xbade, 0xae7b, 0xf7bd, 0x18c6, 0x95b5, 0xb6bd, 0x13a5, 0x59ce, 0xf7c5, 0x38ce, 0x96b5, 0x75b5, 0xf7c5, 0xb6bd, 0x38ce, 0xf3a4, 0x5def, 0xae7b, 0x5def, 0x14a5, 0x9ad6, 0xfbe6, 0x9194, 0x3ce7, 0xf7c5, 0xd29c, 0x0f84, 0xd29c, 0xa95a, 0x0221, 0xa118, 0x8118, 0xa118, 0x8118, 0xc120, 0xc120, 0xc128, 
	0xa118, 0x6008, 0xc118, 0x0652, 0xa118, 0x4008, 0x8110, 0xc118, 0xc220, 0x0b63, 0xd6bd, 0xdade, 0x508c, 0x95b5, 0xdbde, 0xd29c, 0xfbe6, 0x14a5, 0x9ad6, 0x59ce, 0x13a5, 0x9ef7, 0x75ad, 0xb6b5, 0x0b63, 0x3cef, 0x18c6, 0x75b5, 0xb6bd, 0x34ad, 0x79d6, 0x38ce, 0x38ce, 0xb6b5, 0xbade, 0x79d6, 0xb6bd, 0xf7bd, 0x75b5, 0x5def, 0x8d73, 0x3ce7, 0xb6bd, 0x96b5, 0xfbe6, 0x9194, 0x79d6, 0xb29c, 0x17c6, 0x95b5, 0xef83, 0x274a, 0xe128, 0xe128, 0xc120, 0x6010, 0x8110, 0x6010, 0xa118, 0xa118, 
	0xa120, 0x6010, 0xa118, 0x0652, 0x4331, 0x4008, 0x6110, 0xa118, 0xa118, 0x2329, 0x484a, 0xaa5a, 0x0742, 0x484a, 0xa95a, 0x0742, 0x8952, 0x0742, 0x484a, 0x0f84, 0xb6bd, 0xd39c, 0x0742, 0x074a, 0xa541, 0x895a, 0x074a, 0xc641, 0xe741, 0xc641, 0x074a, 0xe741, 0xe741, 0xc639, 0x0742, 0x274a, 0x2752, 0x2752, 0x675a, 0x885a, 0xa539, 0xe741, 0xe741, 0xa539, 0x4852, 0x074a, 0xea6a, 0xa962, 0x895a, 0x2752, 0xc639, 0x6431, 0x2231, 0xe128, 0x8118, 0x4008, 0x6110, 0x6010, 0x8110, 0xa118
  };
uint8_t tentativas = 0, recorde = 255;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void IniciarJogo();
void SelecionarCarta(char tabuleiro[4][4], uint8_t i, uint8_t j, uint8_t linhas, uint8_t colunas);
void Jogo(char tabuleiro[4][4], uint8_t linhas, uint8_t colunas, uint8_t linhaAtual, uint8_t colunaAtual);
void GerarParesAleatorios(char tabuleiro[4][4], uint8_t linhas, uint8_t colunas);
bool VerificaSeExisteCartaDisponivelLinha(char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t colunas);
bool VerificaSeExisteCartaDisponivelColuna(char tabuleiro[4][4],uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t linhas);
void MoverParaProximaCartaLinha(char tabuleiro[4][4], uint8_t* colunaAtual, uint8_t* linhaAtual, uint8_t colunas, uint8_t sentido);
void MoverParaLinhaComCarta(char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t linhas, uint8_t colunas, uint8_t sentido);
void MoverParaColunaComCarta(char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t linhas, uint8_t colunas, uint8_t sentido);
void MoverParaProximaCartaColuna(char tabuleiro[4][4], uint8_t* colunaAtual, uint8_t* linhaAtual, uint8_t linhas, uint8_t sentido);
void AtualizarRecorde(uint8_t atual);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7789_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	IniciarJogo();
	ExibirFimDeJogo(tentativas, recorde);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
uint16_t seta = WHITE;
uint32_t last_tick = 0;

void NavegadorCursor(bool jogo, char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t linhas, uint8_t colunas){
	int x, y;
	if ((HAL_GetTick()-last_tick)>500){
		if(seta==WHITE)
			{
				seta=BLACK;
			}
		else if(seta==BLACK)
			{
			seta=WHITE;
			}
		last_tick=HAL_GetTick();
	}
	if(jogo){

		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)) { //esquerda
			if(VerificaSeExisteCartaDisponivelLinha(tabuleiro, linhaAtual, colunaAtual, colunas)){
				MoverParaProximaCartaLinha(tabuleiro, colunaAtual, linhaAtual, colunas, 0);
			}
            else{
            	MoverParaLinhaComCarta(tabuleiro, linhaAtual, colunaAtual, linhas, colunas, 0);
            }
        }

		else if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)) { // baixo
			if(VerificaSeExisteCartaDisponivelColuna(tabuleiro, linhaAtual, colunaAtual, linhas)){
				MoverParaProximaCartaColuna(tabuleiro, colunaAtual, linhaAtual, linhas, 1);
			}
			else{
				MoverParaColunaComCarta(tabuleiro, linhaAtual, colunaAtual, linhas, colunas, 1);
			}

        }

		else if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)) { //direita
			if(VerificaSeExisteCartaDisponivelLinha(tabuleiro, linhaAtual, colunaAtual, colunas)){
				MoverParaProximaCartaLinha(tabuleiro, colunaAtual, linhaAtual, colunas, 1);
			}
			else{
			    MoverParaLinhaComCarta(tabuleiro, linhaAtual, colunaAtual, linhas, colunas, 1);
			}
		}

		else if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)) { //cima
			if(VerificaSeExisteCartaDisponivelColuna(tabuleiro, linhaAtual, colunaAtual, linhas)){
				MoverParaProximaCartaColuna(tabuleiro, colunaAtual, linhaAtual, linhas, 0);
			}
			else{
				MoverParaColunaComCarta(tabuleiro, linhaAtual, colunaAtual, linhas, colunas, 0);
			}
		}
	}
	else{
	ST7789_DrawFilledRectangle(10, 38, 60, 6, WHITE);
	ST7789_DrawFilledRectangle(170, 38, 60, 6, WHITE);
	x=5;
	y=79;
	jogo=true;
	}
	ST7789_DrawFilledTriangle(x+18, y-6, x+20, y+6, x+30, y, seta);
	ST7789_DrawFilledRectangle(x, y-3, 25 , 6, seta);
}

bool VerificaSeExisteCartaDisponivelLinha(char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t colunas){
	for(int c = 0; c < colunas; c++){
		if(tabuleiro[*linhaAtual][c] != '0' && c != *colunaAtual) return true;
	}
	return false;
}

void MoverParaProximaCartaLinha(char tabuleiro[4][4], uint8_t* colunaAtual, uint8_t* linhaAtual, uint8_t colunas, uint8_t sentido){ // 1 pra direita ou 0 pra esquerda
	uint8_t original = *colunaAtual;
	do{
		if(sentido>0) *colunaAtual = (*colunaAtual + 1) % colunas;
		else *colunaAtual = (*colunaAtual == 0) ? colunas - 1 : *colunaAtual - 1;
	} while(tabuleiro[*linhaAtual][*colunaAtual] == '0' && *colunaAtual != original);
}

void MoverParaLinhaComCarta(char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t linhas, uint8_t colunas, uint8_t sentido) { // 1 para baixo ou 0 para cima
	uint8_t linhaOriginal = *linhaAtual;
	do {
		if(sentido > 0)*linhaAtual = (*linhaAtual + 1) % linhas;
		else *linhaAtual = (*linhaAtual == 0) ? linhas - 1 : *linhaAtual - 1;
	} while (!VerificaSeExisteCartaDisponivelLinha(tabuleiro, linhaAtual, colunaAtual, colunas) && *linhaAtual != linhaOriginal);
	for (int c = 0; c < colunas; c++) {
		if (tabuleiro[*linhaAtual][c] != '0') {
			*colunaAtual = c;
			break;
		}
	}
}

void MoverParaProximaCartaColuna(char tabuleiro[4][4], uint8_t* colunaAtual, uint8_t* linhaAtual, uint8_t linhas, uint8_t sentido){
	uint8_t original = *linhaAtual;
	do{
		if(sentido > 0) *linhaAtual = (*linhaAtual + 1) % linhas;
		else  *linhaAtual = (*linhaAtual == 0) ? linhas - 1 : *linhaAtual - 1;
	} while(tabuleiro[*linhaAtual][*colunaAtual] == '0' && *linhaAtual != original);
}

void MoverParaColunaComCarta(char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t linhas, uint8_t colunas, uint8_t sentido){
	uint8_t original = *colunaAtual;
	do {
		if(sentido > 0) *colunaAtual = (*colunaAtual + 1) % colunas;
		else *colunaAtual = (*colunaAtual == 0) ? colunas - 1 : *colunaAtual - 1;
	} while (!VerificaSeExisteCartaDisponivelColuna(tabuleiro, linhaAtual, colunaAtual, linhas) && *colunaAtual != original);
	for (int l = 0; l < linhas; l++) {
			if (tabuleiro[l][*colunaAtual] != '0') {
				*linhaAtual = l;
				break;
			}
		}
}

bool VerificaSeExisteCartaDisponivelColuna(char tabuleiro[4][4], uint8_t* linhaAtual, uint8_t* colunaAtual, uint8_t linhas){
	for(int l = 0; l<linhas; l++){
		if(tabuleiro[l][*colunaAtual] != '0') return true;
	}
	return false;
}

void IniciarJogo () {
	bool menu = true;
	uint8_t linhas = 4, colunas = 4, jogadores = 1;
	ST7789_Fill_Color(BLACK);
	ST7789_WriteString(0,0, "Matching Pairs", Font_16x26, WHITE, BLACK);
	ST7789_WriteString(88,30, "Game", Font_16x26, WHITE, BLACK);

     while(menu){
     ST7789_WriteString(40,70, "Iniciar jogo", Font_11x18, WHITE, BLACK);
     ST7789_WriteString(40,100, "Recordes", Font_11x18, WHITE, BLACK);
     ST7789_WriteString(40,130, "Configuracoes", Font_11x18, WHITE, BLACK);
     NavegadorCursor(false, 0, 0, 0, 0, 0);
    }
     char tabuleiro[4][4];
     tentativas = 0;
     GerarParesAleatorios(tabuleiro, linhas, colunas);
     Jogo(tabuleiro, linhas, colunas, 0, 0);
     AtualizarRecorde(tentativas);
}

void GerarParesAleatorios(char tabuleiro[4][4], uint8_t linhas, uint8_t colunas){
	char temp[linhas*colunas];
	for(int i = 0; i< linhas*colunas/2; i++){
		temp[i*2] = 'a' + i;
		temp[i*2 + 1] = 'a' + i;
	}
	for(int i = linhas*colunas - 1; i>0; i--){
		uint8_t j = rand() % (i+1);
		char tmp = temp[i];
		temp[i] = temp[j];
		temp[j] = tmp;
	}
	uint8_t count = 0;
	for(int i = 0; i<linhas; i++){
		for(int j = 0; j<colunas; j++){
			tabuleiro[i][j] = temp[count];
			count++;
		}
	}
}

void SelecionarCarta(char tabuleiro[4][4], uint8_t i, uint8_t j, uint8_t linhas, uint8_t colunas){
	uint8_t x = 240/colunas * j, y = 240/linhas * i;
	switch(tabuleiro[i][j]){
	case 'a':
		DrawCard(x, y, RED, (const bool*) hearts);
		break;
	case 'b':
		DrawCard(x, y, RED, (const bool*) diamonds);
		break;
	case 'c':
		DrawCard(x, y, BLACK, (const bool*) clubs);
		break;
	case 'd':
		DrawCard(x, y, BLACK, (const bool*) spades);
		break;
	case 'e':
		DrawCard(x, y, BLACK, (const bool*) hearts);
		break;
	case 'f':
		DrawCard(x, y, BLACK, (const bool*) diamonds);
		break;
	case 'g':
		DrawCard(x, y, RED, (const bool*) clubs);
		break;
	case 'h':
		DrawCard(x, y, RED, (const bool*) spades);
		break;
	}
}

void VirarTodasCartas(uint8_t linhas, uint8_t colunas){
	uint8_t x = 240/colunas, y = 240/linhas;
	for(int i = 0; i<linhas; i++){
		for(int j = 0; j<colunas; j++){
			ST7789_DrawImage(x*j, y*i, 50, 50, (const uint16_t *)fundocarta);
		}
	}
}

void AtualizarRecorde(uint8_t atual){
	recorde = (recorde > atual) ? atual : recorde;
}

bool CompararPares(char a, char b){
	return a==b;
}

void AtualizarTentativas(uint8_t *tentativas){
	(*tentativas)++;
}

bool VerificaFimDeJogo(uint8_t acertos, uint8_t linhas, uint8_t colunas){
	return acertos >= linhas*colunas;
}

void ExibirFimDeJogo(uint8_t numeroDeTentativasDaRodada, uint8_t recorde){
	uint32_t startTime = HAL_GetTick(); 
    uint8_t currentFrame = 0; 

    while ((HAL_GetTick() - startTime) < 5000) {
        ST7789_Fill_Color(BLACK);

        if (currentFrame == 0) {
            ST7789_DrawImage(60, 40, 50, 50, (const uint16_t *)minion1);
        } else {
            ST7789_DrawImage(60, 40, 50, 50, (const uint16_t *)minion2);
        }

        currentFrame = !currentFrame;

        HAL_Delay(200);


    ST7789_WriteString(40, 20, "Fim de Jogo!", Font_11x18, WHITE, BLACK);
	ST7789_WriteString(40, 50, "Tentativas:", Font_11x18, WHITE, BLACK);
	ST7789_WriteString(40, 80, "Recorde:", Font_11x18, WHITE, BLACK);
	ST7789_WriteString(40, 110, "Aperte qualquer botao", Font_11x18, WHITE, BLACK);
	ST7789_WriteString(40, 140, "para reiniciar", Font_11x18, WHITE, BLACK);

	char tentativasStr[3], recordeStr[3];
	sprintf(tentativasStr, "%d", numeroDeTentativasDaRodada);
	sprintf(recordeStr, "%d", recorde);
	ST7789_WriteString(150, 50, tentativasStr, Font_11x18, WHITE, BLACK);
	ST7789_WriteString(150, 80, recordeStr, Font_11x18, WHITE, BLACK);

	while(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) && !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) && !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) && !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12));


}
}
void Jogo(char tabuleiro[4][4], uint8_t linhas, uint8_t colunas, uint8_t linhaAtual, uint8_t colunaAtual){
	for(;;){
		uint8_t totalDeCartasSelecionadas = 0, acertos = 0, posicoesCartasSelecionadas[2][2];
		for(int i = 0; i < colunas; i++){
			for(int j = 0; j < linhas; j++){
				SelecionarCarta(tabuleiro, i, j, linhas, colunas);
			}
		}
		HAL_Delay(1500);
		VirarTodasCartas(linhas, colunas);
		uint8_t ultimaPosicao[2] = {100, 100};
		while(!VerificaFimDeJogo(acertos, linhas, colunas)){
			NavegadorCursor(true, tabuleiro, &linhaAtual, &colunaAtual, linhas, colunas);
			if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) && !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) && linhaAtual != ultimaPosicao[0] && colunaAtual != ultimaPosicao[1]){
				SelecionarCarta(tabuleiro, linhaAtual, colunaAtual, linhas, colunas);
				posicoesCartasSelecionadas[totalDeCartasSelecionadas%2][0] = linhaAtual;
				posicoesCartasSelecionadas[totalDeCartasSelecionadas%2][1] = colunaAtual;
				totalDeCartasSelecionadas++;
				ultimaPosicao[0] = linhaAtual;
				ultimaPosicao[1] = colunaAtual;
				if(totalDeCartasSelecionadas % 2 == 0){
					AtualizarTentativas(&tentativas);
					char carta1 = tabuleiro[posicoesCartasSelecionadas[0][0]][posicoesCartasSelecionadas[0][1]];
					char carta2 = tabuleiro[posicoesCartasSelecionadas[1][0]][posicoesCartasSelecionadas[1][1]];
					if(CompararPares(carta1, carta2)){
						acertos++;
						tabuleiro[posicoesCartasSelecionadas[0][0]][posicoesCartasSelecionadas[0][1]] = '0';
						tabuleiro[posicoesCartasSelecionadas[1][0]][posicoesCartasSelecionadas[1][1]] = '0';
					}
					else{
						HAL_Delay(1000);
						ST7789_DrawImage(240/colunas*posicoesCartasSelecionadas[0][1], 240/linhas*posicoesCartasSelecionadas[0][0], 50, 50, (const uint16_t *)fundocarta);
						ST7789_DrawImage(240/colunas*posicoesCartasSelecionadas[1][1], 240/linhas*posicoesCartasSelecionadas[1][0], 50, 50, (const uint16_t *)fundocarta);
					}
				}
			}
		}
		//ganhou o jogo
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
