/*
 * ImageAloc.h
 *
 *  Created on: 19.03.2019
 *      Author: mechatronik
 */

#ifndef IMAGEALOC_H_
#define IMAGEALOC_H_


#define	MEM_cervi			391802
#define	MEM_iomenu			120122
#define	MEM_piomenu			120122
#define	MEM_servo			120122
#define	MEM_pservo			120122
#define MEM_miomenu			21122
#define MEM_mstepmenu		21122
#define MEM_on				17222
#define MEM_off				17222
#define MEM_back1			10922
#define MEM_pback1			10922
#define MEM_plagin			19322
#define MEM_plagout			19322

#define ADR_cervi			(uint8_t *)0xC0260000
#define ADR_iomenu			ADR_cervi+MEM_cervi
#define ADR_piomenu			ADR_iomenu+MEM_iomenu
#define ADR_servo			ADR_piomenu+MEM_piomenu
#define ADR_pservo			ADR_servo+MEM_servo
#define ADR_miomenu			ADR_pservo+MEM_pservo
#define ADR_mstepmenu		ADR_miomenu+MEM_miomenu
#define ADR_on				ADR_mstepmenu+MEM_mstepmenu
#define ADR_off				ADR_on+MEM_on
#define ADR_back1			ADR_off+MEM_off
#define ADR_pback1			ADR_back1+MEM_back1
#define ADR_plugin			ADR_pback1+MEM_pback1
#define ADR_plugout			ADR_plugin+MEM_plagin


#endif /* IMAGEALOC_H_ */
