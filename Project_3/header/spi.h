/*
* spi.h
*
*
* Created on: Nov 19, 2017
*
* Author: Sanika
*/

#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>

void SPI_init();
void SPI_read_byte( uint8_t byte);
void SPI_write_byte( uint8_t byte);
void SPI_send_packet( uint8_t* p, size_t length);
void SPI_flush();

#endif
