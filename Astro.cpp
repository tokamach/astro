#include<ncurses.h>
#include<iostream>
#include<stdlib.h>
#include<fstream>

#include  "Astro.h"
#include "Player.h"

#define STAR_GEN_CHANCE 1

//This will do some stuff to fill the ship with goodies like air
void Astro::initShip()
{
  
}

/*
 *  The main function. Run it as while loop param, and it will return false on exit.
 */
void Astro::drawAll()
{
  int width;
  int height;
  getmaxyx(stdscr, width, height); 

  if(!cursesStarted)
    {
      std::cerr << "Start ncurses you idiot\n";
      return;
    }
  if(firstRun)
    {
      drawStars(width, height); 
      firstRun = false;
      curs_set(0);
    }

   drawStructure(width, height);
   drawPlayer();
   refresh();
   timeout(-1);
}

void Astro::fixPlayer()
{
  
}

/*
 *  Gets key input and moves the player accordingly.
 */
int Astro::getMove()
{
	int m = getch();
	switch(m)
	{
		case 27:
			return -1;
			break;

		case KEY_UP:
			player.moveUp();
			break;
      
		case KEY_DOWN:
			player.moveDown();
			break;
      
		case KEY_LEFT:
			player.moveLeft();
			break;

		case KEY_RIGHT:
			player.moveRight();
			break;
    }
}

void Astro::drawPlayer()
{
    move(player.playerx, player.playery);
    addch('@');
}

void Astro::drawStructure(int width, int height)
{
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 30; j++)
		{
			move(i, j);
			addch('|');
		}
	}
}

//Oh my god, its full of stars
void Astro::drawStars(int width, int height)
{ 
	int i = 0;
	for(int x = 0; x < width; x++)
	{
		for(int y = 0;y < height; y++)
		{
			move(x, y);
			//LOL SO RANDOM LOL
			if(rand() % 100 < STAR_GEN_CHANCE)
			{
				addch('*');
			}
			if(rand() % 100 > STAR_GEN_CHANCE && rand() % 100 < STAR_GEN_CHANCE + 3)
			{
				addch('.');
			}
			i++;
	    }
	}
}

//Start ncurses
void Astro::startCurses()
{
	if(cursesStarted)
	{
		std::cerr << "ncurses was started but some bozo started it agian, I'll just refresh the screen.\n";
		refresh();
	}
	else
	{
		initscr();
		timeout(-1);
		cbreak();
		noecho();
		intrflush(stdscr, false);
		keypad(stdscr, true);
		cursesStarted = true;
	}
}

//Stop ncurses
void Astro::stopCurses()
{
  if(cursesStarted && !isendwin())
    {
      curs_set(1);
      endwin();
    }
  else
    {
      std::cerr << "Start ncurses before stopping it, duh.\n";
    }
}
