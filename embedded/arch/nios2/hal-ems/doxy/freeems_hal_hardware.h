/**
 * $Id: freeems_hal_hardware.h 502 2015-11-05 14:18:19Z klugeflo $
 * @author Andreas Meixner
 *
 * @page hal_hardware_desc Hardware requirements
 *
 * @brief This section explains what hardware FreeEMS needs, and how to set it up properly.
 *
 * # Needed hardware
 *
 * - 3x Programmable interval timer with interrupt support
 * - 8x Output compare channel
 * - 2x Input capture channel
 * - 8x GPIO channel
 * - 16x ADC channel
 *
 * maybe
 *  - 8x PWM channel
 *  - arbitrary number of GPIO channels for debug output
 *  - USB
 *
 * # PITs (Programmable Interrupt Timer)
 *
 * ## Ignition
 * FreeEMS uses two timers to generate the output signals for the ignition system.
 * The period of the first timer (IGNITION_DWELL_PIT) will allways be set to the time when the next coil needs to be loaded.
 * The period of the second timer (IGNITION_FIRE_PIT) will allways be set to the time when the next coil needs to be fired.
 * The ISRs of the timers will set the state of the ignition channels.
 *
 *
 * #### Configuration
 * - the timers are counting down, e.g. if the interval is set to 10, the cunter value starts at 10 and decreases by one each period.
 * - the frequency is 40MHz ( each period is 0.8µs ) e.g. the countervalue will be decreased by one every 0.8µs.
 * - the timers need to be synchronized with the IC timers for the RPM sensor and the OC timers for the injection channels.
 *
 * ## RTC
 * FreeEMS internally keeps track of time. For that, one timer is needed that periodically causes an interrupt.
 *
 * #### Configuration
 * - the frequency is 8kHz (each period is 125µs)
 *
 * # Input channels
 * ## IC channels
 * FreeEMS needs up to two input compare channels for the RPM sensor. In this implementation only the NipponDenso decoder is included,
 * which needs two ICs.
 *
 * #### Configuration
 * - the timer frequency is 40MHz (each period is 0.8µ).
 * - the channel timers need to be synchronizes with the timers for the ignition and the timers for the injection channels.
 *
 * ## ADC channels
 * Freeems uses up to 16 ADC channles, to gather data from various sensors. Currently the following information is gathered an processed:
 * - inlet air temperature
 * - coolant/head temperature
 * - throttle position
 * - exhaust gas oxygen
 * - exhaust gas oxygen 2
 * - manifold absolute preasure
 * - manifold air temperature
 * - atmospheric absolute preasure
 * - battery reference voltage
 * - intercooler absolute preasure
 * - mass air flow
 *
 * #### Configuration
 * - resolution has to be 10 bit
 * - sampling time is 1µs
 *
 * # Output channels
 * ##OC channels
 * FreeEMS uses up to eight output compare channels to control up to eight injectors. Each channel is connected to one injector.
 * In this implementation only six injectors are used.
 * It is planned to support staged injection which will need additional output channels, but this version of FreeEMS does
 * not inclued a working implementation of staged injection.
 *
 * #### Configuration
 * - the timer frequency is 40MHz (each period is 0.8µs)
 * - the channel timers need to be synchrinized with the timers for the ignition and RPM sensor.
 *
 * ## GPIO channels
 * FreeEMS uses up to eight GPIO channels to control the ignition. In this implementation only six channels are used.
 *
 * #### Configuration
 * - What mode do we need here? (open drain, pupd, ...)
 *
 * ##Debug channels
 * FreeeEMS outputs signals on various GPIO channels for debugging purposes. These channels are only needed during development, #
 * they are not needed for any functionality of FreeEMS. That means number and configuraqtion of these channels are up to the developers and
 * may vary.
 *
 * As of now the HAL has support for eight debug channels.
 *
 * ## PWM channels
 * This version of FreeEMS has some code for PWM, although it does not do anything yet. For future versions PWM may be mandatory.
 * The test code supports up do eight PWM channels.
 *
 * #### Configuration
 * Not yet used, so nothing can be said about the configuration of the PWM channels.
 *
 * ##Communication
 * FreeEMS provides a module for serial communication. This can be used to output logging or debug information,
 * as well as sending commands or configuration parameters to FreeEMS.
 *
 * ####Configuration
 * To be done
 */
