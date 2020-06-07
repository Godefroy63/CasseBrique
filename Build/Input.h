#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>


class Input
{
	//Attribus
	struct Button { bool Click_left, Click_right, up, down, left, right,jump, attack, enter,num1,num2,num3,num4; };
	

	public:

	//Constructeur
	Input();

	//Acesseur
	Button getButton() const;
	sf::Vector2i getPosSouris() const;
	void setButton(int Button, bool etat);

	//Methode

	void gestionInputs(sf::RenderWindow& window);
	void getInput(sf::RenderWindow& window);
	

	private:
	
	sf::Event event;
	Button button;
	sf::Vector2i PosSouris;

	const enum{ Click_left, Click_right, up, down, left, right, jump, attack, enter, num1, num2, num3, num4};

};

#endif // !INPUT_H

