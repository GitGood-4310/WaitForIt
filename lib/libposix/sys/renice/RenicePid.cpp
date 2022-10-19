#include <FreeNOS/User.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys/RenicePid.h"
#include "sys/types.h"
#include <errno.h>
#include <unistd.h>

void renicepid(ProcessID PID, int priority, ProcessClient::Info info) {
    // ProcessClient proc;
    // proc.setPriority(PID, priority, info);
    // printf("%d\n", info.priorityLevel);
    // ERROR("Priority is " << info.priorityLevel);
    // ERROR("PID is " << PID);
    ProcessClient proc;
    proc.processInfo(PID, info);
    info.priorityLevel = priority;
    ProcessInfo info1;
    info1.priorityLevel = priority;
    ProcessCtl(PID, SetPriority, (Address) &info1);
    //proc.setPriority(PID, priority, info);

}