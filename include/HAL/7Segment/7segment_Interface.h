/********************************************************************/
/* SWC: 7Segment Driver                                             */
/* Author: Zeyad Attia                                            	*/
/* Version: v0.0                                                   	*/
/* Date: Aug 17, 2023                                               */
/* Description: ex: Header of the 7Segment API			 			*/
/********************************************************************/

#ifndef SEGMENT_INTERFACE_H
#define SEGMENT_INTERFACE_H

#include "STD_TYPES.h"
void SEG_voidCountUp(u8 copy_u8PortID, u32 copy_u32mSeconds, u8 copy_u8UpperLimit, u8 copy_u8LowerLimit);
void SEG_voidShowCount(u8 copy_u8PortID, u8 copy_u8Count);

#endif /* SEGMENT_INTERFACE_H */
