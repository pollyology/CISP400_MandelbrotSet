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
	unsigned int width = 800;
	unsigned int height = 800;

	VideoMode vm(width, height);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	ComplexPlane plane(width, height);
	const int NUM_THREADS = 10;

	Color textColor = Color::Black;
	Text text;
	Font font;

	if (!font.loadFromFile("assets/font/matryoshka.ttf"))
	{
		cout << "Unable to load font file \n";
	}

	text.setFont(font);
	text.setCharacterSize(25);
	text.setFillColor(Color(31, 181, 122, 128));
	text.setOutlineColor(textColor);
	text.setOutlineThickness(0.5);
	text.setPosition(14, 14);

	window.setMouseCursorVisible(false);
	Texture cursorTexture;
	Texture zoomInTexture;
	Texture zoomOutTexture;

	cursorTexture.loadFromFile("assets/sprites/Zoom.png");
	zoomInTexture.loadFromFile("assets/sprites/Zoom_In.png");
	zoomOutTexture.loadFromFile("assets/sprites/Zoom_Out.png");

	Sprite cursor(cursorTexture);
	cursor.setScale(1.0f, 1.0f);

	Music music;
	if (!music.openFromFile("assets/music/Aquatic_Ambiance.flac"))
	{
		cout << "Unable to locate music file \n";
	}

	music.setLoop(true);
	music.setVolume(40);
	music.play();
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			Vector2i relativePos(Mouse::getPosition(window));												// Gets mouse position relative to window size
			Vector2i const currentMousePos = static_cast<Vector2i>(window.mapPixelToCoords(relativePos)); // Adjusts mouse position to work with window resize
			
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

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				plane.resetZoom();
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::E)
			{
				plane.toggleZoom();
			}

		}

		Vector2i cursorPos = Mouse::getPosition(window);
		cursor.setPosition(Vector2f(cursorPos));

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		
		// Autozoom Function
		plane.zoomInAuto();

		// Update Scene
		plane.updateRender(NUM_THREADS);
		plane.loadText(text);

		// Draw Scene
		window.clear();
		window.draw(plane);
		window.draw(text);
		window.draw(cursor);
		window.display();

	}
}
