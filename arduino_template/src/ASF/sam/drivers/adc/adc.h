/**
 * \file
 *
 * \brief Analog-to-Digital Converter (ADC/ADC12B) driver for SAM.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include "compiler.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

//Nate adds to make compile work

/* -------- ADC_CR : (ADC Offset: 0x00) Control Register -------- */
#define ADC_CR_SWRST (0x1u << 0) /**< \brief (ADC_CR) Software Reset */
#define ADC_CR_START (0x1u << 1) /**< \brief (ADC_CR) Start Conversion */
#define ADC_CR_AUTOCAL (0x1u << 3) /**< \brief (ADC_CR) Automatic Calibration of ADC */
/* -------- ADC_MR : (ADC Offset: 0x04) Mode Register -------- */
#define ADC_MR_TRGEN (0x1u << 0) /**< \brief (ADC_MR) Trigger Enable */
#define   ADC_MR_TRGEN_DIS (0x0u << 0) /**< \brief (ADC_MR) Hardware triggers are disabled. Starting a conversion is only possible by software. */
#define   ADC_MR_TRGEN_EN (0x1u << 0) /**< \brief (ADC_MR) Hardware trigger selected by TRGSEL field is enabled. */
#define ADC_MR_TRGSEL_Pos 1
#define ADC_MR_TRGSEL_Msk (0x7u << ADC_MR_TRGSEL_Pos) /**< \brief (ADC_MR) Trigger Selection */
#define   ADC_MR_TRGSEL_ADC_TRIG0 (0x0u << 1) /**< \brief (ADC_MR) External trigger */
#define   ADC_MR_TRGSEL_ADC_TRIG1 (0x1u << 1) /**< \brief (ADC_MR) TIO Output of the Timer Counter Channel 0 */
#define   ADC_MR_TRGSEL_ADC_TRIG2 (0x2u << 1) /**< \brief (ADC_MR) TIO Output of the Timer Counter Channel 1 */
#define   ADC_MR_TRGSEL_ADC_TRIG3 (0x3u << 1) /**< \brief (ADC_MR) TIO Output of the Timer Counter Channel 2 */
#define   ADC_MR_TRGSEL_ADC_TRIG4 (0x4u << 1) /**< \brief (ADC_MR) PWM Event Line 0 */
#define   ADC_MR_TRGSEL_ADC_TRIG5 (0x5u << 1) /**< \brief (ADC_MR) PWM Event Line 1 */
#define ADC_MR_LOWRES (0x1u << 4) /**< \brief (ADC_MR) Resolution */
#define   ADC_MR_LOWRES_BITS_12 (0x0u << 4) /**< \brief (ADC_MR) 12-bit resolution */
#define   ADC_MR_LOWRES_BITS_10 (0x1u << 4) /**< \brief (ADC_MR) 10-bit resolution */
#define ADC_MR_SLEEP (0x1u << 5) /**< \brief (ADC_MR) Sleep Mode */
#define   ADC_MR_SLEEP_NORMAL (0x0u << 5) /**< \brief (ADC_MR) Normal Mode: The ADC Core and reference voltage circuitry are kept ON between conversions */
#define   ADC_MR_SLEEP_SLEEP (0x1u << 5) /**< \brief (ADC_MR) Sleep Mode: The wake-up time can be modified by programming FWUP bit */
#define ADC_MR_FWUP (0x1u << 6) /**< \brief (ADC_MR) Fast Wake Up */
#define   ADC_MR_FWUP_OFF (0x0u << 6) /**< \brief (ADC_MR) If SLEEP is 1 then both ADC Core and reference voltage circuitry are OFF between conversions */
#define   ADC_MR_FWUP_ON (0x1u << 6) /**< \brief (ADC_MR) If SLEEP is 1 then Fast Wake-up Sleep Mode: The Voltage reference is ON between conversions and ADC Core is OFF */
#define ADC_MR_FREERUN (0x1u << 7) /**< \brief (ADC_MR) Free Run Mode */
#define   ADC_MR_FREERUN_OFF (0x0u << 7) /**< \brief (ADC_MR) Normal Mode */
#define   ADC_MR_FREERUN_ON (0x1u << 7) /**< \brief (ADC_MR) Free Run Mode: Never wait for any trigger. */
#define ADC_MR_PRESCAL_Pos 8
#define ADC_MR_PRESCAL_Msk (0xffu << ADC_MR_PRESCAL_Pos) /**< \brief (ADC_MR) Prescaler Rate Selection */
#define ADC_MR_PRESCAL(value) ((ADC_MR_PRESCAL_Msk & ((value) << ADC_MR_PRESCAL_Pos)))
#define ADC_MR_STARTUP_Pos 16
#define ADC_MR_STARTUP_Msk (0xfu << ADC_MR_STARTUP_Pos) /**< \brief (ADC_MR) Start Up Time */
#define   ADC_MR_STARTUP_SUT0 (0x0u << 16) /**< \brief (ADC_MR) 0 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT8 (0x1u << 16) /**< \brief (ADC_MR) 8 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT16 (0x2u << 16) /**< \brief (ADC_MR) 16 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT24 (0x3u << 16) /**< \brief (ADC_MR) 24 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT64 (0x4u << 16) /**< \brief (ADC_MR) 64 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT80 (0x5u << 16) /**< \brief (ADC_MR) 80 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT96 (0x6u << 16) /**< \brief (ADC_MR) 96 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT112 (0x7u << 16) /**< \brief (ADC_MR) 112 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT512 (0x8u << 16) /**< \brief (ADC_MR) 512 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT576 (0x9u << 16) /**< \brief (ADC_MR) 576 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT640 (0xAu << 16) /**< \brief (ADC_MR) 640 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT704 (0xBu << 16) /**< \brief (ADC_MR) 704 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT768 (0xCu << 16) /**< \brief (ADC_MR) 768 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT832 (0xDu << 16) /**< \brief (ADC_MR) 832 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT896 (0xEu << 16) /**< \brief (ADC_MR) 896 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT960 (0xFu << 16) /**< \brief (ADC_MR) 960 periods of ADCClock */
#define ADC_MR_SETTLING_Pos 20
#define ADC_MR_SETTLING_Msk (0x3u << ADC_MR_SETTLING_Pos) /**< \brief (ADC_MR) Analog Settling Time */
#define   ADC_MR_SETTLING_AST3 (0x0u << 20) /**< \brief (ADC_MR) 3 periods of ADCClock */
#define   ADC_MR_SETTLING_AST5 (0x1u << 20) /**< \brief (ADC_MR) 5 periods of ADCClock */
#define   ADC_MR_SETTLING_AST9 (0x2u << 20) /**< \brief (ADC_MR) 9 periods of ADCClock */
#define   ADC_MR_SETTLING_AST17 (0x3u << 20) /**< \brief (ADC_MR) 17 periods of ADCClock */
#define ADC_MR_ANACH (0x1u << 23) /**< \brief (ADC_MR) Analog Change */
#define   ADC_MR_ANACH_NONE (0x0u << 23) /**< \brief (ADC_MR) No analog change on channel switching: DIFF0, GAIN0 and OFF0 are used for all channels */
#define   ADC_MR_ANACH_ALLOWED (0x1u << 23) /**< \brief (ADC_MR) Allows different analog settings for each channel. See ADC_CGR and ADC_COR Registers */
#define ADC_MR_TRACKTIM_Pos 24
#define ADC_MR_TRACKTIM_Msk (0xfu << ADC_MR_TRACKTIM_Pos) /**< \brief (ADC_MR) Tracking Time */
#define ADC_MR_TRACKTIM(value) ((ADC_MR_TRACKTIM_Msk & ((value) << ADC_MR_TRACKTIM_Pos)))
#define ADC_MR_TRANSFER_Pos 28
#define ADC_MR_TRANSFER_Msk (0x3u << ADC_MR_TRANSFER_Pos) /**< \brief (ADC_MR) Transfer Period */
#define ADC_MR_TRANSFER(value) ((ADC_MR_TRANSFER_Msk & ((value) << ADC_MR_TRANSFER_Pos)))
#define ADC_MR_USEQ (0x1u << 31) /**< \brief (ADC_MR) Use Sequence Enable */
#define   ADC_MR_USEQ_NUM_ORDER (0x0u << 31) /**< \brief (ADC_MR) Normal Mode: The controller converts channels in a simple numeric order depending only on the channel index. */
#define   ADC_MR_USEQ_REG_ORDER (0x1u << 31) /**< \brief (ADC_MR) User Sequence Mode: The sequence respects what is defined in ADC_SEQR1 and ADC_SEQR2 registers and can be used to convert several times the same channel. */
/* -------- ADC_SEQR1 : (ADC Offset: 0x08) Channel Sequence Register 1 -------- */
#define ADC_SEQR1_USCH1_Pos 0
#define ADC_SEQR1_USCH1_Msk (0xfu << ADC_SEQR1_USCH1_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 1 */
#define ADC_SEQR1_USCH1(value) ((ADC_SEQR1_USCH1_Msk & ((value) << ADC_SEQR1_USCH1_Pos)))
#define ADC_SEQR1_USCH2_Pos 4
#define ADC_SEQR1_USCH2_Msk (0xfu << ADC_SEQR1_USCH2_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 2 */
#define ADC_SEQR1_USCH2(value) ((ADC_SEQR1_USCH2_Msk & ((value) << ADC_SEQR1_USCH2_Pos)))
#define ADC_SEQR1_USCH3_Pos 8
#define ADC_SEQR1_USCH3_Msk (0xfu << ADC_SEQR1_USCH3_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 3 */
#define ADC_SEQR1_USCH3(value) ((ADC_SEQR1_USCH3_Msk & ((value) << ADC_SEQR1_USCH3_Pos)))
#define ADC_SEQR1_USCH4_Pos 12
#define ADC_SEQR1_USCH4_Msk (0xfu << ADC_SEQR1_USCH4_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 4 */
#define ADC_SEQR1_USCH4(value) ((ADC_SEQR1_USCH4_Msk & ((value) << ADC_SEQR1_USCH4_Pos)))
#define ADC_SEQR1_USCH5_Pos 16
#define ADC_SEQR1_USCH5_Msk (0xfu << ADC_SEQR1_USCH5_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 5 */
#define ADC_SEQR1_USCH5(value) ((ADC_SEQR1_USCH5_Msk & ((value) << ADC_SEQR1_USCH5_Pos)))
#define ADC_SEQR1_USCH6_Pos 20
#define ADC_SEQR1_USCH6_Msk (0xfu << ADC_SEQR1_USCH6_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 6 */
#define ADC_SEQR1_USCH6(value) ((ADC_SEQR1_USCH6_Msk & ((value) << ADC_SEQR1_USCH6_Pos)))
#define ADC_SEQR1_USCH7_Pos 24
#define ADC_SEQR1_USCH7_Msk (0xfu << ADC_SEQR1_USCH7_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 7 */
#define ADC_SEQR1_USCH7(value) ((ADC_SEQR1_USCH7_Msk & ((value) << ADC_SEQR1_USCH7_Pos)))
#define ADC_SEQR1_USCH8_Pos 28
#define ADC_SEQR1_USCH8_Msk (0xfu << ADC_SEQR1_USCH8_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 8 */
#define ADC_SEQR1_USCH8(value) ((ADC_SEQR1_USCH8_Msk & ((value) << ADC_SEQR1_USCH8_Pos)))
/* -------- ADC_SEQR2 : (ADC Offset: 0x0C) Channel Sequence Register 2 -------- */
#define ADC_SEQR2_USCH9_Pos 0
#define ADC_SEQR2_USCH9_Msk (0xfu << ADC_SEQR2_USCH9_Pos) /**< \brief (ADC_SEQR2) User Sequence Number 9 */
#define ADC_SEQR2_USCH9(value) ((ADC_SEQR2_USCH9_Msk & ((value) << ADC_SEQR2_USCH9_Pos)))
#define ADC_SEQR2_USCH10_Pos 4
#define ADC_SEQR2_USCH10_Msk (0xfu << ADC_SEQR2_USCH10_Pos) /**< \brief (ADC_SEQR2) User Sequence Number 10 */
#define ADC_SEQR2_USCH10(value) ((ADC_SEQR2_USCH10_Msk & ((value) << ADC_SEQR2_USCH10_Pos)))
#define ADC_SEQR2_USCH11_Pos 8
#define ADC_SEQR2_USCH11_Msk (0xfu << ADC_SEQR2_USCH11_Pos) /**< \brief (ADC_SEQR2) User Sequence Number 11 */
#define ADC_SEQR2_USCH11(value) ((ADC_SEQR2_USCH11_Msk & ((value) << ADC_SEQR2_USCH11_Pos)))
#define ADC_SEQR2_USCH12_Pos 12
#define ADC_SEQR2_USCH12_Msk (0xfu << ADC_SEQR2_USCH12_Pos) /**< \brief (ADC_SEQR2) User Sequence Number 12 */
#define ADC_SEQR2_USCH12(value) ((ADC_SEQR2_USCH12_Msk & ((value) << ADC_SEQR2_USCH12_Pos)))
#define ADC_SEQR2_USCH13_Pos 16
#define ADC_SEQR2_USCH13_Msk (0xfu << ADC_SEQR2_USCH13_Pos) /**< \brief (ADC_SEQR2) User Sequence Number 13 */
#define ADC_SEQR2_USCH13(value) ((ADC_SEQR2_USCH13_Msk & ((value) << ADC_SEQR2_USCH13_Pos)))
#define ADC_SEQR2_USCH14_Pos 20
#define ADC_SEQR2_USCH14_Msk (0xfu << ADC_SEQR2_USCH14_Pos) /**< \brief (ADC_SEQR2) User Sequence Number 14 */
#define ADC_SEQR2_USCH14(value) ((ADC_SEQR2_USCH14_Msk & ((value) << ADC_SEQR2_USCH14_Pos)))
#define ADC_SEQR2_USCH15_Pos 24
#define ADC_SEQR2_USCH15_Msk (0xfu << ADC_SEQR2_USCH15_Pos) /**< \brief (ADC_SEQR2) User Sequence Number 15 */
#define ADC_SEQR2_USCH15(value) ((ADC_SEQR2_USCH15_Msk & ((value) << ADC_SEQR2_USCH15_Pos)))
/* -------- ADC_CHER : (ADC Offset: 0x10) Channel Enable Register -------- */
#define ADC_CHER_CH0 (0x1u << 0) /**< \brief (ADC_CHER) Channel 0 Enable */
#define ADC_CHER_CH1 (0x1u << 1) /**< \brief (ADC_CHER) Channel 1 Enable */
#define ADC_CHER_CH2 (0x1u << 2) /**< \brief (ADC_CHER) Channel 2 Enable */
#define ADC_CHER_CH3 (0x1u << 3) /**< \brief (ADC_CHER) Channel 3 Enable */
#define ADC_CHER_CH4 (0x1u << 4) /**< \brief (ADC_CHER) Channel 4 Enable */
#define ADC_CHER_CH5 (0x1u << 5) /**< \brief (ADC_CHER) Channel 5 Enable */
#define ADC_CHER_CH6 (0x1u << 6) /**< \brief (ADC_CHER) Channel 6 Enable */
#define ADC_CHER_CH7 (0x1u << 7) /**< \brief (ADC_CHER) Channel 7 Enable */
#define ADC_CHER_CH8 (0x1u << 8) /**< \brief (ADC_CHER) Channel 8 Enable */
#define ADC_CHER_CH9 (0x1u << 9) /**< \brief (ADC_CHER) Channel 9 Enable */
#define ADC_CHER_CH10 (0x1u << 10) /**< \brief (ADC_CHER) Channel 10 Enable */
#define ADC_CHER_CH11 (0x1u << 11) /**< \brief (ADC_CHER) Channel 11 Enable */
#define ADC_CHER_CH12 (0x1u << 12) /**< \brief (ADC_CHER) Channel 12 Enable */
#define ADC_CHER_CH13 (0x1u << 13) /**< \brief (ADC_CHER) Channel 13 Enable */
#define ADC_CHER_CH14 (0x1u << 14) /**< \brief (ADC_CHER) Channel 14 Enable */
#define ADC_CHER_CH15 (0x1u << 15) /**< \brief (ADC_CHER) Channel 15 Enable */
/* -------- ADC_CHDR : (ADC Offset: 0x14) Channel Disable Register -------- */
#define ADC_CHDR_CH0 (0x1u << 0) /**< \brief (ADC_CHDR) Channel 0 Disable */
#define ADC_CHDR_CH1 (0x1u << 1) /**< \brief (ADC_CHDR) Channel 1 Disable */
#define ADC_CHDR_CH2 (0x1u << 2) /**< \brief (ADC_CHDR) Channel 2 Disable */
#define ADC_CHDR_CH3 (0x1u << 3) /**< \brief (ADC_CHDR) Channel 3 Disable */
#define ADC_CHDR_CH4 (0x1u << 4) /**< \brief (ADC_CHDR) Channel 4 Disable */
#define ADC_CHDR_CH5 (0x1u << 5) /**< \brief (ADC_CHDR) Channel 5 Disable */
#define ADC_CHDR_CH6 (0x1u << 6) /**< \brief (ADC_CHDR) Channel 6 Disable */
#define ADC_CHDR_CH7 (0x1u << 7) /**< \brief (ADC_CHDR) Channel 7 Disable */
#define ADC_CHDR_CH8 (0x1u << 8) /**< \brief (ADC_CHDR) Channel 8 Disable */
#define ADC_CHDR_CH9 (0x1u << 9) /**< \brief (ADC_CHDR) Channel 9 Disable */
#define ADC_CHDR_CH10 (0x1u << 10) /**< \brief (ADC_CHDR) Channel 10 Disable */
#define ADC_CHDR_CH11 (0x1u << 11) /**< \brief (ADC_CHDR) Channel 11 Disable */
#define ADC_CHDR_CH12 (0x1u << 12) /**< \brief (ADC_CHDR) Channel 12 Disable */
#define ADC_CHDR_CH13 (0x1u << 13) /**< \brief (ADC_CHDR) Channel 13 Disable */
#define ADC_CHDR_CH14 (0x1u << 14) /**< \brief (ADC_CHDR) Channel 14 Disable */
#define ADC_CHDR_CH15 (0x1u << 15) /**< \brief (ADC_CHDR) Channel 15 Disable */
/* -------- ADC_CHSR : (ADC Offset: 0x18) Channel Status Register -------- */
#define ADC_CHSR_CH0 (0x1u << 0) /**< \brief (ADC_CHSR) Channel 0 Status */
#define ADC_CHSR_CH1 (0x1u << 1) /**< \brief (ADC_CHSR) Channel 1 Status */
#define ADC_CHSR_CH2 (0x1u << 2) /**< \brief (ADC_CHSR) Channel 2 Status */
#define ADC_CHSR_CH3 (0x1u << 3) /**< \brief (ADC_CHSR) Channel 3 Status */
#define ADC_CHSR_CH4 (0x1u << 4) /**< \brief (ADC_CHSR) Channel 4 Status */
#define ADC_CHSR_CH5 (0x1u << 5) /**< \brief (ADC_CHSR) Channel 5 Status */
#define ADC_CHSR_CH6 (0x1u << 6) /**< \brief (ADC_CHSR) Channel 6 Status */
#define ADC_CHSR_CH7 (0x1u << 7) /**< \brief (ADC_CHSR) Channel 7 Status */
#define ADC_CHSR_CH8 (0x1u << 8) /**< \brief (ADC_CHSR) Channel 8 Status */
#define ADC_CHSR_CH9 (0x1u << 9) /**< \brief (ADC_CHSR) Channel 9 Status */
#define ADC_CHSR_CH10 (0x1u << 10) /**< \brief (ADC_CHSR) Channel 10 Status */
#define ADC_CHSR_CH11 (0x1u << 11) /**< \brief (ADC_CHSR) Channel 11 Status */
#define ADC_CHSR_CH12 (0x1u << 12) /**< \brief (ADC_CHSR) Channel 12 Status */
#define ADC_CHSR_CH13 (0x1u << 13) /**< \brief (ADC_CHSR) Channel 13 Status */
#define ADC_CHSR_CH14 (0x1u << 14) /**< \brief (ADC_CHSR) Channel 14 Status */
#define ADC_CHSR_CH15 (0x1u << 15) /**< \brief (ADC_CHSR) Channel 15 Status */
/* -------- ADC_LCDR : (ADC Offset: 0x20) Last Converted Data Register -------- */
#define ADC_LCDR_LDATA_Pos 0
#define ADC_LCDR_LDATA_Msk (0xfffu << ADC_LCDR_LDATA_Pos) /**< \brief (ADC_LCDR) Last Data Converted */
#define ADC_LCDR_CHNB_Pos 12
#define ADC_LCDR_CHNB_Msk (0xfu << ADC_LCDR_CHNB_Pos) /**< \brief (ADC_LCDR) Channel Number */
/* -------- ADC_IER : (ADC Offset: 0x24) Interrupt Enable Register -------- */
#define ADC_IER_EOC0 (0x1u << 0) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 0 */
#define ADC_IER_EOC1 (0x1u << 1) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 1 */
#define ADC_IER_EOC2 (0x1u << 2) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 2 */
#define ADC_IER_EOC3 (0x1u << 3) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 3 */
#define ADC_IER_EOC4 (0x1u << 4) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 4 */
#define ADC_IER_EOC5 (0x1u << 5) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 5 */
#define ADC_IER_EOC6 (0x1u << 6) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 6 */
#define ADC_IER_EOC7 (0x1u << 7) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 7 */
#define ADC_IER_EOC8 (0x1u << 8) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 8 */
#define ADC_IER_EOC9 (0x1u << 9) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 9 */
#define ADC_IER_EOC10 (0x1u << 10) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 10 */
#define ADC_IER_EOC11 (0x1u << 11) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 11 */
#define ADC_IER_EOC12 (0x1u << 12) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 12 */
#define ADC_IER_EOC13 (0x1u << 13) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 13 */
#define ADC_IER_EOC14 (0x1u << 14) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 14 */
#define ADC_IER_EOC15 (0x1u << 15) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 15 */
#define ADC_IER_EOCAL (0x1u << 23) /**< \brief (ADC_IER) End of Calibration Sequence */
#define ADC_IER_DRDY (0x1u << 24) /**< \brief (ADC_IER) Data Ready Interrupt Enable */
#define ADC_IER_GOVRE (0x1u << 25) /**< \brief (ADC_IER) General Overrun Error Interrupt Enable */
#define ADC_IER_COMPE (0x1u << 26) /**< \brief (ADC_IER) Comparison Event Interrupt Enable */
#define ADC_IER_ENDRX (0x1u << 27) /**< \brief (ADC_IER) End of Receive Buffer Interrupt Enable */
#define ADC_IER_RXBUFF (0x1u << 28) /**< \brief (ADC_IER) Receive Buffer Full Interrupt Enable */
/* -------- ADC_IDR : (ADC Offset: 0x28) Interrupt Disable Register -------- */
#define ADC_IDR_EOC0 (0x1u << 0) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 0 */
#define ADC_IDR_EOC1 (0x1u << 1) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 1 */
#define ADC_IDR_EOC2 (0x1u << 2) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 2 */
#define ADC_IDR_EOC3 (0x1u << 3) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 3 */
#define ADC_IDR_EOC4 (0x1u << 4) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 4 */
#define ADC_IDR_EOC5 (0x1u << 5) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 5 */
#define ADC_IDR_EOC6 (0x1u << 6) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 6 */
#define ADC_IDR_EOC7 (0x1u << 7) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 7 */
#define ADC_IDR_EOC8 (0x1u << 8) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 8 */
#define ADC_IDR_EOC9 (0x1u << 9) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 9 */
#define ADC_IDR_EOC10 (0x1u << 10) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 10 */
#define ADC_IDR_EOC11 (0x1u << 11) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 11 */
#define ADC_IDR_EOC12 (0x1u << 12) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 12 */
#define ADC_IDR_EOC13 (0x1u << 13) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 13 */
#define ADC_IDR_EOC14 (0x1u << 14) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 14 */
#define ADC_IDR_EOC15 (0x1u << 15) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 15 */
#define ADC_IDR_EOCAL (0x1u << 23) /**< \brief (ADC_IDR) End of Calibration Sequence */
#define ADC_IDR_DRDY (0x1u << 24) /**< \brief (ADC_IDR) Data Ready Interrupt Disable */
#define ADC_IDR_GOVRE (0x1u << 25) /**< \brief (ADC_IDR) General Overrun Error Interrupt Disable */
#define ADC_IDR_COMPE (0x1u << 26) /**< \brief (ADC_IDR) Comparison Event Interrupt Disable */
#define ADC_IDR_ENDRX (0x1u << 27) /**< \brief (ADC_IDR) End of Receive Buffer Interrupt Disable */
#define ADC_IDR_RXBUFF (0x1u << 28) /**< \brief (ADC_IDR) Receive Buffer Full Interrupt Disable */
/* -------- ADC_IMR : (ADC Offset: 0x2C) Interrupt Mask Register -------- */
#define ADC_IMR_EOC0 (0x1u << 0) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 0 */
#define ADC_IMR_EOC1 (0x1u << 1) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 1 */
#define ADC_IMR_EOC2 (0x1u << 2) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 2 */
#define ADC_IMR_EOC3 (0x1u << 3) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 3 */
#define ADC_IMR_EOC4 (0x1u << 4) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 4 */
#define ADC_IMR_EOC5 (0x1u << 5) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 5 */
#define ADC_IMR_EOC6 (0x1u << 6) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 6 */
#define ADC_IMR_EOC7 (0x1u << 7) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 7 */
#define ADC_IMR_EOC8 (0x1u << 8) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 8 */
#define ADC_IMR_EOC9 (0x1u << 9) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 9 */
#define ADC_IMR_EOC10 (0x1u << 10) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 10 */
#define ADC_IMR_EOC11 (0x1u << 11) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 11 */
#define ADC_IMR_EOC12 (0x1u << 12) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 12 */
#define ADC_IMR_EOC13 (0x1u << 13) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 13 */
#define ADC_IMR_EOC14 (0x1u << 14) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 14 */
#define ADC_IMR_EOC15 (0x1u << 15) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 15 */
#define ADC_IMR_EOCAL (0x1u << 23) /**< \brief (ADC_IMR) End of Calibration Sequence */
#define ADC_IMR_DRDY (0x1u << 24) /**< \brief (ADC_IMR) Data Ready Interrupt Mask */
#define ADC_IMR_GOVRE (0x1u << 25) /**< \brief (ADC_IMR) General Overrun Error Interrupt Mask */
#define ADC_IMR_COMPE (0x1u << 26) /**< \brief (ADC_IMR) Comparison Event Interrupt Mask */
#define ADC_IMR_ENDRX (0x1u << 27) /**< \brief (ADC_IMR) End of Receive Buffer Interrupt Mask */
#define ADC_IMR_RXBUFF (0x1u << 28) /**< \brief (ADC_IMR) Receive Buffer Full Interrupt Mask */
/* -------- ADC_ISR : (ADC Offset: 0x30) Interrupt Status Register -------- */
#define ADC_ISR_EOC0 (0x1u << 0) /**< \brief (ADC_ISR) End of Conversion 0 */
#define ADC_ISR_EOC1 (0x1u << 1) /**< \brief (ADC_ISR) End of Conversion 1 */
#define ADC_ISR_EOC2 (0x1u << 2) /**< \brief (ADC_ISR) End of Conversion 2 */
#define ADC_ISR_EOC3 (0x1u << 3) /**< \brief (ADC_ISR) End of Conversion 3 */
#define ADC_ISR_EOC4 (0x1u << 4) /**< \brief (ADC_ISR) End of Conversion 4 */
#define ADC_ISR_EOC5 (0x1u << 5) /**< \brief (ADC_ISR) End of Conversion 5 */
#define ADC_ISR_EOC6 (0x1u << 6) /**< \brief (ADC_ISR) End of Conversion 6 */
#define ADC_ISR_EOC7 (0x1u << 7) /**< \brief (ADC_ISR) End of Conversion 7 */
#define ADC_ISR_EOC8 (0x1u << 8) /**< \brief (ADC_ISR) End of Conversion 8 */
#define ADC_ISR_EOC9 (0x1u << 9) /**< \brief (ADC_ISR) End of Conversion 9 */
#define ADC_ISR_EOC10 (0x1u << 10) /**< \brief (ADC_ISR) End of Conversion 10 */
#define ADC_ISR_EOC11 (0x1u << 11) /**< \brief (ADC_ISR) End of Conversion 11 */
#define ADC_ISR_EOC12 (0x1u << 12) /**< \brief (ADC_ISR) End of Conversion 12 */
#define ADC_ISR_EOC13 (0x1u << 13) /**< \brief (ADC_ISR) End of Conversion 13 */
#define ADC_ISR_EOC14 (0x1u << 14) /**< \brief (ADC_ISR) End of Conversion 14 */
#define ADC_ISR_EOC15 (0x1u << 15) /**< \brief (ADC_ISR) End of Conversion 15 */
#define ADC_ISR_EOCAL (0x1u << 23) /**< \brief (ADC_ISR) End of Calibration Sequence */
#define ADC_ISR_DRDY (0x1u << 24) /**< \brief (ADC_ISR) Data Ready */
#define ADC_ISR_GOVRE (0x1u << 25) /**< \brief (ADC_ISR) General Overrun Error */
#define ADC_ISR_COMPE (0x1u << 26) /**< \brief (ADC_ISR) Comparison Error */
#define ADC_ISR_ENDRX (0x1u << 27) /**< \brief (ADC_ISR) End of RX Buffer */
#define ADC_ISR_RXBUFF (0x1u << 28) /**< \brief (ADC_ISR) RX Buffer Full */
/* -------- ADC_OVER : (ADC Offset: 0x3C) Overrun Status Register -------- */
#define ADC_OVER_OVRE0 (0x1u << 0) /**< \brief (ADC_OVER) Overrun Error 0 */
#define ADC_OVER_OVRE1 (0x1u << 1) /**< \brief (ADC_OVER) Overrun Error 1 */
#define ADC_OVER_OVRE2 (0x1u << 2) /**< \brief (ADC_OVER) Overrun Error 2 */
#define ADC_OVER_OVRE3 (0x1u << 3) /**< \brief (ADC_OVER) Overrun Error 3 */
#define ADC_OVER_OVRE4 (0x1u << 4) /**< \brief (ADC_OVER) Overrun Error 4 */
#define ADC_OVER_OVRE5 (0x1u << 5) /**< \brief (ADC_OVER) Overrun Error 5 */
#define ADC_OVER_OVRE6 (0x1u << 6) /**< \brief (ADC_OVER) Overrun Error 6 */
#define ADC_OVER_OVRE7 (0x1u << 7) /**< \brief (ADC_OVER) Overrun Error 7 */
#define ADC_OVER_OVRE8 (0x1u << 8) /**< \brief (ADC_OVER) Overrun Error 8 */
#define ADC_OVER_OVRE9 (0x1u << 9) /**< \brief (ADC_OVER) Overrun Error 9 */
#define ADC_OVER_OVRE10 (0x1u << 10) /**< \brief (ADC_OVER) Overrun Error 10 */
#define ADC_OVER_OVRE11 (0x1u << 11) /**< \brief (ADC_OVER) Overrun Error 11 */
#define ADC_OVER_OVRE12 (0x1u << 12) /**< \brief (ADC_OVER) Overrun Error 12 */
#define ADC_OVER_OVRE13 (0x1u << 13) /**< \brief (ADC_OVER) Overrun Error 13 */
#define ADC_OVER_OVRE14 (0x1u << 14) /**< \brief (ADC_OVER) Overrun Error 14 */
#define ADC_OVER_OVRE15 (0x1u << 15) /**< \brief (ADC_OVER) Overrun Error 15 */
/* -------- ADC_EMR : (ADC Offset: 0x40) Extended Mode Register -------- */
#define ADC_EMR_CMPMODE_Pos 0
#define ADC_EMR_CMPMODE_Msk (0x3u << ADC_EMR_CMPMODE_Pos) /**< \brief (ADC_EMR) Comparison Mode */
#define   ADC_EMR_CMPMODE_LOW (0x0u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is lower than the low threshold of the window. */
#define   ADC_EMR_CMPMODE_HIGH (0x1u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is higher than the high threshold of the window. */
#define   ADC_EMR_CMPMODE_IN (0x2u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is in the comparison window. */
#define   ADC_EMR_CMPMODE_OUT (0x3u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is out of the comparison window. */
#define ADC_EMR_CMPSEL_Pos 4
#define ADC_EMR_CMPSEL_Msk (0xfu << ADC_EMR_CMPSEL_Pos) /**< \brief (ADC_EMR) Comparison Selected Channel */
#define ADC_EMR_CMPSEL(value) ((ADC_EMR_CMPSEL_Msk & ((value) << ADC_EMR_CMPSEL_Pos)))
#define ADC_EMR_CMPALL (0x1u << 9) /**< \brief (ADC_EMR) Compare All Channels */
#define ADC_EMR_TAG (0x1u << 24) /**< \brief (ADC_EMR) TAG of the ADC_LDCR register */
/* -------- ADC_CWR : (ADC Offset: 0x44) Compare Window Register -------- */
#define ADC_CWR_LOWTHRES_Pos 0
#define ADC_CWR_LOWTHRES_Msk (0xfffu << ADC_CWR_LOWTHRES_Pos) /**< \brief (ADC_CWR) Low Threshold */
#define ADC_CWR_LOWTHRES(value) ((ADC_CWR_LOWTHRES_Msk & ((value) << ADC_CWR_LOWTHRES_Pos)))
#define ADC_CWR_HIGHTHRES_Pos 16
#define ADC_CWR_HIGHTHRES_Msk (0xfffu << ADC_CWR_HIGHTHRES_Pos) /**< \brief (ADC_CWR) High Threshold */
#define ADC_CWR_HIGHTHRES(value) ((ADC_CWR_HIGHTHRES_Msk & ((value) << ADC_CWR_HIGHTHRES_Pos)))
/* -------- ADC_CGR : (ADC Offset: 0x48) Channel Gain Register -------- */
#define ADC_CGR_GAIN0_Pos 0
#define ADC_CGR_GAIN0_Msk (0x3u << ADC_CGR_GAIN0_Pos) /**< \brief (ADC_CGR) Gain for Channel 0 */
#define ADC_CGR_GAIN0(value) ((ADC_CGR_GAIN0_Msk & ((value) << ADC_CGR_GAIN0_Pos)))
#define ADC_CGR_GAIN1_Pos 2
#define ADC_CGR_GAIN1_Msk (0x3u << ADC_CGR_GAIN1_Pos) /**< \brief (ADC_CGR) Gain for Channel 1 */
#define ADC_CGR_GAIN1(value) ((ADC_CGR_GAIN1_Msk & ((value) << ADC_CGR_GAIN1_Pos)))
#define ADC_CGR_GAIN2_Pos 4
#define ADC_CGR_GAIN2_Msk (0x3u << ADC_CGR_GAIN2_Pos) /**< \brief (ADC_CGR) Gain for Channel 2 */
#define ADC_CGR_GAIN2(value) ((ADC_CGR_GAIN2_Msk & ((value) << ADC_CGR_GAIN2_Pos)))
#define ADC_CGR_GAIN3_Pos 6
#define ADC_CGR_GAIN3_Msk (0x3u << ADC_CGR_GAIN3_Pos) /**< \brief (ADC_CGR) Gain for Channel 3 */
#define ADC_CGR_GAIN3(value) ((ADC_CGR_GAIN3_Msk & ((value) << ADC_CGR_GAIN3_Pos)))
#define ADC_CGR_GAIN4_Pos 8
#define ADC_CGR_GAIN4_Msk (0x3u << ADC_CGR_GAIN4_Pos) /**< \brief (ADC_CGR) Gain for Channel 4 */
#define ADC_CGR_GAIN4(value) ((ADC_CGR_GAIN4_Msk & ((value) << ADC_CGR_GAIN4_Pos)))
#define ADC_CGR_GAIN5_Pos 10
#define ADC_CGR_GAIN5_Msk (0x3u << ADC_CGR_GAIN5_Pos) /**< \brief (ADC_CGR) Gain for Channel 5 */
#define ADC_CGR_GAIN5(value) ((ADC_CGR_GAIN5_Msk & ((value) << ADC_CGR_GAIN5_Pos)))
#define ADC_CGR_GAIN6_Pos 12
#define ADC_CGR_GAIN6_Msk (0x3u << ADC_CGR_GAIN6_Pos) /**< \brief (ADC_CGR) Gain for Channel 6 */
#define ADC_CGR_GAIN6(value) ((ADC_CGR_GAIN6_Msk & ((value) << ADC_CGR_GAIN6_Pos)))
#define ADC_CGR_GAIN7_Pos 14
#define ADC_CGR_GAIN7_Msk (0x3u << ADC_CGR_GAIN7_Pos) /**< \brief (ADC_CGR) Gain for Channel 7 */
#define ADC_CGR_GAIN7(value) ((ADC_CGR_GAIN7_Msk & ((value) << ADC_CGR_GAIN7_Pos)))
#define ADC_CGR_GAIN8_Pos 16
#define ADC_CGR_GAIN8_Msk (0x3u << ADC_CGR_GAIN8_Pos) /**< \brief (ADC_CGR) Gain for Channel 8 */
#define ADC_CGR_GAIN8(value) ((ADC_CGR_GAIN8_Msk & ((value) << ADC_CGR_GAIN8_Pos)))
#define ADC_CGR_GAIN9_Pos 18
#define ADC_CGR_GAIN9_Msk (0x3u << ADC_CGR_GAIN9_Pos) /**< \brief (ADC_CGR) Gain for Channel 9 */
#define ADC_CGR_GAIN9(value) ((ADC_CGR_GAIN9_Msk & ((value) << ADC_CGR_GAIN9_Pos)))
#define ADC_CGR_GAIN10_Pos 20
#define ADC_CGR_GAIN10_Msk (0x3u << ADC_CGR_GAIN10_Pos) /**< \brief (ADC_CGR) Gain for Channel 10 */
#define ADC_CGR_GAIN10(value) ((ADC_CGR_GAIN10_Msk & ((value) << ADC_CGR_GAIN10_Pos)))
#define ADC_CGR_GAIN11_Pos 22
#define ADC_CGR_GAIN11_Msk (0x3u << ADC_CGR_GAIN11_Pos) /**< \brief (ADC_CGR) Gain for Channel 11 */
#define ADC_CGR_GAIN11(value) ((ADC_CGR_GAIN11_Msk & ((value) << ADC_CGR_GAIN11_Pos)))
#define ADC_CGR_GAIN12_Pos 24
#define ADC_CGR_GAIN12_Msk (0x3u << ADC_CGR_GAIN12_Pos) /**< \brief (ADC_CGR) Gain for Channel 12 */
#define ADC_CGR_GAIN12(value) ((ADC_CGR_GAIN12_Msk & ((value) << ADC_CGR_GAIN12_Pos)))
#define ADC_CGR_GAIN13_Pos 26
#define ADC_CGR_GAIN13_Msk (0x3u << ADC_CGR_GAIN13_Pos) /**< \brief (ADC_CGR) Gain for Channel 13 */
#define ADC_CGR_GAIN13(value) ((ADC_CGR_GAIN13_Msk & ((value) << ADC_CGR_GAIN13_Pos)))
#define ADC_CGR_GAIN14_Pos 28
#define ADC_CGR_GAIN14_Msk (0x3u << ADC_CGR_GAIN14_Pos) /**< \brief (ADC_CGR) Gain for Channel 14 */
#define ADC_CGR_GAIN14(value) ((ADC_CGR_GAIN14_Msk & ((value) << ADC_CGR_GAIN14_Pos)))
#define ADC_CGR_GAIN15_Pos 30
#define ADC_CGR_GAIN15_Msk (0x3u << ADC_CGR_GAIN15_Pos) /**< \brief (ADC_CGR) Gain for Channel 15 */
#define ADC_CGR_GAIN15(value) ((ADC_CGR_GAIN15_Msk & ((value) << ADC_CGR_GAIN15_Pos)))
/* -------- ADC_COR : (ADC Offset: 0x4C) Channel Offset Register -------- */
#define ADC_COR_OFF0 (0x1u << 0) /**< \brief (ADC_COR) Offset for channel 0 */
#define ADC_COR_OFF1 (0x1u << 1) /**< \brief (ADC_COR) Offset for channel 1 */
#define ADC_COR_OFF2 (0x1u << 2) /**< \brief (ADC_COR) Offset for channel 2 */
#define ADC_COR_OFF3 (0x1u << 3) /**< \brief (ADC_COR) Offset for channel 3 */
#define ADC_COR_OFF4 (0x1u << 4) /**< \brief (ADC_COR) Offset for channel 4 */
#define ADC_COR_OFF5 (0x1u << 5) /**< \brief (ADC_COR) Offset for channel 5 */
#define ADC_COR_OFF6 (0x1u << 6) /**< \brief (ADC_COR) Offset for channel 6 */
#define ADC_COR_OFF7 (0x1u << 7) /**< \brief (ADC_COR) Offset for channel 7 */
#define ADC_COR_OFF8 (0x1u << 8) /**< \brief (ADC_COR) Offset for channel 8 */
#define ADC_COR_OFF9 (0x1u << 9) /**< \brief (ADC_COR) Offset for channel 9 */
#define ADC_COR_OFF10 (0x1u << 10) /**< \brief (ADC_COR) Offset for channel 10 */
#define ADC_COR_OFF11 (0x1u << 11) /**< \brief (ADC_COR) Offset for channel 11 */
#define ADC_COR_OFF12 (0x1u << 12) /**< \brief (ADC_COR) Offset for channel 12 */
#define ADC_COR_OFF13 (0x1u << 13) /**< \brief (ADC_COR) Offset for channel 13 */
#define ADC_COR_OFF14 (0x1u << 14) /**< \brief (ADC_COR) Offset for channel 14 */
#define ADC_COR_OFF15 (0x1u << 15) /**< \brief (ADC_COR) Offset for channel 15 */
#define ADC_COR_DIFF0 (0x1u << 16) /**< \brief (ADC_COR) Differential inputs for channel 0 */
#define ADC_COR_DIFF1 (0x1u << 17) /**< \brief (ADC_COR) Differential inputs for channel 1 */
#define ADC_COR_DIFF2 (0x1u << 18) /**< \brief (ADC_COR) Differential inputs for channel 2 */
#define ADC_COR_DIFF3 (0x1u << 19) /**< \brief (ADC_COR) Differential inputs for channel 3 */
#define ADC_COR_DIFF4 (0x1u << 20) /**< \brief (ADC_COR) Differential inputs for channel 4 */
#define ADC_COR_DIFF5 (0x1u << 21) /**< \brief (ADC_COR) Differential inputs for channel 5 */
#define ADC_COR_DIFF6 (0x1u << 22) /**< \brief (ADC_COR) Differential inputs for channel 6 */
#define ADC_COR_DIFF7 (0x1u << 23) /**< \brief (ADC_COR) Differential inputs for channel 7 */
#define ADC_COR_DIFF8 (0x1u << 24) /**< \brief (ADC_COR) Differential inputs for channel 8 */
#define ADC_COR_DIFF9 (0x1u << 25) /**< \brief (ADC_COR) Differential inputs for channel 9 */
#define ADC_COR_DIFF10 (0x1u << 26) /**< \brief (ADC_COR) Differential inputs for channel 10 */
#define ADC_COR_DIFF11 (0x1u << 27) /**< \brief (ADC_COR) Differential inputs for channel 11 */
#define ADC_COR_DIFF12 (0x1u << 28) /**< \brief (ADC_COR) Differential inputs for channel 12 */
#define ADC_COR_DIFF13 (0x1u << 29) /**< \brief (ADC_COR) Differential inputs for channel 13 */
#define ADC_COR_DIFF14 (0x1u << 30) /**< \brief (ADC_COR) Differential inputs for channel 14 */
#define ADC_COR_DIFF15 (0x1u << 31) /**< \brief (ADC_COR) Differential inputs for channel 15 */
/* -------- ADC_CDR[16] : (ADC Offset: 0x50) Channel Data Register -------- */
#define ADC_CDR_DATA_Pos 0
#define ADC_CDR_DATA_Msk (0xfffu << ADC_CDR_DATA_Pos) /**< \brief (ADC_CDR[16]) Converted Data */
/* -------- ADC_ACR : (ADC Offset: 0x94) Analog Control Register -------- */
#define ADC_ACR_TSON (0x1u << 4) /**< \brief (ADC_ACR) Temperature Sensor On */
#define ADC_ACR_IBCTL_Pos 8
#define ADC_ACR_IBCTL_Msk (0x3u << ADC_ACR_IBCTL_Pos) /**< \brief (ADC_ACR) ADC Bias Current Control */
#define ADC_ACR_IBCTL(value) ((ADC_ACR_IBCTL_Msk & ((value) << ADC_ACR_IBCTL_Pos)))
/* -------- ADC_WPMR : (ADC Offset: 0xE4) Write Protect Mode Register -------- */
#define ADC_WPMR_WPEN (0x1u << 0) /**< \brief (ADC_WPMR) Write Protect Enable */
#define ADC_WPMR_WPKEY_Pos 8
#define ADC_WPMR_WPKEY_Msk (0xffffffu << ADC_WPMR_WPKEY_Pos) /**< \brief (ADC_WPMR) Write Protect KEY */
#define   ADC_WPMR_WPKEY_PASSWD (0x414443u << 8) /**< \brief (ADC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0 */
/* -------- ADC_WPSR : (ADC Offset: 0xE8) Write Protect Status Register -------- */
#define ADC_WPSR_WPVS (0x1u << 0) /**< \brief (ADC_WPSR) Write Protect Violation Status */
#define ADC_WPSR_WPVSRC_Pos 8
#define ADC_WPSR_WPVSRC_Msk (0xffffu << ADC_WPSR_WPVSRC_Pos) /**< \brief (ADC_WPSR) Write Protect Violation Source */
/* -------- ADC_RPR : (ADC Offset: 0x100) Receive Pointer Register -------- */
#define ADC_RPR_RXPTR_Pos 0
#define ADC_RPR_RXPTR_Msk (0xffffffffu << ADC_RPR_RXPTR_Pos) /**< \brief (ADC_RPR) Receive Pointer Register */
#define ADC_RPR_RXPTR(value) ((ADC_RPR_RXPTR_Msk & ((value) << ADC_RPR_RXPTR_Pos)))
/* -------- ADC_RCR : (ADC Offset: 0x104) Receive Counter Register -------- */
#define ADC_RCR_RXCTR_Pos 0
#define ADC_RCR_RXCTR_Msk (0xffffu << ADC_RCR_RXCTR_Pos) /**< \brief (ADC_RCR) Receive Counter Register */
#define ADC_RCR_RXCTR(value) ((ADC_RCR_RXCTR_Msk & ((value) << ADC_RCR_RXCTR_Pos)))
/* -------- ADC_RNPR : (ADC Offset: 0x110) Receive Next Pointer Register -------- */
#define ADC_RNPR_RXNPTR_Pos 0
#define ADC_RNPR_RXNPTR_Msk (0xffffffffu << ADC_RNPR_RXNPTR_Pos) /**< \brief (ADC_RNPR) Receive Next Pointer */
#define ADC_RNPR_RXNPTR(value) ((ADC_RNPR_RXNPTR_Msk & ((value) << ADC_RNPR_RXNPTR_Pos)))
/* -------- ADC_RNCR : (ADC Offset: 0x114) Receive Next Counter Register -------- */
#define ADC_RNCR_RXNCTR_Pos 0
#define ADC_RNCR_RXNCTR_Msk (0xffffu << ADC_RNCR_RXNCTR_Pos) /**< \brief (ADC_RNCR) Receive Next Counter */
#define ADC_RNCR_RXNCTR(value) ((ADC_RNCR_RXNCTR_Msk & ((value) << ADC_RNCR_RXNCTR_Pos)))
/* -------- ADC_PTCR : (ADC Offset: 0x120) Transfer Control Register -------- */
#define ADC_PTCR_RXTEN (0x1u << 0) /**< \brief (ADC_PTCR) Receiver Transfer Enable */
#define ADC_PTCR_RXTDIS (0x1u << 1) /**< \brief (ADC_PTCR) Receiver Transfer Disable */
#define ADC_PTCR_TXTEN (0x1u << 8) /**< \brief (ADC_PTCR) Transmitter Transfer Enable */
#define ADC_PTCR_TXTDIS (0x1u << 9) /**< \brief (ADC_PTCR) Transmitter Transfer Disable */
/* -------- ADC_PTSR : (ADC Offset: 0x124) Transfer Status Register -------- */
#define ADC_PTSR_RXTEN (0x1u << 0) /**< \brief (ADC_PTSR) Receiver Transfer Enable */
#define ADC_PTSR_TXTEN (0x1u << 8) /**< \brief (ADC_PTSR) Transmitter Transfer Enable */

