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
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  IniciarJogo();
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
bool menu = true;
int x=5, y=79;
short opcao=0,lugar=0;
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

void setar() {

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == 0){
				switch(opcao){
				case 0:
			    ST7789_Fill_Color(BLACK);
			    menu=false;
				break;
				case 1:
			    ST7789_Fill_Color(BLACK);
				opcao=0;
				lugar=1;
				break;
				case 2:
				lugar=3;
				opcao=0;
				break;
			}
			}
		else if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == 0)&& opcao>0){
		    	    last_tick=HAL_GetTick();
		    	    ST7789_DrawFilledTriangle(x+18, y-6, x+20, y+6, x+30, y, BLACK);
		    	    ST7789_DrawFilledRectangle(x, y-3, 25 , 6, BLACK);
					y-=30;
		    		opcao--;
		    		HAL_Delay(100);
		    	}
			else if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == 0)&& opcao<2){
					last_tick=HAL_GetTick();
				    ST7789_DrawFilledTriangle(x+18, y-6, x+20, y+6, x+30, y, BLACK);
				    ST7789_DrawFilledRectangle(x, y-3, 25 , 6, BLACK);
					y+=30;
					opcao++;
					HAL_Delay(100);
			}
			else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == 0&&lugar>0){
			    ST7789_Fill_Color(BLACK);
			    x=5;
			    y=79;
					lugar=0;
			}
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
		ST7789_DrawFilledTriangle(x+18, y-6, x+20, y+6, x+30, y, seta);
		ST7789_DrawFilledRectangle(x, y-3, 25 , 6, seta);

	}
void IniciarJogo () {
	bool apareceu =false;
	uint8_t linhas = 4, colunas = 4, jogadores = 1;
	 ST7789_Fill_Color(BLACK);

	 while(menu){
	 ST7789_WriteString(0,0, "Matching Pairs", Font_16x26, WHITE, BLACK);
	 ST7789_WriteString(88,30, "Game", Font_16x26, WHITE, BLACK);
     ST7789_DrawFilledRectangle(5, 43, 70, 6, WHITE);
     ST7789_DrawFilledRectangle(165, 43, 70 , 6, WHITE);
     if (lugar==0){
    	 ST7789_WriteString(40,70, "Iniciar jogo", Font_11x18, WHITE, BLACK);
    	 ST7789_WriteString(40,100, "Configuracoes", Font_11x18, WHITE, BLACK);
    	 ST7789_WriteString(40,130, "Recordes", Font_11x18, WHITE, BLACK);

     }
     else if(lugar==1){
    	 ST7789_WriteString(0,70, "Tamanho do tabuleiro", Font_11x18, WHITE, BLACK);
    	 ST7789_DrawRectangle(40, 100, 60, 120, WHITE);
    	 ST7789_DrawRectangle(150, 100, 170,120, WHITE);

         ST7789_WriteChar(42, 98 , 'x', Font_16x26, WHITE, BLACK);
    	 ST7789_WriteString(65,101, "4x4", Font_11x18, WHITE, BLACK);
    	 ST7789_WriteString(175,101, "3x4", Font_11x18, WHITE, BLACK);
    	 ST7789_WriteString(0,150, "Quantidade de players", Font_11x18, WHITE, BLACK);
    	 ST7789_DrawRectangle(30, 180, 50, 200, WHITE);
    	 ST7789_DrawRectangle(150,180, 170,200, WHITE);
    	 ST7789_WriteString(65,181, "1", Font_11x18, WHITE, BLACK);
    	 ST7789_WriteString(175,181, "2", Font_11x18, WHITE, BLACK);
     }
     setar();
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
	//teste
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
