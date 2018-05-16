#include "Organ.hpp"
#include <SFML/Graphics.hpp>
#include <Application.hpp>
#include <cmath>


using namespace std;

//----CONSTRUCTEUR----//
Organ::Organ(bool generation)
{
    /*générer, à la demande, des organes vides de contenu ou doté d'un contenu*/
    if (generation==true) {
        generate();
    }
}

//----DESTRUCTEUR----//
Organ::~Organ()
{
    for (int i = 0; i < nbCells_; ++i) {
        for (int j = 0; j < nbCells_; ++j) {
            delete cellHandlers_[i][j]; //si l'organe disparait, on gère la disparition des strates
            cellHandlers_[i][j] = nullptr;
        }
    }
    cellHandlers_.clear();
}

/*méthode qui fait évoluer un organe au cours du temps*/
void Organ::update()
{
    updateRepresentation(true);
}

/*méthode qui dessine l'organe*/
void Organ::drawOn(sf::RenderTarget& targetWindow)
{
    sf::Sprite image(renderingCache_.getTexture()); // transforme l'image en texture
    targetWindow.draw(image); // affiche la texture
}

/*des getters retournant la largeur et la hauteur graphiques associées à la vue interne*/
double Organ::getWidth()const
{
    return getAppConfig().simulation_organ_size;
}

double Organ::getHeight()const
{
    return getAppConfig().simulation_organ_size;
}

/*méthode qui initialise le nombre de case par ligne et la taille de chaque cellule*/
void Organ::reloadConfig()
{
    nbCells_= getAppConfig().simulation_organ_nbCells;  //initialiser le nombre de cellules par ligne
    cellSize_ = getWidth()/nbCells_; //initialiser la taille graphique de chaque cellule

    cellHandlers_.resize(nbCells_);
    for(int i(0); i < nbCells_; ++i) {
        cellHandlers_[i].resize(nbCells_, nullptr);
        for (int j = 0; j < nbCells_; ++j) {
            CellCoord coord(i, j);
            cellHandlers_[i][j] = new CellHandler(coord, this);
        }
    }

}

/*méthode qui initialise la repésentation associée au tableau en fonction de la grille*/
void Organ::reloadCacheStructure()
{
    unsigned int horizontalSize(nbCells_*cellSize_);
    unsigned int verticalSize(horizontalSize);
    renderingCache_.create(horizontalSize, verticalSize);
    /*initialiser l'attribut renderingCache_ à la taille que représente son image*/
    /*initialiser bloodVertexes_ et liverVertexes_ avec le même ensemble de sommets,
    celui correspondant aux sommets de toutes les cases de la grille. */
    bloodVertexes_ = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells_, cellSize_);

    liverVertexes_ = generateVertexes(getAppConfig().simulation_organ["textures"], nbCells_, cellSize_);
}

/*crée le foie*/
void Organ::createLiver()
{
    for (int i = 0; i < nbCells_; ++i)
    {
        for (int j = 0; j < nbCells_; ++j)
        {
            if(cellHandlers_[i][j] != nullptr) 
            {
                if((pow(i, 2) + pow((j - nbCells_), 2) < pow((nbCells_ + 1), 2)) and (pow((i - nbCells_), 2) + pow(j, 2) < pow((nbCells_ +1), 2)))
                {
                    updateCellHandler({i, j}, Kind::Liver);
                }
            }
        }
    }
}

/*crée le réseau sangin*/
void Organ::createBloodSystem(bool generateCapillaries)
{
    generateArtery();

    if(generateCapillaries)
    {
        generateStartPoint();

        for(size_t i(0); i < StartPointRight_.size(); ++i)
        {
            generateCapillaryFromPosition(StartPointRight_[i], {1, 0});
        }

        for(size_t i(0); i < StartPointLeft_.size(); ++i)
        {
            generateCapillaryFromPosition(StartPointLeft_[i], {-1,0});
        }
    }
}

/*méthode qui met à jour la représentation de l'organe*/
void Organ::updateRepresentation(bool updateOrgan)
{
    if(updateOrgan) {
        /*efface l'image renderingCache_ en lui donnant un fond tout rose*/
        renderingCache_.clear(sf::Color(223,196,176));
        //dessiner les carrés texturés
        drawRepresentation();
        for (int i = 0; i < nbCells_; ++i) {
            for (int j = 0; j < nbCells_; ++j) {
                update();
                updateRepresentationAt({i, j});
            }
        }
        cellHandlers_.erase(std::remove(cellHandlers_.begin(), cellHandlers_.end(), nullptr), cellHandlers_.end());
        renderingCache_.display();
    } else {
        /*efface l'image renderingCache_ en lui donnant un fond tout rose*/
        renderingCache_.clear(sf::Color(223,196,176));
        //dessiner les carrés texturés
        drawRepresentation();
        renderingCache_.display();
    }
}

/*méthode qui génère le contenu d'un organe; cette méthode utilise les
 * cinq fonctions que l'ont vient de définir, suivant un ordre précis.*/
void Organ::generate()
{
    reloadConfig(); //1. on initialise nos attributs
    reloadCacheStructure(); //2. on initialise la représentation
    //createLiver();//3. on crée le foie
    createBloodSystem(false);//4. on crée le réseau sanguin
    //updateRepresentation();//5. on met à jour la représentation

}

bool Organ::isOut(CellCoord cell)
{
    if(cell.x >= getWidth() or cell.y >= getHeight()) {
        return true;
    } else if((cell.x < 0 and cell.y < 0) or (cell.x <0 or cell.y < 0)) {
        return true;
    } else {
        return false;
    }
}

CellCoord Organ::toCellCoord(Vec2d const& pos) const
{
    //Find the cell to which belong position, and return position
    return vec2dToCellCoord(pos, getWidth(), getHeight(), cellSize_);
}

