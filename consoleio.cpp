#include "consoleio.h"
#include <iomanip>
#include <bitset>
#include <string.h>

//////////////////////////////////////////////////////
// Module global namespace                          //
//////////////////////////////////////////////////////
using namespace std;

//////////////////////////////////////////////////////
// Module global macros                             //
//////////////////////////////////////////////////////
// Space symbol
#define SP ' '

// Fulfill symbol for string representation
// of integer values
#define FILL '0'

// Base names in string form
#define BASE_BIN_S "binary"
#define BASE_OCT_S "octal"
#define BASE_HEX_S "hexadecimal"
#define BASE_DEC_S "decimal"

//////////////////////////////////////////////////////
// Module global data types                         //
//////////////////////////////////////////////////////

// Enumeration basis value for various base types
enum basis_n
{
    BASE_BIN_N = 2, // Binary
    BASE_OCT_N = 8, // Octal
    BASE_HEX_N = 16,// Hexadecimal
    BASE_DEC_N = 10,// Decimal
};

// Printable number of characters in string representation
// of integer values of various types and enumeration bases
enum base_w
{
    // Binary
    BASE_BIN_W_CHAR     = 8,
    BASE_BIN_W_SHORT    = 16,
    BASE_BIN_W_LONG     = 32,
    BASE_BIN_W_DOUBLE   = 64,
    // Octal
    BASE_OCT_W_CHAR     = 3,
    BASE_OCT_W_SHORT    = 6,
    BASE_OCT_W_LONG     = 11,
    BASE_OCT_W_DOUBLE   = 22,
    // Hexadecimal
    BASE_HEX_W_CHAR     = 2,
    BASE_HEX_W_SHORT    = 4,
    BASE_HEX_W_LONG     = 8,
    BASE_HEX_W_DOUBLE   = 16,
    // Decimal
    BASE_DEC_W_CHAR     = 3,
    BASE_DEC_W_SHORT    = 5,
    BASE_DEC_W_LONG     = 10,
    BASE_DEC_W_DOUBLE   = 20,
};

//////////////////////////////////////////////////////
// Module global objects                            //
//////////////////////////////////////////////////////
// Constants used in class methods                  //
//////////////////////////////////////////////////////
// Base type name
static const char*
base_name[] = {BASE_BIN_S, BASE_OCT_S, BASE_HEX_S, BASE_DEC_S};

// Enumeration basis value
static const int
base_basis[] = {BASE_BIN_N, BASE_OCT_N, BASE_HEX_N, BASE_DEC_N);

// Printable width of 'char' value in various base types
static const size_t
base_w_char[] =
    {BASE_BIN_W_CHAR, BASE_OCT_W_CHAR, BASE_HEX_W_CHAR, BASE_DEC_W_CHAR};

// Printable width of 'short' value in various base types
static const size_t
base_w_short[] =
    {BASE_BIN_W_SHORT, BASE_OCT_W_SHORT, BASE_HEX_W_SHORT, BASE_DEC_W_SHORT};

// Printable width of 'long' value in various base types
static const size_t
base_w_long[] =
    {BASE_BIN_W_LONG, BASE_OCT_W_LONG, BASE_HEX_W_LONG, BASE_DEC_W_LONG};

// Printable width of 'long long' value in various base types
static const size_t
base_w_double[] =
    {BASE_BIN_W_DOUBLE, BASE_OCT_W_DOUBLE, BASE_HEX_W_DOUBLE, BASE_DEC_W_DOUBLE};

//////////////////////////////////////////////////////
// Class 'base' methods,                            //
// see definitions in consoleio.h                   //
//////////////////////////////////////////////////////

// Constructor
base::base(base_t type = BASE_DFLT) : base_type(type), base_type_i((int)type)
base::base(void) : base_type(BASE_DFLT), base_type_i((int)BASE_DFLT)

// Get base type
base_t
base::type(void)
{
    return base_type;
}

// Get base type index
int
base::type_i(void)
{
    return base_type_i;
}

// Get base name
const char*
base::name(void)
{
    return base_name[base_type_i];
}

// Get basis value
int
base::basis(void)
{
    return base_basis[base_type_i];
}

// Get constants
#define BASE_GET_CONST(_field) \
size_t                                  \
base::_field(void)                      \
{                                       \
    return base_##_field[base_type_i];  \
}
BASE_GET_CONST(w_char)
BASE_GET_CONST(w_short)
BASE_GET_CONST(w_long)
BASE_GET_CONST(w_double)
#undef BASE_GET_CONST()

//////////////////////////////////////////////////////
// Class 'scalar' methods,                          //
// see definitio in consoleio.h                     //
//////////////////////////////////////////////////////