/*@}*/

/* The max ADC clock freq definition*/
#if !SAM4C && !SAM4CP && !SAM4CM
#define ADC_FREQ_MAX   20000000
#else
#define ADC_FREQ_MAX   16000000
#endif
/* The min ADC clock freq definition*/
#define ADC_FREQ_MIN    1000000
/* The normal ADC startup time*/
#define ADC_STARTUP_NORM     40
/* The fast ADC startup time*/
#define ADC_STARTUP_FAST     12

/* Definitions for ADC resolution */
#if SAM3S || SAM4S || SAM3XA
enum adc_resolution_t {
	ADC_10_BITS = ADC_MR_LOWRES_BITS_10,    /* ADC 10-bit resolution */
	ADC_12_BITS = ADC_MR_LOWRES_BITS_12     /* ADC 12-bit resolution */
};
#elif SAM3N
enum adc_resolution_t {
	ADC_8_BITS = ADC_MR_LOWRES_BITS_8,      /* ADC 8-bit resolution */
	ADC_10_BITS = ADC_MR_LOWRES_BITS_10     /* ADC 10-bit resolution */
};
#elif SAM3U
enum adc_resolution_t {
	ADC_8_BITS = ADC_MR_LOWRES_BITS_8,      /* ADC 8-bit resolution */
	ADC_10_BITS = ADC12B_MR_LOWRES_BITS_10, /* ADC 10-bit resolution */
	ADC_12_BITS = ADC12B_MR_LOWRES_BITS_12  /* ADC 12-bit resolution */
};
#elif SAM4C || SAM4CP || SAM4CM
enum adc_resolution_t {
	ADC_8_BITS  = ADC_MR_LOWRES_BITS_8,  /* ADC 8-bit resolution */
	ADC_10_BITS = ADC_MR_LOWRES_BITS_10, /* ADC 10-bit resolution */
	ADC_11_BITS = ADC_EMR_OSR_OSR4,      /* ADC 11-bit resolution */
	ADC_12_BITS = ADC_EMR_OSR_OSR16      /* ADC 12-bit resolution */
};
#endif

