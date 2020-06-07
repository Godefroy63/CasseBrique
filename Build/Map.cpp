#include "Map.h"

//Constructeur

Map::Map(sf::RenderWindow& window)
{
	this->mHauteurTile = this->mLargeurTile = this->mNbtileX = this->mNbtileY = this->mNbTileMapX = this->mNbTileMapY = 0;
	this->mTabMap = nullptr;
	this->mPostionBrique.x = this->mPostionBrique.y = 0.0f;
	this->mTabBriqueTexture = nullptr;
	this->mTabBriqueSprite = nullptr;
	this->mCouleurBalle = 3;
	this->mLargeurBalle = 16;
	this->mHauteurBalle = 16;
	this->mBalleCole = true;
	this->mNbPoint = 0.0f;
	
	
	

	//Chargement du plateau
	if (!this->mPlateauTexture.loadFromFile("Image/Plateau.png"))
	{
		//Message d'erreur
		std::cout << "Erreur dans le chargement du plateau" << std::endl;
	}
	else
	{
		this->mPlateauSprite.setTexture(this->mPlateauTexture);

	}

	this->mPostionplateau.x = (window.getSize().x / 2) - (this->mPlateauTexture.getSize().x / 2);
	this->mPostionplateau.y = window.getSize().y - this->mPlateauTexture.getSize().y;


	//Chargement du plateau
	if (!this->mTabBalleTexture.loadFromFile("Image/Balle.png"))
	{
		//Message d'erreur
		std::cout << "Erreur dans le chargement du plateau" << std::endl;
	}
	else
	{
		this->mTabBalleSprite.setTexture(this->mTabBalleTexture);

	}

	this->mPostionBalles.x = this->mPostionplateau.x + (this->mPlateauTexture.getSize().x / 2) - (this->mLargeurBalle/2);
	this->mPostionBalles.y = this->mPostionplateau.y - this->mTabBalleTexture.getSize().y;
	this->mVitesse.x = -2;
	this->mVitesse.y = 2;

	if (this->mfont.loadFromFile("Font/VCR_OSD_MONO_1.001.ttf"))
	{
		//Message d'erreur
		std::cout << "Erreur dans le chargement du Font" << std::endl;
	}

}

//Destructeur

Map::~Map()
{
	//Destruction des sprite et texture brique
	delete[]this->mTabBriqueTexture;
	this->mTabBriqueTexture = nullptr;
	delete[]this->mTabBriqueSprite;
	this->mTabBriqueSprite = nullptr;

	
	//Destruction du tableau 2D Avec le Layer 1
	for (int i{ 0 }; i < this->mNbTileMapX; i++)
	{
		delete[]this->mTabMap[i];
		this->mTabMap[i] = nullptr;

	}
	delete[]this->mTabMap;
	this->mTabMap = nullptr;
}


//Méthode

void Map::chargerMap(std::string fichier)
{

	//Création de variable de travail
	std::string buffer, buffer2;	//Memoire tempon pour lire dans le fichier
	int NumTile{ 0 };				//Numerotation des tiles


	//Ouverture du fichier de config de la map et du TileSet
	std::ifstream monFlux(fichier);

	if (monFlux)
	{
		monFlux >> buffer;					//#Tile Set
		monFlux >> this->mLevel;			//Non du fichier image
		monFlux >> this->mHauteurTile;		//Hauteur d'un tile
		monFlux >> this->mLargeurTile;		//Largeur d'un tile
		monFlux >> this->mNbtileX;			//Nombre de tile en largeur du tileset
		monFlux >> this->mNbtileY;			//Nombre de tile en hauteur du tileset

		//Allocation dynamique des tableau en fonction de la config du fichier
		this->mTabBriqueSprite = new sf::Sprite[this->mNbtileX * this->mNbtileY];
		this->mTabBriqueTexture = new sf::Texture[this->mNbtileX * this->mNbtileY];

		//Chargement des texures et sprites
		for (int j{ 0 }; j < this->mNbtileY; j++)
		{
			for (int i{ 0 }; i < this->mNbtileX; i++)
			{
				if (!this->mTabBriqueTexture[NumTile].loadFromFile(this->mLevel, sf::IntRect(i * this->mLargeurTile, j * this->mHauteurTile, 32, 32)))
				{
					//Message d'erreur
					std::cout << "Erreur dans le chargement du Tile_set " << std::endl;
				}
				else
				{
					this->mTabBriqueSprite[NumTile].setTexture(this->mTabBriqueTexture[NumTile]);
					NumTile++;
				}
			}
		}

		NumTile = 0;		//Raz de la numerotation des tiles

		monFlux >> this->mNbTileMapX;		//Nombre de tile en Largeur de la map
		monFlux >> this->mNbTileMapY;		//Nombre de tile en Hauteur de la map

		//Allocation dynamique du Tableau 2D contenant la map
		this->mTabMap = new int* [this->mNbTileMapX];

		for (int i{ 0 }; i < this->mNbTileMapX; i++)
		{
			this->mTabMap[i] = new int[this->mNbTileMapY];
		}

		//Chargement de la map dans le tableau 2D Layer 1
		for (int j{ 0 }; j < this->mNbTileMapY; j++)
		{
			for (int i{ 0 }; i < this->mNbTileMapX; i++)
			{
				monFlux >> NumTile;					// Lecture du numero de tile dans fichier
				this->mTabMap[i][j] = NumTile;
			}
		}

		monFlux.close();
	}
	else
	{
		std::cout << "Erreur fichier de chargement" << std::endl;
	}

}



