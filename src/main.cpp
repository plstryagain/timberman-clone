#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

inline static constexpr uint32_t SCREEN_WIDTH = 1920;
inline static constexpr uint32_t SCREEN_HEIGHT = 1080;
#ifdef __APPLE__
inline static constexpr uint32_t DPI_SCALE = 2;
#else
inline static constexpr uint32_t DPI_SCALE = 1;
#endif

struct Cloud
{
    sf::Sprite sprite;
    uint32_t x;
    uint32_t y;
    bool is_active;
    float speed;
    uint32_t seed;
};

int main()
{
    sf::VideoMode vm(SCREEN_WIDTH * DPI_SCALE, SCREEN_HEIGHT * DPI_SCALE);
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
    std::vector<Cloud> clouds = {
        { {}, 0, 0, false, 0.0f, 1 },
        { {}, 0, 250, false, 0.0f, 2 },
        { {}, 0, 500, false, 0.0f, 3 },
    };
    size_t cloud_num = clouds.size();
    for (int i = 0; i < cloud_num; ++i) {
        clouds[i].sprite.setTexture(texture_cloud);
        clouds[i].sprite.setPosition(clouds[i].x, clouds[i].y);
    }

    sf::Clock clock{};
    bool is_paused = true;

    while (window.isOpen()) {
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        //     window.close();
        // }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    is_paused = false;
                    std::cout << "enter" << std::endl;
                }
            }
        }
        // update
        if (!is_paused) {
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
            for (auto& cloud : clouds) {
                if (!cloud.is_active) {
                    srand(static_cast<int>(time(0)) * 10 * cloud.seed);
                    cloud.speed = (rand() % 200);
                    // std::cout << "speed: " << cloud.speed << std::endl;
                    srand(static_cast<int>(time(0)) * 10 * cloud.seed);
                    float cloud_height = (rand() % 150 * cloud.seed);
                    if (cloud_height > 150) {
                        cloud_height -= 150;
                    }
                    // std::cout << "height: " << cloud_height << std::endl;
                    cloud.sprite.setPosition(-200, cloud_height);
                    cloud.is_active = true;
                } else {
                    cloud.sprite.setPosition(cloud.sprite.getPosition().x + (cloud.speed * dt.asSeconds()),
                                                cloud.sprite.getPosition().y);
                    if (cloud.sprite.getPosition().x > SCREEN_WIDTH) {
                        cloud.is_active = false;
                    }
                }
            }
        }

        // render
        window.clear();
        window.draw(sprite_background);
        for (auto& cloud : clouds) {
            // std::cout << cloud.x << ", " << cloud.y << ", " << cloud.speed << std::endl;
            window.draw(cloud.sprite);
        }
        window.draw(sprite_tree);

        window.draw(sprite_bee);
        window.display();
    }
    return 0;
}