#ifndef BOX_HPP
#define BOX_HPP
#include <iostream>
#include <vector>
#include <Utility/Vec2d.hpp>

using namespace std;

typedef pair <Vec2d, Vec2d> Wall; //bottom right corner, top left corner

class Box
{

private:
    Vec2d centre_;

    double largeur_;

    double hauteur_;

    double epaisseur_;

    Wall Top;

    Wall Bottom;

    Wall Right;

    Wall Left;

    bool AnimalPresent_;
    /*cet attribut sert à "marquer" une boîte; soit comme étant inoccupée et donc
     * notre attribut sera mis à "false", ou alors comme étant occupée et notre attribut
     * sera mis à "true".*/


public:
    /*constructeur*/
    Box(Vec2d centre, double largeur=300, double hauteur=300, double epaisseur=10);

    /*getters*/
    Vec2d getCenter() {
        return centre_;
    }

    double getWidth() {
        return largeur_;   //murs compris
    }

    double getHeight() {
        return hauteur_;   //murs compris
    }

    double getWallWidth() {
        return epaisseur_;
    }

    /*getters qui retournent la face interne du mur si intern vaut true
     * et de la face externe si intern vaut false*/
    double getLeftLimit(bool intern = false);

    double getRightLimit(bool intern = false);

    double getTopLimit(bool intern = false);
    //coordonnée y au lieu de x avec mur du haut

    double getBottomLimit(bool intern = false);
    // coordonnée y avec mur du bas

    /*méthode qui retourne vrai si un point à une position donnée est COMPLETEMENT a l'interieur de la boite;
     * i.e. un point sur le  bord interne d'un mur ne sera pas considere comme a l'intérieur.*/
    bool isPositionInside(const Vec2d& position);

    /*vérifie si la position est sur l'un des murs de la boîte*/
    bool isPositionOnWall(const Vec2d& position);

    /*des getters qui retournent les murs de la boîte*/
    Wall getTop() {
        return Top;
    }

    Wall getLeft() {
        return Left;
    }

    Wall getBottom() {
        return Bottom;
    }

    Wall getRight() {
        return Right;
    }

    /*méthode qui vérifie si la boîte est vite*/
    bool isEmpty()const;

    /*setter qui marque une boîte comme étant "occupée"*/
    void addOccupant();

    /*méthode qui marque la boîte comme étant inocuppée*/
    void reset();


};
#endif