//////////////////////////////////////////////////////////////
// Stream I/O operations:                                   //
// 1) to get vector and scalar values from input streams    //
// 2) to put vector and scalar values to output streams     //
//////////////////////////////////////////////////////////////
#ifndef HAVE_CONSOLEIO_H
#define HAVE_CONSOLEIO_H
#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////
// Global library defines                                   //
//////////////////////////////////////////////////////////////

// Default prefix string values
// for string representation of integer values
// in various enumeration base types
#define PREFIX_STR_BIN "d"      // Binary
#define PREFIX_STR_OCT "o"      // Octal
#define PREFIX_STR_HEX "0x"     // Hexadecimal
// No printable prefix for decimal representation

// Default enumeration base type - decimal
#define BASE_DFLT   base_t::BASE_DEC

// Default enumeration basis - 10, decimal enumeration base
#define BASE_DFLT_N base_n::BASE_DEC_N

// Default value type for scalar value, 'long' integer
#define SCALAR_DFLT scalar_t::TYPE_LONG

//////////////////////////////////////////////////////////////
// Global library data types                                //
//////////////////////////////////////////////////////////////

// I/O stream type
enum class stream_t
{
    STREAM_STDIN = 0,   // STDIN
    STREAM_STDOUT,      // STDOUT
    STREAM_STDERR,      // STDERR
};

// Representation type for integer values
// in stream output operations.
enum class io_t
{
    IO_FORM,    // Formatted representation with
                // enumeration base prefix,
                // printable width and leading zeros
    IO_UFOFM,   // Unformatted representation without
                // enumeration base prefix,
                // printable width and leading zeros
};

// Enumeration base type for string representation
// of integer values in console I/O operations.
enum class base_t
{
    BASE_BIN = 0,   // Binary
    BASE_OCT,       // Octal
    BASE_HEX,       // Hexadecimal
    BASE_DEC,       // Decimal
};

// Class to represent enumeration base types
// of integer values
typedef class base
{
     public:
       base_t  base_type;      // Enumeration
                                // base type
        int     base_type_i;    // Enumeration
                                // base type index
        // Constructor
        // arg[in] type Enumeration base type
        base(base_t type = BASE_DFLT);
        // Get base type in the form of
        // base type enumeration class and
        // in the form of an integer value
        base_t      type(void);
        int         type_i(void);
        // Get get enumeration base type name
        const char *name(void);
        // Get enumeration basis value
        int         basis(void);
        // Get value printable width in characters
        // for various types of integer value
        int         w_char(void);
        int         w_short(void);
        int         w_long(void);
        int         w_double(void);
} base;

// Scalar value type for string representation
// of integer values in console I/O operations.
enum class scalar_t
{
    TYPE_BYTE = 0,  // int8_t, char
    TYPE_UBYTE,     // uint8_t, unsigned char
    TYPE_SHORT,     // int16_t, short
    TYPE_USHORT,    // uint16_t, unsigned short
    TYPE_LONG,      // signed, int, int32_t
    TYPE_ULONG,     // unsigned, unsigned int, uint32_t
    TYPE_DOUBLE,    // long long, int64_t
    TYPE_UDOUBLE,   // long long, uint64_t
};

// Class to represent scalar values
typedef class scalar
{
    private:
        scalar_t    scalar_type;    // Value type
    public:
       base         scalar_base;    // Enumeration
                                    // base type
                                    // for integers
        //
        // arg[in] val_type     Scalar value
        //                      type, TYPE_LONG
        //                      on default
        // srg[in] val_base     Enumeration
        //                      base type,
        //                      BASE_DEC
        //                      on default
        scalar(scalar_t val_type = SCALAR_DFLT,
               base_t val_base = BASE_DFLT);
        scalar(void);
        // Get scalar value type
        scalar_t    val_type(void);
        // Get enumeration base type
        base_t      val_base(void);
        // Get enumeration base type index
        int         val_base_i(void);
} scalar;

//////////////////////////////////////////////////////////////
// Functions to get vector and scalar values                //
// from input stream                                        //
//////////////////////////////////////////////////////////////
// Functions to process vector values                       //
//////////////////////////////////////////////////////////////
// Functions to process string values                       //
//////////////////////////////////////////////////////////////

// Generic function to get string value from
// input stream with possible trimming final CR/EOL sequence
//
// arg[in]  stream      Stream type
// arg[in]  trim_eol    Trim CR/EOL at the end of input string
// arg[out] input       User input in string form taken from
//                      input stream
//
// return 0 - on success, -1 -on fault
extern int stream_get_str(stream_t stream,
                            bool skip_eol, std::string &input);
// Note! Function allocates memory for return value
extern int stream_get_str(stream_t stream,
                            bool skip_eol, char **input);

// Get string value from STDIN stream
// with trimming final CR/EOL sequence
//
// arg[out] input   User input in string form
//                  taken from 'cin' stream
static inline int
console_get_str(std::string &input)
{
    return stream_get_str(stream_t::STREAM_STDIN, true, input);
}
static inline int
console_get_str(char **input)
{
    return stream_get_str(stream_t::STREAM_STDIN, true, **input);
}

//////////////////////////////////////////////////////
// Functions to put string values to output stream  //
//////////////////////////////////////////////////////

