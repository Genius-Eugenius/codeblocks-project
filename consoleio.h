//////////////////////////////////////////////////////////////
// Stream I/O operations:                                   //
// 1) to get vector and scalar values from input streams    //
// 2) to put vector and scalar values to output streams     //
//////////////////////////////////////////////////////////////
#ifndef HAVE_CONSOLEIO_H
#define HAVE_CONSOLEIO_H
#include <iostream>

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
// of integer values.
typedef class base
{
    private:
        base_t  base_type;      // Enumeration
                                // base type.
        int     base_type_i;    // Enumeration
                                // base type index.
    public:
        // Constructor
        // arg[in] type Enumeration base type.
        base(base_t type = BASE_DFLT) : \
            base_type(type), base_type_i((int)type) {};
        // Get base type in the form of
        // base type enumeration class and
        // in the form of an integer value.
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
        // Get enumeration base type name.
        const char *name(void);
        // Get enumeration basis value.
        int         basis(void);
        // Get printable width in characters
        // for given base type for various types
        // of integer values.
        int         w_char(void);
        int         w_short(void);
        int         w_long(void);
        int         w_double(void);
        // Assignment operators.
        // Assign enumeration base type
        base_t operator=(base &val);
        base_t operator=(base_t val);
        base_t operator=(int val);
        base_t operator=(const char *val);
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
        // Get scalar value cast to
        // various integer types
        //
        // return scalar value cast to
        // integer type on success or
        // -1 cast to integer type on fault
        long                val_l(void);
        long long           val_d(void);
        unsigned long       val_ul(void);
        unsigned long long  val_ud(void);
        // Assign the type of scalar value
        scalar_t        operator=(scalar_t type)
        {
            scalar_type = type;
            return scalar_type;
        }
        // Assign scalar value and scalar type
        // from various types of integer values.
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
    stream_t    operator=(const stream_t type)
    {
        stream_type = type;
        return stream_type;
    }
    // Left shift operator.
    //
    // Put data of various scalar types onto output stream
    // (with stream_type == STOUT || stream_type == STDERR).
    //
    // stream << scalar
    int             operator<<(scalar& val);
    // Right shift operator.
    //
    // Get data of various scalar types from input stream
    // (with stream_type == STDIN).
    //
    // stream >> scalar
    int             operator>>(scalar& val);
} stream;

#endif //HAVE_CONSOLEIO_H