// Constructor
scalar::scalar(scalar_t val_type = SCALAR_DFLT, \
               base_t val_base = BASE_DFLT) : scalar_type(val_type)
{
    scalar_base.base(val_base);
}
scalar::scalar(void) : scalar_type(SCALAR_DFLT)
{
    scalar_base.base(BASE_DFLT);
}

// Get scalar value type
scalar_t
scalar::val_type(void)
{
    return scalar_type;
}

// Get enumeration base type
base_t
scalar::val_base(void)
{
    return scalar_base.type();
}

// Get enumeration base type index
int
scalar::val_base_i(void);
{
    return scalar_base.type_i();
}


//////////////////////////////////////////////////////
// Module global functions                          //
//////////////////////////////////////////////////////

// Convert value from the string decimal form to signed integer.
//
// arg[in] str  String representation
// arg[out] val Numeric representation
//
// return Status, 0 - success, -1 - fault
static int
str_dec2signed(string &str, int &val)
{
    try
    {
        val = stoi(str);
    }
    catch (invalid_argument(str))
    {
        return -1;
    }

    return 0;
}

// Convert value from the string form to unsigned integer.
// Octal, decimal and hexadecimal representations are supported.
//
// arg[in]  str     String representation
// arg[in]  base    Enumeration base type object
// arg[out] val     Numeric representation
//
// return Status, 0 - success, -1 - fault
static int
str2unsigned(string &str, base &base, unsigned &val)
{
    try
    {
        val = stoul(str, nullptr, base::num()); stoul
    }
    catch (invalid_argument(val))
    {
        return -1;
    }

    return 0;
}

// Get unsigned integer value from user input.
//
// arg[in]  base    Enumeration base structure
// arg[out] val     Returned integer value
//
// return Status, 0 - success, -1 - fault
static int
console_get_base_unsigned(base &base, unsigned &val)
{
    int rc;
    string input;
    const char *base_str = base::name();

    console_get_user_input(input);

    if ((rc = str2unsigned(input, base, val)) != 0)
    {
        cerr
                << __FUNCTION__ << "() ERROR: Failed to convert user input '"
                << input << "' to the unsigned string value" << endl <<
                " Enumeration base is " << base_str << endl;
    }

    return rc;
}

// Generic function to get scalar values from strings
//
// arg[in]  val_str     String representation of scalar value
// arg[in]  scal_type   Scalar type of the value
// arg[out] val         Returned scalar value
//
// return Status, 0 - on success, -1 on fault
static int
str2scalar(string &val_str, scalar &scal_type, signed &val)
{
    int         rc = -1;
    scalar_t    val_type = scal_type.val_type();
    base_t      val_base = scal_type.val_base();

    if (val_type == scalar_t::TYPE_DOUBLE ||
        val_type == scalar_t::TYPE_UDOUBLE)
    {
        cerr << __FUNCTION__ "() 64-bit integers are not supported" << endl;
        return -1;
    }

    if (val_base == base_t::BASE_DEC)
    {
        if (val_type == scalar_t::TYPE_BYTE ||
            val_type == scalar_t::TYPE_SHORT ||
            val_type == scalar_t::TYPE_LONG))
        {
            rc = str_dec2signed(val_str, val);
        }
        else
        {
            rc = str2unsigned(val_str, scal_type.base, val);
        }
    }
    else
    {
        if (val_type == scalar_t::TYPE_UBYTE ||
            val_type == scalar_t::TYPE_USHORT ||
            val_type == scalar_t::TYPE_ULONG))
        {
            rc = str2unsigned(val_str, scal_type.base, val);
        }
        else
        {
            cerr << __FUNCTION__ << "() Signed integer values in non-decimal "
                "base representation are not supported" << endl;
        }
    }

    return rc;
}
static int
str2scalar(string &val_str, scalar &scal_type, int64_t &val)
{
    int         rc = -1;
    scalar_t    val_type = scal_type.val_type();
    base_t      val_base = scal_type.val_base();

    if (val_type != scalar_t::TYPE_DOUBLE &&
        val_type != scalar_t::TYPE_UDOUBLE)
    {
        cerr << __FUNCTION__ "() Only 64-bit integers are supported" << endl;
        return -1;
    }

    if (val_base == base_t::BASE_DEC)
    {
        if (val_type == scalar_t::TYPE_DOUBLE)
            rc = str_dec2signed(val_str, val);
        else
            rc = str2unsigned(val_str, scal_type.base, val);
    }
    else
    {
        if (val_type == scalar_t::TYPE_UDOUBLE)
        {
            rc = str2unsigned(val_str, scal_type.base, val);
        }
        else
        {
            cerr << __FUNCTION__ << "() Signed integer values in non-decimal "
                "base representation are not supported" << endl;
        }

    }
}

