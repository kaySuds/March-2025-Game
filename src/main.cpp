#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    // Bouncy Ball!
    float ballRadius{ 50.f };
    sf::Vector2f ballVelocity{ 10.f, 10.f };
    sf::CircleShape ball{ ballRadius };
    ball.setFillColor(sf::Color{255, 0, 0});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        // Bouncy ball!
        sf::Vector2f ballPosition = ball.getPosition();
        if ((ballPosition.x > window.getSize().x - ballRadius * 2) || ballPosition.x < 0.f) {
            ballVelocity.x *= -1.f;
        }
        if ((ballPosition.y > window.getSize().y - ballRadius * 2) || ballPosition.y < 0.f) {
            ballVelocity.y *= -1.f;
        }
        ball.setPosition({ ballPosition.x + ballVelocity.x, ballPosition.y + ballVelocity.y });

        window.draw(ball);
        window.display();
    }
}
