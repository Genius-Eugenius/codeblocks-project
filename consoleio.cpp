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
// Class 'base' methods,                            //
// see definitions in consoleio.h                   //
//////////////////////////////////////////////////////

// Return enumeration base type corresponding
// given base type name
static base_t
base_str2type(const char *strtype)
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

// Get base name
const char*
base::name(void)
{
    return base_name[base_type_i];
}

// Get constants
#define BASE_GET_CONST(_field) \
int                                     \
base::_field(vvaloid)                      \
{                                       \
    return base_##_field[base_type_i];  \
}
BASE_GET_CONST(basis)
BASE_GET_CONST(w_char)
BASE_GET_CONST(w_short)
BASE_GET_CONST(w_long)
BASE_GET_CONST(w_double)
#undef BASE_GET_CONST()

// Class base operators
// Assignment operator
base_t
operator=(const base &val)
{
    base_type = val.type();
    base_type_i = (int)base_type;
    return base_type;
}
base_t
operator=(base_t val)
{
    if ((int)val < 0 || (int)val >= (int)(base_t::BASE_INVAL))
    {
        cerr
            << __FUNCTION__ << "() Base type value is invalid." << endl;
        return base_t::BASE_INVAL;
    }

    base_type = val;
    base_type_i = (int)val;

    return base_type;
}
base_t
operator=(int val)
{
    if (val < 0 || val >= (int)(base_t::BASE_INVAL))
    {
        cerr
            << __FUNCTION__ << "() Base type value is invalid." << endl;
        return base_t::BASE_INVAL;
    }

    base_type = (base_t)val;
    base_type_i = val;

    return base_type;
}
base_t
operator=(const char *val)
{
    base_t rc = base_str2type(val);

    if ((int)rc >= 0 && (int)rc < (int)(base_t::BASE_INVAL))
    {
        base_type = rc;
        base_type_i = (int)rc;
    }

    return base_type;
}
base_t
operator=(const std::string &val)
{
    const char *charstr = val.c_str();
    base_t rc = base_str2type(charstr);

    if ((int)rc >= 0 && (int)rc < (int)(base_t::BASE_INVAL))
    {
        base_type = rc;
        base_type_i = (int)rc;
    }

    return base_type;
}

//////////////////////////////////////////////////////
// Class 'scalar' methods,                          //
// see definitio in consoleio.h                     //
//////////////////////////////////////////////////////

// Constructor
scalar::scalar(scalar_t val_type, \
               base_t val_base) : scalar_type(val_type) \
{                                                       \
    scalar_base.base_type = val_base;                   \
    scalar_base.base_type_i = (int)val_base;            \
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
scalar::val_base_i(void)
{
    return scalar_base.type_i();
}

//////////////////////////////////////////////////////
// Module global functions                          //
//////////////////////////////////////////////////////

// Convert value from the string form to integer.
// Octal, decimal and hexadecimal representations are supported.
// Signed and unsigned types are supported.
//
// arg[in]  str     String representation
// arg[in]  base    Enumeration base type object
//
// return:
// On success - pointer to the returned integer value, must be cast
// to the type (long long *) for all 64-bit integer types
// and to (long *) for all other integer types,
// On fault - NULL pointer.
static void*
str2int(string &str, scalar &type)
{
    static long         val_l;
    static long long    val_ll;
    scalar_t            val_type = type.val_type();
    base_t              val_base = type.val_base();
    const char         *base_name = type.base.name();
    const char         *val_type_name;
    void               *retval = 0;

    try
    {
        switch (val_type)
        {
            case scalar_t::TYPE_BYTE:
            case scalar_t::TYPE_SHORT:
            case scalar_t::TYPE_LONG:
                val_l = stol(str, nullptr, val_base);
                val_type_name = "long";
                retval = &val_l;
                break;
            case scalar_t::TYPE_UBYTE:
            case scalar_t::TYPE_USHORT:
            case scalar_t::TYPE_ULONG:
                val_l = (long)stoul(str, nullptr, val_base);
                val_type_name = "unsigned long";
                retval = &val_l;
                break;
            case scalar_t::TYPE_DOUBLE:
                val_ll = stoll(str, nullptr, val_base);
                val_type_name = "long long";
                retval = &val_ll;
                break;
            case scalar_t::TYPE_UDOUBLE:
                val_ll = (long long)stoull(str, nullptr, val_base);
                val_type_name = "unsigned long long";
                retval = &val_ll;
                break;
            default:
                cerr << __FUNCTION__ << "() Scalar type is invalid." << endl;
                return 0;
        }
    }
    catch (invalid_argument(val))
    {
        retval = 0;
    }

    if (retval == 0)
    {
        cerr
            << __FUNCTION__  <<
            << "() ERROR: Failed to convert string input '" << endl
            << input << endl << "' to the integer value type '"
            << val_type_name << "', enumeration base is '"
            << base_str << "'." << endl;
    }

    return retval;
}

// Get integer value from user STDIN input.
//
// arg[in] type     Integer value type and enumeration base
//
// return:
// On success - pointer to the returned integer value, must be cast
// to the type (long long *) for all 64-bit integer types
// and to (long *) for all other integer types,
// On fault - NULL pointer.
static void*
console_get_int(scalar &type)
{
    void       *retval = 0;
    string      input;

    if (console_get_str(input) != 0)
        retval = str2int(input, type);

    return retval;
}

// Namespace for binary output functions
namespace bin_out {
// Put integer value onto generic output in binary format.
//
// arg[in] stream   Output stream, STDOUT or STDERR
// arg[in] type     Integer value type
// arg[in] val_ptr  Pointer to inter value
//
// return Status, 0 - success, -1 - fault
static int
stream_put_int_gen(ostream stream, scalar &type, void *val_ptr)
{
    scalar_t    val_type = type.val_type();
    base_t      val_base = type.val_base();
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
            p_width = type.scalar_base.w_char();
            stream << setfill(FILL) << setw(p_width) << bitset<8>(*((uint8_t *)val_ptr));
            return 0;
        case scalar_t::TYPE_SHORT:
        case scalar_t::TYPE_USHORT:
            p_width = type.scalar_base.w_short();
            stream << setfill(FILL) << setw(p_width) << bitset<16>(*((uint16_t *)val_ptr));
            return 0;
        case scalar_t::TYPE_LONG:
        case scalar_t::TYPE_ULONG:
            p_width = type.scalar_base.w_long();
            stream << setfill(FILL) << setw(p_width) << bitset<32>(*((uint32_t *)val_ptr));
            return 0;
        case scalar_t::TYPE_DOUBLE:
        case scalar_t::TYPE_UDOUBLE:
            p_width = type.scalar_base.w_double();
            stream << setfill(FILL) << setw(p_width) << bitset<64>(*((uint64_t *)val_ptr));
            return 0;
        default:
            cerr << __FUNCTION__ << "() Value type is invalid"
    }

    return -1;
}
}

