#include "MKL25Z4.h"
#include "SPI.h"
#include "nordic.h"

#ifndef GPIO_H_
#define GPIO_H_


void SPI_configure();
void GPIO_nrf_configure();
void nrf_chip_enable();
void nrf_chip_disable();
void nrf_transmit_enable();

#endif
