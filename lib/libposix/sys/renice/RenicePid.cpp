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
    info.priorityLevel = priority;
    // ERROR("Priority is " << info.priorityLevel);
    // ERROR("PID is " << PID);
    ProcessCtl(PID, SetPriority, (Address) &info);
    ProcessClient proc;
    proc.setPriority(PID, priority, info);

    String out;

    out << "ID  PARENT  USER GROUP STATUS     PRI    CMD\r\n";

    for (ProcessID pid = 0; pid < ProcessClient::MaximumProcesses; pid++)
        {
            ProcessClient::Info info;

            const ProcessClient::Result result = proc.processInfo(pid, info);
            if (result == ProcessClient::Success)
            {
                DEBUG("PID " << pid << " state = " << *info.textState);

                // Output a line
                char line[128];
                snprintf(line, sizeof(line),
                        "%3d %7d %4d %5d %10s %6d %32s\r\n",
                        pid, info.kernelState.parent,
                        0, 0, *info.textState, info.priorityLevel, *info.command);
                out << line;
            }
        }
        write(1, *out, out.length());
}