/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file usbuart.c
* @brief Functions for initialising and using UART for serial output.
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/

#include <liboutput/usbuart.h>
#include <libub/stm32_ub_usb_cdc.h>
#include <libub/usb_cdc_lolevel/usbd_cdc_vcp.h>

void usbuart_init(void) {
  if (USB_CDC_NO_INIT != UB_USB_CDC_GetStatus()) {
	//TODO: Exception? Error Code?
	return;
  }
  UB_USB_CDC_Init();
}

char swirlingLineChars[4] = {'|', '/', '-', '\\'};

void usbuart_wait(void) {
  char receive_string = 0;
  int32_t waiter = 0;
  while (USB_CDC_CONNECTED != UB_USB_CDC_GetStatus())
    ;
  while (0 == UB_VCP_StringRx(&receive_string, 1)){
	if (!((waiter++) & 0xfffff))
		usbuart_puts("\rPlease press a ASCII-Key and return... ");
  }
  usbuart_puts("\r\n");
  usbuart_puts("usbuart is initialised.\r\n");
}

int32_t usbuart_putchar(int32_t c) {
  char vc = (char) (c & 0xff);
  
  if (USB_CDC_CONNECTED != UB_USB_CDC_GetStatus()) {
	//TODO: Wait for connection? Error Code?
	return -1;
  }

  UB_VCP_DataTx(vc);

  return (int32_t) vc;
}

int32_t usbuart_puts(char *p) {
  uint32_t ctr = 0;
  
  if (UB_USB_CDC_GetStatus() != USB_CDC_CONNECTED) {
	//TODO: Wait? Error Code?
	return -1;
  }
  
  while (*p != 0) {
    UB_VCP_DataTx(*p);
    ++p;
    ++ctr;
  }
  
  return ctr;
}
