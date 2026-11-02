#include <pspnet_adhocctl.h>
#include <cstring>

extern "C" int __real_sceNetAdhocctlInit(int, int, struct productStruct *);

extern "C" int __wrap_sceNetAdhocctlInit(int stack, int priority, struct productStruct *product)
{
    // The installed OSLib truncates this fixed-width ID to eight bytes, breaking server login.
    struct productStruct corrected = *product;
    memcpy(corrected.product, "ULUS99999", sizeof(corrected.product));
    return __real_sceNetAdhocctlInit(stack, priority, &corrected);
}