/* Definitions for ADC trigger */
enum adc_trigger_t {
	/* Starting a conversion is only possible by software. */
	ADC_TRIG_SW = ADC_MR_TRGEN_DIS,
	/* External trigger */
	ADC_TRIG_EXT = ADC_MR_TRGSEL_ADC_TRIG0 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 0 */
	ADC_TRIG_TIO_CH_0 = ADC_MR_TRGSEL_ADC_TRIG1 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 1 */
	ADC_TRIG_TIO_CH_1 = ADC_MR_TRGSEL_ADC_TRIG2 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 2 */
	ADC_TRIG_TIO_CH_2 = ADC_MR_TRGSEL_ADC_TRIG3 | ADC_MR_TRGEN,
#if SAM4C || SAM4CP || SAM4CM
	/* TIO Output of the Timer Counter Channel 3 */
	ADC_TRIG_TIO_CH_3 = ADC_MR_TRGSEL_ADC_TRIG3 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 4 */
	ADC_TRIG_TIO_CH_4 = ADC_MR_TRGSEL_ADC_TRIG4 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 5 */
	ADC_TRIG_TIO_CH_5 = ADC_MR_TRGSEL_ADC_TRIG5 | ADC_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 6 */
	ADC_TRIG_TIO_CH_6 = ADC_MR_TRGSEL_ADC_TRIG6 | ADC_MR_TRGEN,
#endif
#if SAM3S || SAM4S || SAM3XA || SAM3U
	/* PWM Event Line 0 */
	ADC_TRIG_PWM_EVENT_LINE_0 = ADC_MR_TRGSEL_ADC_TRIG4 | ADC_MR_TRGEN,
	/* PWM Event Line 1 */
	ADC_TRIG_PWM_EVENT_LINE_1 = ADC_MR_TRGSEL_ADC_TRIG5 | ADC_MR_TRGEN
#endif
};

