#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <ncurses.h>
#include <vector>
#include "snake.cpp"
using namespace std;

const int height = 30;
const int width = 50;
string gameScreen[height][width];
Snake *snake = new Snake(height / 2, width / 2);

Snake *tails[50];
Snake *lastTail = snake;
int ntails = 0;

int foodPosX, foodPosY, keypressed, score;
bool gameOver = false;

void draw()
{
  //Tail tails = snake->getTails();
  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      if (row == 0 or row == 29)
      {
        mvaddch(row, column, '#');
      }
      else if (column == 0 or column == 49)
      {
        mvaddch(row, column, '#');
      }
      else if (row == snake->getPosX() and column == snake->getPosY())
      {
        mvaddch(row, column, 'O');
      }
      else if (row == foodPosX and column == foodPosY)
      {
        mvaddch(row, column, 'o');
      }
      else
      {
        mvaddch(row, column, ' ');
      }
    }
  }

  for (int i = 0; i < ntails; i++)
  {
    mvaddch(tails[i]->getPosX(), tails[i]->getPosY(), 'T');
  }
  mvprintw(31, 0, "Score: %d\n", score);
}

void logic()
{
  if (snake->getPosX() == foodPosX and snake->getPosY() == foodPosY)
  {
    //tails[ntails] = new Snake(lastTail->getPosX(), lastTail->getPosY() + 1);
    if(ntails > 0)			
    {
      if (snake->getPosY() > lastTail->getPosY())
      {
        tails[ntails] = new Snake(lastTail->getPosX(), lastTail->getPosY()-1);
      }
      else if(snake->getPosY() < lastTail->getPosY())
      {
        tails[ntails] = new Snake(lastTail->getPosX(), lastTail->getPosY()+1);
      }
      else if(snake->getPosX() > lastTail->getPosX())
      {
        tails[ntails] = new Snake(lastTail->getPosX()-1, lastTail->getPosY());
      }
      else if(snake->getPosX() < lastTail->getPosX())
      {
        tails[ntails] = new Snake(lastTail->getPosX()+1, lastTail->getPosY());
      }
    }
    else 
    {
      if(snake->getPosX() == foodPosX)
      {
      tails[ntails] = new Snake(lastTail->getPosX(), lastTail->getPosY() + 1);
      }
      else if (snake->getPosY() == foodPosY)
      {	
        tails[ntails] = new Snake(lastTail->getPosX() + 1, lastTail->getPosY());
      }
    }
    
    lastTail = tails[ntails];
    score++;
    ntails++;
    foodPosX = rand() % 28 + 1;
    foodPosY = rand() % 48 + 1;
    draw();
    refresh();
  }
  if (snake->getPosX() == 0)
  {
    snake->setPosX(29);
  }
  else if (snake->getPosX() == 29)
  {
    snake->setPosX(0);
  }
  else if (snake->getPosY() == 0)
  {
    snake->setPosY(49);
  }
  else if (snake->getPosY() == 49)
  {
    snake->setPosY(0);
  }
}

void moveTail(int keypressed){
  switch(keypressed)
  {
    case KEY_UP:
      for(int i=0; i<ntails; i++)
      {
        if(tails[i]->getPosY() == snake->getPosY())
        {
          
          tails[i]->setPosX(tails[i]->getPosX()-1);
        }
        else
        {
          if(tails[i]->getPosY() > snake->getPosY())
          {
          tails[i]->setPosY(tails[i]->getPosY()-1);
          }
          else
          {
            tails[i]->setPosY(tails[i]->getPosY()+1);
          }
          
        }
      }
      break;

    case KEY_DOWN:
      for(int i=0; i<ntails; i++)
      {
        if(tails[i]->getPosY() == snake->getPosY())
        {
          tails[i]->setPosX(tails[i]->getPosX()+1);
        }
        else
        {
          if(tails[i]->getPosY() > snake->getPosY())
          {
          tails[i]->setPosY(tails[i]->getPosY()-1);
          }
          else
          {
            tails[i]->setPosY(tails[i]->getPosY()+1);
          }
        }
      }
      break;
    
    case KEY_LEFT:
      for(int i=0; i<ntails; i++)
      {
        if(tails[i]->getPosX() == snake->getPosX())
        {
          tails[i]->setPosY(tails[i]->getPosY()-1);
        }
        else
        {
          if(tails[i]->getPosX() > snake->getPosX())
          {
            tails[i]->setPosX(tails[i]->getPosX()-1);
          }
          else
          {
            tails[i]->setPosX(tails[i]->getPosX()+1);
          }
        }
      }
      break;
    
    case KEY_RIGHT:
      for(int i=0; i<ntails; i++)
      {
        if(tails[i]->getPosX() == snake->getPosX())
        {
          tails[i]->setPosY(tails[i]->getPosY()+1);
        }
        else
        { 
          if(tails[i]->getPosX() > snake->getPosX())
          {
            tails[i]->setPosX(tails[i]->getPosX()-1);
          }
          else
          {
            tails[i]->setPosX(tails[i]->getPosX()+1);
          }
        }
      }
      break;
    
  }
}

void input()
{
  initscr();

  keypad(stdscr, TRUE);

  draw();

  while ((keypressed = getch()) != 'q')
  {
    switch (keypressed)
    {
    case KEY_UP:
      snake->setPosX(snake->getPosX() - 1);
      moveTail(keypressed);
      draw();
      refresh();
      logic();
      break;
    case KEY_DOWN:
      snake->setPosX(snake->getPosX() + 1);
      moveTail(keypressed);
      draw();
      refresh();
      logic();
      break;
    case KEY_RIGHT:
      snake->setPosY(snake->getPosY() + 1);
      moveTail(keypressed);
      draw();
      refresh();
      logic();
      break;
    case KEY_LEFT:
      snake->setPosY(snake->getPosY() - 1);
      moveTail(keypressed);
      draw();
      refresh();
      logic();
      break;
    }
  }

  refresh();
  endwin();
}

int main()
{
  srand(time(NULL));
  foodPosX = rand() % 28 + 1;
  foodPosY = rand() % 48 + 1;
  input();
  return 0;
}