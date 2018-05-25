#include "project1.h"
#include "platform.h"
#include "memory.h"
#include "conversion.h"
#include "debug.h"
#include <stdint.h>
#include "cmocka_test.h"
int main()
{
#ifdef PROJECT1
project1();
#endif
#ifdef CMOCKA
cmocka_test();
#endif
return 0;
}
