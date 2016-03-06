#ifndef CARGAR_HPP
#define CARGAR_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class cargar
{
    public:
        Cargar();
        void run();

    protected:

    private:
        sf::RenderWindow window;
        sf::Clock clock;
        sf::Time time;

        sf::Texture texture_back;
        sf::Sprite bckground;

        sf::Music music;
};

#endif // CARGAR_H
