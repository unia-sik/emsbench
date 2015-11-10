/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file gprintf.c
* @brief
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/



/***********************************************************

	Note: if _gprintf is used with a buffer and without
		  a putchar-function, output will be cut if it
		  does not fit in buffer.

***********************************************************/


#include <stdarg.h>
#include <stdint.h>
#include <intrinsics.h>
#include <stddef.h>
#include <basic/gprintf.h>

#define FLAG_ZERO			0x01
#define FLAG_RIGHT			0x02
#define FLAG_ALTERNATE_FORM	0x04
#define FLAG_SPACE			0x08
#define FLAG_SIGN			0x10



//! put a character into buffer or print it directly
/**
 * buf must be global variable, all others must be declard inside
 * the calling method.
 *
 * hint: to ignore return value, use (void)_GPRINT_PUTCHAR(c)
 *
 * \param	uint8_t c	character
 * \return	1		number of printed/buffered bytes
 * 				(always 1 at the moment)
 */

#define _GPRINT_PUTCHAR(c)						\
  1;									\
  if(buf == NULL && put_fn != NULL)	{				\
    put_fn((uint32_t)c);						\
  } else {								\
    if(buf_pos < buf_len-1) {						\
      buf[buf_pos++] = c;						\
    } else if(put_fn != NULL) {						\
      put_fn((uint32_t)buf);						\
      buf_pos = 0;							\
    }									\
  }

//! if output is bufferd, print	output now
/**
 *	no parameters and no return value
 */
#define _GPRINT_BUF_FLUSH()						\
  if(buf != NULL && put_fn != NULL)	{				\
    buf[buf_pos] = '\0';						\
    put_fn((uint32_t)buf);						\
    buf_pos = 0;							\
  }



//! print a character
/**
 * this methods prints a character (called if %c occurs)
 *
 * \param	uint8_t* buf			output buffer or NULL if direct output
 * \param	uint32_t buf_len		length of buffer or 0 if direct output
 * \param	uint32_t* buf_pos_ptr	pointer to buf_pos used in calling
 * 									method.  Will be incremented in this
 * 									function
 * \param	int32_t(*put_fn)(int32_t)	function pointer to
 * 									output method for either flushing
 * 									buffer or direct output, depending on
 * 									value of buf.
 * \param	uint8_t c				character to print
 *
 * \return	uint32_t				numbers of bytes output or added to
 * 									buffer.  At the moment, always 1 is
 *									returned because only ASCII is allowed.
 */
static uint32_t _gprint_char(char * buf, uint32_t buf_len, uint32_t *buf_pos_ptr, int32_t(*put_fn)(int32_t), char c) {
  uint32_t ctr = 0;
  uint32_t buf_pos;

  buf_pos = *buf_pos_ptr;

  ctr = _GPRINT_PUTCHAR(c);

  *buf_pos_ptr = buf_pos;

  return ctr;
}

//! print a \0 terminated string
/**
 * this methods prints a string (called if %s occurs)
 *
 * \param	uint8_t* buf			output buffer or NULL if direct output
 * \param	uint32_t buf_len		length of buffer or 0 if direct output
 * \param	uint32_t* buf_pos_ptr	pointer to buf_pos used in calling
 * 									method.  will be incremented in this
 * 									function
 * \param	int32_t(*put_fn)(int32_t)	function pointer to
 * 									output method for either flushing
 * 									buffer or direct output, depending on
 * 									value of buf.
 * \param	char* s					string to print, must be terminated
 *									with '\0'
 *
 * \return	uint32_t				numbers of bytes output or added to
 * 									buffer.  At the moment, only ASCII
 * 									is supported, so number of bytes is
 * 									equal to number of characters (without
 * 									trailing '\0').
 */
static uint32_t _gprint_string(char * buf, uint32_t buf_len, uint32_t *buf_pos_ptr, int32_t(*put_fn)(int32_t), char * s) {
  uint32_t c = 0;
  uint32_t buf_pos;

  buf_pos = *buf_pos_ptr;
  while(*s) {
    c += _GPRINT_PUTCHAR(*s++);
  }

  *buf_pos_ptr = buf_pos;
  return c;
}

//! macro for creating methods to handle different widths of numeric
//! values.
/**
 * macro for different widths of numeric values (may be used to create
 * methods for 8-, 16-, 32- and 64-bit values
 *
 * notice:	parameters are described below when this macro is used.
 *
 * \param	num_bits				with of value in bits (use only
 * 									common values (8, 16, 32, 64)
 *
 * \return	uint32_t				numbers of bytes output or added to
 * 									buffer.
 */
