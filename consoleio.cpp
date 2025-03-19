#include "consoleio.h"
#include <string>
#include <iomanip>
#include <bitset>
#include <cstring>

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

// Default prefix string values
// for string representation of integer values
// in various enumeration base types
#define PREFIX_STR_BIN "d"      // Binary
#define PREFIX_STR_OCT "o"      // Octal
#define PREFIX_STR_HEX "0x"     // Hexadecimal
// No printable prefix for decimal representation

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
base_basis[] = {BASE_BIN_N, BASE_OCT_N, BASE_HEX_N, BASE_DEC_N};

// Printable width of 'char' value in various base types
static const int
base_w_char[] =
    {BASE_BIN_W_CHAR, BASE_OCT_W_CHAR, BASE_HEX_W_CHAR, BASE_DEC_W_CHAR};

// Printable width of 'short' value in various base types
static const int
base_w_short[] =
    {BASE_BIN_W_SHORT, BASE_OCT_W_SHORT, BASE_HEX_W_SHORT, BASE_DEC_W_SHORT};

// Printable width of 'long' value in various base types
static const int
base_w_long[] =
    {BASE_BIN_W_LONG, BASE_OCT_W_LONG, BASE_HEX_W_LONG, BASE_DEC_W_LONG};

// Printable width of 'long long' value in various base types
static const int
base_w_double[] =
    {BASE_BIN_W_DOUBLE, BASE_OCT_W_DOUBLE, BASE_HEX_W_DOUBLE, BASE_DEC_W_DOUBLE};

//////////////////////////////////////////////////////
// Module global functions                          //
//////////////////////////////////////////////////////

// Return enumeration base type corresponding
// given base type name
static base_t
base_str2type(const char *val)
{
    base_t rc = base_t::BASE_INVAL;

    if (val == 0)
    {
        cerr
            << __FUNCTION__ << "() Base type value is NULL." << endl;
        return rc;
    }

    if (strcmp(val, BASE_BIN_S) == 0)
        rc = base_t::BASE_BIN;
    else if (strcmp(val, BASE_OCT_S) == 0)
        rc = base_t::BASE_OCT;
    else if (strcmp(val, BASE_HEX_S) == 0)
        rc = base_t::BASE_HEX;
    else if (strcmp(val, BASE_DEC_S) == 0)
        rc = base_t::BASE_DEC;
    else
    {
        cerr
            << __FUNCTION__ << "() Base type is invalid." << endl;
    }

    return rc;
}

// Convert value from the string form to integer.
// Octal, decimal and hexadecimal representations are supported.
// Signed and unsigned types are supported.
//
// arg[in]  str     String representation
// arg[out] val     Scalar value
//
// return: 0 - on success, -1 on fault
static int
str2scalar(string &str, scalar &val)
{
    int                 rc;
    static long         val_l;
    static long long    val_ll;
    scalar_t            val_type        = val.val_type();
    int                 basis           = val.enum_base.basis();
    const char         *base_name       = val.enum_base.name();
    const char         *val_type_name;

    try
    {
        rc = 0;

        switch (val_type)
        {
            case scalar_t::TYPE_BYTE:
            case scalar_t::TYPE_SHORT:
            case scalar_t::TYPE_LONG:
                val_l = stol(str, nullptr, basis);
                val_type_name = "long";
                break;
            case scalar_t::TYPE_UBYTE:
            case scalar_t::TYPE_USHORT:
            case scalar_t::TYPE_ULONG:
                val_l = (long)stoul(str, nullptr, basis);
                val_type_name = "unsigned long";
                break;
            case scalar_t::TYPE_DOUBLE:
                val_ll = stoll(str, nullptr, basis);
                val_type_name = "long long";
                break;
            case scalar_t::TYPE_UDOUBLE:
                val_ll = (long long)stoull(str, nullptr, basis);
                val_type_name = "unsigned long long";
                break;
            default:
                cerr << __FUNCTION__ << "() Scalar type is invalid." << endl;
                return -1;
        }
    }
    catch (invalid_argument(val))
    {
        rc = -1;
    }

    if (rc != 0)
    {
        cerr
            << __FUNCTION__
            << "() ERROR: Failed to convert string input '" << endl
            << str << endl << "' to the integer value type '"
            << val_type_name << "', enumeration base is '"
            << base_name << "'." << endl;
        return -1;
    }

    switch (val_type)
    {
        case scalar_t::TYPE_BYTE:       val = (int8_t)val_l;    break;
        case scalar_t::TYPE_SHORT:      val = (int16_t)val_l;   break;
        case scalar_t::TYPE_LONG:       val = (int32_t)val_l;   break;
        case scalar_t::TYPE_DOUBLE:     val = (int64_t)val_ll;  break;
        case scalar_t::TYPE_UBYTE:      val = (uint8_t)val_l;   break;
        case scalar_t::TYPE_USHORT:     val = (uint16_t)val_l;  break;
        case scalar_t::TYPE_ULONG:      val = (uint32_t)val_l;  break;
        case scalar_t::TYPE_UDOUBLE:    val = (uint64_t)val_ll; break;
        default:;
    }

    return 0;
}

