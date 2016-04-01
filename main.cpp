#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "parallax.h"

#include <iostream>

using namespace std;

std::string toString(int number)
 {
     if (number == 0)
         return "0";


     if(number < 0)
         return "-"+toString(-number);


     std::string temp="";
     std::string returnvalue="";
     while (number>0)
     {
         temp+=number%10+48;
         number/=10;
     }
     for (int i=0;i<(int)temp.length();i++)
         returnvalue+=temp[temp.length()-i-1];
     return returnvalue;
 }

 bool colision(sf::Sprite rect1,sf::Sprite rect2){
     if(rect1.getPosition().x>rect2.getPosition().x+200){
        //evaluar izquierda
        return false;
     }
     if(rect1.getPosition().x+200<rect2.getPosition().x){
         //evaluar derecha
        return false;
     }
     if(rect1.getPosition().y<rect2.getPosition().y-200){
        //evaluar arriba
        return false;
     }
     if(rect1.getPosition().y-200>rect2.getPosition().y){
        //evaluar abajo
        return false;
     }
    return true;
 }


    sf::RenderWindow window;
 	sf::Texture texture_back;
 	sf::Sprite background, background3;
 	sf::Music music;
 	sf::Font myFont;
 	sf::Mouse mouse;
 	string cadena,cadena1;

    void inputsDelMouse(){
        sf::RenderWindow window2;
        sf::Texture texture, mouse_texture;
        sf::Sprite background, mouse_background;

        window2.create(sf::VideoMode(840,620,32),"Inputs del Mouse", sf::Style::Close);
        window2.setVerticalSyncEnabled(true);


        if (!myFont.loadFromFile("arial.ttf")){

        }
        sf::Text pos_text_x,pos_text_y;
        pos_text_x.setFont(myFont);
        pos_text_y.setFont(myFont);

        pos_text_x.setCharacterSize(72);
        pos_text_y.setCharacterSize(72);

        pos_text_x.setColor(sf::Color::White);
        pos_text_y.setColor(sf::Color::White);

        pos_text_x.setPosition(20,0);
        pos_text_y.setPosition(690,0);

        texture.loadFromFile("inputs.png");
        background.setTexture(texture);
         mouse_texture.loadFromFile("mouse.png");
         mouse_background.setTexture(mouse_texture);

        mouse_background.setPosition(250,200);

        int eje_x = 0,eje_y = 0;
        while(window2.isOpen()){
            sf::Event event;
            while(window2.pollEvent(event)){
                if(event.type==sf::Event::Closed){
                    window2.close();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    window2.close();
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    cout<<"Haciendo Clic Izquierdo.."<<endl;
                    mouse_texture.loadFromFile("mouse1.png");
                    mouse_background.setTexture(mouse_texture);
                }else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                    cout<<"Haciendo Clic Derecho.."<<endl;
                    mouse_texture.loadFromFile("mouse2.png");
                    mouse_background.setTexture(mouse_texture);
                }else if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
                    cout<<"Pulsando Scroll.."<<endl;
                    mouse_texture.loadFromFile("mouse3.png");
                    mouse_background.setTexture(mouse_texture);
                }else{
                    mouse_texture.loadFromFile("mouse.png");
                    mouse_background.setTexture(mouse_texture);
                }
            }

            eje_x = mouse.getPosition().x;
            cadena = toString(eje_x);
            pos_text_x.setString(cadena);

            eje_y = mouse.getPosition().y;
            cadena1 = toString(eje_y);
            pos_text_y.setString(cadena1);

            window2.draw(background);
            window2.draw(mouse_background);
            window2.draw(pos_text_x);
            window2.draw(pos_text_y);
            window2.display();
        }
    }

    void parallax(){
        sf::RenderWindow window2;
        sf::Texture texture, texture1, arbol;
        sf::Sprite background, background2, background_arbol;

        sf::CircleShape circulo(30);
        circulo.setFillColor(sf::Color::Yellow);
        circulo.setPosition(30,30);

        sf::CircleShape circulo2(30);
        circulo2.setFillColor(sf::Color::Blue);
        circulo2.setPosition(720,500);

        int frames=0;

        window2.create(sf::VideoMode(840,620,32),"Parallax", sf::Style::Close);
        window2.setVerticalSyncEnabled(true);


        texture.loadFromFile("cielo.png");
        background.setTexture(texture);

        texture1.loadFromFile("montana1.png");
        background2.setPosition(0,90);
        background2.setTexture(texture1);
        background3.setPosition(0,90);
        background3.setTexture(texture1);

        bool flag = false;
        int pos_x_yellow = circulo.getPosition().x;
        int pos_x_blue = circulo2.getPosition().x;

        while(window2.isOpen()){
            sf::Event event;
            while(window2.pollEvent(event)){
                if(event.type==sf::Event::Closed){
                    window2.close();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    window2.close();
                }
            }

            if(!flag){
                circulo.setPosition(pos_x_yellow++,30);
                circulo2.setPosition(pos_x_blue--,500);
                if(circulo.getPosition().x==500){
                    flag=true;
                }
            }else{
                circulo.setPosition(pos_x_yellow--,30);
                circulo2.setPosition(pos_x_blue++,500);
                if(circulo.getPosition().x==30){
                    flag=false;
                }
            }

            if(background2.getPosition().x>840)
                background2.setPosition(0,90);
            window2.draw(background);
            window2.draw(background2);
            background3.setPosition(background2.getPosition().x-840,90);
            window2.draw(background3);

            if(frames%2==0){
                background2.move(1,0);
            }
            window2.draw(circulo2);
            window2.draw(circulo);
            window2.display();
            frames++;
        }
    }

    void colisiones(){
        sf::RenderWindow window2;
        sf::Texture texture,avion_comercial,avion_guerra,colision_image;
        sf::Sprite background,b_avion_comercial,b_avion_guerra,b_colision_image;


        avion_guerra.loadFromFile("aviones/guerra/2.png");
        b_avion_guerra.setTexture(avion_guerra);
        b_avion_guerra.setPosition(30,300);

        avion_comercial.loadFromFile("aviones/comercial/4.png");
        b_avion_comercial.setTexture(avion_comercial);
        b_avion_comercial.setPosition(600,300);

        colision_image.loadFromFile("colision.png");
        b_colision_image.setTexture(colision_image);

        window2.create(sf::VideoMode(840,620,32),"Colisiones", sf::Style::Close);
        window2.setVerticalSyncEnabled(true);

        texture.loadFromFile("colisiones.png");
        background.setTexture(texture);

        int pos_y_rect1 =300,pos_x_rect1=600;
        int pos_y_rect =300,pos_x_rect=30;

        while(window2.isOpen()){
            sf::Event event;
            while(window2.pollEvent(event)){
                if(event.type==sf::Event::Closed){
                    window2.close();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    window2.close();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    avion_comercial.loadFromFile("aviones/comercial/1.png");
                    b_avion_comercial.setTexture(avion_comercial);
                    b_avion_comercial.setPosition(pos_x_rect1,pos_y_rect1-=2);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    avion_comercial.loadFromFile("aviones/comercial/3.png");
                    b_avion_comercial.setTexture(avion_comercial);
                    b_avion_comercial.setPosition(pos_x_rect1,pos_y_rect1+=2);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    avion_comercial.loadFromFile("aviones/comercial/2.png");
                    b_avion_comercial.setTexture(avion_comercial);
                    b_avion_comercial.setPosition(pos_x_rect1+=2,pos_y_rect1);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    avion_comercial.loadFromFile("aviones/comercial/4.png");
                    b_avion_comercial.setTexture(avion_comercial);
                    b_avion_comercial.setPosition(pos_x_rect1-=2,pos_y_rect1);
                }


                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    avion_guerra.loadFromFile("aviones/guerra/1.png");
                    b_avion_guerra.setTexture(avion_guerra);
                    b_avion_guerra.setPosition(pos_x_rect,pos_y_rect-=2);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    avion_guerra.loadFromFile("aviones/guerra/3.png");
                    b_avion_guerra.setTexture(avion_guerra);
                    b_avion_guerra.setPosition(pos_x_rect,pos_y_rect+=2);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    avion_guerra.loadFromFile("aviones/guerra/2.png");
                    b_avion_guerra.setTexture(avion_guerra);
                    b_avion_guerra.setPosition(pos_x_rect+=2,pos_y_rect);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    avion_guerra.loadFromFile("aviones/guerra/4.png");
                    b_avion_guerra.setTexture(avion_guerra);
                    b_avion_guerra.setPosition(pos_x_rect-=2,pos_y_rect);
                }
            }

            window2.draw(background);
            window2.draw(b_avion_comercial);
            window2.draw(b_avion_guerra);

            if(colision(b_avion_comercial,b_avion_guerra)){
                b_colision_image.setPosition(300,50);
                window2.draw(b_colision_image);
            }

            window2.display();
        }
    }

    void efectosDeSonido(){
        sf::RenderWindow window2;
        sf::Texture texture;
        sf::Sprite background;

        window2.create(sf::VideoMode(840,620,32),"Efectos de Sonido", sf::Style::Close);
        window2.setVerticalSyncEnabled(true);

        texture.loadFromFile("efectos.png");
        background.setTexture(texture);

        while(window2.isOpen()){
            sf::Event event;
            while(window2.pollEvent(event)){
                if(event.type==sf::Event::Closed){
                    window2.close();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    window2.close();
                }
            }
            window2.draw(background);
            window2.display();
        }
    }

    void menuPrincipal(){
        int opc =1;
        sf::RenderWindow window1;
        window1.create(sf::VideoMode(840,620,32),"Menu Principal", sf::Style::Close);
        window.setVerticalSyncEnabled(true);

        sf::Texture menu0, menu1, menu2, menu3;
        sf::Sprite background0, background1, background2, background3;

        menu0.loadFromFile("menu0.png");
        background0.setTexture(menu0);
        menu1.loadFromFile("menu1.png");
        background1.setTexture(menu1);
        menu2.loadFromFile("menu2.png");
        background2.setTexture(menu2);
        menu3.loadFromFile("menu3.png");
        background3.setTexture(menu3);

        while(window1.isOpen()){
            sf::Event event1;

            while(window1.pollEvent(event1)){
                if(event1.type==sf::Event::Closed){
                    window1.close();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    opc++;
                    if(opc>3)
                        opc = 3;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    opc--;
                    if(opc<1)
                        opc = 1;
                }

//--------------------------------------------------------------------
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    switch(opc){
                    case 1:
                        inputsDelMouse(); opc = 1;
                        break;
                    case 2:
                        parallax(); opc = 1;
                        break;
                    case 3:
                        colisiones(); opc = 1;
                        break;
                    }
                }
            }
            window1.draw(background0);
            if(opc==1)
                window1.draw(background1);
            if(opc==2)
                window1.draw(background2);
            if(opc==3)
                window1.draw(background3);
            window1.display();
        }
    }