// Put integer value onto generic output stream
//
// arg[in] stream   Output etream, cout or cerr
// arg[in] val      Value to put to stream in binary form
//
// return Status, 0 - success, -1 - fault
namespace out_bin {
static int
console_put_gen_byte(ostream stream, uint8_t val)
{
    stream << setfill(FILL) << setw(BASE_2_W_CHAR) << bitset<8>(val);
    return 0;
}
static int
console_put_gen_short(ostream stream, uint16_t val)
{
    stream << setfill(FILL) << setw(BASE_2_W_SHORT) << bitset<16>(val);
    return 0;
}
static int
console_put_gen_long(ostream stream, uint32_t val)
{
    stream << setfill(FILL) << setw(BASE_2_W_LONG) << bitset<32>(val);
    return 0;
}
static int
console_put_gen_double(ostream stream, uint64_t val)
{
    stream << setfill(FILL) << setw(BASE_2_W_DOUBLE) << bitset<64>(val);
    return 0;
}
}

//////////////////////////////////////////////////////
// Exported functions                               //
//////////////////////////////////////////////////////
// Functions for I/O operations with vector values  //
//////////////////////////////////////////////////////
// Functions for I/O operations with string values  //
//////////////////////////////////////////////////////

// See definition in consoleio.h
int
stream_get_str(stream_t stream, bool skip_eol, string &input)
{
    if (stream != stream_t::STREAM_STDIN)
    {
        cerr << __FUNCTION__
            "() Stream type value of 'stream' argument "
            "is not supported" << endl;
        return -1;
    }

    cin >> input;
    if (skip_eol)
        cin.ignore();

    return 0;
}
int
stream_get_str(stream_t stream, bool skip_eol, char **input)
{
    int     rc = -1;
    string  str;

    do {
        if (input == NULL)
        {
            cerr << __FUNCTION__ "() Value 'input' is NULL" << endl;
            break;
        }

        if (stream_get_str(stream, skip_eol, str) != 0)
            break;

        if ((*input = new char[str.length() + 1]) == NULL)
        {
            cerr << __FUNCTION__ "() Memory allocation fault" << endl;
            break;
        }

        strcpy(*input, str.c_str());

        rc = 0;
    } while(0);

    return rc;
}

// See definition in consoleio.h
int
stream_put_str(stream_t stream, bool put_endl, const string &val)
{
    ostream out_stream;

    switch (stream)
    {
        case stream_t::STREAM_STDOUT:
            out_stream = cout;
            break;
        case stream_t::STREAM_STDERR:
            out_stream = cerr;
            break;
        default:
            cerr << __FUNCTION__
                "() Stream type value of 'stream' argument "
                "is not supported" << endl;
            return -1;
    }

    if (put_endl)
        out_stream << val << endl;
    else
        out_stream << val;

    return 0;
}
int
stream_put_str(stream_t stream, bool put_endl, const char *val)
{
    string  str;

    if (val == NULL)
    {
        cerr << __FUNCTION__ "() Value 'val' is NULL" << endl;
        return -1;
    }
    if (strlen(val) == 0)
    {
        cerr << __FUNCTION__ "() Argument 'val' is empty string" << endl;
    }

    str = val;

    return stream_put_str(stream, put_endl, str);
}

//////////////////////////////////////////////////////
// Functions for I/O operations with scalar values, //
//////////////////////////////////////////////////////

// See definition in consoleio.h
#define STREAM_GET_SCALAR(_val_type) \
int                                                                 \
stream_get_scalar(stream_t stream, scalar &type, _val_type &val)    \
{                                                                   \
    string input;                                                   \
                                                                    \
    if (stream_get_str(stream, true, input) != 0)                   \
        return -1;                                                  \
                                                                    \
    return str2salar(input, type, val);                             \
}
STREAM_GET_SCALAR(signed)
STREAM_GET_SCALAR(int64_t)
#undef STREAM_GET_SCALAR

// Functions to put scalar integer values onto console.
//
// See definition in consoleio.h
#define CONSOLE_PUT_GEN(_namespace, _name, _stream) \
int                                                         \
console_##_name##_bin(uint8_t val)                          \
{                                                           \
    return _namespace::console_put_gen_byte(_stream, val);  \
}                                                           \
int                                                         \
console_##_name##_bin(uint16_t val)                         \
{                                                           \
    return _namespace::console_put_gen_short(_stream, val); \
}                                                           \
int                                                         \
console_##_name##_bin(uint32_t val)                         \
{                                                           \
    return _namespace::console_put_gen_long(_stream, val);  \
}                                                           \
int                                                         \
console_##_name##_bin(uint64_t val)                         \
{                                                           \
    return _nemespace::console_put_gen_double(_stream, val);\
}
CONSOLE_PUT_GEN(out_bin, out, cout)
CONSOLE_PUT_GEN(out_bin, err, cerr)
#undef

