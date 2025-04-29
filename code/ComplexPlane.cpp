#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) :
	m_pixel_size{ pixelWidth, pixelHeight },
	m_plane_center{ 0, 0 },
	m_plane_size{ BASE_WIDTH, BASE_HEIGHT * m_aspectRatio },
	m_zoomCount(0),
	m_state(State::CALCULATING)
{
	m_aspectRatio = float(pixelHeight) / float(pixelWidth);
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(size_t(pixelWidth) * size_t(pixelHeight));
}

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
				int newIndex = x + y * pixelWidth;
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
	std::stringstream ss;

	// Assume m_plane_center is center and m_mouseLocation is the cursor
	ss << "Mandelbrot Set\n";
	ss << "Center: " << m_plane_center.x << "," << m_plane_center.y << ")\n";
	ss << "Cursor: " << m_mouseLocation.x << "," << m_mouseLocation.y << ")\n";
	ss << "Left-click to Zoom in\n";
	ss << "Right-click to Zoom out\n";

	text.setString(ss.str());
}

int ComplexPlane::countIterations(Vector2f coord)
{
	// Count the number of iterations of the set for the given coordinate as specified above
	// Mandelbrot Set Equation: f(z) = z^2 + c

	complex<double> z = 0;
	complex<double> c = {coord.x, coord.y}; // complex = real + imaginary, ex: 2 + 3i

	int iterations = 0;

	while (abs(z) < 2.0 && iterations <= MAX_ITER) // max magnitude is 2.0
	{
		z = pow(z, 2) + c;
		iterations++;
	}

	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	// TODO: Rlly bad color palette, change later - 4/28 PC
	if (count == MAX_ITER)
	{
		r = g = b = 0;
	}
	else if (count > 0 && count <= MAX_ITER * 0.25)
	{
		r = g = b = 256 * 0.25;
	}
	else if (count > 16 && count <= MAX_ITER * 0.50)
	{
		r = g = b = 256 * 0.50;
	}
	else if (count > 32 && count <= MAX_ITER * 0.75)
	{
		r = g = b = 256 * 0.75;
	}
	else
	{
		r = 218;
		g = 247;
		b = 166;
	}

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	// ((n - a) / (b - a)) * (d - c) + c
	// n = mousePixel.x/y = mousePos_x & mousePos_y
	// a = m_plane_size.x/y = planeWidth & planeHeight
	// b = m_pixel_size.x/y = screenWidth & screenHeight
	// d - c = m_plane_size.x/y 
	// +c = (m_plane_center.x/y  - m_plane_size.x/y)
	// ((mousePixel.x - m_plane_size.x) / (m_pixel_size.x - m_plane_size.x)) * m_plane_size.x + (m_plane_center.x - m_plane.size.x / 2.0)
	
	int xMousePos = mousePixel.x;
	int yMousePos = mousePixel.y;

	float xPlaneWidth = m_plane_size.x;
	float yPlaneHeight = m_plane_size.y;

	float xPlaneCenter = m_plane_center.x;
	float yPlaneCenter = m_plane_center.y;

	float xScreenWidth = m_pixel_size.x;
	float yScreenHeight = m_pixel_size.y;


	float xCoord = ((xMousePos - xPlaneWidth) / (xScreenWidth - xPlaneWidth)) * xPlaneWidth + (xPlaneCenter - xPlaneWidth / 2.0);
	float yCoord = ((yMousePos - yPlaneHeight) / (yScreenHeight - yPlaneHeight)) * yPlaneHeight + (yPlaneCenter - yPlaneHeight / 2.0);;

	return Vector2f(xCoord, yCoord);
}
