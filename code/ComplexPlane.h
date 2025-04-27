#ifndef COMPLEXPLANE_H
#define COMPLEXPlANE_H

#include <iostream>
#include <complex>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace sf; 
using namespace std;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State
{
	CALCULATING,
	DISPLAYING,
};

class ComplexPlane
{
	public:
		ComplexPlane(int pixelWidth, int pixelHeight) :
		m_pixel_size{ pixelWidth, pixelHeight },
		m_plane_center{0, 0},
		m_plane_size{BASE_WIDTH, BASE_HEIGHT * m_aspectRatio},
		m_zoomCount(0),
		m_state(State::CALCULATING)
		{
			m_aspectRatio = float(pixelHeight / pixelWidth);
			m_vArray.setPrimitiveType(Points);
			m_vArray.resize(size_t(pixelWidth * pixelHeight));
		};
		
		void draw(RenderTarget& target, RenderStates states) const;
		void zoomIn();
		void zoomOut();
		void setCenter(Vector2i mousePixel);
		void setMouseLocation(Vector2i mousePixel);
		void loadText(Text& text);
		void updateRender();

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

		// Methods
		int countIterations(Vector2f coord);
		void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
		Vector2f mapPixelToCoords(Vector2i mousePixel);

};

#endif
