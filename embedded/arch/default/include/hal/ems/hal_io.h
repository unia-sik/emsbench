/*
 * This file is part of EmsBench.
 *
 * Copyright 2015 University of Augsburg
 *
 * EmsBench is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EmsBench is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EmsBench.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * $Id: hal_io.h 502 2015-11-05 14:18:19Z klugeflo $
 * @ingroup halInterface
 * @brief General definitions fpr IO.
 * @file hal_io.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef HAL_IO_H_
#define HAL_IO_H_

/**
 * @author Andreas Meixner
 * @brief This enum defines all available I/O channels FreeEMS may use.
 *
 *
 */
typedef enum channel_ids {
  /**
   * ID of the input channel that is connected to the primary wheel of the rev
   * counter.
   */
  PRIMARY_RPM_INPUT = 0,
  /**
   * ID of the input channel that is connected to the secondary wheel of the rev
   * counter.
   */
  SECONDARY_RPM_INPUT = 1,
  /**
   * ID of the output channel that is connected to the main injection of the
   * first zylinder.
   */
  INJECTION1_OUTPUT = 10,
  /**
   * ID of the output channel that is connected to the main injection of the
   * second zylinder.
   */
  INJECTION2_OUTPUT = 11,
  /**
   * ID of the output channel that is connected to the main injection of the
   * zhird zylinder.
   */
  INJECTION3_OUTPUT = 12,
  /**
   * ID of the output channel that is connected to the main injection of the
   * fourth zylinder.
   */
  INJECTION4_OUTPUT = 13,
  /**
   * ID of the output channel that is connected to the main injection of the
   * fifth zylinder.
   */
  INJECTION5_OUTPUT = 14,
  /**
   * ID of the output channel that is connected to the main injection of the
   * sixth zylinder.
   */
  INJECTION6_OUTPUT = 15,
  /**
   * ID of the output channel that is connected to the main injection of the
   * seventh zylinder.
   */
  INJECTION7_OUTPUT = 16,
  /**
   * ID of the output channel that is connected to the main injection of the
   * eighth zylinder.
   */
  INJECTION8_OUTPUT = 17,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * first zylinder.
   */
  STAGED_INJECTION1_OUTPUT = 30,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * second zylinder.
   */
  STAGED_INJECTION2_OUTPUT = 31,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * third zylinder.
   */
  STAGED_INJECTION3_OUTPUT = 32,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * fourth zylinder.
   */
  STAGED_INJECTION4_OUTPUT = 33,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * fifth zylinder.
   */
  STAGED_INJECTION5_OUTPUT = 34,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * sixth zylinder.
   */
  STAGED_INJECTION6_OUTPUT = 35,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * seventh zylinder.
   */
  STAGED_INJECTION7_OUTPUT = 36,
  /**
   * ID of the output channel that is connected to the staged injection of the
   * eighth zylinder.
   */
  STAGED_INJECTION8_OUTPUT = 37,
  /**
   * ID of the channel that causes the ignition coil of the first zylinder.
   * Pulling this pin up means charging the coil, pulling it down fires
   * theignition.
   */
  IGNITION1_OUTPUT = 50,
  /**
   * ID of the channel that causes the ignition coil of the second zylinder to
   * charge up. Pulling this pin up means charging the coil, pulling it down
   * fires theignition.
   */
  IGNITION2_OUTPUT = 51,
  /**
   * ID of the channel that causes the ignition coil of the third zylinder to
   * charge up. Pulling this pin up means charging the coil, pulling it down
   * fires theignition.
   */
  IGNITION3_OUTPUT = 52,
  /**
   * ID of the channel that causes the ignition coil of the fourth zylinder to
   * charge up. Pulling this pin up means charging the coil, pulling it down
   * fires theignition.
   */
  IGNITION4_OUTPUT = 53,
  /**
   * ID of the channel that causes the ignition coil of the fifth zylinder to
   * charge up. Pulling this pin up means charging the coil, pulling it down
   * fires theignition.
   */
  IGNITION5_OUTPUT = 54,
  /**
   * ID of the channel that causes the ignition coil of the sixth zylinder to
   * charge up. Pulling this pin up means charging the coil, pulling it down
   * fires theignition.
   */
  IGNITION6_OUTPUT = 55,
  /**
   * ID of the channel that causes the ignition coil of the seventh zylinder to
   * charge up. Pulling this pin up means charging the coil, pulling it down
   * fires theignition.
   */
  IGNITION7_OUTPUT = 56,
  /**
   * ID of the channel that causes the ignition coil of the eighth zylinder to
   * charge up. Pulling this pin up means charging the coil, pulling it down
   * fires theignition.
   */
  IGNITION8_OUTPUT = 57,
  /**
   * ID of the first GPIO channel used for debugoutput.
   * This was channel 0 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_1 = 100,
  /**
   * ID of the second GPIO channel used for debugoutput.
   * This was channel 1 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_2 = 101,
  /**
   * ID of the third GPIO channel used for debugoutput.
   * This was channel 2 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_3 = 102,
  /**
   * ID of the fourth GPIO channel used for debugoutput.
   * This was channel 3 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_4 = 103,
  /**
   * ID of the fifth GPIO channel used for debugoutput.
   * This was channel 4 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_5 = 104,
  /**
   * ID of the sixth GPIO channel used for debugoutput.
   * This was channel 5 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_6 = 105,
  /**
   * ID of the seventh GPIO channel used for debugoutput.
   * This was channel 6 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_7 = 106,
  /**
   * ID of the eighth GPIO channel used for debugoutput.
   * This was channel 7 on port J on the original FreeEMS board.
   */
  DEBUG_OUTPUT_8 = 107
} channelid_t;

/**
 * @author Andreas Meixner
 * This array is only needed internally by the INJECTIONX_OUTPUT(channelNumber)
 * macro.
 */
extern channelid_t injectionOutputChannels[];
/**
 * @author Andreas Meixner
 * This array is only needed internally by the IGNITIONX_OUTPUT(channelNumber)
 * macro.
 */
extern channelid_t ignitionChannels[];
/**
 * @author Andreas Meixner
 * @brief This enum lists all possible states for a single pin.
 */
typedef enum pinstates {
  /**
   * Indicates that the pin state is low.
   */
  LOW = 0,
  /**
   * Indicates that the pin state is high.
   */
  HIGH = 1
} pinstate_t;

/**
 * @author Andreas Meixner
 * @brief This macro is used to get the channel ID of the n-th injection channel.
 * Internally FreeEMS referes to the injection channels by number, starting with
 * 0 for the first channel, 1 for the second and so on.
 * This macro returns the actual channel ID for the given channel number.
 * @seealso channelid_t
 */
#define INJECTIONX_OUTPUT(channelNumber) injectionOutputChannels[channelNumber]

/**
 * @author Andreas Meixner
 * @brief This macro is used to get the channel ID of the n-th ignition channel.
 * Internally FreeEMS referes to the igniotion channels by number, starting with
 * 0 for the first channel, 1 for the second and so on.
 * This macro returns the actual channel ID for the given channel number.
 * @seealso channelid_t
 */
#define IGNITIONX_OUTPUT(channelNumber) ignitionChannels[channelNumber]
#endif /* HAL_IO_H_ */