#if SAM3U
/* Definitions for ADC trigger */
enum adc12b_trigger_t {
	/* Starting a conversion is only possible by software. */
	ADC12B_TRIG_SW = ADC12B_MR_TRGEN_DIS,
	/* External trigger */
	ADC12B_TRIG_EXT = ADC12B_MR_TRGSEL_ADC_TRIG0 | ADC12B_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 0 */
	ADC12B_TRIG_TIO_CH_0 = ADC12B_MR_TRGSEL_ADC_TRIG1 | ADC12B_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 1 */
	ADC12B_TRIG_TIO_CH_1 = ADC12B_MR_TRGSEL_ADC_TRIG2 | ADC12B_MR_TRGEN,
	/* TIO Output of the Timer Counter Channel 2 */
	ADC12B_TRIG_TIO_CH_2 = ADC12B_MR_TRGSEL_ADC_TRIG3 | ADC12B_MR_TRGEN,
	/* PWM Event Line 0 */
	ADC12B_TRIG_PWM_EVENT_LINE_0 = ADC12B_MR_TRGSEL_ADC_TRIG4 | ADC12B_MR_TRGEN,
	/* PWM Event Line 1 */
	ADC12B_TRIG_PWM_EVENT_LINE_1 = ADC12B_MR_TRGSEL_ADC_TRIG5 | ADC12B_MR_TRGEN
};
#endif

