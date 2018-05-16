#include "SimulatedEntity.hpp"
#include "Animal.hpp"
#include "Box.hpp"
#include "Cheese.hpp"
#include "Random/Random.hpp"
#include <Application.hpp>
#include <Utility/Arc.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <cmath>

Animal::Animal(double energie, Vec2d position, sf::Texture texture, double angleVision, double distanceVision, double Masse)
    : SimulatedEntity(energie, position, texture)
    , etat(WANDERING)
    , velocity(0.0)
    , compteur(sf::Time::Zero)
    , angleVision_(angleVision)
    , distanceVision_(distanceVision)
    , Masse_(Masse)
    , TargetFood_(nullptr)
{
    organ_ = new Organ(true);
}


const Intervals Animal::intervals { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
const Probs Animal::probs
{
    0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000
};

void Animal::update(sf::Time dt)
{
    SimulatedEntity::update(dt);
    etat = updateState(dt);
    if (organ_!=nullptr) {
        organ_->update();
    }
    switch(etat) {
    case FOOD_IN_SIGHT :
        move(force(), dt);
        break;

    case FEEDING :
        energie_ += FoodQuantity()*getAppConfig().animal_meal_retention; //comment faire pour la faire manger tous les dt ??
        if(TargetFood_ != nullptr) {
            TargetFood_->provideEnergy(FoodQuantity());
            if(TargetFood_->isdead()) {
                TargetFood_ = nullptr;
            }
        }
        break;

    case WANDERING :
        move(dt);
        velocity = getMaxSpeed();

    case IDLE :
        break;
    }
    energie_ -= getAppConfig().animal_base_energy_consumption + sqrt(pow(getSpeedVector().x, 2) + pow(getSpeedVector().y, 2)) * getLossFactor() * dt.asSeconds();
}

Etat Animal::updateState(sf::Time)
{
    TargetFood_= getAppEnv().FindTargetInSight(this); //l'attribut cible de l'animal est initialisé à la cible en vue
    if(TargetFood_ == nullptr or ((etat == WANDERING) && isRepete())) {
        return WANDERING; //si toutes ces conditions ne sont pas satisfaites, l'animal retourne en WANDERING
    }

    if(TargetFood_ != nullptr) { //on vérifie s'il n'est pas un pointeur nul
        if(isMeeting(TargetFood_) and energie_ < getAppConfig().animal_satiety_max) { //si l'animal est en collision avec la cible et si son énergie est en dessous du seuil max alors il passe en FEEDING
            return FEEDING;
        }

        if(not isRepete()) { //si l'animal n'est pas rassasié, on retourne FOOD_IN_SIGHT (on a déjà testé dans FindTargetInSight s'il avait une cible en vue
            return FOOD_IN_SIGHT;
        }
    }
    return WANDERING;
}

Vec2d Animal::getSpeedVector()
{
    return getHeading()*velocity;
}

void Animal::move(sf::Time dt)
{
    compteur += dt;
    Vec2d newPosition(position_ + getSpeedVector()*dt.asSeconds());
    if(TestCollision(newPosition)) {
        if(compteur >= getAppConfig().animal_time_between_rotations) {
            anglerad_ = (-getHeading()).angle();
            compteur = sf::Time::Zero;
        }
    } else {
        if(compteur >= getAppConfig().animal_time_between_rotations) {
            anglerad_ += getNewRotation();
            compteur = sf::Time::Zero;
        }
        position_ = newPosition;
    }
}

bool Animal::TestCollision(Vec2d newP)
{
    return ((newP.y - getRadius() <= box_->getTopLimit(true))
            or (newP.y + getRadius() >= box_->getBottomLimit(true))
            or	(newP.x - getRadius() <= box_->getLeftLimit(true))
            or (newP.x + getRadius() >= box_->getRightLimit(true)));
}

Angle Animal::getNewRotation()
{
    return DEG_TO_RAD * piecewise_linear(intervals, probs);
}

double Animal::getViewRange() const
{
    return angleVision_;
}

double Animal::getViewDistance() const
{
    return distanceVision_;
}

void Animal::drawOn(sf::RenderTarget& targetWindow)
{
    SimulatedEntity::drawOn(targetWindow);
    if(isDebugOn()) {
        sf::Color color = sf::Color::Black;
        color.a = 16; // light, transparent grey
        Arc arcgraphics((-getViewRange()/2)/DEG_TO_RAD, (getViewRange()/2)/DEG_TO_RAD, getViewDistance(), color, getViewDistance());
        arcgraphics.rotate(getHeading().angle()/DEG_TO_RAD);
        arcgraphics.setOrigin(getViewDistance(), getViewDistance());
        arcgraphics.setPosition(position_);
        targetWindow.draw(arcgraphics);
        string un_texte;
        switch(etat) {
        case WANDERING :
            un_texte = "WANDERING";
            break;
        case FOOD_IN_SIGHT :
            un_texte = "FOOD_IN_SIGHT";
            break;
        case FEEDING :
            un_texte = "FEEDING";
            break;
        case IDLE :
            un_texte = "IDLE";
            break;
        }
        Vec2d position(position_);
        position += {90, 90};
        auto text = buildText(un_texte, position, getAppFont(), getAppConfig().default_debug_text_size,
                              sf::Color::Red);
        targetWindow.draw(text);
    }
}

bool Animal::isTargetInSight(const Vec2d& position)
{
    return (box_->isPositionInside(position) and isInViewRange(position));
}

bool Animal::isInViewRange(Vec2d PositionCible)
{
    Vec2d d = PositionCible - position_;
    Vec2d dn = d/(sqrt(d.lengthSquared()));
    if (isEqual(sqrt(d.lengthSquared()),0.0)) {
        return true;
    } else {
        return ((sqrt(d.lengthSquared())) <= getViewDistance()
                and getHeading().dot(dn) >= cos((getViewRange() + 0.001)/2));
    }
}

void Animal::setRotation(Angle angle)
{
    anglerad_ = angle;
}

Vec2d Animal::getPosition()
{
    return position_;
}

void Animal::confine(Box* box)
{
    box_ = box;
}

void Animal::move(const Vec2d& force, sf::Time dt)
{
    Vec2d acceleration = force / getMasse();
    Vec2d nouvelleVitesse = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d nouvelleDirection = nouvelleVitesse.normalised();
    if(sqrt(nouvelleVitesse.lengthSquared()) > getMaxSpeed()) {
        nouvelleVitesse = nouvelleDirection * getMaxSpeed();
    }
    Vec2d nouvellePosition = position_ + nouvelleVitesse * dt.asSeconds();
    anglerad_ = nouvelleDirection.angle(); //on met à jour son orientation
    position_ = nouvellePosition; //on met à jour sa position
}

double Animal::getMasse() const
{
    return Masse_;
}

Vec2d Animal::force()
{
    Vec2d toTarget(getAppEnv().FindTargetInSight(this)->getCenter() - position_);
    double speed(min(sqrt(toTarget.lengthSquared())/getAppConfig().animal_deceleration, getMaxSpeed()));
    Vec2d vTarget((toTarget/sqrt(toTarget.lengthSquared()))*speed);
    Vec2d force = vTarget - getSpeedVector();
    if(sqrt(toTarget.lengthSquared())== 0.0) {
        return Vec2d(0.0,0.0);
    } else {
        return force;
    }
}

bool Animal::isRepete() //teste si l'animal est rassasié
{
    if(energie_> getAppConfig().animal_satiety_min) {
        return true;
    } else {
        return false;
    }
}


bool Animal::isMeeting(SimulatedEntity* entite)
{
    if(entite != nullptr) {
        return (distance(getCenter(), entite->getCenter()) <= (getRadius() + entite->getRadius()));
    } else {
        return false;
    }
}

/*cette méthode dessine un curseur de traque sur notre animal traqué*/
void Animal::dessinerTracked(sf::RenderTarget& target)
{
    Vec2d decalage(0, - (getRadius()));
    decalage.rotate(anglerad_ - PI/4);
    sf::Sprite tracked = buildSprite(position_, getRadius(), getAppTexture(getAppConfig().entity_texture_tracked));
    target.draw(tracked);
}

/*cette méthode permet de faire évoluer l'organe de notre animal, s'il existe.
 * il fait appel à la fonction update de la classe Organ.*/
void Animal::updateOrgan()
{
    if (organ_!=nullptr) {
        organ_->update();
    }
}

/*cette méthode dessine l'organe de notre animal. Elle fait appel
 * àa la méthode de dessin de notre organe.*/
void Animal::drawOrgan(sf::RenderTarget& targetWindow)
{
    if (organ_ != nullptr) {
        organ_->drawOn(targetWindow);
    }
}

void Animal::setOrgan(Organ* organ)
{
    if (organ_)
        delete organ_;
    organ_ = organ;
}

Animal::~Animal()
{
    delete organ_;
}

