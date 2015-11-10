//--------------------------------------------------------------
// File     : usb_bsp.c
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <libub/usb_cdc_lolevel/usb_bsp.h>
#include <libub/usb_cdc_lolevel/usbd_conf.h>


extern USB_OTG_CORE_HANDLE           USB_OTG_dev;
extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);



//--------------------------------------------------------------
void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev)
{
  /* Configure  SOF VBUS ID DM DP Pins */
  rcc_periph_clock_enable(RCC_GPIOA);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
			GPIO8 | GPIO9 | GPIO11 | GPIO12);
	gpio_set_af(GPIOA, GPIO_AF10, GPIO8 | GPIO9 | GPIO11 | GPIO12);
  

  /* this for ID line debug */
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO10);
  gpio_set_af(GPIOA, GPIO_AF10, GPIO10);
 
  rcc_periph_clock_enable(RCC_OTGFS);
  rcc_periph_clock_enable(RCC_SYSCFG);
}

//--------------------------------------------------------------
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{
  scb_set_priority_grouping(SCB_AIRCR_PRIGROUP_GROUP2_SUB8);
  //nvic_set_priority(NVIC_OTG_FS_IRQ, 3);
  nvic_enable_irq(NVIC_OTG_FS_IRQ);
}

//--------------------------------------------------------------
void USB_OTG_BSP_uDelay (const uint32_t usec)
{
  uint32_t count = 0;
  const uint32_t utime = (120 * usec / 7);
  do
  {
    if ( ++count > utime )
    {
      return ;
    }
  }
  while (1);
}


//--------------------------------------------------------------
void USB_OTG_BSP_mDelay (const uint32_t msec)
{
  USB_OTG_BSP_uDelay(msec * 1000);   
}


//--------------------------------------------------------------
void OTG_FS_IRQHandler(void)
{
  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}




