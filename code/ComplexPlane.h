#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <iostream>
#include <complex>
#include <thread>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const unsigned int MAX_ITER = 100;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State
{
	CALCULATING,
	DISPLAYING,
};

class ComplexPlane : public Drawable
{
public:
	ComplexPlane(int pixelWidth, int pixelHeight);
	void draw(RenderTarget& target, RenderStates states) const;
	void updateRender(int threads);
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2i mousePixel);
	void setMouseLocation(Vector2i mousePixel);
	void loadText(Text& text);
	
	// Added Functions
	void zoomInAuto();
	void toggleZoom() { m_autoZoom = !m_autoZoom; }
	void renderFractal(int startRow, int endRow);

private:
	// Objects
	VertexArray m_vArray;
	State m_state;

	// Floats
	Vector2f m_mouseLocation;
	Vector2f m_plane_center;
	Vector2f m_plane_size;
	float m_aspectRatio;

	// Ints
	Vector2i m_pixel_size;
	int m_zoomCount;

	// Bool
	bool m_autoZoom;

	// Methods
	int countIterations(Vector2f coord);
	void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
	Vector2f mapPixelToCoords(Vector2i mousePixel);

};

#endif
