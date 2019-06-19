/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  :
 * Student number:
 */
#include "player.h"

void player_Initialise(Player *player, Position position)
{
    player->position = position;
    player->numArrows = INIT_ARROW_COUNT;
    return;
}

Position player_GetNextPosition(Position position, Direction direction)
{
    Position nextPosition;
    nextPosition = position;

    if (direction == player_NORTH)
    {
        nextPosition.y = position.y - 1;
    }
    else if (direction == player_EAST)
    {
        nextPosition.x = position.x + 1;
    }
    else if (direction == player_SOUTH)
    {
        nextPosition.y = position.y + 1;
    }
    else if (direction == player_WEST)
    {
        nextPosition.x = position.x - 1;
    }
    else
    {
        assert(0);
    }
    return nextPosition;
}

void player_UpdatePosition(Player *player, Position position)
{
    player->position = position;
}
