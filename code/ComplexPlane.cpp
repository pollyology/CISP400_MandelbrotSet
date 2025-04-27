#include "ComplexPlane.h"

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
	Uint8 r, g, b;
	int pixelWidth = m_pixel_size.x;
	int pixelHeight = m_pixel_size.y;

	if (m_state == State::CALCULATING)
	{
		for (int x = 0; x < pixelWidth; x++)
		{
			for (int y = 0; y < pixelHeight; y++)
			{
				size_t newIndex = size_t(x + y * pixelWidth);
				m_vArray[newIndex].position = { (float)x, (float)y };
				Vector2f newCoord = mapPixelToCoords(Vector2i(x, y));
				int numIter = countIterations(newCoord);
				
				iterationsToRGB(numIter, r, g, b);
				m_vArray[newIndex].color = { r, g, b };
			}
			
		}
	}
	m_state = State::DISPLAYING;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float newX = float(BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount));
	float newY = float(BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(newX, newY);
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float newX = float(BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount));
	float newY = float(BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(newX, newY);
	m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
	// Use stringstream and member variables to output:
		// Mandelbrot Set
		// Center: (0,0)
		// Cursor: (-1.05313, 0.828125)
		// Left-click to Zoom in
		// Right-click to Zoom out
			// Center updates after click
			// Cursor updates live
}

int ComplexPlane::countIterations(Vector2f coord)
{
	// Count the number of iterations of the set for the given coordinate as specified above
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{

}