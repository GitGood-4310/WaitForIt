/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}
Size Scheduler::count() const
{
    return m_queue_level_One.count();
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    int priority = proc->getPriority(); 
    Scheduler::Result result;

    switch (priority)
    {
        case 1:
            m_queue_level_One.push(proc);
            result = Success;
            break;
        case 2:
            m_queue_level_Two.push(proc);
            result = Success;
            break;
        case 3:
            m_queue_level_Three.push(proc);
            result = Success;
            break;
        case 4:
            m_queue_level_Four.push(proc);
            result = Success;
            break;
        case 5:
            m_queue_level_Five.push(proc);
            result = Success;
            break;
        default:
            break;
    }
    return result;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    Size count_One = m_queue_level_One.count();
    Size count_Two = m_queue_level_Two.count();
    Size count_Three = m_queue_level_Three.count();
    Size count_Four = m_queue_level_Four.count();
    Size count_Five = m_queue_level_Five.count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count_One; i++)
    {
        Process *p = m_queue_level_One.pop();

        if (p == proc)
            return Success;
        else
            m_queue_level_One.push(p);
    }

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count_Two; i++)
    {
        Process *p = m_queue_level_Two.pop();

        if (p == proc)
            return Success;
        else
            m_queue_level_Two.push(p);
    }

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count_Three; i++)
    {
        Process *p = m_queue_level_Three.pop();

        if (p == proc)
            return Success;
        else
            m_queue_level_Three.push(p);
    }

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count_Four; i++)
    {
        Process *p = m_queue_level_Four.pop();

        if (p == proc)
            return Success;
        else
            m_queue_level_Four.push(p);
    }

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count_Five; i++)
    {
        Process *p = m_queue_level_Five.pop();

        if (p == proc)
            return Success;
        else
            m_queue_level_Five.push(p);
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process * Scheduler::select()
{
    if (m_queue_level_Five.count() > 0)
    {
        Process *p = m_queue_level_Five.pop();
        m_queue_level_Five.push(p);

        return p;
    }
    else if (m_queue_level_Four.count() > 0)
    {
        Process *p = m_queue_level_Four.pop();
        m_queue_level_Four.push(p);

        return p;
    }
    else if (m_queue_level_Three.count() > 0)
    {
        Process *p = m_queue_level_Three.pop();
        m_queue_level_Three.push(p);

        return p;
    }
    else if (m_queue_level_Two.count() > 0)
    {
        Process *p = m_queue_level_Two.pop();
        m_queue_level_Two.push(p);

        return p;
    }
    else if (m_queue_level_One.count() > 0)
    {
        Process *p = m_queue_level_One.pop();
        m_queue_level_One.push(p);

        return p;
    }
}
