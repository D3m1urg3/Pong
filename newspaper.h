#ifndef __NEWSPAPER__
#define __NEWSPAPER__

#include <vector>
#include "globals.h"

enum Possible_event
{
    NO_EVENT,
    EV_PLAYER_SCORED,
    EV_OPPONENT_SCORED
};

class News
{
public:
    News();
    ~News();

    void register_gossip(const Possible_event& gossip);
    void clean_events();
    Possible_event listen();

private:
    static Possible_event* events;
    uint alloc_size;
    uint amount_of_events;
    uint index;

    
};
#endif