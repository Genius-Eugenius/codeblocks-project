#include "consoleio.h"

using namespace std;

int main(int argc, char **argv)
{
    string str;
//    char val_c;
    signed val_s;
    unsigned val_u;

    console_log_msg("Hello, World!");

#if 0
//    val_s = -13;
//   cout << hex << setfill('0') << uppercase << setw(40) << val_s << endl;
    val_c = 0x01;
    cout << bitset<8>(val_c) << endl;
    cout << bitset<8>(-1) << SP << bitset<16>(~1) << endl << bitset<32>(555) << endl;
    cout << bitset<64>(~1) << endl;
#endif // 0
    return 0;
}