void Map::drawMap(sf::RenderWindow & window)
	{
		int NumTile{ 0 };
		

		//for (int i{ maxX }; i > minX; i--)
		for (int i{ 0 }; i < this->mNbTileMapX; i++)
		{

			//for (int j{ maxY }; j > minY; j--)
			for (int j{ 0 }; j < this->mNbTileMapY; j++)
			{

				NumTile = this->mTabMap[i][j];

				this->mPostionBrique.x = i * this->mLargeurTile; 
				this->mPostionBrique.y = j * this->mHauteurTile;


				this->mTabBriqueSprite[NumTile].setPosition(sf::Vector2f(this->mPostionBrique.x, this->mPostionBrique.y));
				window.draw(this->mTabBriqueSprite[NumTile]);

			}
		}
	}

void Map::drawPlateau(sf::RenderWindow& window)
{
	this->mPlateauSprite.setPosition(sf::Vector2f(this->mPostionplateau.x, this->mPostionplateau.y));
	window.draw(this->mPlateauSprite);


	this->mTabBalleSprite.setTextureRect(sf::IntRect(this->mCouleurBalle * this->mLargeurBalle, 0, this->mLargeurBalle, this->mHauteurBalle));
	this->mTabBalleSprite.setPosition(sf::Vector2f(this->mPostionBalles.x, this->mPostionBalles.y));
	window.draw(this->mTabBalleSprite);

	this->mtexte = std::to_string(this->mNbPoint);
	this->mText.setFont(this->mfont);
	this->mText.setString(this->mtexte);
	this->mText.setCharacterSize(24);
	window.draw(this->mText);
}

void Map::depacement(sf::RenderWindow& window,Input input)
{
	
	if (input.getButton().Click_left == true)
	{
		this->mBalleCole = false;
	}

	this->mPostionplateau.x = sf::Mouse::getPosition(window).x;// -(this->mPlateauTexture.getSize().x / 2);
	

	if (this->mPostionplateau.x < 0 )
		this->mPostionplateau.x = 0;

	if (this->mPostionplateau.x  > window.getSize().x - this->mPlateauTexture.getSize().x)
		this->mPostionplateau.x = window.getSize().x - this->mPlateauTexture.getSize().x;
	
	if (this->mBalleCole == true)
	{
		this->mPostionBalles.x = this->mPostionplateau.x + (this->mPlateauTexture.getSize().x / 2) - (this->mLargeurBalle / 2);
		this->mPostionBalles.y = this->mPostionplateau.y - this->mTabBalleTexture.getSize().y;
	}
	else
	{
		this->mPostionBalles.x += this->mVitesse.x;
		this->mPostionBalles.y += this->mVitesse.y;

		if (this->mPostionBalles.x > window.getSize().x - this->mLargeurBalle)
		{
			this->mVitesse.x = 0 - this->mVitesse.x;
			this->mPostionBalles.x = window.getSize().x - this->mLargeurBalle;
		}
			
			
		if (this->mPostionBalles.x < 0)
		{
			this->mVitesse.x = 0 - this->mVitesse.x;
			this->mPostionBalles.x = 0;
		}


		if (this->mPostionBalles.y < 0)
		{
			this->mVitesse.y = 0 - this->mVitesse.y;
			this->mPostionBalles.y = 0;
		}
		
		
		if (this->mPostionBalles.y > window.getSize().y - this->mHauteurBalle - this->mPlateauTexture.getSize().y && this->mPostionBalles.x >= this->mPostionplateau.x
			&& this->mPostionBalles.x < this->mPostionplateau.x + this->mPlateauTexture.getSize().x)
		{
			this->mVitesse.y += 0.5;
			this->mVitesse.y = 0 - this->mVitesse.y;
			this->mPostionBalles.y = window.getSize().y - this->mHauteurBalle - this->mPlateauTexture.getSize().y;
		}
			

		if (this->mPostionBalles.y > window.getSize().y)
		{
			this->mBalleCole = true;
			this->mCouleurBalle = 3;
			this->mVitesse.y = 2;
		}
			

		if(this->collision(this->mPostionBalles.x + (this->mLargeurBalle/2), this->mPostionBalles.y - (this->mHauteurBalle / 2)) != 0)
			this->mVitesse.y = 0 - this->mVitesse.y;


	}

	
}


