#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = float(pixelHeight) / float(pixelWidth);

	m_plane_center = { 0, 0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;

	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
	int pixelWidth = m_pixel_size.x;
	int pixelHeight = m_pixel_size.y;

	if (m_state == State::CALCULATING)
	{
		for (int j = 0; j < pixelWidth; j++)
		{
			for (int i = 0; i < pixelHeight; i++)
			{
				m_vArray[j + i * pixelWidth].position = { (float)j, (float)i };
				Vector2f newCoord = mapPixelToCoords(Vector2i(j, i));
				int numIter = countIterations(newCoord);

				Uint8 r, g, b;
				iterationsToRGB(numIter, r, g, b);
				m_vArray[j + i * pixelWidth].color = { r, g, b };
			}

		}
		m_state = State::DISPLAYING;
	}
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
	ss << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")\n";
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")\n";
	ss << "Left-click to Zoom in\n";
	ss << "Right-click to Zoom out\n";

	text.setString(ss.str());
}

int ComplexPlane::countIterations(Vector2f coord)
{
	// Count the number of iterations of the set for the given coordinate as specified above
	// Mandelbrot Set Equation: f(z) = z^2 + c

	complex<float> c = { coord.x, coord.y }; // complex = real + imaginary, ex: 2 + 3i
	complex<float> z = c;

	size_t iterations = 0;

	while (abs(z) < 2.0 && iterations < MAX_ITER) // max magnitude is 2.0
	{
		z = z * z + c;
		iterations++;
	}

	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	// TODO: Rlly bad color palette, change later - 4/28 PC
	if (count >= MAX_ITER)
	{
		r = g = b = 0;
	}
	else
	{
		// Simple RGB gradient: fades from blue to white
		Uint8 brightness = static_cast<Uint8>(255 * count / MAX_ITER);

		r = brightness;
		g = brightness;
		b = 255; // Full blue base
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

	float xCoord = (float(mousePixel.x - 0) / (m_pixel_size.x - 0)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0);
	float yCoord = (float(mousePixel.y - m_pixel_size.y) / (0 - m_pixel_size.y)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0);

	return Vector2f(xCoord, yCoord);
}