//    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
//
//    sf::Texture textura;
//
//    if(textura.loadFromFile("paste.jpg")){
//        return EXIT_FAILURE;
//    }
//
//    sf::Sprite sprite;
//    sprite.setTexture(textura);
//
//    sprite.setPosition(0,0);
//    sprite.setTextureRect(sf::IntRect(0,0,200,200));
//
//    sprite.move(50, 100);
//
//    sf::Vector2f centro;
//
//    centro.x = sprite.getTextureRect().width/2.f;
//    centro.y = sprite.getTextureRect().height/2.f;
//
//    sprite.setOrigin(centro);
//
////    sprite.rotate(45);
////
////    sf::Sprite otro(textura);
////    otro.setPosition(200, 150);
////    otro.setTextureRect(sf::IntRect(128, 128, 64, 64));
//
//
//    sf::Music musica;
//
//    musica.openFromFile("grillo.ogg");
//
//    musica.setLoop(true);
//
//    musica.play();
//
//
//
//    if(sf::Mouse::getPosition().x==3)
//        musica.pause();
//    int frame =0;
//    while (window.isOpen())
//    {
//        if(frame % 2 == 0){
//            sprite.rotate(1);
////            shape.move(1,0);
////            shape1.move(0,1);
//        }
//
//
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//            {
//                cout<<"Haciendo clic en la pantalla...!"<<endl;
//            }
//
//            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
//                sf::RenderWindow window2(sf::VideoMode(300, 300), "SFML works!");
//                continue;
//            }
//
////            cout<<"Posicion en X: "<<sf::Mouse::getPosition().x<<endl;
////            cout<<"Posicion en Y: "<<sf::Mouse::getPosition().y<<endl;
//
//        }
//
////        sf::Mouse::setPosition(sf::Vector2i(40, 50), window);
//        frame++;
//        window.clear();
////        window.draw(shape);
//        window.draw(sprite);
////        window.draw(shape1);
//        window.display();
//    }
    int main()
    {
        menuPrincipal();
        return 0;
    }
