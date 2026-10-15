#include <SFML/Graphics.hpp>
#include <iostream>


bool checkCollision(float ballX, float ballY, float padY) {
    const float ballRadius = 7.5f;
    const float padX = 50.0f;
    const float padWidth = 15.0f;
    const float padHeight = 120.0f;
    float padLeft = padX - padWidth / 2.0f;
    float padRight = padX + padWidth / 2.0f;
    float padTop = padY - padHeight / 2.0f;
    float padBottom = padY + padHeight / 2.0f;
    float closestX = (ballX < padLeft) ? padLeft :
                     (ballX > padRight) ? padRight : ballX;
    float closestY = (ballY < padTop) ? padTop :
                     (ballY > padBottom) ? padBottom : ballY;
    float dx = ballX - closestX;
    float dy = ballY - closestY;
    return dx * dx + dy * dy <= ballRadius * ballRadius;
}

int main() {
    sf::ContextSettings settings;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    unsigned int width = 1000;
    unsigned int height = 500;
    float ballSpeedX = 0.7;
    float ballSpeedY = 0.5;
    float ballX = 500.0;
    float ballY = 250.0;
    float padSpeed = 0.4;
    float padY = 250.0;
    int score = 0;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({width, height}), "Pong", sf::State::Windowed, settings);
    sf::CircleShape ball(7.5f);
    sf::RectangleShape pad({15.0f, 120.0f});
    pad.setOrigin(pad.getSize() / 2.0f);
    pad.setPosition({50, 250});
    ball.setOrigin(ball.getGeometricCenter());
    ball.setPosition({500, 250});
    while(window->isOpen()){
        while(const std::optional event = window->pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window->close();
            };
        };
        if(ballY >= 485.0 || ballY <= 15.0){
            ballSpeedY *= -1.0;
        };
        if(ballX >= 985.0) {
            ballSpeedX *= -1.0;
        };
        if(padY > 440.0) {
            padY = 440.0;
        };
        if(padY < 60.0) {
            padY = 60.0;
        };
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)){
            padY -= 0.4;
        };
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)){
            padY += 0.4;
        };
        if(checkCollision(ballX, ballY, padY)){
            ballSpeedX *= -1.0;
            score += 1;
        };
        if(ballX <= 0){
            window->close();
            std::cout << "You lost!" << '\n';
            std::cout << "Your score was " << score;
        };
        ballX += ballSpeedX;
        ballY += ballSpeedY;
        ball.setPosition({ballX, ballY});
        pad.setPosition({50, padY});
        window->clear();
        window->draw(ball);
        window->draw(pad);
        window->display();
    };
    delete window;
    return 0;
};
