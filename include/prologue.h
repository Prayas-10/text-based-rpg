#ifndef PROLOGUE_H
#define PROLOGUE_H

class Player;

class Prologue
{
private:
    void opening(Player& player);
    void scene1(Player& player);
    void scene2(Player& player);
public:
    void play(Player& player);
};
#endif
