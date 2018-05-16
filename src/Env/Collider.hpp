#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/System.hpp>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>

class Collider
{
public:
    virtual Vec2d getCenter() const = 0;
    virtual double getRadius() const = 0;
    //teste si other est en collision avec instance courante
    bool isColliding(const Collider& other) const;
    //teste si point est dans l'instance courante
    bool isPointInside(const Vec2d& point) const;
    void dessiner(sf::RenderTarget& target);
};

//permet de tester si body1 est en collision avec body2
bool operator| (const Collider& body1, const Collider& body2);
//permet de tester si point est dans body
bool operator> (const Collider& body, const Vec2d& point);

#endif
