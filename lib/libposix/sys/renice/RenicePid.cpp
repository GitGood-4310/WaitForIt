#include <FreeNOS/User.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys/RenicePid.h"
#include "sys/types.h"
#include <errno.h>
#include <unistd.h>

void renicepid(ProcessID PID, int priority, ProcessClient::Info info) {
    ProcessClient proc;
    proc.processInfo(PID, info);
    info.priorityLevel = priority;
    ProcessInfo info1;
    info1.priorityLevel = priority;
    ProcessCtl(PID, SetPriority, (Address) &info1);
}