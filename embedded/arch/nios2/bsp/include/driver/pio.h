/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file pio.h
* @brief Programming tools for PIOs
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/
#ifndef PIO_H
#define PIO_H 1

#ifdef __cplusplus
extern "C" {
#endif

#define PIO_DATA    0x00
#define PIO_DIR     0x04
#define PIO_IM      0x08
#define PIO_EC      0x0c
#define PIO_OS      0x10
#define PIO_OC      0x14

#ifdef __cplusplus
}
#endif

#endif /* PIO_H */
