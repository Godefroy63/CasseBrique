#include "Input.h"

//--------------Constructeurs---------------------------------------

Input::Input()
{
	this->button.Click_left = this->button.Click_right = this->button.left = this->button.right = this->button.up = this->button.down = this->button.attack = this->button.enter = this->button.jump = false;
    this->button.num1 = this->button.num2 = this->button.num3 = this->button.num4 = false;
}  

//----------------Acceseurs------------------------------------------

Input::Button Input::getButton() const
{
	return this->button;
}

sf::Vector2i Input::getPosSouris() const
{
    sf::Vector2i PosSouris;

    PosSouris.x = this->event.mouseButton.x;
    PosSouris.y = this->event.mouseButton.y;
    

    return PosSouris;
}

void Input::setButton(int bouton, bool etat)
{
    switch (bouton)
    {
    case up:
        this->button.up = etat;
        break;

    case down:
        this->button.down = etat;
        break;

    case right:
        this->button.right = etat;
        break;

    case left:
        this->button.left = etat;
        break;

    case attack:
        this->button.attack = etat;
        break;

    case jump:
        this->button.jump = etat;
        break;

    case enter:
        this->button.enter = etat;
        break;
    }
}


//--------------Methodes--------------------------

void Input::gestionInputs(sf::RenderWindow& window)
{
 //Pour l'instant, on ne gère que le clavier.
//On gèrera les joysticks plus tard, s'il y en a
//un de branché.
//Pour l'instant, cette fonction n'est donc pas indispensable.
    getInput(window);
}

void Input::getInput(sf::RenderWindow& window)
{
    // Tant qu'il y a des évènements à traiter...
    while (window.pollEvent(event))
    {
        // on regarde le type de l'évènement...
        switch (event.type)
        {
            // On ferme la fenêtre
        case sf::Event::Closed:
            window.close();
            break;

            // Touche pressée
        case sf::Event::KeyPressed:
            switch (this->event.key.code) // La touche qui a été pressée
            {
            case sf::Keyboard::Escape: // Echap
                window.close();
                break;

            case sf::Keyboard::C:
                this->button.jump = true;
                break;

            case sf::Keyboard::V:
                this->button.attack = true;
                break;

            case sf::Keyboard::Left:
                this->button.left = true;
                break;

            case sf::Keyboard::Right:
                this->button.right = true;
                break;

            case sf::Keyboard::Down:
                this->button.down = true;
                break;

            case sf::Keyboard::Up:
                this->button.up = true;
                break;

            case sf::Keyboard::Return:
                this->button.enter = true;
                break;

            case sf::Keyboard::Numpad1:
                this->button.num1 = true;
                break;

            case sf::Keyboard::Numpad2:
                this->button.num2 = true;
               break;

            case sf::Keyboard::Numpad3:
                this->button.num3 = true;
                break;

            case sf::Keyboard::Numpad4:
                this->button.num4 = true;
                this->button.num1 = false;
                this->button.num2 = false;
                this->button.num3 = false;
               break;

            default:
                break;
            }
            break;

            // Touche relâchée
        case sf::Event::KeyReleased:
            switch (this->event.key.code)
            {
            case sf::Keyboard::C:
                this->button.left = false;
                break;

            case sf::Keyboard::Left:
                this->button.left = false;
                break;

            case sf::Keyboard::Right:
                this->button.right = false;
                break;

            case sf::Keyboard::Down:
                this->button.down = false;
                break;

            case sf::Keyboard::Up:
                this->button.up = false;
                break;


            case sf::Keyboard::Return:
                this->button.enter = false;
                break;


            case sf::Keyboard::Numpad4:
                this->button.num4 = false;
                break;

            default:
                break;
            }
            break;

        case sf::Event::MouseButtonPressed:
            switch (this->event.mouseButton.button)
            {
            case sf::Mouse::Left:
                this->button.Click_left = true;
                break;

            case sf::Mouse::Right:
                this->button.Click_right = true;
                break;

            default:
                break;
            }
        break;

        case sf::Event::MouseButtonReleased:
            switch (this->event.mouseButton.button)
            {
            case sf::Mouse::Left:
                this->button.Click_left = false;
                break;

            case sf::Mouse::Right:
                this->button.Click_right = false;
                break;

            default:
                break;
            }
            break;

         


            // on ne traite pas les autres types d'évènements
        default:
            break;
        }
    }
}