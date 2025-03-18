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

// Enumeration base names in string form
#define BASE_BIN_S "binary"
#define BASE_OCT_S "octal"
#define BASE_HEX_S "hexadecimal"
#define BASE_DEC_S "decimal"

// Default enumeration base type - decimal
#define BASE_DFLT   base_t::BASE_DEC

// Default enumeration basis - 10, decimal enumeration base
#define BASE_DFLT_N base_n::BASE_DEC_N

// Default value type for scalar value, 'long' integer
#define SCALAR_DFLT scalar_t::TYPE_LONG

// I/0 streams and default stream
#define STDIN       stream_t::STREAM_STDIN
#define STDOUT      stream_t::STREAM_STDOUT
#define STDERR      stream_t::STREAM_STDERR
#define STREAM_DFLT STDIN

//////////////////////////////////////////////////////////////
// Global library data types                                //
//////////////////////////////////////////////////////////////

// Enumeration base type for string representation
// of integer values in console I/O operations.
enum class base_t
{
    BASE_BIN = 0,   // Binary
    BASE_OCT,       // Octal
    BASE_HEX,       // Hexadecimal
    BASE_DEC,       // Decimal
    BASE_INVAL,
};

// Class to represent enumeration base types
// of integer values
typedef class base
{
    private:
        base_t  base_type;      // Enumeration
                                // base type
        int     base_type_i;    // Enumeration
                                // base type index
    public:
        // Constructor
        // arg[in] type Enumeration base type
        base(base_t type = BASE_DFLT) : \
            base_type(type), base_type_i((int)type) {};
        // Get base type in the form of
        // base type enumeration class and
        // in the form of an integer value
        base_t
        type(void)
        {
            return base_type;
        }
        int
        type_i(void)
        {
            return base_type_i;
        }
        // Get enumeration base type name
        const char *name(void);
        // Get enumeration basis value
        int         basis(void);
        // Get value printable width in characters
        // for various types of integer value
        int         w_char(void);
        int         w_short(void);
        int         w_long(void);
        int         w_double(void);
        // Assignment operators
        base_t operator=(base &val);
        base_t operator=(base_t val);
        base_t operator=(int val);
        base_t operator=(const char *val);
        base_t operator=(const std::string &val);
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
    TYPE_INTS,      // Integer types boarder
    // Floating-point types are not supported yet
    TYPE_INVAL = TYPE_INTS,
};

// Class to represent scalar values of various integer
// types and enumeration base types
typedef class scalar
{
    private:
        // Scaler value data
        // Location space is enough to place
        // any scalar value from
        // uint8_t to long double
        uint8_t     scalar_val[16];
        // Scalar value type
        scalar_t    scalar_type;
    public:
        // Enumeration base
        base        enum_base;
        //
        // arg[in] val_type     Scalar value
        scalar(scalar_t val_type = SCALAR_DFLT,
               base_t val_base = BASE_DFLT);
        // Get scalar value type
        scalar_t    val_type(void);
        // Get enumeration base type
        base_t      val_base(void);
        // Get enumeration base type index
        int         val_base_i(void);
        // Get pointer to scalar value
        void*       val_ptr(void);
        uint8_t         operator=(uint8_t val);
        uint16_t        operator=(uint16_t val);
        uint32_t        operator=(uint32_t val);
        uint64_t        operator=(uint64_t val);
        int8_t          operator=(int8_t val);
        int16_t         operator=(int16_t val);
        int32_t         operator=(int32_t val);
        int64_t         operator=(int64_t val);
} scalar;

// I/O stream type
enum class stream_t
{
    STREAM_STDIN = 0,   // STDIN
    STREAM_STDOUT,      // STDOUT
    STREAM_STDERR,      // STDERR
    STREAM_INVAL,
};

// Class to represent various types of I/O
// stream with appropriate I/O operators
// for various types of I/O data.
typedef class stream {
private:
    stream_t stream_type;
public:
    // Constructor
    stream(stream_t type = STREAM_DFLT) : \
        stream_type(type) {};
    // Assignment operator
    // Set necessary stream type through
    // assignment operator
    stream_t    operator=(const stream_t type);
    // Left shift operator.
    //
    // Put data of various types onto output stream
    // (with stream_type == STOUT || stream_type == STDERR).
    //
    // stream << scalar
    // stream << string
    // stream << charstring
    int             operator<<(scalar& val);
    int             operator<<(const std::string& val);
    int             operator<<(const char* val);
    // Right shift operator.
    //
    // Get data of various types from input stream
    // (with stream_type == STDIN).
    //
    // stream >> scalar
    // stream >> string
    // stream >> charstring
    int             operator>>(scalar& val);
    int             operator>>(std::string& val);
    int             operator>>(char** val);
} stream;

//////////////////////////////////////////////////////////////
// I/O functions fot string values                          //
//////////////////////////////////////////////////////////////

// Generic function to get string value from
// input stream with possible trimming final CR/EOL sequence
//
// arg[in]  trim_eol    Trim CR/EOL at the end of input string
// arg[out] input       User input in string form taken from
//                      input stream
//
// return 0 - on success, -1 -on fault
extern int stream_get_str(std::string &input, bool trim_eol = true);
// Note! Function allocates memory for return value
extern int stream_get_str(char **input, bool trim_eol = true);

// Get string value from STDIN stream
// with trimming final CR/EOL sequence
//
// arg[out] input   User input in string form
//                  taken from 'cin' stream
static inline int
console_get_str(std::string &input)
{
    return stream_get_str(input);
}
static inline int
console_get_str(char **input)
{
    return stream_get_str(input);
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
#endif //HAVE_CONSOLEIO_H
