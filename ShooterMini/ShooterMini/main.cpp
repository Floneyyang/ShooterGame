
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Game.hpp"

using namespace sf;

static const int screenWidth = 1600;
static const int screenHeight = 1200;

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Shooter Game By Floney");
    Game game(&window);
    
    game.Start(screenWidth,screenHeight);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        //Update
        game.Update();

        // Clear screen
        window.clear(Color(100, 149, 237));

        // Draw the sprite
        //window.draw();
        //Draw
        game.Draw();

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

