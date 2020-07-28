#include <iostream>
#include <vector>
#include "tail.cpp"
using namespace std;

class Snake{
  private:
    int x, y;
  public:
    Snake(int posX, int posY);
    inline int getPosX() { return x; }
    inline int getPosY() { return y; }
    void setPosX(int newPosY);
    void setPosY(int newPosY);
    void addTail(Tail tail);
    Tail getTails();
};

Snake::Snake(int posX, int posY){
  x = posX; y=posY;
}

void Snake::setPosX(int newPosX){
  this->x = newPosX;	
}
 
void Snake::setPosY(int newPosY){
  this->y = newPosY;
}
