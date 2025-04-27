#ifndef COMPLEXPLANE_H
#define COMPLEXPlANE_H

#include <iostream>
#include <complex>
#include <vector>
#include <SFML/Graphics/VertexArray.hpp>

using namespace sf, std
using std::vector;

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
		m_pixel_size{pixelWidth, pixelHeight},
		m_plane_center{0, 0},
		m_plane_size{BASE_WIDTH, BASE_HEIGHT * m_aspectRatio},
		m_zoomCount(0),
		m_state(State::CALCULATING)
		{
			m_aspectRatio = (float)pixelHeight / (float)pixelWidth;
			m_vArray.setPrimitiveArray(Points);
			m_vArray.resize(pixelWidth * pixelHeight);
		};
		
		void draw(RenderTarget& target, RenderStates states) const;
		void zoomIn();
		void zoomOut();
		void setCenter(vector<Vector2i> mousePixel);
		void setMouseLocation(vector<Vector2i> mousePixel);
		void loadText(Text& text);
		void updateRender();

	private:
		sf::VertexArray m_vArray;
		State m_state;
		std::vector<Vector2f> m_mouseLocation;
		std::vector<Vector2i> m_pixel_size;
		std::vector<Vector2f> m_plane_center;
		std::vector<Vector2f> m_plane_size;
		int m_zoomCount;
		float m_aspectRatio;

		int countIterations(std::vector<Vector2f> coord);
		void iterationsToRGB(size_t count, uint8& r, uint8& g, uint8& b);
		std::vector<Vector2f> mapPixelToCoords(std::vector<Vector2i> mousePixel);

};

#endif
