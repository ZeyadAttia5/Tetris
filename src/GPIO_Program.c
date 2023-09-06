/********************************************/
/* SWC: GPIO Driver                         */
/* Author: Seif Hashad                      */
/* Version: v0.0                            */
/* Date: 11 AUG 2023                        */
/* Description: This is the implem. of GPIO */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_Interface.h"
#include "GPIO_Private.h"
#include "GPIO_Config.h"

/*****************************************************************/
/* Func. Name: GPIO_voidSetPinMode                               */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                   */
/* i/p arguments: Copy_u8PinId: PIN0 --> PIN15                   */
/* i/p arguments: Copy_u8Mode: INPUT, OUTPUT, AF, ANALOG         */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to Set the mode of a specific pin*/
/*****************************************************************/
void GPIO_voidSetPinMode(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Mode)
{
    /*i/p Validation*/
    if((Copy_u8PortId > IOC) || (Copy_u8PinId > PIN15) || (Copy_u8Mode > ANALOG))
    {
        /*Do Nothing*/
    }
    else
    {
        switch(Copy_u8Mode)
        {
            case INPUT: switch(Copy_u8PortId)
                        {
                            case IOA:   CLR_BIT(GPIOA->MODER, (Copy_u8PinId*2));
                                        CLR_BIT(GPIOA->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOB:   CLR_BIT(GPIOB->MODER, (Copy_u8PinId*2));
                                        CLR_BIT(GPIOB->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOC:   CLR_BIT(GPIOC->MODER, (Copy_u8PinId*2));
                                        CLR_BIT(GPIOC->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                        } 
                        break;
            case OUTPUT:switch(Copy_u8PortId)
                        {
                            case IOA:   SET_BIT(GPIOA->MODER, (Copy_u8PinId*2));
                                        CLR_BIT(GPIOA->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOB:   SET_BIT(GPIOB->MODER, (Copy_u8PinId*2));
                                        CLR_BIT(GPIOB->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOC:   SET_BIT(GPIOC->MODER, (Copy_u8PinId*2));
                                        CLR_BIT(GPIOC->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                        } 
                        break;
            case AF:    switch(Copy_u8PortId)
                        {
                            case IOA:   CLR_BIT(GPIOA->MODER, (Copy_u8PinId*2));
                                        SET_BIT(GPIOA->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOB:   CLR_BIT(GPIOB->MODER, (Copy_u8PinId*2));
                                        SET_BIT(GPIOB->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOC:   CLR_BIT(GPIOC->MODER, (Copy_u8PinId*2));
                                        SET_BIT(GPIOC->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                        } 
                        break;
            case ANALOG:switch(Copy_u8PortId)
                        {
                            case IOA:   SET_BIT(GPIOA->MODER, (Copy_u8PinId*2));
                                        SET_BIT(GPIOA->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOB:   SET_BIT(GPIOB->MODER, (Copy_u8PinId*2));
                                        SET_BIT(GPIOB->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                            case IOC:   SET_BIT(GPIOC->MODER, (Copy_u8PinId*2));
                                        SET_BIT(GPIOC->MODER, ((Copy_u8PinId*2)+1));
                                        break;
                        } 
                        break;
        }
    }
}

/*****************************************************************/
/* Func. Name: GPIO_voidSetPinType                               */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                   */
/* i/p arguments: Copy_u8PinId: PIN0 --> PIN15                   */
/* i/p arguments: Copy_u8Type: OUTPUT_PP, OUTPUT_OD              */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to Set the type of a specific pin*/
/*****************************************************************/
void GPIO_voidSetPinType(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Type)
{
    /*i/p Validation*/
    if((Copy_u8PortId > IOC) || (Copy_u8PinId > PIN15) || (Copy_u8Type > OUTPUT_OD))
    {
        /*Do Nothing*/
    }
    else
    {
        switch (Copy_u8Type)
        {
            case OUTPUT_PP: switch(Copy_u8PortId)
                            {
                                case IOA:   CLR_BIT(GPIOA->OTYPER, Copy_u8PinId);
                                            break;
                                case IOB:   CLR_BIT(GPIOB->OTYPER, Copy_u8PinId);
                                            break;
                                case IOC:   CLR_BIT(GPIOC->OTYPER, Copy_u8PinId);
                                            break;
                            }
                            break;
            case OUTPUT_OD: switch(Copy_u8PortId)
                            {
                                case IOA:   SET_BIT(GPIOA->OTYPER, Copy_u8PinId);
                                            break;
                                case IOB:   SET_BIT(GPIOB->OTYPER, Copy_u8PinId);
                                            break;
                                case IOC:   SET_BIT(GPIOC->OTYPER, Copy_u8PinId);
                                            break;
                            }
                            break;
        }
    }
}

/******************************************************************/
/* Func. Name: GPIO_voidSetPinSpeed                               */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                    */
/* i/p arguments: Copy_u8PinId: PIN0 --> PIN15                    */
/* i/p arguments: Copy_u8Speed: OUTPUT_LS, OUTPUT_MS, OUTPUT_HS   */
/* o/p arguments: nothing                                         */
/* Desc. : This API allows user to Set the speed of a specific pin*/
/******************************************************************/
void GPIO_voidSetPinSpeed(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Speed)
{
    /*i/p Validation*/
    if((Copy_u8PortId > IOC) || (Copy_u8PinId > PIN15) || (Copy_u8Speed > OUTPUT_HS))
    {
        /*Do Nothing*/
    }
    else
    {
        switch(Copy_u8Speed)
        {
            case OUTPUT_LS: switch(Copy_u8PortId)
                            {
                                case IOA:   CLR_BIT(GPIOA->OSPEEDR, (Copy_u8PinId*2));
                                            CLR_BIT(GPIOA->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                                case IOB:   CLR_BIT(GPIOB->OSPEEDR, (Copy_u8PinId*2));
                                            CLR_BIT(GPIOB->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                                case IOC:   CLR_BIT(GPIOC->OSPEEDR, (Copy_u8PinId*2));
                                            CLR_BIT(GPIOC->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                            } 
                            break;
            case OUTPUT_MS: switch(Copy_u8PortId)
                            {
                                case IOA:   SET_BIT(GPIOA->OSPEEDR, (Copy_u8PinId*2));
                                            CLR_BIT(GPIOA->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                                case IOB:   SET_BIT(GPIOB->OSPEEDR, (Copy_u8PinId*2));
                                            CLR_BIT(GPIOB->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                                case IOC:   SET_BIT(GPIOC->OSPEEDR, (Copy_u8PinId*2));
                                            CLR_BIT(GPIOC->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                            } 
                            break;
            case OUTPUT_HS: switch(Copy_u8PortId)
                            {
                                case IOA:   CLR_BIT(GPIOA->OSPEEDR, (Copy_u8PinId*2));
                                            SET_BIT(GPIOA->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                                case IOB:   CLR_BIT(GPIOB->OSPEEDR, (Copy_u8PinId*2));
                                            SET_BIT(GPIOB->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                                case IOC:   CLR_BIT(GPIOC->OSPEEDR, (Copy_u8PinId*2));
                                            SET_BIT(GPIOC->OSPEEDR, ((Copy_u8PinId*2)+1));
                                            break;
                            } 
                            break;
        }
    }
}

/*********************************************************************/
/* Func. Name: GPIO_voidSetPinPuPdConfig                             */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                       */
/* i/p arguments: Copy_u8PinId: PIN0 --> PIN15                       */
/* i/p arguments: Copy_u8PUPDType: INPUT_FLOATING, INPUT_PU, INPUT_PD*/
/* o/p arguments: nothing                                            */
/* Desc. : This API allows user to Set the value of a specific pin   */
/*********************************************************************/
void GPIO_voidSetPinPuPdConfig(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PUPDType)
{
    /*i/p Validation*/
    if((Copy_u8PortId > IOC) || (Copy_u8PinId > PIN15) || (Copy_u8PUPDType > INPUT_PD))
    {
        /*Do Nothing*/
    }
    else
    {
        switch (Copy_u8PUPDType)
        {
            case INPUT_FLOATING: switch(Copy_u8PortId)
                                 {
                                     case IOA:   CLR_BIT(GPIOA->PUPDR, (Copy_u8PinId*2));
                                                 CLR_BIT(GPIOA->PUPDR, ((Copy_u8PinId*2)+1));
                                                 break;
                                     case IOB:   CLR_BIT(GPIOB->PUPDR, (Copy_u8PinId*2));
                                                 CLR_BIT(GPIOB->PUPDR, ((Copy_u8PinId*2)+1));
                                                 break;
                                     case IOC:   CLR_BIT(GPIOC->PUPDR, (Copy_u8PinId*2));
                                                 CLR_BIT(GPIOC->PUPDR, ((Copy_u8PinId*2)+1));
                                                 break;
                                 } 
                                 break;
            case INPUT_PU:      switch(Copy_u8PortId)
                                {
                                    case IOA:   SET_BIT(GPIOA->PUPDR, (Copy_u8PinId*2));
                                                CLR_BIT(GPIOA->PUPDR, ((Copy_u8PinId*2)+1));
                                                break;
                                    case IOB:   SET_BIT(GPIOB->PUPDR, (Copy_u8PinId*2));
                                                CLR_BIT(GPIOB->PUPDR, ((Copy_u8PinId*2)+1));
                                                break;
                                    case IOC:   SET_BIT(GPIOC->PUPDR, (Copy_u8PinId*2));
                                                CLR_BIT(GPIOC->PUPDR, ((Copy_u8PinId*2)+1));
                                                break;
                                } 
                                break;
            case INPUT_PD:      switch(Copy_u8PortId)
                                {
                                    case IOA:   CLR_BIT(GPIOA->PUPDR, (Copy_u8PinId*2));
                                                SET_BIT(GPIOA->PUPDR, ((Copy_u8PinId*2)+1));
                                                break;
                                    case IOB:   CLR_BIT(GPIOB->PUPDR, (Copy_u8PinId*2));
                                                SET_BIT(GPIOB->PUPDR, ((Copy_u8PinId*2)+1));
                                                break;
                                    case IOC:   CLR_BIT(GPIOC->PUPDR, (Copy_u8PinId*2));
                                                SET_BIT(GPIOC->PUPDR, ((Copy_u8PinId*2)+1));
                                                break;
                                } 
                                break;
        }
    }
}

/*****************************************************************/
/* Func. Name: GPIO_voidSetPinValue                              */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                   */
/* i/p arguments: Copy_u8PinId: PIN0 --> PIN15                   */
/* i/p arguments: Copy_u8Value: OUTPUT_LOW, OUTPUT_HIGH          */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to Set the value of a specific pin*/
/*****************************************************************/
void GPIO_voidSetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Value)
{
    /*i/p Validation*/
    if((Copy_u8PortId > IOC) || (Copy_u8PinId > PIN15) || (Copy_u8Value > OUTPUT_HIGH))
    {
        /*Do Nothing*/
    }
    else
    {
        switch (Copy_u8Value)
        {
            case OUTPUT_LOW: switch(Copy_u8PortId)
                            {
                                case IOA:   CLR_BIT(GPIOA->ODR, Copy_u8PinId);
                                            break;
                                case IOB:   CLR_BIT(GPIOB->ODR, Copy_u8PinId);
                                            break;
                                case IOC:   CLR_BIT(GPIOC->ODR, Copy_u8PinId);
                                            break;
                            }
                            break;
            case OUTPUT_HIGH: switch(Copy_u8PortId)
                            {
                                case IOA:   SET_BIT(GPIOA->ODR, Copy_u8PinId);
                                            break;
                                case IOB:   SET_BIT(GPIOB->ODR, Copy_u8PinId);
                                            break;
                                case IOC:   SET_BIT(GPIOC->ODR, Copy_u8PinId);
                                            break;
                            }
                            break;
        }
    }
}

/*****************************************************************/
/* Func. Name: GPIO_voidSetPinValueDirectAccess                  */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                   */
/* i/p arguments: Copy_u8PinId: PIN0 --> PIN15                   */
/* i/p arguments: Copy_u8SetRstType: OUTPUT_RST, OUTPUT_SET      */
/* o/p arguments: nothing                                        */
/* Desc. : This API allows user to Set the value of a specific pin*/
/*****************************************************************/
void GPIO_voidSetPinValueDirectAccess(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8SetRstType)
{
    /*i/p Validation*/
    if((Copy_u8PortId > IOC) || (Copy_u8PinId > PIN15) || (Copy_u8SetRstType > OUTPUT_SET))
    {
        /*Do Nothing*/
    }
    else
    {
        switch (Copy_u8SetRstType)
        {
            case OUTPUT_RST: switch(Copy_u8PortId)
                            {
                                case IOA:   GPIOA->BSRR = (1 << (Copy_u8PinId+16));
                                            break;
                                case IOB:   GPIOB->BSRR = (1 << (Copy_u8PinId+16));
                                            break;
                                case IOC:   GPIOC->BSRR = (1 << (Copy_u8PinId+16));
                                            break;
                            }
                            break;
            case OUTPUT_SET: switch(Copy_u8PortId)
                            {
                                case IOA:   GPIOA->BSRR = (1 << Copy_u8PinId);
                                            break;
                                case IOB:   GPIOB->BSRR = (1 << Copy_u8PinId);
                                            break;
                                case IOC:   GPIOC->BSRR = (1 << Copy_u8PinId);
                                            break;
                            }
                            break;
        }
    }
}

void GPIO_voidSetPortValue(u8 Copy_u8PortId, u32 Copy_u32Value)
{
    if((Copy_u8PortId > IOC))
    {
        /*Do Nothing*/
    }
    else
    {
        switch(Copy_u8PortId)
        {
            case IOA:   GPIOA->ODR = Copy_u32Value;
                        break;
            case IOB:   GPIOB->ODR = Copy_u32Value;
                        break;
            case IOC:   GPIOC->ODR = Copy_u32Value;
                        break;
        }
    }
}

/*****************************************************************/
/* Func. Name: GPIO_u8GetPinValue                                */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                   */
/* i/p arguments: Copy_u8PinId: PIN0 --> PIN15                   */
/* o/p arguments: u8                                             */
/* Desc. : This API allows user to get the value of a specific pin*/
/*****************************************************************/
u8   GPIO_u8GetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId)
{
    u8 Local_u8PinValue;
    /*i/p Validation*/
    if((Copy_u8PortId > IOC) || (Copy_u8PinId > PIN15))
    {
        /*Do Nothing*/
    }
    else
    {
        switch(Copy_u8PortId)
        {
            case IOA:   Local_u8PinValue = GET_BIT(GPIOA->IDR, Copy_u8PinId);
                        break;
            case IOB:   Local_u8PinValue = GET_BIT(GPIOB->IDR, Copy_u8PinId);
                        break;
            case IOC:   Local_u8PinValue = GET_BIT(GPIOC->IDR, Copy_u8PinId);
                        break;
        }
    }
    return Local_u8PinValue;
}