#include "newspaper.h"

Possible_event* News::events = nullptr;

News::News()
    :index(0),
    amount_of_events(0),
    alloc_size(0)
{
    alloc_size = 10;
    events = new Possible_event[10];
    for (int i = 0; i < alloc_size; ++i)
    { 
        events[i] = NO_EVENT;
    }
}

News::~News()
{
    delete[] events;
}

void News::register_gossip(const Possible_event& gossip)
{
    // If array is full make more space
    if (amount_of_events >= alloc_size)
    {
        Possible_event* temp_storage = events;
        events = new Possible_event[alloc_size + 10];
        alloc_size += 10;
        for (int i = 0; i < alloc_size; ++i)
        {
            if (i < amount_of_events)
            {
                events[i] = temp_storage[i];

            }
            else
            {
                events[i] = NO_EVENT;
            }
        }
        delete[] temp_storage;
    }

    events[amount_of_events] = gossip;
    ++amount_of_events;
}

void News::clean_events()
{
    for (int i = 0; i < amount_of_events; ++i)
    {
        events[i] = NO_EVENT;
    }
}

Possible_event News::listen()
{
    if (index < amount_of_events)
    {
        return events[index++];
    }
    else
    {
        index = 0;
        return NO_EVENT;
    }
}
