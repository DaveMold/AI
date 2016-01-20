#include "stdafx.h"
#include "Factory.h"



Factory::Factory()
{
    texture.loadFromFile("Resorces/Img/Factory.png");
    sprite.setTexture(texture);
    velocity = new Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
    location = new Pvector(rand() % 750 + 1, rand() % 550 + 1);//x, y);
}

Factory::Factory(int x, int y) : Factory()
{
    //sprite.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Factory::ScreenRap(sf::Vector2f pos, sf::RenderWindow &w)
{
    if (pos.x < 0 - (spritePosOffSet * 2))
        pos.x = w.getSize().x;
    else if (pos.x > w.getSize().x)
        pos.x = 1 - (spritePosOffSet * 2);
    if (pos.y < 0 - (spritePosOffSet * 2))
        pos.y = w.getSize().y;
    else if (pos.y > w.getSize().y + 1)
        pos.y = 1 - (spritePosOffSet * 2);
    return pos;
}

void Factory::Update()
{

}

void Factory::Draw(sf::RenderWindow &w)
{
    sprite.setPosition(ScreenRap(sf::Vector2f(location->x, location->y), w));
    w.draw(sprite);
}

Factory::~Factory()
{
}