// Namespace for printout in octal format
namespace oct_out {
// Put integer value onto generic output in octal format.
//
// arg[in] stream   Output stream, STDOUT or STDERR
// arg[in] type     Integer value type
// arg[in] val_ptr  Pointer to inter value
//
// return Status, 0 - success, -1 - fault
static int
stream_put_int_gen(ostream stream, scalar &type, void *val_ptr)
{
    uint8_t     val_c = *((uint8_t *)val_ptr);
    uint16_t    val_s = *((uint16_t *)val_ptr);
    uint32_t    val_l = *((uint32_t *)val_ptr);
    uint64_t    val_d = *((uint64_t *)val_ptr);
    scalar_t    val_type = type.val_type();
    base_t      val_base = type.val_base();
    int         p_width;

    if (val_base != base_t::BASE_OCT)
    {
        cerr << __FUNCTION__ << "() Enumeration base is invalid." << endl;
        return -1;
    }

    switch (val_type)
    {
        case scalar_t::TYPE_BYTE:
        case scalar_t::TYPE_UBYTE:
            p_width = type.scalar_base.w_char();
            stream << oct << setfill(FILL) << setw(p_width) << val_c;
            return 0;
        case scalar_t::TYPE_SHORT:
        case scalar_t::TYPE_USHORT:
            p_width = type.scalar_base.w_short();
            stream << oct << setfill(FILL) << setw(p_width) << val_s;
            return 0;
        case scalar_t::TYPE_LONG:
        case scalar_t::TYPE_ULONG:
            p_width = type.scalar_base.w_long();
            stream << oct << setfill(FILL) << setw(p_width) << val_l;
            return 0;
        case scalar_t::TYPE_DOUBLE:
        case scalar_t::TYPE_UDOUBLE:
            p_width = type.scalar_base.w_double();
            stream << oct << setfill(FILL) << setw(p_width) << val_l;
            return 0;
        default:
            cerr << __FUNCTION__ << "() Value type is invalid"
    }

    return -1;
}
}

// Namespace for printout in hexadecimal format.
namespace oct_out {
// Put integer value onto generic output in hexadecimal format.
//
// arg[in] stream   Output stream, STDOUT or STDERR
// arg[in] type     Integer value type
// arg[in] val_ptr  Pointer to inter value
//
// return 0 - success, -1 - fault
static int
stream_put_int_gen(ostream stream, scalar &type, void *val_ptr)
{
    uint8_t     val_c = *((uint8_t *)val_ptr);
    uint16_t    val_s = *((uint16_t *)val_ptr);
    uint32_t    val_l = *((uint32_t *)val_ptr);
    uint64_t    val_d = *((uint64_t *)val_ptr);
    scalar_t    val_type = type.val_type();
    base_t      val_base = type.val_base();
    int         p_width;

    if (val_base != base_t::BASE_HEX)
    {
        cerr << __FUNCTION__ << "() Enumeration base is invalid." << endl;
        return -1;
    }

    switch (val_type)
    {
        case scalar_t::TYPE_BYTE:
        case scalar_t::TYPE_UBYTE:
            p_width = type.scalar_base.w_char();
            stream << hex << setfill(FILL) << setw(p_width) << val_c;
            return 0;
        case scalar_t::TYPE_SHORT:
        case scalar_t::TYPE_USHORT:
            p_width = type.scalar_base.w_short();
            stream << hex << setfill(FILL) << setw(p_width) << val_s;
            return 0;
        case scalar_t::TYPE_LONG:
        case scalar_t::TYPE_ULONG:
            p_width = type.scalar_base.w_long();
            stream << hex << setfill(FILL) << setw(p_width) << val_l;
            return 0;
        case scalar_t::TYPE_DOUBLE:
        case scalar_t::TYPE_UDOUBLE:
            p_width = type.scalar_base.w_double();
            stream << hex << setfill(FILL) << setw(p_width) << val_l;
            return 0;
        default:
            cerr << __FUNCTION__ << "() Value type is invalid"
    }

    return -1;
}
}