// Get integer value from user STDIN input.
//
// arg[out] val Scalar value
//
// return: 0 - on success, -1 - on fault
static int
console_get_scalar(scalar &val)
{
    scalar_t    val_type = val.val_type();
    string      input;

    if ((int)val_type < 0 || (int)val_type >= (int)(scalar_t::TYPE_INTS))
    {
        cerr << "Stream operator >> : Scalar value type is invalid." << endl;
        return -1;
    }

    cin >> input;
    cin.ignore();

    return str2scalar(input, val);
}

// Namespace for binary output functions
namespace bin_out {
// Put integer value onto generic output in binary format.
//
// arg[in] stream   Output stream, STDOUT or STDERR
// arg[in] val      Scalar value type
//
// return Status, 0 - success, -1 - fault
static int
stream_put_int_gen(ostream &stream, scalar &val)
{
    void*       val_ptr     = val.val_ptr();
    scalar_t    val_type    = val.val_type();
    base_t      val_base    = val.val_base();
    int         p_width;

    if (val_base != base_t::BASE_BIN)
    {
        cerr
            << __FUNCTION__ << "() "
            << "enumeration base is not supported." << endl;
        return -1;
    }

    switch (val_type)
    {
        case scalar_t::TYPE_BYTE:
        case scalar_t::TYPE_UBYTE:
            p_width = val.enum_base.w_char();
            stream << setfill(FILL) << setw(p_width) << bitset<8>(*((uint8_t *)val_ptr));
            return 0;
        case scalar_t::TYPE_SHORT:
        case scalar_t::TYPE_USHORT:
            p_width = val.enum_base.w_short();
            stream << setfill(FILL) << setw(p_width) << bitset<16>(*((uint16_t *)val_ptr));
            return 0;
        case scalar_t::TYPE_LONG:
        case scalar_t::TYPE_ULONG:
            p_width = val.enum_base.w_long();
            stream << setfill(FILL) << setw(p_width) << bitset<32>(*((uint32_t *)val_ptr));
            return 0;
        case scalar_t::TYPE_DOUBLE:
        case scalar_t::TYPE_UDOUBLE:
            p_width = val.enum_base.w_double();
            stream << setfill(FILL) << setw(p_width) << bitset<64>(*((uint64_t *)val_ptr));
            return 0;
        default:
            cerr << __FUNCTION__ << "() Value type is invalid." << endl;
    }

    return -1;
}
} // namespace bin_out