#if SAM3S || SAM4S ||  SAM3N || SAM3XA || SAM4C || SAM4CP || SAM4CM
/* Definitions for ADC channel number */
enum adc_channel_num_t {
	ADC_CHANNEL_0  = 0,
	ADC_CHANNEL_1  = 1,
	ADC_CHANNEL_2  = 2,
	ADC_CHANNEL_3  = 3,
	ADC_CHANNEL_4  = 4,
	ADC_CHANNEL_5  = 5,
	ADC_CHANNEL_6  = 6,
#if SAM4C || SAM4CP || SAM4CM
	ADC_TEMPERATURE_SENSOR = 7,
#else
	ADC_CHANNEL_7  = 7,
	ADC_CHANNEL_8  = 8,
	ADC_CHANNEL_9  = 9,
	ADC_CHANNEL_10 = 10,
	ADC_CHANNEL_11 = 11,
	ADC_CHANNEL_12 = 12,
	ADC_CHANNEL_13 = 13,
	ADC_CHANNEL_14 = 14,
	ADC_TEMPERATURE_SENSOR = 15,
#endif
};
#elif SAM3U
/* Definitions for ADC channel number */
enum adc_channel_num_t {
	ADC_CHANNEL_0  = 0,
	ADC_CHANNEL_1  = 1,
	ADC_CHANNEL_2  = 2,
	ADC_CHANNEL_3  = 3,
	ADC_CHANNEL_4  = 4,
	ADC_CHANNEL_5  = 5,
	ADC_CHANNEL_6  = 6,
	ADC_CHANNEL_7  = 7,
};
#endif
#if !SAM4C && !SAM4CP && !SAM4CM
/* Definitions for ADC gain value */
enum adc_gainvalue_t {
	ADC_GAINVALUE_0 = 0,
	ADC_GAINVALUE_1 = 1,
	ADC_GAINVALUE_2 = 2,
	ADC_GAINVALUE_3 = 3
};
#endif
/* Definitions for ADC analog settling time */
#if SAM3S || SAM4S ||  SAM3XA
enum adc_settling_time_t {
	ADC_SETTLING_TIME_0 = ADC_MR_SETTLING_AST3,
	ADC_SETTLING_TIME_1 = ADC_MR_SETTLING_AST5,
	ADC_SETTLING_TIME_2 = ADC_MR_SETTLING_AST9,
	ADC_SETTLING_TIME_3 = ADC_MR_SETTLING_AST17
};
#endif

