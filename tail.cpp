using namespace std;

class Tail
{
  private:
    int x,y;

  public:
    Tail(int posX, int posY);
    inline int getPosX() { return x; }
    inline int getPosY() { return y; }
    void setPosX(int newPosX);
    void setPosY(int newPosY);
};

Tail::Tail(int posX, int posY)
{
  this->x = posX;
  this->y = posY;
}

void Tail::setPosX(int newPosX)
{
  this->x = newPosX;
}

void Tail::setPosY(int newPosY)
{
  this->y = newPosY;
}

