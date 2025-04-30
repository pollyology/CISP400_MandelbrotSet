#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

int main()
{
	unsigned int width = VideoMode::getDesktopMode().width;
	unsigned int height = VideoMode::getDesktopMode().height;

	VideoMode vm(width / 2, height / 2);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	ComplexPlane plane(width, height);

	Color default = Color::Black;
	Text text;
	Font font;

	if (!font.loadFromFile("matryoshka.ttf"))
	{
		cout << "Unable to load font file \n";
	}

	text.setFont(font);
	text.setCharacterSize(25);
	text.setFillColor(default);
	text.setPosition(14, 14);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				plane.zoomOut();
				plane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				plane.zoomIn();
				plane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.type == Event::MouseMoved)
			{
				plane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.y));
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		
		// Update Scene

		plane.updateRender();
		plane.loadText(text);

		// Draw Scene

		window.clear();
		//plane.draw(window, RenderStates::Default);
		window.draw(plane);
		window.draw(text);
		window.display();

	}
}