#define _GPRINT_NUM_FN(num_bits)					\
  /*static*/ uint32_t _gprint_num_ ## num_bits ## bits(			\
						   char * buf, uint32_t buf_len, uint32_t *buf_pos_ptr,	\
						   int32_t(*put_fn)(int32_t), uint ## num_bits ## _t v,	\
						   uint8_t base, uint8_t sign, uint8_t width, uint8_t flag, \
						   char letter) {	\
  									\
    register uint8_t c = 0;						\
    register uint8_t i = 0;						\
    register uint8_t w = 0;						\
    uint8_t chars[15];							\
    uint32_t buf_pos;							\
    									\
    buf_pos = *buf_pos_ptr;						\
    									\
    if(sign) {								\
      if((int ## num_bits ## _t)v < 0) {				\
	v = -v;								\
	c += _GPRINT_PUTCHAR('-');					\
	if(width > 0)							\
	  width--;							\
      } else if(flag & FLAG_SIGN) {					\
	c += _GPRINT_PUTCHAR('+');					\
	if(width > 0)							\
	  width--;							\
      } else if(flag & FLAG_SPACE) {					\
	c += _GPRINT_PUTCHAR(' ');					\
	if(width > 0)							\
	  width--;							\
      }									\
    }									\
    									\
    if(v == 0) {							\
      chars[i++] = 0;							\
      w++;								\
    }									\
    									\
    while(v != 0) {							\
      chars[i++] = v % base;						\
      v /= base;							\
      w++;								\
    }									\
    									\
    if(!(flag & FLAG_RIGHT) && (width > 0)) {				\
      for(; width>w; width--) {						\
	if(flag & FLAG_ZERO) {						\
	  c += _GPRINT_PUTCHAR('0');					\
	} else {							\
	  c += _GPRINT_PUTCHAR(' ');					\
	}								\
      }									\
    }									\
    									\
    for(; i>0; i--) {							\
      if(chars[i-1] < 10)	{					\
	c += _GPRINT_PUTCHAR(chars[i-1]+'0');				\
      } else {								\
	c += _GPRINT_PUTCHAR(chars[i-1]+letter-10);			\
      }									\
    }									\
    									\
    if((flag & FLAG_RIGHT) && (width > 0)) {				\
      for(; width>w; width--) {						\
	c += _GPRINT_PUTCHAR(' ');					\
      }									\
    }									\
    									\
    *buf_pos_ptr = buf_pos;						\
    									\
    return c;								\
  }

//! print numeric value with 8/16/32 bits.
/**
 * this methods prints a numeric value and formats it regarding the
 * given parameters.
 *
 * \param uint8_t* buf			output buffer or NULL if direct output
 * \param uint32_t buf_len		length of buffer or 0 if direct output
 * \param uint32_t* buf_pos_ptr	pointer to buf_pos used in calling
 * 					method.  will be incremented in this
 * 					function
 * \param int32_t(*put_fn)(int32_t)	function pointer to
 * 					output method for either flushing
 * 					buffer or direct output, depending on
 * 					value of buf.
 * \param uint??_t v			value to print.  With must match the
 * 					function, conversion to signed value
 * 					is done internally.
 * \param uint8_t	base		base for conversion (10: decimal,
 * 					16: hexadecimal, ...)
 * \param uint8_t	sign		0: value is unsigned, else value is
 * 					signed
 * \param uint8_t	width		width of output, evtl. filled with
 * 					' ' or 0.
 * \param uint8_t	flag		format flags
 * \param char	letter			letter to use for numbers > 9
 * 					usually 'a' or 'A'
 *
 * \return uint32_t			numbers of bytes output or added to
 * 					buffer.
 */
_GPRINT_NUM_FN(8)
_GPRINT_NUM_FN(16)
_GPRINT_NUM_FN(32)
//_GPRINT_NUM_FN(64)



uint32_t gprintf(char * buf, uint32_t buf_len, int32_t(*put_fn)(int32_t), const char * format, ...) {
  va_list ap;
  uint32_t ctr;

  va_start(ap, format);
  ctr = gprintf_va(buf, buf_len, put_fn, format, ap);
  va_end(ap);

  return ctr;
}

//! format a given string
/**
 * a given string is formatted regarding the most common rules of the
 * usage of %.  if a buffer is given, output is buffered, otherwise
 *
 *
 * \param uint8_t* buf			output buffer or NULL if direct output
 * \param uint32_t buf_len		length of buffer or 0 if direct output
 * \param int32_t(*put_fn)(int32_t)	function pointer to
 * 					output method for either flushing
 * 					buffer or direct output, depending on
 * 					value of buf.  be carefull: for direct
 * 					output, put_fn is given a single
 * 					character (casted to uint32_t).  In
 * 					case of buffering, put_fn has to be
 * 					a puts-like function, the parameter
 * 					is a \0-terminated string, but casted
 * 					to uint32_t!
 * \param uint8_t* format		\0-terminated string to parse
 * \param ...				values to replace each single
 * 					%-commando, done in given order
 *
 * \return uint32_t		numbers of bytes output or added to
 * 				buffer.  at the moment, always 1 is
 *				returned because only ASCII is allowed.
 */
uint32_t gprintf_va(char * buf, uint32_t buf_len, int32_t(*put_fn)(int32_t), const char * format, va_list ap) {

  //	va_list ap;
  uint32_t c = 0, buf_pos = 0;
  uint8_t arg_size;
  uint8_t width;
  uint8_t flag;
  uint8_t base, sign;
  char letter;

  //va_start(ap, format);

  for(; *format; format++) {

    if(*format == '%') {
      format++;

      arg_size = 32;
      width = 0;
      flag = 0;
      base = 10;
      sign = 0;
      letter = 'a';

      if(*format == '\0') {
        break;
      }

      if(*format == '%') {
        c += _GPRINT_PUTCHAR('%');
        continue;
      }

      if(*format == '-') {
        flag |= FLAG_RIGHT;
        format++;
      }

      if(*format == '#') {
        flag |= FLAG_ALTERNATE_FORM;
        format++;
      }

      if(*format == '0') {
        flag |= FLAG_ZERO;
        format++;
      }

      if(*format == ' ') {
        flag |= FLAG_SPACE;
        format++;
      }

      if(*format == '+') {
        flag |= FLAG_SIGN;
        format++;
      }
      /* format with */
      for(; (*format > '0') && (*format < '9'); format++) {
        width *= 10;
        width += *format-'0';
      }

      /* length modifiers for short and short short */
      for(; *format == 'h' && (arg_size > 1); format++) {
        arg_size >>= 1;
      }

      /* ignore first l (long int is default) */
      if(*format == 'l') {
        format++;
      }

      /* length modifiers for long long */
      for(; *format == 'l' && (arg_size < 8); format++) {
        arg_size <<= 1;
      }

      switch(*format) {
      case 'c':
        c += _gprint_char(buf, buf_len, &buf_pos, put_fn,
                          (char)va_arg(ap, uint32_t));
        continue;
      case 's':
        c += _gprint_string(buf, buf_len, &buf_pos, put_fn,
                            (char*)va_arg(ap, char*));
        continue;

      case 'u':
        sign = 0;
        base = 10;
        break;
      case 'd':
      case 'i':
        sign = 1;
        base = 10;
        break;
      case 'p':
        flag = FLAG_ALTERNATE_FORM|FLAG_ZERO;
        width = 8;
        sign = 0;
        base = 16;
        break;
      case 'x':
        sign = 0;
        base = 16;
        break;
      case 'X':
        sign = 0;
        base = 16;
        letter = 'A';
        break;
      case 'B':
      case 'b':
        base = 2;
        sign = 0;
        break;
      case 'O':
      case 'o':
        base = 8;
        sign = 0;
        break;
      default:
        c += _GPRINT_PUTCHAR('%');
        c += _GPRINT_PUTCHAR(*format);
        continue;
      }
      if(flag & FLAG_ALTERNATE_FORM) {
        switch(base) {
        case 2:
          c += _GPRINT_PUTCHAR('B');
          break;
        case 8:
          c += _GPRINT_PUTCHAR('0');
          break;
        case 16:
          c += _GPRINT_PUTCHAR('0');
          c += _GPRINT_PUTCHAR('x');
          break;
        }
      }
      switch(arg_size) {
      case 8 :
        c += _gprint_num_8bits (buf, buf_len, &buf_pos,
                                put_fn, (uint8_t) va_arg(ap, uint32_t),
                                base, sign, width, flag, letter);
        break;
      case 16:
        c += _gprint_num_16bits(buf, buf_len, &buf_pos,
                                put_fn, (uint16_t)va_arg(ap, uint32_t),
                                base, sign, width, flag, letter);
        break;
      case 32:
        c += _gprint_num_32bits(buf, buf_len, &buf_pos,
                                put_fn, (uint32_t)va_arg(ap, uint32_t),
                                base, sign, width, flag, letter);
        break;
        /*	case 64: c += _gprint_num_64bits(buf, buf_len, &buf_pos,
        	put_fn, (uint64_t)va_arg(ap, uint64_t),
        	base, sign, width, flag, letter);
        	break;
        */
      }

      continue;
    }

    /* not related to format command */
    c += _GPRINT_PUTCHAR(*format);

  }

  //	va_end(ap);

  /* flush buffer if used */
  _GPRINT_BUF_FLUSH();

  return c;
}

