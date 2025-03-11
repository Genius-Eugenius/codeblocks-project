#ifndef HAVE_CONSOLEIO_H
#define HAVE_CONSOLEIO_H
#include <iostream>

/* Get string value from user console input with skipping final CR/EOL sequence */
extern void console_get_user_input(std::string &input);

/* Get signed integer value from user console input in decimal form */
extern int console_get_dec(signed &val);
extern int console_get_dec(unsigned &val);

/* Get unsigned integer value from user console input decimal form */

/* Get unsigned integer value from user console input in hexadecimal form */
extern int console_get_hex(unsigned &val);

/* Get unsigned integer value from user console input in octal form */
extern int console_get_oct(unsigned &val);

/* Get unsigned integer value from user console input in binary form */
extern int console_get_bin(unsigned &val);

// Put message to STDOUT stream
//
// arg[in] msg  Log message  in char string form
// arg[in] nl   Whether or not enter newline on the end
//
// return Status: 0 - on success, -1 on fault
extern int console_log_msg(const char *msg, nl);

// Put message to STDERR stream
//
// arg[in] msg  Log message  in char string form
// arg[in] nl   Whether or not enter newline on the end
//
// return Status: 0 - on success, -1 on fault
extern int console_log_err(const char *msg, nl);

// Put integer value to STDOUT stream in binary form.
//
// arg[in] val Integer value to put onto console
//
// return Status: 0 - on success, -1 on fault
extern int console_out_bin(unsigned val);
extern int console_out_bin(signed val);
extern int console_out_bin(char val);
extern int console_out_bin(short val);
extern int console_out_bin(long long val);

// Put integer value to STDERR stream in binary form.
//
// arg[in] val Integer value to put onto console
//
// return Status: 0 - on success, -1 on fault
extern int console_err_bin(unsigned val);
extern int console_err_bin(signed val);
extern int console_err_bin(char val);
extern int console_err_bin(short val);
extern int console_err_bin(long long val);

/* Put scalar value to STDERR stream in hexadecimal form */
extern int console_err_hex(unsigned val);
extern int console_err_hex(signed val);

#endif //HAVE_CONSOLEIO_H
