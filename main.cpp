#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath>


class Player{
    public:
        sf::CircleShape sprite;
        Player(float radius = 50.f) : sprite(radius){
            sprite.setOrigin(sf::Vector2f({0.f, 0.f }));
            sprite.setFillColor(sf::Color::Green);
        }
};


void gameLoop(Player &character, sf::RenderWindow &window){
    // States...
    bool is_in_game = true;
    bool is_in_pause = false;
    bool is_finished = false;

    while(is_in_game && window.isOpen()){

        while (const std::optional event = window.pollEvent() )
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(character.sprite);
        window.display();
        // Listen for input.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            character.sprite.move(sf::Vector2f({-1.f,0.f}));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            character.sprite.move(sf::Vector2f({1.f,0.f}));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            character.sprite.move(sf::Vector2f({0.f,-1.f}));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            character.sprite.move(sf::Vector2f({0.f,1.f}));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            character.sprite.move(sf::Vector2f({(-1.f/sqrt(2.f)),(1.f/sqrt(2.f))}));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            character.sprite.move(sf::Vector2f({(1.f/sqrt(2.f)),(1.f/sqrt(2.f))}));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            character.sprite.move(sf::Vector2f({(-1.f/sqrt(2.f)),(-1.f/sqrt(2.f))}));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            character.sprite.move(sf::Vector2f({(1.f/sqrt(2.f)),(-1.f/sqrt(2.f))}));
        }
    }
}
int main(){
    sf::RenderWindow window(sf::VideoMode({960,720}),"Hello World");

    Player player;

    gameLoop(player, window);

    return 0;
}