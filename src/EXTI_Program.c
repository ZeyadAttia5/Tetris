/********************************************************************/
/* SWC: EXTI Driver                                                 */
/* Author: Zeyad Attia                                              */
/* Version: v0.0                                                    */
/* Date: 26 Aug 2023                                                */
/* Description: implemntation of the EXTI driver in the STM32F401CC */
/********************************************************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/EXTI/EXTI_Interface.h"
#include "MCAL/EXTI/EXTI_Private.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"


static EXTI_Callback_t EXTI_Callbacks[EXTI_MAX_LINE_NUMBERS];

void EXTI_voidInit(u8 copy_u8LineID) {

	switch (copy_u8LineID) {
	case EXTI9:
		NVIC_u8EnablePerInt(23);

		GPIO_voidSetPinMode(IOA, PIN9, INPUT);
		GPIO_voidSetPinPuPdConfig(IOA, PIN9, INPUT_PU);
		GPIO_voidSetPinSpeed(IOA, PIN9, OUTPUT_LS);
		EXTI_voidEXTILineEnable(EXTI9);
		EXTI_voidSetSenseControl(EXTI9, EXTI_SC_FallingEdge);
		break;
	}

}

/*
 EXTI_voidEXTILineEnable
 i/p arguments: copy_enumLineID EXTIx: x = [0:4], EXTI5_9, EXTI10_15
 o/p arguments: void
 Description: this API allows the user to enable the EXTI Interrupt Line
 */
void EXTI_voidEXTILineEnable(u8 copy_u8LineID) {
	if (copy_u8LineID < 22 && copy_u8LineID != 20 && copy_u8LineID != 19) {
		SET_BIT(EXTI->IMR, copy_u8LineID);
	}
}

/*
 EXTI_voidEXTILineDisable
 i/p arguments: copy_enumLineID EXTIx: x = [0:4], EXTI5_9, EXTI10_15
 o/p arguments: void
 Description: this API allows the user to disable the EXTI Interrupt Line
 */
void EXTI_voidEXTILineDisable(u8 copy_u8LineID) {
	if (copy_u8LineID < 22 && copy_u8LineID != 20 && copy_u8LineID != 19) {
		CLR_BIT(EXTI->IMR, copy_u8LineID);
	}
}
void EXTI_voidClrPendingFlag(u8 copy_u8EXTILineId) {
	if (copy_u8EXTILineId < 22 && copy_u8EXTILineId != 20
			&& copy_u8EXTILineId != 19) {
		SET_BIT(EXTI->PR, copy_u8EXTILineId);
	}
}
/*
 EXTI_voidSetSenseControl
 i/p arguments: copy_u8SenseControl: EXTI_SC_RisingEdge, EXTI_SC_FallingEdge, EXTI_SC_DoubleEdge
 i/p arguments: copy_u8Line: EXTIx, where x=[0:15]
 o/p arguments: void
 Description: this API allows the user to Set Sense control for a given Line
 */
void EXTI_voidSetSenseControl(u8 copy_u8Line, u8 copy_u8SenseControl) {
	if (copy_u8Line > EXTI15) {
		// invalid EXTI Line Id
		return;
	}

	if (copy_u8SenseControl == EXTI_SC_DoubleEdge) {
		SET_BIT(EXTI->RTSR, copy_u8Line);
		SET_BIT(EXTI->FTSR, copy_u8Line);
	} else if (copy_u8SenseControl == EXTI_SC_RisingEdge) {
		SET_BIT(EXTI->RTSR, copy_u8Line);
		CLR_BIT(EXTI->FTSR, copy_u8Line);
	} else if (copy_u8SenseControl == EXTI_SC_FallingEdge) {
		CLR_BIT(EXTI->RTSR, copy_u8Line);
		SET_BIT(EXTI->FTSR, copy_u8Line);
	}
}
// void EXTI_voidSetEXTIPinConfig(u8 copy_u8PortId, u8 copy_u8Line);
// void EXTI_voidSetEXTIConfig(u8 copy_u8PortId, u8 copy_u8Line);

/*
 EXTI_voidSetSenseControl
 i/p arguments: copy_u8SenseControl: EXTI_SC_RisingEdge, EXTI_SC_FallingEdge, EXTI_SC_DoubleEdge
 i/p arguments: copy_u8Line: EXTIx, where x=[0:15]
 o/p arguments: void
 Description: this API allows the user to Set Sense control for a given Line
 */
void EXTI_voidSetCallBack(EXTI_Callback_t callback, u8 copy_u8LineId) {

	if (copy_u8LineId <= 15) {
		EXTI_Callbacks[copy_u8LineId] = callback;
	}
}

