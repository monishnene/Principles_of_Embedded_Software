/*
 * platform.h
 *
 *  Created on: Sep 29, 2017
 *      Author: monish and sanika
 */

#ifndef	PLATFORM_H_
#define PLATFORM_H_
#if PLATFORM==KL25Z
#ifdef VERBOSE 
#undef VERBOSE /*undefining verbose for kl25z*/
#endif
#endif 
#endif /*platform.h*/
