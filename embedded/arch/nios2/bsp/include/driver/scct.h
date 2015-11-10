/**
 * $Id: scct.h 308 2015-06-12 10:51:58Z klugeflo $
 * @file scct.h
 * @brief Register map and bit definitions for SCCT, assuming
 * a 32 bit architecture.
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 * @copyright GNU General Public License v3.
 */

#ifndef DRIVER_SCCT_H
#define DRIVER_SCCT_H 1

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Registers
 * @{
 */

#define SCCT_CTR 0x00 //!< Counter registers (32 bit)
#define SCCT_PSC 0x04 //!< Prescaler (32 bit)
#define SCCT_CTR_IE 0x08 //!< Counter interrupt enable
#define SCCT_CTR_IS 0x0c //!< Counter interrupt status

#define SCCT_CH_MS 0x20 //!< Channel mode select (8 bit), 0=IC, 1=OC
#define SCCT_CH_AS 0x24 //!< Channel action select (16 bit)
#define SCCT_CH_IE 0x28 //!< Channel interrupt enable (8 bit)
#define SCCT_CH_IS 0x2c //!< Channel interrupt status (8 bit)

#define SCCT_CH_OCF 0x30 //!< Force output compare (8 bit)
#define SCCT_CH_INP 0x34 //!< Read input pins status (8 bit)
#define SCCT_CH_OUT 0x38 //!< Reat output pins status (8 bit)

#define SCCT_CH_CCR0 0x40 //!< Channel 0 capture/compare register
#define SCCT_CH_CCR1 0x44 //!< Channel 1 capture/compare register
#define SCCT_CH_CCR2 0x48 //!< Channel 2 capture/compare register
#define SCCT_CH_CCR3 0x4c //!< Channel 3 capture/compare register
#define SCCT_CH_CCR4 0x50 //!< Channel 4 capture/compare register
#define SCCT_CH_CCR5 0x54 //!< Channel 5 capture/compare register
#define SCCT_CH_CCR6 0x58 //!< Channel 6 capture/compare register
#define SCCT_CH_CCR7 0x5c //!< Channel 7 capture/compare register

/**
 *@}
 */


/**
 * @name Bit definitions
 * @{
 */

#define SCCT_CTR_I_O 0x1 //!< Counter overflow interrupt bit

#define SCCT_CH_MS_IC 0x0 //!< Input-capture mode
#define SCCT_CH_MS_OC 0x1 //!< Output-compare mode

#define SCCT_IC_NONE    0x0 //!< No IC
#define SCCT_IC_POSEDGE 0x1 //!< Capture rising edges
#define SCCT_IC_NEGEDGE 0x2 //!< Capture falling edges
#define SCCT_IC_ANYEDGE 0x3 //!< Capture any edge

#define SCCT_OC_NONE   0x0 //!< No OC output action
#define SCCT_OC_HIGH   0x1 //!< Pull OC pin to high
#define SCCT_OC_LOW    0x2 //!< Pull OC pin to low
#define SCCT_OC_TOGGLE 0x3 //!< Toggle OC pin level

/**
 * @}
 */


/**
 * @name Macros for bit shifts
 * The return values of these macros must be bitwise or'ed with the
 * corresponding register's current content.
 * @{
 */

/**
 * @brief Calculate bit for 1-bit register.
 *
 * Use this macro to calculate bitmasks for the SCCT_CH_MS, SCCT_CH_IE,
 * and SCCT_CH_OCF registers.
 * Results can also be used to test the SCCT_CH_IS, SCCT_CH_INP, and
 * SCCT_CH_OUT registers.
 *
 * @param channel For which channel?
 * @param value the value for the bit
 * @return a bit mask with the relevant bit set to the given value
 */
#define SCCT_CH_BITS_1(channel, value) (((value) << (channel)) & (1 << (channel)))

/**
 * @brief Calculate bit for 2-bit register
 * @param channel For which channel?
 * @param value the value for the bits
 * @return a bit mask with the relevant bits set to the given value
 */
#define SCCT_CH_BITS_2(channel, value) (((value) << ((channel)*2)) & (3 << ((channel)*2)))

/**
 * @brief Get bitmask for setting channel do mode value
 * @param channel Affected channel
 * @param value Target mode, one of #SCCT_CH_MS_IC or #SCCT_CH_MS_OC
 * @return corresponding bitmask
 */
#define SCCT_CH_MODE(channel, value) SCCT_CH_BITS_1((channel), (value))

/**
 * @brief Get bitmask to set given channel to input-capture mode
 * @param channel Affected channel
 * @return Bitmask to set the given channel to input-capture mode
 */
#define SCCT_CH_MODE_IC(channel) SCCT_CH_MODE((channel), SCCT_CH_MS_IC)

/**
 * @brief Get bitmask to set given channel to output-compare mode
 * @param channel Affected channel
 * @return Bitmask to set the given channel to output-compare mode
 */
#define SCCT_CH_MODE_OC(channel) SCCT_CH_MODE((channel), SCCT_CH_MS_OC)

/**
 * @brief Get bitmask to set given channel's action
 * @param channel Affected channel
 * @param value depending on the channel's mode, either one of
 * #SCCT_IC_NONE, #SCCT_IC_POSEDGE, #SCCT_IC_NEGEDGE, #SCCT_IC_ANYEDGE,
 * or #SCCT_OC_NONE, #SCCT_OC_HIGH, #SCCT_OC_LOW, #SCCT_OC_TOGGLE.
 * @return corresponding bitmask
 */
#define SCCT_CH_ACTION(channel, value) SCCT_CH_BITS_2((channel), (value))

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif // !DRIVER_SCCT_H
