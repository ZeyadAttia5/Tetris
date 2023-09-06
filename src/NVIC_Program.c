
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "NVIC_Interface.h"
#include "NVIC_Private.h"
#include "NVIC_Config.h"

static u8 Global_u8PriorityConfig = 245;
/*
    NVIC_voidEnablePerInt
    i/p arguments: copy_u8PerID (0 - 84)
    o/p arguments: void
    Description: this API allows the user to enable a peripheral's interrupt
*/
u8 NVIC_u8EnablePerInt(u8 copy_u8PerID)
{
    u8 loc_u8Error = SUCCESS;
    if (copy_u8PerID < 85)
    {
        u8 loc_u8PerID = copy_u8PerID / 32;
        u8 loc_u8BitNo = copy_u8PerID % 32;
        SET_BIT(NVIC->ISER[loc_u8PerID], loc_u8BitNo);
    }
    else
    {
        loc_u8Error = FAIL;
    }

    return loc_u8Error;
}

/*
    NVIC_voidDisablePerInt
    i/p arguments: copy_u8PerID (0 - 84)
    o/p arguments: void
    Description: this API allows the user to disable a peripheral's interrupt
*/
u8 NVIC_u8DisablePerInt(u8 copy_u8PerID)
{
    u8 loc_u8Error = SUCCESS;
    if (copy_u8PerID < 85)
    {
        u8 loc_u8PerID = copy_u8PerID / 32;
        u8 loc_u8BitNo = copy_u8PerID % 32;
        CLR_BIT(NVIC->ISER[loc_u8PerID], loc_u8BitNo);
    }
    else
    {
        loc_u8Error = FAIL;
    }
    return loc_u8Error;
}

/*
    NVIC_voidSetPriorityConfig
    i/p arguments: copy_u8PriortyConfig: G16_SG0, G8_SG2, G4_SG4, G2_SG8, G0_SG16
    o/p arguments: void
    Description: this API allows the user to disable a peripheral's interrupt
*/
void NVIC_voidSetPriorityConfig(u8 copy_u8PriortyConfig)
{
    switch (copy_u8PriortyConfig)
    {
    case G16_SG0:
        SCB_AIRCR = VECT_KEY | (G4Bits_SG0Bits << 8);

        Global_u8PriorityConfig = G4Bits_SG0Bits;
        break;
    case G8_SG2:
        SCB_AIRCR = VECT_KEY | (G3Bits_SG1Bits << 8);
        Global_u8PriorityConfig = G3Bits_SG1Bits;
        break;
    case G4_SG4:
        SCB_AIRCR = VECT_KEY | (G2Bits_SG2Bits << 8);
        Global_u8PriorityConfig = G2Bits_SG2Bits;
        break;
    case G2_SG8:
        SCB_AIRCR = VECT_KEY | (G1Bits_SG3Bits << 8);
        Global_u8PriorityConfig = G1Bits_SG3Bits;
        break;
    case G0_SG16:
        SCB_AIRCR = VECT_KEY | (G0Bits_SG4Bits << 8);
        Global_u8PriorityConfig = G0Bits_SG4Bits;
        break;
    default:
        break;
    }
}

/*
    NVIC_voidSetPendingFlag
    i/p arguments: copy_u8PerID (0 - 84)
    o/p arguments: void
    Description: this API allows the user to enable a peripheral's pending flag
*/
void NVIC_voidSetPendingFlag(u8 copy_u8PerID)
{
    u8 local_u8GroupID = copy_u8PerID / 32;
    u8 local_u8BitNo = copy_u8PerID % 32;
    SET_BIT(NVIC->ISPR[local_u8GroupID], local_u8BitNo);
}
void NVIC_voidClrPendingFlag(u8 copy_u8PerID)
{
    u8 local_u8GroupID = copy_u8PerID / 32;
    u8 local_u8BitNo = copy_u8PerID % 32;
    SET_BIT(NVIC->ICPR[local_u8GroupID], local_u8BitNo);
}

/*
    NVIC_voidSetPerPriority
    i/p arguments: copy_u8PerId: 0-239, inclusive
    i/p arguments: copy_u8GroupId: 0 - maximum (set by user)
    i/p arguments: copy_u8SubGrouPId: 0 - maximum (set by user)
    o/p arguments: void
    Description: this API allows the user to set the priority of a peripheral's interrupt
*/
void NVIC_voidSetPerPriority(u8 copy_u8PerId, u8 copy_u8GroupId, u8 copy_u8SubGrouPId)
{
    u8 Local_u8LocalPriority = copy_u8SubGrouPId | copy_u8GroupId << (Global_u8PriorityConfig - 3);
    ASSIGN_REG(NVIC->IPR[copy_u8PerId], (Local_u8LocalPriority << 4));
}