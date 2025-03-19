#include "consoleio.h"

using namespace std;

int main(int argc, char **argv)
{
    stream my_stream;
    scalar val;

    my_stream = STDERR;
    val = scalar_t::TYPE_BYTE;
    val.enum_base = base_t::BASE_OCT;

    val = (uint8_t)13;
    my_stream << val;

    return 0;
}