void EXTI0_IRQHandler(void) {

	// check if the pending flag is on
	if (GET_BIT(EXTI->PR, private_EXTI0) == 1) {
		SET_BIT(EXTI->PR, private_EXTI0);
		if (EXTI_Callbacks[private_EXTI0] != NULL) {
			EXTI_Callbacks[private_EXTI0]();
		}
	}
	EXTI_voidClrPendingFlag(EXTI0);
}
void EXTI1_IRQHandler(void) {

	// check if the pending flag is on
	if (GET_BIT(EXTI->PR, private_EXTI1) == 1) {
		SET_BIT(EXTI->PR, private_EXTI1);
		if (EXTI_Callbacks[private_EXTI1] != NULL) {
			EXTI_Callbacks[private_EXTI1]();
		}
	}
	EXTI_voidClrPendingFlag(EXTI1);
}
void EXTI2_IRQHandler(void) {

	// check if the pending flag is on
	if (GET_BIT(EXTI->PR, private_EXTI2) == 1) {
		SET_BIT(EXTI->PR, private_EXTI2);
		if (EXTI_Callbacks[private_EXTI2] != NULL) {
			EXTI_Callbacks[private_EXTI2]();
		}
	}
	EXTI_voidClrPendingFlag(EXTI2);
}
void EXTI3_IRQHandler(void) {

	// check if the pending flag is on
	if (GET_BIT(EXTI->PR, private_EXTI3) == 1) {
		SET_BIT(EXTI->PR, private_EXTI3);
		if (EXTI_Callbacks[private_EXTI3] != NULL) {
			EXTI_Callbacks[private_EXTI3]();
		}
	}
	EXTI_voidClrPendingFlag(EXTI3);
}
void EXTI4_IRQHandler(void) {

	// check if the pending flag is on
	if (GET_BIT(EXTI->PR, private_EXTI4) == 1) {
		SET_BIT(EXTI->PR, private_EXTI4);
		if (EXTI_Callbacks[private_EXTI4] != NULL) {
			EXTI_Callbacks[private_EXTI4]();
		}
	}
	EXTI_voidClrPendingFlag(EXTI4);
}
void EXTI9_5_IRQHandler(void) {

	// check if the pending flag is on
	if (GET_BIT(EXTI->PR, private_EXTI5) == 1) {
		SET_BIT(EXTI->PR, private_EXTI5);
		if (EXTI_Callbacks[private_EXTI5] != NULL) {
			EXTI_Callbacks[private_EXTI5]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI6) == 1) {
		SET_BIT(EXTI->PR, private_EXTI6);
		if (EXTI_Callbacks[private_EXTI6] != NULL) {
			EXTI_Callbacks[private_EXTI6]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI7) == 1) {
		SET_BIT(EXTI->PR, private_EXTI7);
		if (EXTI_Callbacks[private_EXTI7] != NULL) {
			EXTI_Callbacks[private_EXTI7]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI8) == 1) {
		SET_BIT(EXTI->PR, private_EXTI8);
		if (EXTI_Callbacks[private_EXTI8] != NULL) {
			EXTI_Callbacks[private_EXTI8]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI9) == 1) {
		SET_BIT(EXTI->PR, private_EXTI9);
		if (EXTI_Callbacks[private_EXTI9] != NULL) {
			EXTI_Callbacks[private_EXTI9]();
		}
	}
	EXTI_voidClrPendingFlag(EXTI9);
}

void EXTI10_15_IRQHandler(void) {

	// check if the pending flag is on
	if (GET_BIT(EXTI->PR, private_EXTI10) == 1) {
		SET_BIT(EXTI->PR, private_EXTI10);
		if (EXTI_Callbacks[private_EXTI10] != NULL) {
			EXTI_Callbacks[private_EXTI10]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI11) == 1) {
		SET_BIT(EXTI->PR, private_EXTI11);
		if (EXTI_Callbacks[private_EXTI11] != NULL) {
			EXTI_Callbacks[private_EXTI11]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI12) == 1) {
		SET_BIT(EXTI->PR, private_EXTI12);
		if (EXTI_Callbacks[private_EXTI12] != NULL) {
			EXTI_Callbacks[private_EXTI12]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI13) == 1) {
		SET_BIT(EXTI->PR, private_EXTI13);
		if (EXTI_Callbacks[private_EXTI13] != NULL) {
			EXTI_Callbacks[private_EXTI13]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI14) == 1) {
		SET_BIT(EXTI->PR, private_EXTI14);
		if (EXTI_Callbacks[private_EXTI14] != NULL) {
			EXTI_Callbacks[private_EXTI14]();
		}
	}

	if (GET_BIT(EXTI->PR, private_EXTI15) == 1) {
		SET_BIT(EXTI->PR, private_EXTI15);
		if (EXTI_Callbacks[private_EXTI15] != NULL) {
			EXTI_Callbacks[private_EXTI15]();
		}
	}
	EXTI_voidClrPendingFlag(EXTI12);
}
