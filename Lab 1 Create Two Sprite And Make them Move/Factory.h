#ifndef FACTORY_H
#define FACTORY_H


class Factory
{

public:
    Factory();
    Factory(int x , int y);

    void Update();
    void CalculateAlignment(std::vector<Factory*> facs);
    void CalculateCohesion(std::vector<Factory*> facs);
    void CalculateSeperation(std::vector<Factory*> facs);
    void NormalizeVelocity();
    Pvector Avoid(Pvector playerLocation);
    void applyForce(Pvector force);
    void borders();
    //void borders();
    void Draw(sf::RenderWindow & w, sf::Vector2f &wb);
    ~Factory();

    Pvector* getVelocity() { return velocity; }
    void setVelocity(Pvector velo) { *velocity = velo; }
    Pvector* getLocation() { return location; }
    void setLocation(Pvector loc) { *location = loc; }


    Pvector getAlignment() { return alignment; }
    Pvector getCohesion() { return cohesion; }
    Pvector getSeperation() { return seperation; }

private:
    sf::Texture texture;
    sf::Vector2f direction;
    sf::Sprite sprite;
    float rotation = 0.2;//Radiants
    float speed = 1.5f;
    float maxSteeringForce = 1.0f;

    float spritePosOffSet = 16;
    Pvector* location;
    Pvector*  velocity;// = 0.03;
    Pvector* acceleration;// = 0.01;

    Pvector alignment;
    Pvector cohesion;
    Pvector seperation;
    int flockingDistance = 300;
    int neighborCount;

};

#endif // !FACTORY_H