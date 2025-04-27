#include "ComplexPlane.h"

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
	uint8 r, g, b;

	if (m_state == State::CALCULATING)
	{
		for (int x = 0; x < BASE_WIDTH; x++)
		{
			for (int y = 0; y < BASE_HEIGHT; y++)
			{
				vArray[x + y * pixelWidth].position = { (float)x, (float)i };
				Vector2f newCoord = mapPixelToCoords(x, y);
				numIter = countIterations(newCoord);
				
				iterationsToRGB(numIter, r, g, b)
				vArray[j + i * pixelWidth].color = { r, g, b };
			}
			
		}
	}
	m_state = State::DISPLAYING;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float newX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float newY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size(newX, newY);
	m_state == State::CALCULATING;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount--;
	float newX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float newY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size(newX, newY);
	m_state == State::CALCULATING;
}

void ComplexPlane::setCenter(std::vector<Vector2i> mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state == State::CALCULATING;
}

void ComplexPlane::setMouseLocation(vector<Vector2i> mousePixel)
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

int ComplexPlane::countIterations(std::vector<Vector2f> coord)
{
	// Count the number of iterations of the set for the given coordinate as specified above
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{

}