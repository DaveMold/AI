#ifndef FACTORY_H
#define FACTORY_H


class Factory
{

public:
    Factory();
    Factory(int x , int y);

    sf::Vector2f ScreenRap(sf::Vector2f pos, sf::RenderWindow & w);
    void Update();
    void Draw(sf::RenderWindow & w);
    ~Factory();

private:
    sf::Texture texture;
    sf::Vector2f direction;
    sf::Sprite sprite;
    float rotation = 0.2;//Radiants
    float speed = 3.0f;
    float maxSpeed = 3.0f;

    float spritePosOffSet = 16;
    Pvector* location;
    Pvector*  velocity;// = 0.03;
    Pvector* acceleration;// = 0.01;

};

#endif // !FACTORY_H