// Put integer value onto generic output.
// Output format depends on specified binary type.
//
// arg[in] stream   Output etream, STDOUT or STDERR
// arg[in] type     Integer value type and enumeration base
// arg[in] val_ptr  Pointer to location of integer value
//
// return: 0 - success, -1 - fault
int
stream_put_int_gen(ostream stream, scalar &type, void *val_ptr)
{
    long        val_l;
    long long   val_ll;
    scalar_t    val_type = type.val_type();
    base_t      val_base = type.val_base();

    if (val_ptr == 0)
    {
        cerr << __FUNCTION__ << "() argument 'val_ptr' is NULL" << endl;
        return -1;
    }

    switch (val_base)
    {
        case base_t::BASE_BIN:
            return bin_out::stream_put_int_gen(stream, type, val_ptr);
        case base_t::BASE_OCT:
            return oct_out::stream_put_int_gen(stream, type, val_ptr);
        case base_t::BASE_HEX:
            return hex_out::stream_put_int_gen(stream, type, val_ptr);
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
        case scalar_t::TYPE_UBYTE:
            val_l = (long)(*((uint8_t *)val_ptr));
            break;
        case scalar_t::TYPE_SHORT:
        case scalar_t::TYPE_USHORT:
            val_l = (long)(*((uint16_t *)val_ptr));
            break;
        case scalar_t::TYPE_LONG:
        case scalar_t::TYPE_ULONG:
            val_l = (long)(*((uint32_t *)val_ptr));
            break;
        case scalar_t::TYPE_DOUBLE:
        case scalar_t::TYPE_UDOUBLE:
            val_l = (long)(*((uint64_t *)val_ptr));
            break;
        default:
            cerr
                << __FUNCTION__ << "() "
                << "Integer value type is invalid." << endl;
            return -1;
    }

    switch (val_type) {
        case scalar_t::TYPE_BYTE:
        case scalar_t::TYPE_SHORT:
        case scalar_t::TYPE_LONG:
            stream << val_l;
            break;
        case scalar_t::TYPE_UBYTE:
        case scalar_t::TYPE_USHORT:
        case scalar_t::TYPE_ULONG:
            stream << (unsigned long)val_l;
            break;
        case scalar_t::TYPE_DOUBLE:
            stream << val_ll;
            break;
        case scalar_t::TYPE_UDOUBLE:
            stream << (unsigned long long)val_ll;
            break;
        default:;
    }

    return 0;
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
        cerr
            <<  __FUNCTION__
            <<  "() Stream type value of 'stream' argument "
                "is not supported"
            << endl;
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
            cerr << __FUNCTION__ << "() Value 'input' is NULL" << endl;
            break;
        }

        if (stream_get_str(stream, skip_eol, str) != 0)
            break;

        if ((*input = new char[str.length() + 1]) == NULL)
        {
            cerr << __FUNCTION__ << "() Memory allocation fault" << endl;
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
#define PUT_ON_STREAM(_stream) \
    if (put_endl)                   \
        _stream << val << endl;     \
    else                            \
        _stream << val;             \
    break;
    switch (stream)
    {
        case stream_t::STREAM_STDOUT:
            PUT_ON_STREAM(cout)
        case stream_t::STREAM_STDERR:
            PUT_ON_STREAM(cerr)
        default:
            cerr
                << __FUNCTION__
                << "() Stream type value of 'stream' argument "
                   "is not supported"
                << endl;
            return -1;
    }
#undef PUT_ON_STREAM

    return 0;
}
int
stream_put_str(stream_t stream, bool put_endl, const char *val)
{
    string  str;

    if (val == NULL)
    {
        cerr << __FUNCTION__ << "() Value 'val' is NULL" << endl;
        return -1;
    }
    if (strlen(val) == 0)
    {
        cerr << __FUNCTION__ << "() Argument 'val' is empty string" << endl;
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
    return str2scalar(input, type, val);                            \
}
STREAM_GET_SCALAR(signed)
STREAM_GET_SCALAR(int64_t)
#undef STREAM_GET_SCALAR

