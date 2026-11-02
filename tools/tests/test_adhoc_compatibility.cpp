#include "stubs/pspnet_adhocctl.h"
#include <cassert>
#include <cstring>
extern "C" int __wrap_sceNetAdhocctlInit(int, int, productStruct *);
extern "C" int __real_sceNetAdhocctlInit(int stack, int priority, productStruct *product)
{
    assert(stack == 8192 && priority == 32);
    assert(!memcmp(product->product, "ULUS99999", 9));
    assert(product->unknown == 0);
    return -42;
}
int main()
{
    productStruct truncated = {};
    memcpy(truncated.product, "ULUS9999", 8);
    assert(__wrap_sceNetAdhocctlInit(8192, 32, &truncated) == -42);
    assert(truncated.product[8] == 0);
}