#if SAM3S || SAM4S ||  SAM3N || SAM3XA || SAM4C || SAM4CP || SAM4CM
/** Definitions for ADC Start Up Time */
enum adc_startup_time {
	ADC_STARTUP_TIME_0 = ADC_MR_STARTUP_SUT0,
	ADC_STARTUP_TIME_1 = ADC_MR_STARTUP_SUT8,
	ADC_STARTUP_TIME_2 = ADC_MR_STARTUP_SUT16,
	ADC_STARTUP_TIME_3 = ADC_MR_STARTUP_SUT24,
	ADC_STARTUP_TIME_4 = ADC_MR_STARTUP_SUT64,
	ADC_STARTUP_TIME_5 = ADC_MR_STARTUP_SUT80,
	ADC_STARTUP_TIME_6 = ADC_MR_STARTUP_SUT96,
	ADC_STARTUP_TIME_7 = ADC_MR_STARTUP_SUT112,
	ADC_STARTUP_TIME_8 = ADC_MR_STARTUP_SUT512,
	ADC_STARTUP_TIME_9 = ADC_MR_STARTUP_SUT576,
	ADC_STARTUP_TIME_10 = ADC_MR_STARTUP_SUT640,
	ADC_STARTUP_TIME_11 = ADC_MR_STARTUP_SUT704,
	ADC_STARTUP_TIME_12 = ADC_MR_STARTUP_SUT768,
	ADC_STARTUP_TIME_13 = ADC_MR_STARTUP_SUT832,
	ADC_STARTUP_TIME_14 = ADC_MR_STARTUP_SUT896,
	ADC_STARTUP_TIME_15 = ADC_MR_STARTUP_SUT960
};
#endif

