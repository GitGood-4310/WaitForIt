#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Change priority of a process");
    parser().registerFlag('n', "priority", "display priority level of processes when you do");
    parser().registerPositional("PRI", "Priority Level you want to change it to");
    parser().registerPositional("PID", "Priority ID");
}

Renice::Result Renice::exec()
{
    int priority = 0;
    int pid = 0;
    ProcessID PID;
    const ProcessClient process;

    priority = atoi(arguments().get("PRI"));
    pid = atoi(arguments().get("PID"));
    PID = pid;
    ProcessClient::Info info;
    const ProcessClient::Result result = process.processInfo(PID, info);
    //const API::Result result = ProcessCtl(pid, SetPriority);

    if (priority > 5) {
        ERROR("invalid priority `" << arguments().get("PRI") << "'");
        return InvalidArgument;
    }
    else {
        // if (result == ProcessClient::Success)
        // {
            printf("%d\n", info.priorityLevel);
            info.priorityLevel = priority;
            printf("%d\n", info.priorityLevel);
            ProcessCtl(PID, SetPriority, (Address) &info);
            //info.priorityLevel = priority;
            //ERROR("Priority Level is `" << info.priorityLevel << "'");

            // DEBUG("PID " << pid << " state = " << *info.textState);

            // // Output a line
            // char line[128];
            // snprintf(line, sizeof(line),
            //         "%3d %7d %4d %5d %10s %6d %32s\r\n",
            //         pid, info.kernelState.parent,
            //         0, 0, *info.textState, info.priorityLevel, *info.command);
            // out << line;
        //}
    }
    
    return Success;
}