void Organ::updateRepresentationAt(const CellCoord& cellCoord)
{
    vector<size_t> indexes = indexesForCellVertexes(cellCoord.x, cellCoord.y, nbCells_);

    for(size_t i(0); i < indexes.size(); ++i) {
        liverVertexes_[indexes[i]].color.a = cellHandlers_[cellCoord.x][cellCoord.y]->hasLiver() ? 255 : 0; //si le cellHandler contient une cellule hépatique-> rendre visible le liverVertexes_
        bloodVertexes_[indexes[i]].color.a = cellHandlers_[cellCoord.x][cellCoord.y]->hasBlood() ? 255 : 0; //si le cellHandler contient une cellule sanguine-> rendre visible le bloodVertexes_
    }
}


void Organ::drawRepresentation()
{
    //dessin d'un bloodVertexes_
    sf::RenderStates rs;
    auto textures = getAppConfig().simulation_organ["textures"];
    rs.texture = &getAppTexture(textures["blood"].toString()); // ici pour la texture liée une cellule sanguine

    // nous dessinons sur l'image associée à Organ
    // et non pas directement dans la fenêtre:

    renderingCache_.draw(bloodVertexes_.data(), bloodVertexes_.size(), sf::Quads, rs);

    //dessin d'un liverVertexes_
    sf::RenderStates rs1;
    auto textureRs1 = getAppConfig().simulation_organ["textures"];
    rs1.texture = &getAppTexture(textureRs1["liver"].toString()); // ici pour la texture liée une cellule sanguine
    renderingCache_.draw(liverVertexes_.data(), liverVertexes_.size(), sf::Quads, rs1);
}

void Organ::updateCellHandler(const CellCoord& pos, Kind kind)
{
    switch(kind) {
    case Kind::ECM :
        cellHandlers_[pos.x][pos.y]->setECM();
        break;
    case Kind::Liver :
        cellHandlers_[pos.x][pos.y]->setLiver();
        break;
    case Kind::Artery :
        cellHandlers_[pos.x][pos.y]->setBlood(ARTERY);
        break;
    case Kind::Capillary :
        cellHandlers_[pos.x][pos.y]->setBlood(CAPILLARY);
        break;
    }
}

void Organ::generateArtery()
{
    int SIZE_ARTERY(max(0.03*nbCells_, 1.0));
    for(int i= (nbCells_ - SIZE_ARTERY) / 2; i <= (nbCells_ + SIZE_ARTERY)/2; ++i)
    {
        for(int j=0; j <nbCells_; ++j)
        {
            CellCoord positionArtery({i, j});
            updateCellHandler(positionArtery, Organ::Kind::Artery);
        }
    }
}


void Organ::generateCapillaryOneStep(CellCoord &current_position, const CellCoord& dir, int& nbCells, const int& maxLength)
{
    CellCoord coordinate{0,1};

    if(cellHandlers_.size() == 0 || nbCells == maxLength)
        return;

    if(bernoulli(1.0/6.0) and not isOut(current_position - coordinate) and not (current_position.y == 1) and not cellHandlers_[current_position.x][current_position.y-1]->hasBlood())
    {
        ++nbCells;
        current_position -= coordinate;
        updateCellHandler(current_position, Kind::Capillary);

    } else if(bernoulli(1.0/6.0) and not isOut(current_position + coordinate) and not cellHandlers_[current_position.x][current_position.y+1]->hasBlood())
    {
        ++nbCells;
        current_position += coordinate;
        updateCellHandler(current_position, Organ::Kind::Capillary);

    } else if(bernoulli(2.0/3.0) and not isOut(current_position + dir) and not cellHandlers_[current_position.x + dir.x][current_position.y + dir.y]->hasBlood())
    {
        ++nbCells;
        current_position += dir;
        updateCellHandler(current_position, Kind::Capillary);
    }

}

void Organ::generateCapillaryFromPosition(CellCoord& current_position, CellCoord dir)
{
    int LENGTH_CAPILLARY((nbCells_/2)-4);
    int nbCells(0);
    int compteur(0);
    do{
        for (int i = 0; i < LENGTH_CAPILLARY ; ++i)
        {
            generateCapillaryOneStep(current_position, dir, nbCells, LENGTH_CAPILLARY);
            ++compteur;
        }
    } while(compteur <= 60); //taille compteur ??
}

void Organ::generateStartPoint()
{
    int START_CREATION_FROM(getAppConfig().blood_creation_start);
    int NB_CAPILLARY((nbCells_-START_CREATION_FROM)/3);
    int SIZE_ARTERY(max(0.03*nbCells_, 1.0));
    int previousStartPointRight(START_CREATION_FROM - getAppConfig().blood_capillary_min_dist);
    int previousStartPointLeft(START_CREATION_FROM - getAppConfig().blood_capillary_min_dist);
    int nCapillaryRight = 0;
    int nCapillaryLeft = 0;
    for (int y = START_CREATION_FROM; y < nbCells_; ++y)
    {
        if(bernoulli(1.0/3.0) and (y - previousStartPointRight) >= getAppConfig().blood_capillary_min_dist)
        {
            StartPointRight_.push_back({(nbCells_ + SIZE_ARTERY)/2, y});
            previousStartPointRight = y;
            if (++nCapillaryRight > NB_CAPILLARY)
                break;
        }

        if(bernoulli(1.0/3.0) and (y - previousStartPointLeft) >= getAppConfig().blood_capillary_min_dist)
        {
            StartPointLeft_.push_back({(nbCells_ - SIZE_ARTERY)/2, y});
            previousStartPointLeft = y;
            if (++nCapillaryLeft > NB_CAPILLARY)
                break;
        }
    }
}