#if SAM3S || SAM4S ||  SAM3N || SAM3XA || SAM4C || SAM4CP || SAM4CM
uint32_t adc_init(Adc *p_adc, const uint32_t ul_mck,
		const uint32_t ul_adc_clock, const enum adc_startup_time startup);
void adc_configure_trigger(Adc *p_adc, const enum adc_trigger_t trigger,
		const uint8_t uc_freerun);
void adc_configure_sequence(Adc *p_adc, const enum adc_channel_num_t ch_list[],
		const uint8_t uc_num);
void adc_enable_tag(Adc *p_adc);
void adc_disable_tag(Adc *p_adc);
enum adc_channel_num_t adc_get_tag(const Adc *p_adc);
void adc_start_sequencer(Adc *p_adc);
void adc_stop_sequencer(Adc *p_adc);
void adc_set_comparison_mode(Adc *p_adc, const uint8_t uc_mode);
#if SAM4C || SAM4CP || SAM4CM
void adc_set_comparison_filter(Adc *p_adc, uint8_t filter);
#endif
uint32_t adc_get_comparison_mode(const Adc *p_adc);
void adc_set_comparison_window(Adc *p_adc, const uint16_t us_low_threshold,
		const uint16_t us_high_threshold);
void adc_set_comparison_channel(Adc *p_adc,
		const enum adc_channel_num_t channel);
void adc_set_writeprotect(Adc *p_adc, const uint32_t ul_enable);
uint32_t adc_get_writeprotect_status(const Adc *p_adc);
void adc_check(Adc* p_adc, const uint32_t ul_mck);
uint32_t adc_get_overrun_status(const Adc *p_adc);
#elif SAM3U
uint32_t adc_init(Adc * p_adc, const uint32_t ul_mck, const uint32_t ul_adc_clock,
		const uint32_t ul_startuptime);
void adc_configure_trigger(Adc *p_adc, const enum adc_trigger_t trigger);
void adc_configure_power_save(Adc *p_adc, const uint8_t uc_sleep);
#endif

#if SAM3S8 || SAM4S || SAM3N || SAM3SD8
void adc_configure_power_save(Adc *p_adc, const uint8_t uc_sleep,
		const uint8_t uc_fwup);
#elif SAM3U || SAM4C || SAM4CP || SAM4CM
void adc_configure_power_save(Adc *p_adc, const uint8_t uc_sleep);
#endif
void adc_set_resolution(Adc *p_adc, const enum adc_resolution_t resolution);
void adc_start(Adc *p_adc);
void adc_stop(Adc *p_adc);
void adc_enable_channel(Adc *p_adc, const enum adc_channel_num_t adc_ch);
void adc_disable_channel(Adc *p_adc, const enum adc_channel_num_t adc_ch);
void adc_enable_all_channel(Adc *p_adc);
void adc_disable_all_channel(Adc *p_adc);
uint32_t adc_get_channel_status(const Adc *p_adc, const enum adc_channel_num_t adc_ch);
uint32_t adc_get_channel_value(const Adc *p_adc,const enum adc_channel_num_t adc_ch);
uint32_t adc_get_latest_value(const Adc *p_adc);
uint32_t adc_get_actual_adc_clock(const Adc *p_adc, const uint32_t ul_mck);
void adc_enable_interrupt(Adc *p_adc, const uint32_t ul_source);
void adc_disable_interrupt(Adc *p_adc, const uint32_t ul_source);
uint32_t adc_get_status(const Adc *p_adc);
uint32_t adc_get_interrupt_mask(const Adc *p_adc);
Pdc *adc_get_pdc_base(const Adc *p_adc);

#if SAM3S || SAM4S || SAM3XA
void adc_configure_timing(Adc *p_adc, const uint8_t uc_tracking,
		const enum adc_settling_time_t settling, const uint8_t uc_transfer);
void adc_enable_anch( Adc *p_adc );
void adc_disable_anch( Adc *p_adc );
void adc_enable_channel_differential_input(Adc *p_adc, const enum adc_channel_num_t channel);
void adc_disable_channel_differential_input(Adc *p_adc, const enum adc_channel_num_t channel);
void adc_enable_channel_input_offset(Adc *p_adc, const enum adc_channel_num_t channel);
void adc_disable_channel_input_offset(Adc *p_adc, const enum adc_channel_num_t channel);
void adc_set_channel_input_gain(Adc *p_adc, const enum adc_channel_num_t channel,
		const enum adc_gainvalue_t uc_gain);
void adc_set_bias_current(Adc *p_adc, const uint8_t uc_ibctl);
#elif SAM3N || SAM4C || SAM4CP || SAM4CM
void adc_configure_timing(Adc *p_adc, const uint8_t uc_tracking);
#elif SAM3U
void adc_configure_timing(Adc *p_adc, const uint32_t ul_sh);
#endif

#if SAM3S || SAM4S || SAM3XA || SAM4C || SAM4CP || SAM4CM
void adc_enable_ts(Adc *p_adc);
void adc_disable_ts(Adc *p_adc);
#if SAM4C || SAM4CP || SAM4CM
/** Definitions for Temperature Comparison Mode */
enum adc_temp_cmp_mode {
	ADC_TEMP_CMP_MODE_0 = ADC_TEMPMR_TEMPCMPMOD_LOW,
	ADC_TEMP_CMP_MODE_1 = ADC_TEMPMR_TEMPCMPMOD_HIGH,
	ADC_TEMP_CMP_MODE_2 = ADC_TEMPMR_TEMPCMPMOD_IN,
	ADC_TEMP_CMP_MODE_3 = ADC_TEMPMR_TEMPCMPMOD_OUT
};
void adc_configure_ts_comparison(Adc *p_adc, enum adc_temp_cmp_mode mode,
		uint16_t low_threshold, uint16_t high_threshold);
#endif
#endif

#if  SAM3S8 || SAM3SD8 || SAM4S
void adc_set_calibmode(Adc *p_adc);
#endif

#if SAM4C || SAM4CP | SAM4CM
void adc_set_averaging_trigger(Adc *p_adc, bool multi);
enum adc_internal_ref_voltage {
	ADC_INTERNAL_REF_2426MV = 0,
	ADC_INTERNAL_REF_2305MV,
	ADC_INTERNAL_REF_2184MV,
	ADC_INTERNAL_REF_2063MV,
	ADC_INTERNAL_REF_1941MV,
	ADC_INTERNAL_REF_1820MV,
	ADC_INTERNAL_REF_1699MV,
	ADC_INTERNAL_REF_1578MV,
	ADC_INTERNAL_REF_3396MV,
	ADC_INTERNAL_REF_3275MV,
	ADC_INTERNAL_REF_3154MV,
	ADC_INTERNAL_REF_3032MV,
	ADC_INTERNAL_REF_2911MV,
	ADC_INTERNAL_REF_2790MV,
	ADC_INTERNAL_REF_2699MV,
	ADC_INTERNAL_REF_2547MV,
};
struct adc_internal_ref {
	bool adc_internal_ref_change_enable;
	enum adc_internal_ref_voltage volt;
	bool adc_force_internal_ref;
	bool adc_internal_ref_on;
};
enum status_code adc_set_internal_reference_voltage(Adc *p_adc,
		struct adc_internal_ref *ref);
#endif

#if SAM3U
uint32_t adc12b_init(Adc12b *p_adc, const uint32_t ul_mck, const uint32_t ul_adc_clock,
		const uint32_t ul_startuptime, const uint32_t ul_offmode_startuptime);
void adc12b_set_resolution(Adc12b *p_adc, const enum adc_resolution_t resolution);
void adc12b_configure_trigger(Adc12b *p_adc, const enum adc12b_trigger_t trigger);
void adc12b_configure_power_save(Adc12b *p_adc, const uint8_t uc_sleep,
		const uint8_t uc_offmode);