// Generic function to put string value to output stream
// with possible entering final 'endl' sign
//
// arg[in] stream   Output stream type
// arg[in] put_endl Put 'endl' sign at the end of output
// arg[in] val      String value to put onto stream
//
// return 0 - on success, -1 - on fault
extern int stream_put_str(stream_t stream,
                          bool put_endl, const std::string &val);
extern int stream_put_str(stream_t stream,
                          bool put_endl, const char *val);

// Functions to put string value to STDOUT and
// STDERR streams with possible entering final 'endl' sign
//
// arg[in] put_endl Put 'endl' sign at the end of output
// arg[in] val      String value to put onto stream
//
// return 0 - on success, -1 - on fault
// To STDOUT stream
static inline int
console_put_str_out(bool put_endl, const std::string &val)
{
    return stream_put_str(stream_t::STREAM_STDOUT, put_endl, val);
}
static inline int
console_put_str_out(bool put_endl, const char *val)
{
    return stream_put_str(stream_t::STREAM_STDOUT, put_endl, val);
}
// To STDERR stream
static inline int
console_put_str_err(bool put_endl, const std::string &val)
{
    return stream_put_str(stream_t::STREAM_STDERR, put_endl, val);
}
static inline int
console_put_str_err(bool put_endl, const char *val)
{
    return stream_put_str(stream_t::STREAM_STDERR, put_endl, val);
}

// Log message to STDOUT with closing 'endl' sign
//
// arg[in] msg Message to log
//
// return 0 - on success, -1 - on fault
// To STDOUT stream
static inline int
console_log_msg(const std::string &msg)
{
    return console_put_str_out(true, msg);
}
static inline int
console_log_msg(const char *msg)
{
    return console_put_str_out(true, msg);
}

// Log message to STDERR with closing 'endl' sign
//
// arg[in] msg Message to log
//
// return 0 - on success, -1 - on fault
// To STDOUT stream
static inline int
console_log_err(const std::string &msg)
{
    return console_put_str_err(true, msg);
}
static inline int
console_log_err(const char *msg)
{
    return console_put_str_err(true, msg);
}

//////////////////////////////////////////////////////////////
// Get scalar values from input stream                      //
//////////////////////////////////////////////////////////////

// Generic function to get scalar value from input stream
//
// arg[in] type     Scalar value type
// arg[out] val     Variable to put received value to
//
// return 0 - on success, -1 - on fault
#define STREAM_GET_SCALAR(_val_type) \
extern int stream_get_scalar(stream_t stream,       \
                             scalar &type,          \
                             _val_type &val);
STREAM_GET_SCALAR(unsigned)
STREAM_GET_SCALAR(signed)
STREAM_GET_SCALAR(uint64_t)
STREAM_GET_SCALAR(int64_t)
#undef STREAM_GET_SCALAR

// Get scalar value from STDIN stream in various base
// representations
//
// arg[in] type     Scalar value type
// arg[out] val     Variable to put received value to
//
// return 0 - on success, -1 - on fault
#define CONSOLE_GET_SCALAR(_val_type) \
static inline int                                       \
console_get_scalar(scalar &type, _val_type &val)        \
{                                                       \
    return stream_get_scalar(stream_t::STREAM_STDIN,    \
                                 type, val);            \
}
CONSOLE_GET_SCALAR(unsigned)
CONSOLE_GET_SCALAR(signed)
CONSOLE_GET_SCALAR(uint64_t)
CONSOLE_GET_SCALAR(int64_t)
#undef CONSOLE_GET_SCALAR

//////////////////////////////////////////////////////
// Put scalar values to output stream               //
//////////////////////////////////////////////////////

// Put scalar value to output stream
//
// arg[in] stream   Stream to put value to
// arg[in] type     Value type
// arg[in] val      Value to put onto stream
#define CONSOLE_PUT_SCALAR_GEN
extern int stream_put_scalar_gen(stream_t stream, scalar &type, unsigned &val);

// Put scalar value to output stream in various types
// of string representations
//
// arg[in] stream   Output stream to put value to
// arg[in] base     Enumeration base for integer values
// arg[in] val Integer value to put onto console
//
// return Status: 0 - on success, -1 on fault
extern int console_out_bin(uint8_t val);
extern int console_out_bin(uint16_t val);
extern int console_out_bin(uint32_t val);
extern int console_out_bin(uint64_t val);

// Put integer value to STDERR stream in binary form.
//
// arg[in] val Integer value to put onto console
//
// return Status: 0 - on success, -1 on fault
extern int console_err_bin(uint8_t val);
extern int console_err_bin(uint16_t val);
extern int console_err_bin(uint32_t val);
extern int console_err_bin(uint64_t val);

// Put integer value to STDOUT stream in hexadecimal form.
//
// arg[in] val Integer value to put onto console
//
// return Status: 0 - on success, -1 on fault
extern int console_out_hex(uint8_t val);
extern int console_out_hex(uint16_t val);
extern int console_out_hex(uint32_t val);
extern int console_out_hex(uint64_t val);

// Put integer value to STDERR stream in hexadecimal form.
//
// arg[in] val Integer value to put onto console
//
// return Status: 0 - on success, -1 on fault
extern int console_err_hex(uint8_t val);
extern int console_err_hex(uint16_t val);
extern int console_err_hex(uint32_t val);
extern int console_err_hex(uint64_t val);

#endif //HAVE_CONSOLEIO_H
