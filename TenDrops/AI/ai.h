//
// Module			: ai.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-13
// Last Modification: 2013-10-13
// Description		: AI for search.
//

#ifndef AI_H
#define AI_H

#include <QLinkedList>

class State;

class AI
{
public:
    struct Point
    {
        int x;
        int y;
    };
public:
    AI() = delete;
    static void bfs(State* state, Point** op, int* steps);

private:
    static State *bfs_traversal();
    static void bfs_addToOpenList(State* newState);

private:
    static QLinkedList<State*> open;
    static QLinkedList<State*> closed;
};

#endif // AI_H