void adc12b_configure_timing(Adc12b *p_adc, const uint32_t ul_sh);
void adc12b_start(Adc12b *p_adc);
void adc12b_stop(Adc12b *p_adc);
void adc12b_enable_channel(Adc12b *p_adc, const enum adc_channel_num_t adc_ch);
void adc12b_disable_channel(Adc12b *p_adc, const enum adc_channel_num_t adc_ch);
void adc12b_enable_all_channel(Adc12b *p_adc);
void adc12b_disable_all_channel(Adc12b *p_adc);
uint32_t adc12b_get_channel_status(const Adc12b *p_adc,const enum adc_channel_num_t adc_ch);
uint32_t adc12b_get_channel_value(const Adc12b *p_adc, const enum adc_channel_num_t adc_ch);
uint32_t adc12b_get_latest_value(const Adc12b *p_adc);
void adc12b_enable_differential_input(Adc12b *p_adc);
void adc12b_disable_differential_input(Adc12b *p_adc);
void adc12b_enable_input_offset(Adc12b *p_adc);
void adc12b_disable_input_offset(Adc12b *p_adc);
void adc12b_set_input_gain(Adc12b *p_adc, const enum adc_gainvalue_t uc_gain);
uint32_t adc12b_get_actual_adc_clock(const Adc12b *p_adc, const uint32_t ul_mck);
void adc12b_enable_interrupt(Adc12b *p_adc, const uint32_t ul_source);
void adc12b_disable_interrupt(Adc12b *p_adc, const uint32_t ul_source);
uint32_t adc12b_get_interrupt_mask(const Adc12b *p_adc);
uint32_t adc12b_get_status(const Adc12b *p_adc);
void adc12b_set_bias_current(Adc12b *p_adc, const uint8_t uc_ibctl);
Pdc *adc12b_get_pdc_base(const Adc12b *p_adc);
#endif

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page sam_adc_quickstart Quickstart guide for SAM ADC driver
 *
 * This is the quickstart guide for the \ref adc_group "SAM ADC driver",
 * with step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section adc_basic_use_case Basic use case
 * In this basic use case, the ADC module and single channel are configured for:
 * - 12-bit, unsigned conversions
 * - Internal bandgap as 3.3 V reference
 * - ADC clock rate of at most 6.4 MHz and maximum sample rate is 1 MHz
 * - Software triggering of conversions
 * - Interrupt-based conversion handling
 * - Single channel measurement
 * - ADC_CHANNEL_5 as positive input
 *
 * \subsection sam_adc_quickstart_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (Sysclock)"
 * -# \ref pmc_group "Power Management Controller (PMC)"
 *
 * \section adc_basic_use_case_setup Setup steps
 * \subsection adc_basic_use_case_setup_code Example code
 * Add to application C-file:
 * \code
	   void ADC_IrqHandler(void)
	   {
	       // Check the ADC conversion status
	       if ((adc_get_status(ADC) & ADC_ISR_DRDY) == ADC_ISR_DRDY)
	       {
	       // Get latest digital data value from ADC and can be used by application
	           uint32_t result = adc_get_latest_value(ADC);
	       }
	   }
	   void adc_setup(void)
	   {
	       adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 8);

	       adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);

	       adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);

	       adc_enable_channel(ADC, ADC_CHANNEL_5);

	       adc_enable_interrupt(ADC, ADC_IER_DRDY);

	       adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	   }
\endcode
 *
 * \subsection adc_basic_use_case_setup_flow Workflow
 * -# Define the interrupt service handler in the application:
 *   - \code
	void ADC_IrqHandler(void)
	{
	    //Check the ADC conversion status
	    if ((adc_get_status(ADC) & ADC_ISR_DRDY) == ADC_ISR_DRDY)
	    {
	    //Get latest digital data value from ADC and can be used by application
	        uint32_t result = adc_get_latest_value(ADC);
	    }
	}
\endcode
 *   - \note Get ADC status and check if the conversion is finished. If done, read the last ADC result data.
 * -# Initialize the given ADC with the specified ADC clock and startup time:
 *   - \code adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 8); \endcode
 *   - \note The ADC clock range is between master clock / 2 and master clock / 512.
 * The function sysclk_get_main_hz() is used to get the master clock frequency while ADC_CLOCK gives the ADC clock frequency.
 * -# Configure ADC timing:
 *   - \code adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1); \endcode
 *   - \note Tracking Time = (0 + 1) * ADC Clock period
 * Settling Time =  ADC_SETTLING_TIME_3 * ADC Clock period
 * Transfer Time = (1 * 2 + 3) * ADC Clock period
 * -# Set the ADC resolution.
 *   - \code adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12); \endcode
 *   - \note The resolution value can be set to 10 bits or 12 bits.
 * -# Enable the specified ADC channel:
 *   - \code adc_enable_channel(ADC, ADC_CHANNEL_5); \endcode
 * -# Enable ADC interrupts:
 *   - \code adc_enable_interrupt(ADC, ADC_IER_DRDY); \endcode
 * -# Configure software conversion trigger:
 *   - \code adc_configure_trigger(ADC, ADC_TRIG_SW, 0); \endcode
 *
 * \section adc_basic_use_case_usage Usage steps
 * \subsection adc_basic_use_case_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
	adc_start(ADC);
\endcode
 *
 * \subsection adc_basic_use_case_usage_flow Workflow
 * -# Start ADC conversion on channel:
 *   - \code adc_start(ADC); \endcode
 *
 * \section adc_use_cases Advanced use cases
 * For more advanced use of the ADC driver, see the following use cases:
 * - \subpage adc_use_case_1 : 12-bits unsigned, comparison event happen and interrupt
 * driven
 */
/**
 * \page adc_use_case_1 Advanced use cases
 * In this use case the ADC module and one channel are configured for:
 * - 12-bit, unsigned conversions
 * - Internal bandgap as 3.3 V reference
 * - ADC clock rate of at most 6.4 MHz and maximum sample rate is 1 MHz
 * - Software triggering of conversions
 * - Comparison event happen and interrupt handling
 * - Single channel measurement
 * - ADC_CHANNEL_5 as positive input
 *
 * \section adc_use_case_1_setup Setup steps
 * \subsection adc_use_case_1_setup_code Example code
 * Add to application C-file:
 * \code
	void ADC_IrqHandler(void)
	{
	    // Check the ADC conversion status
	    if ((adc_get_status(ADC) & ADC_ISR_COMPE) == ADC_ISR_COMPE)
	    {
	        // Get comparison mode of ADC
	        uint32_t ul_mode = adc_get_comparison_mode(ADC);
	        // Get latest digital data value from ADC and can be used by application
	        uint16_t us_adc = adc_get_channel_value(ADC, ADC_CHANNEL_5);
	    }
	}
\endcode
 *
 * \code
	   void adc_setup(void)
	   {
	       adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 8);

	       adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);

	       adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);

	       adc_enable_channel(ADC, ADC_CHANNEL_5);

	       adc_set_comparison_channel(ADC, ADC_CHANNEL_5);
	       adc_set_comparison_mode(ADC, ADC_EMR_CMPMODE_IN);
	       adc_set_comparison_window(ADC, MAX_DIGITAL, 0);

	       adc_enable_interrupt(ADC, ADC_IER_COMPE);

	       adc_configure_trigger(ADC, ADC_TRIG_TIO_CH_0, 0);
	   }
\endcode
 *
 * \subsection adc_basic_use_case_setup_flow Workflow
 * -# Define the interrupt service handler in the application:
 *   - \code
	void ADC_IrqHandler(void)
	{
	    // Check the ADC conversion status
	    if ((adc_get_status(ADC) & ADC_ISR_COMPE) == ADC_ISR_COMPE)
	    {
	        // Get comparison mode of ADC
	        uint32_t ul_mode = adc_get_comparison_mode(ADC);
	        // Get latest digital data value from ADC and can be used by application
	        uint16_t us_adc = adc_get_channel_value(ADC, ADC_CHANNEL_5);
	    }
	}
\endcode
 *   - \note Get ADC status and check if comparison event occurred. If occurred, read the ADC channel value and comparison mode.
 * -# Initialize the given ADC with the specified ADC clock and startup time:
 *   - \code adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 10); \endcode
 *   - \note The ADC clock range is between master clock/2 and master clock/512.
 * The function sysclk_get_main_hz() is used to get the master clock frequency while ADC_CLOCK gives the ADC clock frequency.
 * -# Configure ADC timing:
 *   - \code adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1); \endcode
 *   - \note Tracking Time = (0 + 1) * ADC Clock period
 * Settling Time =  ADC_SETTLING_TIME_3 * ADC Clock period
 * Transfer Time = (1 * 2 + 3) * ADC Clock period
 * -# Set the ADC resolution.
 *   - \code adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12); \endcode
 *   - \note The resolution value can be set to 10 bits or 12 bits.
 * -# Enable the specified ADC channel:
 *   - \code adc_enable_channel(ADC, ADC_CHANNEL_5); \endcode
 * -# Set the comparison ADC channel, mode and window:
 *   - \code adc_set_comparison_channel(ADC, ADC_CHANNEL_5);
	adc_set_comparison_mode(ADC, ADC_EMR_CMPMODE_IN);
	adc_set_comparison_window(ADC, us_high_threshold, us_low_threshold); \endcode
 *   - \note The high and low threshold of comparison window can be set by the user.
 * An event will be generated whenever the converted data is in the comparison window.
 * -# Enable ADC interrupts:
 *   - \code adc_enable_interrupt(ADC, ADC_IER_COMPE); \endcode
 * -# Configure software conversion trigger:
 *   - \code adc_configure_trigger(ADC, ADC_TRIG_SW, 0); \endcode
 *
 * \section adc_use_case_1_usage Usage steps
 * \subsection adc_use_case_1_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
	adc_start(ADC);
\endcode
 *
 * \subsection adc_use_case_1_usage_flow Workflow
 * -# Start ADC conversion on the configured channels:
 *   - \code adc_start(ADC); \endcode
 */
#endif /* ADC_H_INCLUDED */
