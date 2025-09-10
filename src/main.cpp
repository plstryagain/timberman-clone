#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

inline static constexpr uint32_t SCREEN_WIDTH = 1920;
inline static constexpr uint32_t SCREEN_HEIGHT = 1080;

int main()
{
    sf::VideoMode vm(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
    sf::RenderWindow window(vm, "Timber!", sf::Style::Default);
    window.setView(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))); 

    sf::Texture texture_background;
    texture_background.loadFromFile("assets/graphics/background.png");
    sf::Sprite sprite_background;
    sprite_background.setTexture(texture_background);
    sprite_background.setPosition(0,0);

    sf::Texture texture_tree;
    texture_tree.loadFromFile("assets/graphics/tree.png");
    sf::Sprite sprite_tree;
    sprite_tree.setTexture(texture_tree);
    sprite_tree.setPosition(810, 0);

    sf::Texture texture_bee;
    texture_bee.loadFromFile("assets/graphics/bee.png");
    sf::Sprite sprite_bee;
    sprite_bee.setTexture(texture_bee);
    sprite_bee.setPosition(0, 800);
    bool is_bee_active{false};
    float bee_speed{0.0f};

    sf::Texture texture_cloud;
    texture_cloud.loadFromFile("assets/graphics/cloud.png");
    sf::Sprite sprite_cloud1;
    sf::Sprite sprite_cloud2;
    sf::Sprite sprite_cloud3;
    sprite_cloud1.setTexture(texture_cloud);
    sprite_cloud2.setTexture(texture_cloud);
    sprite_cloud3.setTexture(texture_cloud);
    sprite_cloud1.setPosition(0, 0);
    sprite_cloud2.setPosition(0, 250);
    sprite_cloud3.setPosition(0, 500);

    bool is_cloud1_active{false};
    bool is_cloud2_active{false};
    bool is_cloud3_active{false};
    float cloud1_speed{0.0f};
    float cloud2_speed{0.0f};
    float cloud3_speed{0.0f};
    sf::Clock clock{};

    while (window.isOpen()) {
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        //     window.close();
        // }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // update
        sf::Time dt = clock.restart();
        if (!is_bee_active) {
            srand(static_cast<int>(time(0)));
            bee_speed = (rand() % 200) + 200;

            srand(static_cast<int>(time(0)) * 10);
            float bee_height = (rand() % 500) + 500;
            sprite_bee.setPosition(2000, bee_height);
            is_bee_active = true;
        } else {
            sprite_bee.setPosition(sprite_bee.getPosition().x - (bee_speed * dt.asSeconds()),
                                    sprite_bee.getPosition().y);
            if (sprite_bee.getPosition().x < -100) {
                is_bee_active = false;
            }
        }

        if (!is_cloud1_active) {
            srand(static_cast<int>(time(0)) * 10);
            cloud1_speed = (rand() % 200);
            srand(static_cast<int>(time(0)) * 10);
            float cloud1_height = (rand() % 150);
            sprite_cloud1.setPosition(-200, cloud1_height);
            is_cloud1_active = true;
        } else {
            sprite_cloud1.setPosition(sprite_cloud1.getPosition().x + (cloud1_speed * dt.asSeconds()),
                                        sprite_cloud1.getPosition().y);
            if (sprite_cloud1.getPosition().x > SCREEN_WIDTH) {
                is_cloud1_active = false;
            }
        }

        // render
        window.clear();
        window.draw(sprite_background);
        window.draw(sprite_cloud1);
        window.draw(sprite_cloud2);
        window.draw(sprite_cloud3);
        window.draw(sprite_tree);

        window.draw(sprite_bee);
        window.display();
    }
    return 0;
}