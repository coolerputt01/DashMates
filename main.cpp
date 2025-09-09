#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath>

using namespace std;

const float GRAVITY = 800.f;
const float MOVE_SPEED = 300.f; 
const float JUMP_STRENGTH = -350.f;

class Player{
    public:
        sf::RectangleShape sprite;
        sf::Vector2f velocity;
        bool onGround = false;
        Player(sf::Vector2f width_height = sf::Vector2f({50.f, 50.f})) : sprite(width_height){
            sprite.setOrigin(sf::Vector2f({0.f, 0.f}));
            sprite.setFillColor(sf::Color::Green);
        }
};


void gameLoop(Player &character, sf::RenderWindow &window){
    // States...
    bool is_in_game = true;
    bool is_in_pause = false;
    bool is_finished = false;

    sf::Clock clock;

    sf::Font font("assets/fonts/ByteBounce.ttf");
    sf::Text text(font);
    text.setPosition(sf::Vector2f({
        360.f,0.f
    }));
    text.setString("Dash-Mates");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);

    while(is_in_game && window.isOpen()){
        while (const std::optional event = window.pollEvent() )
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        float delta = clock.restart().asSeconds();

        window.clear(sf::Color::Black);
        window.draw(character.sprite);
        window.draw(text);
        window.display();
        // Listen for input.

        sf::Vector2f direction = sf::Vector2f({0.f,0.f});

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            direction.x -= 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            direction.x += 1.f;
        }
        

        character.velocity.x = direction.x * MOVE_SPEED;

        if(!character.onGround){
            character.velocity.y += GRAVITY * delta;
        }

        float groundY = 600.f - character.sprite.getSize().y; 
        if(character.sprite.getPosition().y >= groundY){
            character.sprite.setPosition({character.sprite.getPosition().x, groundY});
            character.velocity.y = 0.f;
            character.onGround = true;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && character.onGround){
                character.velocity.y = JUMP_STRENGTH;
                character.onGround = false;
            }
        }
        character.sprite.move(character.velocity * delta);
    }
}
int main(){
    sf::RenderWindow window(sf::VideoMode({960,720}),"Hello World");

    Player player;

    gameLoop(player, window);

    return 0;
}