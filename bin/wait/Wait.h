#ifndef __BIN_WAIT_WAIT_H
#define __BIN_WAIT_WAIT_H

#include <FreeNOS/User.h>
#include "sys/wait.h"
#include "sys/types.h"
#include <errno.h>

#include <POSIXApplication.h>

/**
 * @addtogroup bin
 * @{
 */

class Wait : public POSIXApplication
{
    public:
        /**
         * Constructor
         * 
         * @param argc
         * @param argv
         */
        Wait(int argc, char **argv);
        
        /**
         * Destructor
         */
        virtual ~Wait();

        /**
         * Execute the application.
         *
         * @return Result code
         */
        virtual Result exec();
};

#endif