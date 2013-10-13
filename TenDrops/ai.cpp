//
// Module			: ai.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		:
//

#include "ai.h"
#include "state.h"

void AI::bfs(State *state, Point **op, int *steps)
{
    for (int x = 0; x < 6; ++x)
    {
        for (int y = 0; y < 6; ++y)
        {

        }
    }
    *op = new Point[2];
    (*op)[0].x = 0;
    (*op)[0].y = 0;
    (*op)[1].x = 2;
    (*op)[1].y = 0;
    *steps = 2;
}
