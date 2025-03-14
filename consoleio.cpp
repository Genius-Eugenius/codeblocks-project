#include "consoleio.h"
#include <iomanip>
#include <bitset>
#include <string.h>

//////////////////////
// Global namespace //
//////////////////////
using namespace std;

///////////////////
// Global macros //
///////////////////
// Space symbol
#define SP ' '

// Fulfill symbol
#define FILL '0'

// Base names in string form
#define BASE_2_S "binary"
#define BASE_8_S "octal"
#define BASE_10_S "decimal"
#define BASE_16_S "hexadecimal"

////////////////
// Data types //
////////////////

// Enumeration base numbers for integer values
enum base_n
{
    BASE_2_N = 2,
    BASE_8_N = 8,
    BASE_16_N = 16,
    BASE_10_N = 10,
};

// Printable width values for integer values
// of various types and base representations
enum base_w
{
    // Binary
    BASE_2_W_CHAR = 8,
    BASE_2_W_SHORT = 16,
    BASE_2_W_LONG = 32,
    BASE_2_W_DOUBLE = 64,
    // Octal
    BASE_8_W_CHAR = 3,
    BASE_8_W_SHORT = 6,
    BASE_8_W_LONG = 11,
    BASE_8_W_DOUBLE = 22,
    // Decimal
    BASE_10_W_CHAR = 3,
    BASE_10_W_SHORT = 5,
    BASE_10_W_LONG = 10,
    BASE_10_W_DOUBLE = 20,
    // Hexadecimal
    BASE_16_W_CHAR = 2,
    BASE_16_W_SHORT = 4,
    BASE_16_W_LONG = 8,
    BASE_16_W_DOUBLE = 16,
};

////////////////////////////////////////////
// Constants used in 'base' class methods //
////////////////////////////////////////////
// Base type name
static const char*
base_name[] = {BASE_2_S, BASE_8_S, BASE_16_S, BASE_10_S};

// Enumeration base number
static const int
base_num[] = {BASE_2_N, BASE_8_N, BASE_16_N, BASE_10_N);

// Printable width of 'char' value in various base types
static const size_t
base_w_char[] = {BASE_2_W_CHAR, BASE_8_W_CHAR, BASE_16_W_CHAR, BASE_10_W_CHAR};

// Printable width of 'short' value in various base types
static const size_t
base_w_short[] = {BASE_2_W_SHORT, BASE_8_W_SHORT, BASE_16_W_SHORT, BASE_10_W_SHORT};

// Printable width of 'long' value in various base types
static const size_t
base_w_long[] = {BASE_2_W_LONG, BASE_8_W_LONG, BASE_16_W_LONG, BASE_10_W_LONG};

// Printable width of 'long long' value in various base types
static const size_t
base_w_double[] = {BASE_2_W_DOUBLE, BASE_8_W_DOUBLE, BASE_16_W_LONG, BASE_10_W_DOUBLE};

// Class base methods
// Constructor
base::base(base_t type = BASE_DFLT) : base_type(type), base_type_i((int)type)
base::base(void) : base_type(BASE_DFLT), base_type_i((int)BASE_DFLT)

// Get base type
base_t
base::type(void)
{
    return base_type;
}

// Get base number
int
base::num(void)
{
    return base_num[base_type_i];
}

// Get base name
const char*
base::name(void)
{
    return base_name[base_type_i];
}

// Get enumerated fields
#define BASE_GET_INT(_field) \
size_t                                  \
base::_field(void)                      \
{                                       \
    return base_##_field[base_type_i];  \
}
BASE_GET_INT(num)
BASE_GET_INT(w_char)
BASE_GET_INT(w_short)
BASE_GET_INT(w_long)
BASE_GET_INT(w_double)
#undef BASE_GET_INT

////////////////////
// Module globals //
////////////////////

/////////////////////////////
// Module global functions //
/////////////////////////////
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
        val = stoul(str, nullptr, base::num());
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

// Put message in char string form onto generic output stream
//
// arg[in] stream Output stream type, cout or cerr
// arg[in] msg      Message in char string form
// arg[in] nl       Whether or not put new line on the end
//
// return Status, 0 - success, -1 - fault
static int
console_log_gen(ostream stream, const char *msg, bool nl)
{
    if (msg == 0)
    {
        cerr << __FUNCTION__ << "() ERROR: message sting is empty" << endl;
        return -1;
    }

    if (nl)
        stream << msg << endl;
    else
        stream << msg;

    return 0;
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

////////////////////////
// Exported functions //
////////////////////////
// See definition in consoleio.h
void
console_get_user_input(string &input)
{
    cin >> input;
    cin.ignore();
}

// See definition in consoleio.h
int
console_get_dec(signed &val)
{
    int rc;
    string input;

    console_get_user_input(input);

    if ((rc = str_dec2signed(input, val)) != 0)
    {
        cerr
            << __FUNCTION__ << "() ERROR: Failed to convert user input '"
            << input << "' to the signed integer value" << endl;
    }

    return rc;
}

// See definition in consoleio.h
#define CONSOLE_GET_BASE_UNSIGNED(_name, _base_t) \
int \
console_get_##_name(unsigned &val) \
{ \
    base base(_base_t); \
    return console_get_base_unsigned(base, val); \
}
/* See definition in consoleio.h */
CONSOLE_GET_BASE_UNSIGNED(bin, base_t::BASE_2)
CONSOLE_GET_BASE_UNSIGNED(oct, base_t::BASE_8)
CONSOLE_GET_BASE_UNSIGNED(dec, base_t::BASE_10)
CONSOLE_GET_BASE_UNSIGNED(hex, base_t::BASE_16)
#undef CONSOLE_GET_BASE_UNSIGNED

// Functions to log messages on console.
//
// See definition in consoleio.h
int
console_log_msg(const char *msg, bool nl)
{
    return console_log_gen(cout, msg, nl);
}

// See definition in consoleio.h
int
console_log_err(const char *msg, bool nl)
{
    return console_log_gen(cerr, msg, nl);
}

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

