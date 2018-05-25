/*
 * RTC.h
 *
 *  Created on: Nov 26, 2017
 *      Author: monis
 */

#ifndef INCLUDES_RTC_H_
#define INCLUDES_RTC_H_

uint32_t date_to_sec(void);
void RTC_configure(void);
void RTC_Seconds_IRQHandler();


#endif /* INCLUDES_RTC_H_ */
