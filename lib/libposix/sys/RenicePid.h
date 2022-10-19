/*
 * Copyright (C) 2009 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBPOSIX_RENICEPID_H
#define __LIBPOSIX_RENICEPID_H

#include <Macros.h>
#include "types.h"
#include <ProcessClient.h>

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libposix
 * @{
 */

/**
 * Returns the exit status of the child process
 *
 * @param st Contains the stat_loc value from waitpid()
 *
 * @return Exit status of the child process
 */
#define WEXITSTATUS(st) (st)


extern C void renicepid(ProcessID PID, int priority, ProcessClient::Info info);

/**
 * @}
 * @}
 */

#endif /* __LIBPOSIX_WAIT_H */
