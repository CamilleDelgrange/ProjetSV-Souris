#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "SimulatedEntity.hpp"
#include "Box.hpp"
#include "Random/Random.hpp"
#include "Lab.hpp"
#include "Cheese.hpp"
#include "Organ.hpp"

enum Etat {
    FOOD_IN_SIGHT, //nourriture en vue (il sera attiré par la nourriture)
    FEEDING, // en train de manger (là en principe il arrête de se déplacer)
    WANDERING, //déambule
    IDLE, //au repos
};

class Animal:public SimulatedEntity
{

public:
    Animal(double energie, Vec2d position, sf::Texture texture, double angleVision, double distanceVision, double Masse);

    //-------MISE A JOUR COMPORTEMENT ANIMAL--------//
    virtual void update(sf::Time dt) override; //met à jour le comportement de l'animal selon son état
    Etat updateState(sf::Time); //retourne l'état de l'animal selon des conditions

    //---------GETTERS--------//
    Vec2d getSpeedVector();
    virtual double getMaxSpeed() = 0; //redéfinie dans mouse
    virtual double getViewRange() const; //retourne angle de vision
    virtual double getViewDistance() const;//retourne la distance maximale de vision
    Vec2d getPosition();
    virtual double getLossFactor()=0; //redéfinie dans mouse
    virtual double getMasse() const; //redéfini dans Mouse

    //-------MOUVEMENT ANIMAL--------//
    void move(sf::Time dt);
    bool TestCollision(Vec2d newP);
    Angle getNewRotation();
    void move(const Vec2d& force, sf::Time dt);
    Vec2d force();

    //-------DESSIN ANIMAL---------//
    virtual void drawOn(sf::RenderTarget& targetWindow);

    //-------Y-A-T-IL UNE CIBLE EN VUE ?--------//
    bool isTargetInSight(const Vec2d& position); //y a t-il une cible en vue ?
    bool isInViewRange(Vec2d PositionCible); //est-elle dans le champ de vision ?

    //-------CONDITIONS--------//
    void confine(Box* box);
    bool isRepete(); //repete = rassasié, fonction qui retourne true s'il est rassasié
    bool isMeeting(SimulatedEntity* entite); //teste si une souris est en collision avec un fromage

    virtual Quantity FoodQuantity() = 0;

    /*cette méthode dessine un curseur de traque sur notre animal traqué*/
    void dessinerTracked(sf::RenderTarget& target);

    /*cette méthode permet de faire évoluer l'organe de notre animal*/
    void updateOrgan();

    /*cette méthode dessine l'organe de notre animal*/
    void drawOrgan(sf::RenderTarget& targetWindow);

    virtual ~Animal();


protected:
    Etat etat;
    double velocity;
    static const Intervals intervals;
    static const Probs probs;
    sf::Time compteur;
    double angleVision_;
    double distanceVision_;
    void setRotation(double angleVision);
    double Masse_;
    SimulatedEntity* TargetFood_; //atribut de la cible en vue
    Organ* organ_;
    void setOrgan(Organ* organ);

};
#endif
