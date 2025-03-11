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

// Fullfil symbol
#define FILL '0'

// Default base type, decimal
#define BASE_DFLT BASE_10
#define BASE_DFLT_N 10

// Base names in string form
#define BASE_2_S "binary"
#define BASE_8_S "octal"
#define BASE_10_S "decimal"
#define BASE_16_S "hexadecimal"

////////////////
// Data types //
////////////////
// Enumeration base types for integer values
enum class base_t
{
    BASE_2 = 0,
    BASE_8,
    BASE_10,
    BASE_16,
};

// Enumeration base numbers for integer values
enum base_n
{
    BASE_2_N = 2,
    BASE_8_N = 8,
    BASE_10_N = 10,
    BASE_16_N = 16,
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

// Class to represent enumeration base of all integer values
class base
{
private:
    // Base type
    base_t base_type;
    int base_type_i;
    // Common constants for all class units
public:
    base(base_t type);
    base()
    base_t type(void);
    const char *name(void);
    int num(void);
    int w_char(void);
    int w_short(void);
    int w_long(void);
    int w_double(void);
};

// Class base methods
// Constructor
base::base(base_t type) : base_type(type), base_type_i((int)type)

// Get base type
    base::type(void)
{
    return base_type;
}

// Get enumerated fields
#define BASE_GET(_field) \
base::##_field(void) \
{ \
    return base_##_field[(int)base_type]; \
}
BASE_GET(num)
BASE_GET(name)
BASE_GET(w_char)
BASE_GET(w_short)
BASE_GET(w_long)
BASE_GET(w_double)
#undef BASE_GET

////////////////////
// Module globals //
////////////////////

////////////////////////////////////////////
// Constants used in 'base' class methods //
////////////////////////////////////////////
// Base type name
static const char*
base_name[] = {BASE_2_S, BASE_8_S, BASE_10_S, BASE_16_S};

// Enumeration base values
static const int
base_num[] = {BASE_2_N, BASE_8_N, BASE_10_N, BASE_16_N};

// Printable width of 'char' value in various base types
static const int
base_w_char[] = {BASE_2_W_CHAR, BASE_8_W_CHAR, BASE_10_W_CHAR, BASE_16_W_CHAR};

// Printable width of 'short' value in various base types
static const int
base_w_short[] = {BASE_2_W_SHORT, BASE_8_W_SHORT, BASE_10_W_SHORT, BASE_16_W_SHORT};

// Printable width of 'long' value in various base types
static const int
base_w_long[] = {BASE_2_W_LONG, BASE_8_W_LONG, BASE_10_W_LONG, BASE_16_W_LONG};

// Printable width of 'long long' value in various base types
static const int
base_w_double[] = {BASE_2_W_DOUBLE, BASE_8_W_DOUBLE, BASE_10_W_DOUBLE, BASE_16_W_LONG};

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
    if (msg == 0 || strlen(msg) == 0)
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

static int
console_put_gen_bin_byte(ostream stream, int val)
{
    stream << bitset<8>((uint8_t)val);
    return 0;
}

static int
console_put_gen_bin_short(ostream stream, int val)
{
    stream << bitset<16>((uint16_t)val);
    return 0;
}

static int
console_put_gen_bin_long(ostream stream, int val)
{
    stream << bitset<32>((uint32_t)val);
    return 0;
}

// Put long long integer in binary form onto ostream console
//
// arg[in] stream   Output stream, cout or cerr
// arg[in] val      Value to put
//
// return Status, 0 - success, -1 - fault
static int
console_put_gen_bin_double(ostream stream, uint64_t val)
{
    ostream << bitset<64>(val);
    return 0;
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

#define CONSOLE_PUT_HEX_GEN_SCALAR(_val_type)\

int
console_out_bin(unsigned val)
{
    cout << bitset<32>(val);
    return 0;
}
int
console_out_bin(signed val);
{
    return console_out_bin((unsigned)val);
}
int
console_out_bin(char val)
{
    cout << bitset<8>(val);
    return 0;
}
extern int console_out_bin(short val);
extern int console_out_bin(long long val);
static int
console_put_hex_gen_char(ostream stream, int val)
{
    stream << "0x" << setw(2) << setfill('0') << uppercase << hex << (unsigned char)val << endl;
}

