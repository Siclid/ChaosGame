// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Load font and set up instructions
    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error loading font!" << endl;
        return -1;
    }

    Text instructions;
    instructions.setFont(font);
    instructions.setString(
        "Click 3 points to form a triangle.\n"
        "Click a 4th point to start the Chaos Game.\n"
        "Press ESC to exit.");
    instructions.setCharacterSize(24);
    instructions.setFillColor(Color::White);
    instructions.setPosition(10.f, 10.f);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (points.size() > 0)
        {
            for (int i = 0; i < 100; ++i)
            {
                int randomIndex = rand() % vertices.size();
                Vector2f lastPoint = points.back();
                Vector2f newPoint(
                    (lastPoint.x + vertices[randomIndex].x) / 2,
                    (lastPoint.y + vertices[randomIndex].y) / 2
                );
                points.push_back(newPoint);
            }
        }

        window.clear();

        // Draw instructions
        window.draw(instructions);

        // Draw vertices
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Draw fractal points
        for (const auto& point : points)
        {
            RectangleShape rect(Vector2f(2, 2));
            rect.setPosition(Vector2f(point.x, point.y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        window.display();
    }
}