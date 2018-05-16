#include <iostream>
#include <Env/Collider.hpp>
#include <Utility/Vec2d.hpp>
#include <Application.hpp>

bool Collider::isColliding(const Collider& other) const
{
    return (distance(getCenter(), other.getCenter()) <= (getRadius() + other.getRadius()));
}

bool Collider::isPointInside(const Vec2d& point) const
{
    return (distance(getCenter(), point) <= (getRadius()));
}

bool operator| (const Collider& body1, const Collider& body2)
{
    return (body1.isColliding(body2)) ;
}

bool operator> (const Collider& body, const Vec2d& point)
{
    return (body.isPointInside(point));
}

void Collider::dessiner(sf::RenderTarget& target)
{
    if(isDebugOn()) {
        auto circle(buildCircle(getCenter(), getRadius(), sf::Color(20,150,20,30)));
        target.draw(circle);
    }
}
