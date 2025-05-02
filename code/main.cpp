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

	VideoMode vm(width, height);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	ComplexPlane plane(width, height);

	Color default = Color::White;
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

	window.setMouseCursorVisible(false);
	Texture cursorTexture;
	Texture zoomInTexture;
	Texture zoomOutTexture;

	cursorTexture.loadFromFile("Zoom.png");
	zoomInTexture.loadFromFile("Zoom_In.png");
	zoomOutTexture.loadFromFile("Zoom_Out.png");

	Sprite cursor(cursorTexture);
	cursor.setScale(2.0f, 2.0f);
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			Vector2i currentMousePos(event.mouseButton.x, event.mouseButton.y);
			
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				plane.zoomIn();
				plane.setCenter(currentMousePos);

				cursor.setTexture(zoomInTexture);
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				plane.zoomOut();
				plane.setCenter(currentMousePos);

				cursor.setTexture(zoomOutTexture);
			}

			if (event.type == Event::MouseMoved)
			{
				plane.setMouseLocation(currentMousePos);
			}
		}

		Vector2i cursorPos = Mouse::getPosition(window);
		cursor.setPosition(Vector2f(cursorPos));

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
		window.draw(cursor);
		window.display();

	}
}
