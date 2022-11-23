<!-- In FreeNos, we are using both physical and virtual memory
    For memory management, we are able to add things into memory using First-fit/ Next-Fit
    First-Fit: Always starts the search from the beginning of the list and allocates the first hole large
    Next-Fit: Starts each search t the point of the last allocaiton
    Lookup - converts the virtual memory to physical or something along those lines -->

One of the main goals of an Operating System is to be able to allocate files into memory. For FreeNos, this is no different. Looking through the Library files, we found different code related to the memory and memory management. From them we drew the following conclusions:

Does FreeNos use physical and virtual memory?
    Yes. If you look in the Memory Header file (Memory.h), there is a structure called range that takes in 4 different parameters, 2 of these being for both a virtual address and physical address. 

How does FreeNos allocate memory? 
    In class, we learned that there were 4 types of algorithms that allocate files into free-memory. They are first-fit, next-fit, best-fit, and worst-fit. For first-fit, the code would have a hard-coded starting point for the algorithm so that when it begin searching for a free space, it will start at the "starting point" then iterate through each space checking if it is free. For next-fit, rather than having a hard-coded "starting-point", there would be a pointer that would state where the last iteration left off on. For both best-fit and worst-fit, the algorithm would have a loop that would iterate through the memory stack and find a free memory space (either a space that fits the program best or the biggest space available), save the spot in a pointer, and then allocate the program into the selected space. Searching through the MemoryContext.cpp code, found the following method: 
        
        MemoryContext::Result MemoryContext::findFree(Size size, MemoryMap::Region region, Address *virt) const
        {
            Memory::Range r = m_map->range(region);
            Size currentSize = 0;
            Address addr = r.virt, currentAddr = r.virt, tmp;

            while (addr < r.virt+r.size && currentSize < size)
            {
                if (lookup(addr, &tmp) == InvalidAddress)
                {
                    currentSize += PAGESIZE;
                }
                else
                {
                    currentSize = 0; 
                    currentAddr = addr + PAGESIZE;
                }
                addr += PAGESIZE;
            }

            if (currentSize >= size)
            {
                *virt = currentAddr;
                return Success;
            }
            else
                return OutOfMemory;
        }

                
        lib/libarch/MemoryContext.cpp (Line 117-144)

In this method, we note that the while loop is not iterating through the whole memory stack before allocating the program to an openspace so it eliminates the options of best-fit and worst-fit. Thus, we are left with two options for memory allocation: first-fit and next-fit. Looking closer at the parameters of the while loop, there is a statement checking if currentSize < size. It is noted that currentSize is initialized to 0 at the start of the method and size has no reference related to the file that we are trying to allocate in memory, meaning that it is reffering to the memory stacks size. Therefore, memory is allocated using the First-fit algorithm. 

What is the Page Size?
The page is initialized as a static const of 4096 (unsigned) which is found in BootImageCreate.h 

How many segments are there?
We found BootImageCreate.h that the max number of memory regions is 16. The number of segments is set to: 

    numSegments += input[i]->numRegions

    bin/img/BootImageCreate.cpp (Line 16)

What is segment size?
The size of the segment is set in this line 244 of BootImageCreate.cpp : 

    sizeof(BootSegment)

    bin/img/BootImageCreate.cpp (Line 244)

In BootImage.h you can see that the segment size is variable type u32.
The number of segments per page is 8, which means that the offset is 8. This is the code that we used to find the segment size.

    segments = new BootSegment[numSegments];
    symbols[i].segmentsOffset = numSegments;


    for (Size i = 0; i < input.count(); i++)
        {
            strncpy(symbols[i].name, input[i]->symbol.name, BOOTIMAGE_NAMELEN);
            symbols[i].type  = input[i]->symbol.type;
            symbols[i].entry = input[i]->symbol.entry;
            symbols[i].segmentsOffset = numSegments;
            symbols[i].segmentsCount  = input[i]->numRegions;
            symbols[i].segmentsTotalSize = 0;
            numSegments += input[i]->numRegions;
        }
    bin/img/BootImageCreate.cpp (Line 229-238) 

    Vector<BootEntry > input (Line195)

    typedef struct BootEntry
    {
        /** BootSymbol definition/
        BootSymbol symbol;

        / Input data buffer read from the original file /
        u8data;

        / Memory regions for this symbol /
        ExecutableFormat::Region regions[BOOTENTRY_MAX_REGIONS];

        /** Number of memory regions./
        Size numRegions;
    }
    BootEntry;

    bin/img/BootImageCreate.h (Line 36-50)

Is the segment table paged?
The segment table is paged. 

Is there address translation?
Yes the address translation could be found at lib/libarch/intel/IntelPageTable.cpp line 57.

MemoryContext::Result IntelPageTable::translate(Address virt, Address *phys) const
{
    if (!(m_pages[ TABENTRY(virt) ] & PAGE_PRESENT))
        return MemoryContext::InvalidAddress;

    *phys = (m_pages[ TABENTRY(virt) ] & PAGEMASK);
    return MemoryContext::Success;
}

It sets physical address equal to entry inside page table of a virtual address using a page mask.

Interesting things to note:
FreeNOS has a log 