int Map::collision(float x, float y)
{
	int xmin, xmax, ymin, ymax;

	xmin = x / this->mLargeurTile;
	ymin = y / this->mHauteurTile;
	xmax = (x + this->mLargeurTile - 1) / this->mLargeurTile;
	ymax = (y + this->mHauteurTile - 1) / this->mHauteurTile;


	
	if (this->mTabMap[xmin][ymin] == 0)
	{
		this->mCouleurBalle = 2;
		this->mTabMap[xmin][ymin] = 1;
		return 1;
	}
	else if(this->mTabMap[xmax][ymax] == 0)
	{
		this->mCouleurBalle = 2;
		this->mTabMap[xmax][ymax] = 1;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 0)
	{
		this->mCouleurBalle = 2;
		this->mTabMap[xmin][ymax] = 1;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 0)
	{
		this->mCouleurBalle = 2;
		this->mTabMap[xmin][ymax] = 1;
		return 1;
	}
	else if (this->mTabMap[xmin][ymin] == 1)
	{
		this->mNbPoint += 10;
		this->mCouleurBalle = 2;
		this->mTabMap[xmin][ymin] = 8;
		return 1;
	}
	else if (this->mTabMap[xmax][ymax] == 1)
	{
		this->mNbPoint += 10;
		this->mCouleurBalle = 2;
		this->mTabMap[xmax][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 1)
	{
		this->mNbPoint += 10;
		this->mCouleurBalle = 2;
		this->mTabMap[xmin][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 1)
	{
		this->mNbPoint += 10;
		this->mCouleurBalle = 2;
		this->mTabMap[xmin][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymin] == 2)
	{
		this->mNbPoint += 5;
		this->mCouleurBalle = 0;
		this->mTabMap[xmin][ymin] = 8;
		return 1;
	}
	else if (this->mTabMap[xmax][ymax] == 2)
	{
		this->mNbPoint += 5;
		this->mCouleurBalle = 0;
		this->mTabMap[xmax][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 2)
	{
		this->mNbPoint += 5;
		this->mCouleurBalle = 0;
		this->mTabMap[xmin][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 2)
	{
		this->mNbPoint += 5;
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymin] == 3)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymin] = 4;
		return 1;
	}
	else if (this->mTabMap[xmax][ymax] == 3)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmax][ymax] = 4;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 3)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymax] = 4;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 3)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymax] = 4;
		return 1;
	}
	else if (this->mTabMap[xmin][ymin] == 4)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymin] = 5;
		return 1;
	}
	else if (this->mTabMap[xmax][ymax] == 4)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmax][ymax] = 5;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 4)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymax] = 5;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 4)
	{
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymax] = 5;
		return 1;
	}
	else if (this->mTabMap[xmin][ymin] == 5)
	{
		this->mNbPoint += 20;
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymin] = 8;
		return 1;
	}
	else if (this->mTabMap[xmax][ymax] == 5)
	{
		this->mNbPoint += 20;
		this->mCouleurBalle = 1;
		this->mTabMap[xmax][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 5)
	{
		this->mNbPoint += 20;
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymax] = 8;
		return 1;
	}
	else if (this->mTabMap[xmin][ymax] == 5)
	{
		this->mNbPoint += 20;
		this->mCouleurBalle = 1;
		this->mTabMap[xmin][ymax] = 8;
		return 1;
	}
	else
		return 0;
	
	



	
}

