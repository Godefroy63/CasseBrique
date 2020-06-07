#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Input.h"
#include <fstream>
#include <iomanip>
class Map
{

	public :

	//Constructeur
		Map(sf::RenderWindow& window);
		~Map();

	//Acesseur

	//Mutateur

	//Methode
	void chargerMap(std::string fichier);
	void drawMap(sf::RenderWindow& window);
	void drawPlateau(sf::RenderWindow& window);
	void depacement(sf::RenderWindow& window, Input input);
	int collision(float x, float y);

	private:

	//Sprite et texture pour les briques
	sf::Texture* mTabBriqueTexture;
	sf::Sprite* mTabBriqueSprite;
	sf::Vector2f mPostionBrique;

	//Sprite et texture pour les balles
	sf::Texture mTabBalleTexture;
	sf::Sprite mTabBalleSprite;
	sf::Vector2f mPostionBalles;

	//Sprite et texture pour le plateau
	sf::Texture mPlateauTexture;
	sf::Sprite mPlateauSprite;
	sf::Vector2f mPostionplateau;

	//Fichier config level
	std::string mLevel;
	int mHauteurTile, mLargeurTile, mNbtileX, mNbtileY, mNbTileMapX, mNbTileMapY;
	int mCouleurBalle,mHauteurBalle,mLargeurBalle;
	bool mBalleCole;
	sf::Vector2f mVitesse;

	//Tableau 2D contenant la map
	int** mTabMap;

	//Font
	sf::Font mfont;
	sf::Text mText;
	int mNbPoint;
	std::string mtexte;


	









};

#endif // !MAP_H

