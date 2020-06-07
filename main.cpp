#include "main.h"


int main()
{
    //création de la fenerte
    sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "lender");
    
    //Limite les fps à 60 images / seconde
    window.setFramerateLimit(60);
    //On active la synchro verticale
    window.setVerticalSyncEnabled(true);

    //instance 
    Input input;
    Map map(window);

    //Chargement de la map 
    map.chargerMap("Level/niveau1.txt");

    //Game loop
    while (window.isOpen())
    {
        //Gestion des input
        input.getInput(window);
        map.depacement(window,input);
        
        window.clear(sf::Color(0, 0, 0));

        //Draw de la map
        map.drawMap(window);
        map.drawPlateau(window);

      
        
        window.display();
    }

    return 0;
}



