/**
 * $Id: stm32f4.h 502 2015-11-05 14:18:19Z klugeflo $
 *
 * @page stm32f4_desc
 *
 * @brief Description of the HAL implementation for the STM32F4.
 *
 * @b Channels
 *
 * |HAL channel/timer						| STM32F4 Timer/Port/Channel					|
 * |:---------------------------------------|:----------------------------------------------|
 * |Primary RPM input channel (IC)			| TIM4 channel 1. Set to port B pin 8			|
 * |Secondry RPM input channel (IC)			| TIM4 channel 2. Set to port B pin 9			|
 * |Injection 1 channel	(OC)				| TIM3 channel 1 Set to port B pin 4			|
 * |Injection 2 channel	(OC)				| TIM3 channel 1 Set to port B pin 5			|
 * |Injection 3 channel	(OC)				| TIM3 channel 1 Set to port B pin 0			|
 * |Injection 4 channel	(OC)				| TIM3 channel 1 Set to port B pin 1			|
 * |Injection 5 channel	(OC)				| TIM4 channel 1 Set to port B pin 6			|
 * |Injection 6 channel	(OC)				| TIM4 channel 1 Set to port B pin 7			|
 * |Injection 7 channel	(OC)				| The current implementation dies not use these |
 * |Injection 8 channel	(OC)				| two channels.									|
 * |Ignition Dwell Timer 					| TIM2 channel 3								|
 * |Ignition FireTimer 						| TIM2 channel 4								|
 * |Ignition 1 channel (GPIO)				| not configured yet							|
 * |Ignition 2 channel (GPIO)				| not configured yet							|
 * |Ignition 3 channel (GPIO)				| not configured yet							|
 * |Ignition 4 channel (GPIO)				| not configured yet							|
 * |Ignition 5 channel (GPIO)				| not configured yet							|
 * |Ignition 6 channel (GPIO)				| not configured yet							|
 * |Ignition 7 channel (GPIO)				| The current implementation dies not use these |
 * |Ignition 8 channel (GPIO)				| two channels.									|
 *
 * The ignition channels are not ditrectly connected to a timer. Channel 3 an 4 of TIM2 are used to generate an interrupt
 * whenever the state of any ignition channel has to change. The ISR will then set the channel states.
 *
 **/

