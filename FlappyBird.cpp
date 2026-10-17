#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>

int main(){
    srand(time(0));
    sf::ContextSettings settings;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    float birdY = 256;
    float birdYSpeed = 0.0;
    int randomHeight = rand() % 401;
    int ticks = 0;
    int score = 0;
    bool gameOver = false;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({288, 512}), "Flappy Bird", sf::State::Windowed, settings);
    sf::Clock clock;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Texture texture5;
    sf::Texture texture6;
    if (!texture1.loadFromFile("Sprites/background-day.png") || !texture2.loadFromFile("Sprites/yellowbird-midflap.png") || !texture3.loadFromFile("Sprites/base.png") || !texture4.loadFromFile("Sprites/gameover.png") || !texture5.loadFromFile("Sprites/pipe-green-up.png") || !texture6.loadFromFile("Sprites/pipe-green-down.png")) 
    {
        std::cerr << "ERROR: SPRITE DIDINT LOAD!" << std::endl;
        return -1;
    }
    float gravity = 0.1;
    sf::Sprite bg(texture1);
    sf::Sprite bird(texture2);
    sf::Sprite ground(texture3);
    sf::Sprite gameover(texture4);
    sf::Sprite pipeUp(texture5);
    sf::Sprite pipeDown(texture6);
    pipeUp.setPosition({370, (randomHeight + 100)});
    pipeDown.setPosition({370, (randomHeight + 100)});
    bird.setPosition({20, 256});
    ground.setPosition({0, 400});
    gameover.setPosition({48, 235});
    window->setFramerateLimit(60);
    while(window->isOpen()){
        while(const std::optional event = window->pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window->close();
            };
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)){
                birdYSpeed = -3;
            };
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::R) && gameOver){
                gameOver = false;
                birdY = 256;
                birdYSpeed = 0.0;
                randomHeight = rand() % 301;
                std::cout << "You lost!" << '\n';
                std::cout << "Your score was " << score << '\n' << '\n';
                score = 0;
            };
        };
        if (birdY >= 376){
            gameOver = true;
        };
        if(birdY <= 0){
            birdYSpeed = 0;
        };
        birdYSpeed += gravity;
        if(!gameOver){
            birdY += birdYSpeed;
        };
        bird.setPosition({20, birdY});
        if(!gameOver){
            pipeUp.setPosition({(370 - ticks), (randomHeight + 100)});
            pipeDown.setPosition({(370 - ticks), randomHeight - 350});
            ticks++;
        };
        if(ticks >= 430){
            ticks = 0;
            randomHeight = rand() % 301;
        };
        if(ticks == 380){
            score++;
        };
        sf::FloatRect box1 = bird.getGlobalBounds();
        sf::FloatRect box2 = pipeUp.getGlobalBounds();
        sf::FloatRect box3 = pipeDown.getGlobalBounds();
        if(box1.findIntersection(box2) || box1.findIntersection(box3)){
            gameOver = true;
        };
        window->clear();
        window->draw(bg);
        window->draw(bird);
        window->draw(pipeUp);
        window->draw(pipeDown);
        if(gameOver){
            window->draw(gameover);
            ticks = 0;
        };
        window->draw(ground);
        window->display();
    };
    return 0;
};
