/*
* nordic.h
*
*
* Created on: Nov 19, 2017
*
* Author: Sanika
*/

/*
* nordic.h
*
*
* Created on: Nov 19, 2017
*
* Author: Sanika
*/

#ifndef NORDIC_H_
#define NORDIC_H_

#include <stdint.h>
#define NRF_CONFIG_REG (0x00)
#define NRF_TXADDR_REG (0x10)
#define NRF_RF_CH_REG (0x05)
#define NRF_RF_SETUP_REG (0x06)
#define NRF_STATUS_REG (0x07)
#define RX_ADDR_P0_REG (0x0A)
#define RX_ADDR_P1_REG (0x0B)
#define TX_ADDR (0x10)
#define FIFO_STATUS_REG (0x17)
//#define NRF_POWER_UP (0x01)
//#define NRF_POWER_UP_MASK (0x02)
//#define NRF_POWER_DOWN_MASK (0x00)
//#define NRF_EN_AA_REG (0x01)
//#define NRF_EN_RXADDR_REG (0x02)
//#define NRF_SETUP_AW_REG (0x03)
//#define NRF_SETUP_RETR_REG (0x04)
//#define NRF_PIPESIZE (0X11)
//#define NRF_ENRXADDR (0x02)
//#define W_TXPAYLOAD (0xA0)
//#define R_RXPAYLOAD (0x61)

void  nrf_read_register(uint8_t register_function);
void nrf_write_register(uint8_t register_function);
void nrf_read_status();
void nrf_write_config();
void nrf_read_config();
void nrf_read_rf_setup();
void nrf_write_rf_setup();
void nrf_read_rf_ch();
void nrf_write_rf_ch();
void nrf_read_TX_ADDR();
void nrf_write_TX_ADDR();
void nrf_read_fifo_status();
void nrf_flush_tx_fifo();
void nrf_flush_rx_fifo();
#endif
