#include <FreeNOS/User.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys/RenicePid.h"
#include "sys/types.h"
#include <errno.h>
#include <unistd.h>

void renicepid(ProcessID PID, int priority, ProcessClient::Info info) {
    const ulong result = (ulong) ProcessCtl(PID, InfoPID);

    switch ((const API::Result) (result & 0xffff))
    {
        case API::NotFound:
            errno = ESRCH;
            ERROR("failed to wait: " << strerror(errno));
            break;

        case API::Success:
            ProcessClient proc;
            proc.setPriority(PID, priority, info);
            break;

        default:
            errno = EIO;
            break;
    }
}