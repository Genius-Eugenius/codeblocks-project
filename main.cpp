#include "consoleio.h"

using namespace std;

int main(int argc, char **argv)
{
    string str;
//    char val_c;
    signed val_s;
    unsigned val_u;

#if 0
    cout << "Enter string value" << endl;
    console_get_user_input(str);
    cout << "You've entered string value '" << str << "'" << endl;

    cout << "Enter signed integer in decimal form" << endl;
    if (console_get_dec(val_s) == 0)
        cout << "You've entered signed value " << val_s << endl;

    cout << "Enter unsigned integer in decimal form" << endl;
    if (console_get_dec(val_u) == 0)
        cout << "You've entered unsigned value " << val_u << endl;
#endif // 0

    cout << "Enter unsigned integer in hexdecimal form" << endl;
    if (console_get_hex(val_u) == 0){
        console_log_msg("You've entered unsigned value");
        console_out_hex(val_u);
    } else {
        console_log_err( __FUNCTION__ "() Failed to get unsigned value from user input");
    }
#if 0
    cout << "Enter unsigned integer in octal form" << endl;
    if (console_get_oct(val_u) == 0)
        cout << "You've entered unsigned value " << val_u << endl;

    cout << "Enter unsigned integer in binary form" << endl;
    if (console_get_bin(val_u) == 0)
        cout << "You've entered unsigned value " << val_u << endl;


//    val_s = -13;
//   cout << hex << setfill('0') << uppercase << setw(40) << val_s << endl;
    val_c = 0x01;
    cout << bitset<8>(val_c) << endl;
    cout << bitset<8>(-1) << SP << bitset<16>(~1) << endl << bitset<32>(555) << endl;
    cout << bitset<64>(~1) << endl;
#endif // 0
    return 0;
}