// Function body macro
//
// arg _manip   I/O manip 'hex' or 'oct'
// arg _base_t  Base type 'HEX' or 'OCT'
#define STREAM_PUT_INT_GEN(_manip, _base_t) \
{                                                                       \
    scalar_t    val_type    = val.val_type();                           \
    base_t      val_base    = val.val_base();                           \
    int         p_width;                                                \
                                                                        \
    if (val_base != base_t::BASE_##_base_t)                             \
    {                                                                   \
        cerr                                                            \
         << __FUNCTION__ << "() Enumeration base is invalid." << endl;  \
        return -1;                                                      \
    }                                                                   \
                                                                        \
    switch (val_type)                                                   \
    {                                                                   \
        case scalar_t::TYPE_BYTE:                                       \
        case scalar_t::TYPE_UBYTE:                                      \
            p_width = val.enum_base.w_char();                           \
            break;                                                      \
        case scalar_t::TYPE_SHORT:                                      \
        case scalar_t::TYPE_USHORT:                                     \
            p_width = val.enum_base.w_short();                          \
            break;                                                      \
        case scalar_t::TYPE_LONG:                                       \
        case scalar_t::TYPE_ULONG:                                      \
            p_width = val.enum_base.w_long();                           \
            break;                                                      \
        case scalar_t::TYPE_DOUBLE:                                     \
        case scalar_t::TYPE_UDOUBLE:                                    \
            p_width = val.enum_base.w_double();                         \
            break;                                                      \
        default:                                                        \
            cerr                                                        \
                << __FUNCTION__ << "() Value type is invalid." << endl; \
            return -1;                                                  \
    }                                                                   \
                                                                        \
    if (val_type == scalar_t::TYPE_DOUBLE ||                            \
        val_type == scalar_t::TYPE_UDOUBLE)                             \
    {                                                                   \
        stream                                                          \
            << _manip << setfill(FILL) << setw(p_width)                 \
            << val.val_ud();                                            \
    }                                                                   \
    else                                                                \
    {                                                                   \
        stream                                                          \
            << _manip << setfill(FILL) << setw(p_width)                 \
            << val.val_ul();                                            \
    }                                                                   \
                                                                        \
    return 0;                                                           \
}

// Namespace for printout in octal format
namespace oct_out {
// Put integer value onto generic output in octal format.
//
// arg[in] stream   Output stream, STDOUT or STDERR
// arg[in] val      Scalar value type
//
// return Status, 0 - success, -1 - fault
static int
stream_put_int_gen(ostream &stream, scalar &val)
STREAM_PUT_INT_GEN(oct, OCT)
} // namespace oct_out

// Namespace for printout in hexadecimal format.
namespace hex_out {
// Put integer value onto generic output in hexadecimal format.
//
// arg[in] stream   Output stream, STDOUT or STDERR
// arg[in] val      Scalar value
//
// return 0 - success, -1 - fault
static int
stream_put_int_gen(ostream &stream, scalar &val)
STREAM_PUT_INT_GEN(hex, HEX)
} // Namespace hex_out

// Put integer value onto generic output.
// Output format depends on specified binary type.
//
// arg[in] stream   Output stream, STDOUT or STDERR
// arg[in] val      Scalar value
//
// return: 0 - success, -1 - fault
static int
stream_put_int_gen(ostream &stream, scalar &val)
{
    scalar_t    val_type        = val.val_type();
    base_t      val_base        = val.val_base();

    switch (val_base)
    {
        case base_t::BASE_BIN:
            return bin_out::stream_put_int_gen(stream, val);
        case base_t::BASE_OCT:
            return oct_out::stream_put_int_gen(stream, val);
        case base_t::BASE_HEX:
            return hex_out::stream_put_int_gen(stream, val);
        case base_t::BASE_DEC:
            break;
        default:
            cerr
                << __FUNCTION__ << "() Enumeration base is invalid." << endl;
            return -1;
    }

    // Decimal value type is here
    switch (val_type) {
        case scalar_t::TYPE_BYTE:
        case scalar_t::TYPE_SHORT:
        case scalar_t::TYPE_LONG:
            stream << val.val_l();
            break;
        case scalar_t::TYPE_UBYTE:
        case scalar_t::TYPE_USHORT:
        case scalar_t::TYPE_ULONG:
            stream << val.val_ul();
            break;
        case scalar_t::TYPE_DOUBLE:
            stream << val.val_d();
            break;
        case scalar_t::TYPE_UDOUBLE:
            stream << val.val_ud();
            break;
        default:
            cerr
                << __FUNCTION__ << "() "
                << "Integer value type is invalid." << endl;
            return -1;
    }

    return 0;
}

//////////////////////////////////////////////////////
// Class 'base' methods and operators.              //
// See definitions in consoleio.h                   //
//////////////////////////////////////////////////////

// Get enumeration base type name.
const char*
base::name(void)
{
    return base_name[base_type_i];
}

// Get printable width constants
// for given enumeration base type and various
// types of integer values.
#define BASE_GET_CONST(_field) \
int                                     \
base::_field(void)                      \
{                                       \
    return base_##_field[base_type_i];  \
}
BASE_GET_CONST(basis)
BASE_GET_CONST(w_char)
BASE_GET_CONST(w_short)
BASE_GET_CONST(w_long)
BASE_GET_CONST(w_double)
#undef BASE_GET_CONST()

// Class 'base' operators.
// Assignment operator.
// Assign enumeration base type taken from
// source value of various types.
base_t
base::operator=(base &val)
{
    base_type = val.type();
    base_type_i = (int)base_type;
    return base_type;
}
base_t
base::operator=(base_t val)
{
    if ((int)val < 0 || (int)val >= (int)(base_t::BASE_INVAL))
    {
        cerr
            << "Class 'base', operator = : Base type value is invalid." << endl;
        return base_t::BASE_INVAL;
    }

    base_type = val;
    base_type_i = (int)val;

    return base_type;
}
base_t
base::operator=(int val)
{
    if (val < 0 || val >= (int)(base_t::BASE_INVAL))
    {
        cerr
            << "Class 'base', operator = : Base type value is invalid." << endl;
        return base_t::BASE_INVAL;
    }

    base_type = (base_t)val;
    base_type_i = val;

    return base_type;
}
base_t
base::operator=(const char *val)
{
    base_t rc = base_str2type(val);

    if ((int)rc >= 0 && (int)rc < (int)(base_t::BASE_INVAL))
    {
        base_type = rc;
        base_type_i = (int)rc;
    }
    else
    {
        cerr
            << "Class 'base' operator = : Base type string value '"
            << val << "' is invalid." << endl;
        return base_t::BASE_INVAL;
    }

    return base_type;
}

//////////////////////////////////////////////////////
// Class 'scalar' methods,                          //
// see definition in consoleio.h                    //
//////////////////////////////////////////////////////

// Constructor
scalar::scalar(scalar_t val_type, base_t val_base) : \
               scalar_type(val_type)                    \
{                                                       \
    enum_base = val_base;                               \
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
    return enum_base.type();
}

// Get enumeration base type index
int
scalar::val_base_i(void)
{
    return enum_base.type_i();
}

// Get scalar value cast to various
// integer types.
long
scalar::val_l(void)
{
    switch (scalar_type)
    {
        case scalar_t::TYPE_BYTE:
            return (long)(*((int8_t *)scalar_val));
        case scalar_t::TYPE_SHORT:
            return (long)(*((int16_t *)scalar_val));
        case scalar_t::TYPE_LONG:
            return (long)(*((int32_t *)scalar_val));
        default:
            cerr
                << "scalar.val_l(): Value type is invalid." << endl;
    }
    return -1;
}
unsigned long
scalar::val_ul(void)
{
    switch (scalar_type)
    {
        case scalar_t::TYPE_UBYTE:
            return (unsigned long)(*((uint8_t *)scalar_val));
        case scalar_t::TYPE_USHORT:
            return (unsigned long)(*((uint16_t *)scalar_val));
        case scalar_t::TYPE_ULONG:
            return (unsigned long)(*((uint32_t *)scalar_val));
        default:
            cerr
                << "scalar.val_ul(): Value type is invalid." << endl;
    }
    return (unsigned long)-1;
}
long long
scalar::val_d(void)
{
    if (scalar_type == scalar_t::TYPE_DOUBLE)
        return (long long)(*((int64_t *)scalar_val));

    cerr << "scalar.val_d(): Value type is invalid." << endl;

    return -1;
}
unsigned long long
scalar::val_ud(void)
{
    if (scalar_type == scalar_t::TYPE_UDOUBLE)
        return (unsigned long long)(*((uint64_t *)scalar_val));

    cerr << "scalar.val_ud(): Value type is invalid." << endl;

    return (unsigned long long)-1;
}

// Get pointer to scalar value.
// Pointer must be cast to one of listed types
// appropriate to scalar value type:
//
// TYPE_BYTE    - (int8_t *)
// TYPE_SHORT   - (int16_t *)
// TYPE_LONG    - (int32_t *)
// TYPE_DOUBLE  - (int64_t *)
// TYPE_UBYTE   - (uint8_t *)
// TYPE_USHORT  - (uint16_t *)
// TYPE_ULONG   - (uint32_t *)
// TYPE_UDOUBLE - (uint64_t *)
void*
scalar::val_ptr(void)
{
    return scalar_val;
}

// Scalar class operators
#define SCALAR_OPERATOR_ASSIGN(_int_type, _scalar_type) \
_int_type                                               \
scalar::operator=(_int_type val)                        \
{                                                       \
    *((_int_type *)scalar_val) = val;                   \
    scalar_type = scalar_t::TYPE_##_scalar_type;        \
    return *((_int_type *)scalar_val);                  \
}
SCALAR_OPERATOR_ASSIGN(uint8_t, UBYTE)
SCALAR_OPERATOR_ASSIGN(uint16_t, USHORT)
SCALAR_OPERATOR_ASSIGN(uint32_t, ULONG)
SCALAR_OPERATOR_ASSIGN(uint64_t, UDOUBLE)
SCALAR_OPERATOR_ASSIGN(int8_t, BYTE)
SCALAR_OPERATOR_ASSIGN(int16_t, SHORT)
SCALAR_OPERATOR_ASSIGN(int32_t, LONG)
SCALAR_OPERATOR_ASSIGN(int64_t, DOUBLE)
#undef SCALAR_OPERATOR_ASSIGN

//////////////////////////////////////////////////////
// Class stream methods and operators.              //
// See definitions in consoleio.h                   //
//////////////////////////////////////////////////////

// Right shift operator: get scalar values
// from console input
//
// arg[out] val Scalar value to get
//
// return 0 - on success, -1 - on fault
int
stream::operator>>(scalar &val)
{

    if (stream_type != STDIN)
    {
        cerr << "Stream operator >> : Stream must be input stream." << endl;
        return -1;
    }

    return console_get_scalar(val);
}

// Left shift operator: put scalar values
// on stream
//
// return 0 - on success, -1 - on faults
int
stream::operator<<(scalar &val)
{
    scalar_t scalar_type = val.val_type();

    if ((int)scalar_type < 0 || (int)scalar_type >= (int)(scalar_t::TYPE_INTS))
    {
        cerr << "Stream operator << : Scalar value type is invalid." << endl;
        return -1;
    }

    if (stream_type == STDOUT)
        return stream_put_int_gen(cout, val);
    else if (stream_type == STDERR)
        return stream_put_int_gen(cerr, val);
    else
        cerr << "Stream operator << : Stream must be output stream." << endl;

    return -1;
}
