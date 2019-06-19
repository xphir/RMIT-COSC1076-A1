/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  :
 * Student number:
 */
#include "board.h"

Board BOARD_1 =
	{
		{board_EMPTY, board_EMPTY, board_EMPTY, board_PIT, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY},
		{board_BATS, board_EMPTY, board_EMPTY, board_WUMPUS, board_EMPTY},
		{board_EMPTY, board_PIT, board_EMPTY, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_BATS, board_EMPTY, board_EMPTY}};

Board BOARD_2 =
	{
		{board_PIT, board_EMPTY, board_PIT, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_BATS, board_EMPTY, board_EMPTY},
		{board_EMPTY, board_EMPTY, board_EMPTY, board_EMPTY, board_BATS},
		{board_EMPTY, board_WUMPUS, board_EMPTY, board_EMPTY, board_EMPTY},
};

void board_Load(Board board, Board boardToLoad)
{
	int x;
	int y;
	for (x = 0; x < BOARD_HEIGHT; x++)
	{
		for (y = 0; y < BOARD_WIDTH; y++)
		{
			board[y][x] = boardToLoad[y][x];
		}
	}
}

Boolean board_PlacePlayer(Board board, Position position)
{
	/* TODO */
	Cell c;
	c = board[position.y][position.x];

	if (position.x < 0 || position.x >= BOARD_WIDTH || position.y < 0 || position.y >= BOARD_HEIGHT) /* Check if selection is out of bounds */
	{
		return FALSE;
	}
	else if (c == board_WUMPUS || c == board_BATS || c == board_PIT) /* Check if selection is in a hazard */
	{
		return FALSE;
	}
	else
	{
		board[position.y][position.x] = board_PLAYER;
		return TRUE;
	}
}

PlayerMove board_MovePlayer(Board board, Position playerPosition,
							Position nextPosition)
{
	PlayerMove move;

	if (nextPosition.x >= 0 && nextPosition.x <= BOARD_WIDTH && nextPosition.y >= 0 && nextPosition.y <= BOARD_HEIGHT)
	{
		switch (board[nextPosition.y][nextPosition.x])
		{
		case board_EMPTY:
		case board_TRAVERSED:
			board[playerPosition.y][playerPosition.x] = board_TRAVERSED;
			board[nextPosition.y][nextPosition.x] = board_PLAYER;
			move = board_PLAYER_MOVED;
			break;
		case board_BATS:
			board[playerPosition.y][playerPosition.x] = board_TRAVERSED;
			move = board_BAT_CELL;
			break;
		case board_PIT:
		case board_WUMPUS:
			move = board_PLAYER_KILLED;
			break;
		case board_PLAYER:
			printf(PLAYER_OUTPUT);
			break;
		default:
			/* This shouldnt happen */
			assert(0);
			break;
		}
	}
	else
	{
		move = board_OUTSIDE_BOUNDS;
	}
	return move;
}

ArrowHit board_FireArrow(Board board, Position position)
{
	if (position.x >= 0 && position.x <= BOARD_WIDTH && position.y >= 0 && position.y <= BOARD_HEIGHT)
	{
		if (board[position.y][position.x] == board_WUMPUS)
		{
			return board_WUMPUS_KILLED;
		}
		else
		{
			return board_ARROW_MISSED;
		}
	}
	else
	{
		return board_ARROW_OUTSIDE_BOUNDS;
	}
}

void board_Display(Board board)
{
	int x, y;
	/* Print x axis (top side) numbers */
	printf("   ");
	for (x = 0; x < BOARD_WIDTH; ++x)
	{
		printf("%d  ", x);
	}

	putchar(10);

	for (y = 0; y < BOARD_HEIGHT; ++y)
	{

		/* Print line split */
		printf("  -");
		for (x = 0; x < BOARD_WIDTH; ++x)
		{
			printf("---");
		}

		/* Print y axis (left side) numbers */
		printf("\n%d ", y);

		for (x = 0; x < BOARD_WIDTH; ++x)
		{
			putchar(124);
			/* Check what type of cell it is */
			switch (board[y][x])
			{
			case board_EMPTY:
			case board_BATS:
			case board_PIT:
			case board_WUMPUS:
				printf(EMPTY_OUTPUT);
				break;
			case board_TRAVERSED:
				printf(TRAVERSED_OUTPUT);
				break;
			case board_PLAYER:
				printf(PLAYER_OUTPUT);
				break;
			default:
				assert(0);
			}
		}

		putchar(124);
		putchar(10);
	}
	printf("  -");

	for (x = 0; x < BOARD_WIDTH; ++x)
	{
		printf("---");
	}
	putchar(10);
}

void board_DisplayWarnings(Board board, Position position)
{
	Boolean breeze;
	Boolean flapping;
	Boolean wumpus;
	int x, y;

	wumpus = FALSE;
	flapping = FALSE;
	breeze = FALSE;

	for (x = position.x - 1; position.x + 1 >= x; ++x)
	{
		for (y = position.y - 1; position.y + 1 >= y; ++y)
		{
			if (x >= 0 && x <= 4 && y >= 0 && y <= 4)
			{
				switch (board[y][x])
				{
				case board_BATS:
					flapping = TRUE;
					break;
				case board_PIT:
					breeze = TRUE;
					break;
				case board_WUMPUS:
					wumpus = TRUE;
					break;
				case board_EMPTY:
				case board_TRAVERSED:
				case board_PLAYER:
					continue;
				default:
					assert(0);
				}
			}
		}
	}
	if (breeze)
		printf("You feel a breeze!");
	if (flapping)
		printf("You hear flapping!");
	if (wumpus)
		printf("You smell a wumpus!");
	putchar(10);
}