// call to native ESP-IDK tolls to wake up and sleep
#include "xsmc.h"

void xs_setWakeUpTime(xsMachine *the)
{
    uint64_t sleeptime = UINT64_C(15 * 1000000);
    esp_sleep_enable_timer_wakeup(sleeptime);
}
void xs_sleep(xsMachine *the)
{
    esp_deep_sleep_start();  
}