#include <stdio.h>
#include <stdbool.h>

#define frames 3
#define length 20 // length of all pageref strings= 20

int optimal(int pages[]);
int fifo(int pages[]);
int lru(int pages[]);

int main()
{
    // given pageref strings
    int page1[] = {2, 6, 9, 2, 4, 8, 1, 7, 3, 0, 8, 2, 1, 2, 9, 5, 7, 2, 8, 5};
    int page2[] = {0, 6, 3, 0, 2, 6, 3, 5, 2, 4, 1, 3, 5, 6, 1, 4, 2, 1, 5, 7};
    int page3[] = {3, 1, 4, 2, 5, 4, 5, 3, 5, 2, 0, 1, 1, 0, 2, 3, 2, 5, 0, 3};
    int page4[] = {4, 2, 1, 7, 9, 8, 1, 5, 4, 6, 8, 1, 0, 7, 2, 5, 1, 7, 5, 8};

    printf("Page-Reference String: 2,6,9,2,4,8,1,7,3,0,8,2,1,2,9,5,7,2,8,5\n");

    printf("OPT: %d  FIFO: %d  LRU: %d\n",
           optimal(page1),
           fifo(page1),
           lru(page1));

    printf("Page-Reference String: 0,6,3,0,2,6,3,5,2,4,1,3,5,6,1,4,2,1,5,7\n");
    printf("OPT: %d  FIFO: %d  LRU: %d\n",
           optimal(page2),
           fifo(page2),
           lru(page2));

    printf("Page-Reference String: 3,1,4,2,5,4,5,3,5,2,0,1,1,0,2,3,2,5,0,3\n");
    printf("OPT: %d  FIFO: %d  LRU: %d\n",
           optimal(page3),
           fifo(page3),
           lru(page3));

    printf("Page-Reference String: 4,2,1,7,9,8,1,5,4,6,8,1,0,7,2,5,1,7,5,8\n");
    printf("OPT: %d  FIFO: %d  LRU: %d\n",
           optimal(page4),
           fifo(page4),
           lru(page4));

    return 0;
}

// optimal page replacement
int optimal(int pages[])
{
    int memSlots[frames];
    int faults = 0; // tracks # of page faults

    for (int i = 0; i < frames; i++)
        memSlots[i] = -1; // initialize frames to -1 at first

    for (int i = 0; i < length; i++) // loop thru each page in the page ref string
    {
        bool found = false; // flag to check if page is already in mem

        for (int j = 0; j < frames; j++) // check if ccurent page is already in mem
        {
            if (memSlots[j] == pages[i])
            {
                found = true; // if true then no page fault
                break;
            }
        }

        if (!found) // if page is not in mem, page fault occurs
        {
            int victimFrame = -1; // index of the frame to replace
            int futureIndex = i;  // variable to track farthest use in future

            for (int j = 0; j < frames; j++) // find which frame in mem will not be needed for the longest time
            {
                int k;
                for (k = i + 1; k < length; k++) // check how far in the future the curr page is used
                {
                    if (memSlots[j] == pages[k])
                        break; // found the next usage of the curr page
                }
                if (k > futureIndex) // if the curr page is not used again or very far away
                {
                    futureIndex = k; // update the farthest request
                    victimFrame = j; // update vicitmframe
                }
            }
            if (victimFrame == -1) // if no page is used again replace the first frame
            victimFrame = 0;
            memSlots[victimFrame] = pages[i]; // replace the chosen frame w the curr page
            faults++;
        }
    }
    return faults;
}

// FIFO page replacement
int fifo(int pages[])
{
    int memSlots[frames], front = 0, faults = 0;

    for (int i = 0; i < frames; i++)
        memSlots[i] = -1; // all mem frames are -1 at first

    for (int i = 0; i < length; i++)
    {
        bool found = false; // flag to check if the page is in mem

        for (int j = 0; j < frames; j++) // check if the curr page is already is mem

        {
            if (memSlots[j] == pages[i])
            {
                found = true;
                break; // if true no page fault
            }
        }
        if (!found) // if page not in mem
        {
            memSlots[front] = pages[i];   // replace the page at the front position in memory
            front = (front + 1) % frames; // move front to the next frame in circular order
            faults++;
        }
    }
    return faults;
}

// LRU page replacement
// selects the page that has not been used for the longest time to replace.
// It keeps track of when each page was last accessed usageTracker[]
// and ensures that the oldest page is deleted
int lru(int pages[])
{
    int memSlots[frames];
    int usageTracker[frames];
    int faults = 0;

    for (int i = 0; i < frames; i++)
    {
        memSlots[i] = -1;
        usageTracker[i] = -1; // set usage tracker to -1 bc no page has been used yet
    }
    for (int i = 0; i < length; i++)
    {
        bool found = false;
        for (int j = 0; j < frames; j++)
        {
            if (memSlots[j] == pages[i])
            {
                found = true;        // if page found in mem
                usageTracker[j] = i; // update last used time to the curr time i
                break;
            }
        }
        if (!found)
        {
            int oldestFrame = 0; // start with first frame as least recently used
            for (int j = 1; j < frames; j++)
            {
                // find the frame with the smallest usage time
                // lower usage tracker value means it was used long ago
                if (usageTracker[j] < usageTracker[oldestFrame])
                {
                    oldestFrame = j; // update to frame used least recently
                }
            }
            memSlots[oldestFrame] = pages[i]; // replace LRU page with curr page
            usageTracker[oldestFrame] = i;    // update usage time for this newly added pg
            faults++;
        }
    }
    return faults;
}
