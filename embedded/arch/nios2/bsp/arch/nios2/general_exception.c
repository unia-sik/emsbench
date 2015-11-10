#include <stddef.h>
#include <ptrace.h>
#include <spr-defs.h>
#include <intrinsics.h>
#include <output.h>

void handle_ge(uint32_t cause, sc_stackframe_t *sf) {
  //register uint32_t ea __asm__("ea");
  switch (cause) {
  case 2: // Internal Interrupt
  case 3: // Trap
    // both handled in exception.S
    uart_printf("Internal Interrupt or Trap caught in handle_ge() - should have been caught in exception.S already!\n");
    break;
  case 4:
    uart_printf("Unimplemented instruction\n");
    break;
  case 5:
    uart_printf("Illegal instruction @ %x - 4\n", sf->ea);
    break;
  case 6:
    uart_printf("Misaligned data address %x @ %x\n", __rdctl_badaddr(), sf->ea);
    break;
  case 7:
    uart_printf("badaddr: %x @ %x\n", __rdctl_badaddr(), sf->ea);
    while (1);
    break;
  // all other exceptions
  default:
    uart_printf("general exception %d\n", cause);
    break;
  }
  uart_printf("Stopping execution!\n");
  while (1);
}
