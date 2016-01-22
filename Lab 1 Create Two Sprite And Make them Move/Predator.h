#pragma once
class Predator
{
public:
    Predator();//!< contructor.
    Predator(float x, float y,Factory* fac);//!< Override constructor.
    ~Predator();
    void Update();//!< scales the acceleration and applies it and the veloicty to the location of the swarmer.
    void Draw(sf::RenderWindow & w, sf::Vector2f & wb);//!<  Draws the Predator.

    void borders();//!< screen rap for the large area.
	//! Three Laws that boids follow
    void CalculateAlignment(std::vector<Predator*> preds);

    void CalculateCohesion(std::vector<Predator*> preds);

    void CalculateSeperation(std::vector<Predator*> preds);

    Pvector Seek(Pvector playerLocation);//!< Seek the preditor away from a point.

    sf::Vector2f GetPos();//!< gets the posision of the object for collsiion checks in other classes.

    sf::FloatRect GetBounds();//!<  gets the size of the object for collision checks in other classes.

    Pvector* getVelocity() { return velocity; }
    void setVelocity(Pvector velo) { *velocity = velo; }
    Pvector* getLocation() { return location; }
    void setLocation(Pvector loc) { *location = loc; }


    Pvector getAlignment() { return alignment; }
    Pvector getCohesion() { return cohesion; }
    Pvector getSeperation() { return seperation; }

    Factory* getOwner() { return owner; }

private:
    sf::Texture texture;
    sf::Vector2f direction;
    sf::Sprite sprite;
    float rotation = 0.2;//Radiants
    float speed = 3.0f;
    float maxSteeringForce = 1.0f;

    float spritePosOffSet = 16;
    Pvector* location;
    Pvector*  velocity;// = 0.03;
    Pvector* acceleration;// = 0.01;

    Factory* owner;

    Pvector alignment;
    Pvector cohesion;
    Pvector seperation;
    int flockingDistance = 300;
    int neighborCount;
};

