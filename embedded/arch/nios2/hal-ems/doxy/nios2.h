/**
 * $Id: nios2.h 502 2015-11-05 14:18:19Z klugeflo $
 *
 * @page nios2_desc
 *
 * @brief Description of the HAL implementation for the NIOS II processor.
 *
 * @b Channels
 *
 * |HAL channel/timer						| NIOS II channel/timer					|
 * |:---------------------------------------|:----------------------------------------------|
 * |Primary RPM input channel (IC)			| SCCT channel 0 GPIO0 pin A0       			|
 * |Secondry RPM input channel (IC)			| SCCT channel 1 GPIO0 pin A1       			|
 * |Injection 1 channel	(OC)				| SCCT channel 2 GPIO1 pin B8         			|
 * |Injection 2 channel	(OC)				| SCCT channel 3 GPIO1 pin B9         			|
 * |Injection 3 channel	(OC)				| SCCT channel 4 GPIO1 pin B10         			|
 * |Injection 4 channel	(OC)				| SCCT channel 5 GPIO1 pin B11         			|
 * |Injection 5 channel	(OC)				| SCCT channel 6 GPIO1 pin B12         			|
 * |Injection 6 channel	(OC)				| SCCT channel 7 GPIO1 pin B13         			|
 * |Injection 7 channel	(OC)				| The current implementation dies not use these |
 * |Injection 8 channel	(OC)				| two channels.									|
 * |Ignition Dwell Timer 					| TIMER1         								|
 * |Ignition FireTimer 						| TIMER2        								|
 * |Ignition 1 channel (GPIO)				| not configured yet							|
 * |Ignition 2 channel (GPIO)				| not configured yet							|
 * |Ignition 3 channel (GPIO)				| not configured yet							|
 * |Ignition 4 channel (GPIO)				| not configured yet							|
 * |Ignition 5 channel (GPIO)				| not configured yet							|
 * |Ignition 6 channel (GPIO)				| not configured yet							|
 * |Ignition 7 channel (GPIO)				| The current implementation dies not use these |
 * |Ignition 8 channel (GPIO)				| two channels.									|
 *
 *
 **/

