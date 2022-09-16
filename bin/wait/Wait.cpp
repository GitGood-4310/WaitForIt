#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait");
    parser().registerPositional("PID", "PID is argument");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid = 0;

    if ((pid = atoi(arguments().get("PID"))) <= 0)
    {
        ERROR("invalid pid `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }

    if (waitpid(pid, 0, 0) != 0)
    {
        ERROR("failed to wait: " << strerror(errno));
        return IOError;
    }

    return Success;
}