#include "parallax.h"

void cargarImagen(sf::Texture texture, sf::Sprite background, string name){
    texture.loadFromFile(name);
    background.setTexture(texture);
}
