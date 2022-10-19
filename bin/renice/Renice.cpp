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
    //ProcessClient proc;

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
        renicepid(PID, priority, info);
            //printf("%d and %s\n", info.priorityLevel, *info.command);
            //info.priorityLevel = priority;
        //    proc.setPriority(PID, priority, info);
        //    printf("%d\n", info.priorityLevel);
            //ProcessCtl(PID, SetPriority, (Address) &info);
            //info.priorityLevel = priority;
            //ERROR("Priority Level is `" << info.priorityLevel << "'");


    }
    
    return Success;
}