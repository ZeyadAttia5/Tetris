/********************************************/
/* SWC: RCC Driver                          */
/* Author: Zeyad Attia                      */
/* Version: v0.0                            */
/* Date: 04 AUG 2023                        */
/* Description: This is the implem. of RCC  */
/********************************************/

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/RCC/RCC_Private.h"
#include "MCAL/RCC/RCC_Config.h"

/*
 RCC_voidInitSysClk
 i/p arguments: void
 o/p arguments: void
 Description: this API allows the user to select the clock source of the system
 */
void RCC_voidInitSysClk(void) {

#if SYS_CLK_SRC == HSI
	/*1- Turn On HSI*/
	SET_BIT(RCC_CR, HSION);

	/*2- Select HSI as My System Clk*/
	CLR_BIT(RCC_CFGR, SW0);
	CLR_BIT(RCC_CFGR, SW1);

//    /* 3- AHB - Prescaled by 2 */
//    SET_BIT(RCC_CFGR, 7);

#elif SYS_CLK_SRC == HSE

	// select HSE as clk src
	CLR_BIT(RCC_CFGR, SW0);
	CLR_BIT(RCC_CFGR, SW1);

	// turn HSE on
	SET_BIT(RCC_CR, HSEON);

#elif SYS_CLK_SRC == PLL

	// set PLL configuration
	// enable PLL

#if PLL_SRC == HSE
	SET_BIT(RCC_PLLCFGR, PLLSRC);
	SET_BIT(RCC_CR, HSEON);

#elif PLL_SRC == HSI
	CLR_BIT(RCC_PLLCFGR, PLLSRC);
	SET_BIT(RCC_CR, HSION);
#else
#error "invalid PLL source"
#endif

#if PLL_M_Value >= 2 && PLL_M_Value <= 63
	// set M value
	// RCC_PLLCFGR[5:0]
	RCC_PLLCFGR |= (PLL_M_Value << M_OFFSET);

#else
#warning "PLL_M_Value is not within range"
#endif

#if PLL_N_Value >= 192 && PLL_N_Value <= 432
	// set N value
	// RCC_PLLCFGR[14:6]
	RCC_PLLCFGR |= (PLL_N_Value << N_OFFSET);
#else
#warning "PLL_N_Value is not within range"
#endif

#if PLL_P_Value >= 0 PLL_P_Value <= 3
	// set P value
	// RCC_PLLCFGR[17:16]
	RCC_PLLCFGR |= (PLL_P_Value << P_OFFSET);

#else
#warning "PLL_P_Value is not within range"
#endif

	// select PLL as clk src
	CLR_BIT(RCC_CFGR, SW0);
	SET_BIT(RCC_CFGR, SW1);
	SET_BIT(RCC_CR, PLLON);
#else
#error "Invalid Value for the SYS_CLK_SRC"

#endif
}

/*
 RCC_voidEnablePerClk
 i/p arguments: copy_u8BusId: AHB1, AHB2, ABP1, ABP2
 i/p arguments: copy_u8PerId: number between 0 and 31 inclusive
 o/p arguments: void
 Description: this API allows the user to enable the clock for the given peripheral (copy_u8PerId)
 */
void RCC_voidEnablePerClk(u8 copy_u8BusId, u8 copy_u8PerId) {
	if (copy_u8PerId > 31 || (copy_u8BusId > APB2)) {
		// do nothing
	} else {
		switch (copy_u8BusId) {
		case AHB1:
			SET_BIT(RCC_AHB1ENR, copy_u8PerId);
			break;

		case AHB2:
			if (copy_u8PerId != 7) {
//				do nothing
			} else {

				SET_BIT(RCC_AHB2ENR, copy_u8PerId);
			}
			break;
		case APB1:
			SET_BIT(RCC_APB1ENR, copy_u8PerId);
			break;
		case APB2:
			SET_BIT(RCC_APB2ENR, copy_u8PerId);
			break;

		default:
			// wrong copy_u8BusId
			break;
		}
	}
}

/*
 RCC_voidDisablePerClk
 i/p arguments: copy_u8BusId: AHB1, AHB2, ABP1, ABP2
 i/p arguments: copy_u8PerId: number between 0 and 31 inclusive
 o/p arguments: void
 Description: this API allows the user to disable the clock for the given peripherial (copy_u8PerId)
 */
void RCC_voidDisablePerClk(u8 copy_u8BusId, u8 copy_u8PerId) {
	if (copy_u8PerId > 31) {
		// do nothing
	} else {
		switch (copy_u8BusId) {
		case AHB1:
			CLR_BIT(RCC_AHB1ENR, copy_u8PerId);
			break;

		case AHB2:
			if (copy_u8PerId != 7) {
				break;
			} else {

				CLR_BIT(RCC_AHB2ENR, copy_u8PerId);
			}
			break;
		case APB1:
			CLR_BIT(RCC_APB1ENR, copy_u8PerId);
			break;
		case APB2:
			CLR_BIT(RCC_APB2ENR, copy_u8PerId);
			break;

		default:
			// wrong copy_u8BusId
			break;
		}
	}
}
