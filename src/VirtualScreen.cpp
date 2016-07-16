#include "VirtualScreen.h"

namespace sn
{
    void VirtualScreen::create(uint w, uint h, uint pixel_size, sf::Color default_color)
    {
        m_vertices.resize(w * h * 6);
        m_screenSize = {w, h};
        m_vertices.setPrimitiveType(sf::Triangles);
        m_pixelSize = pixel_size;
        for (std::size_t x = 0; x < w; ++x)
        {
            for (std::size_t y = 0; y < h; ++y)
            {
                setPixel(x, y, default_color);
            }
        }
    }

    void VirtualScreen::setPixel(std::size_t x, std::size_t y, sf::Color color)
    {
        auto index = (x * m_screenSize.y + y) * 6;
        auto pixel_size_f = static_cast<float>(m_pixelSize); //rid us of casting in each line we use it
        sf::Vector2f coord2d (x * pixel_size_f, y * pixel_size_f);

        //Triangle-1
        //top-left
        m_vertices[index].position = coord2d;
        m_vertices[index].color    = color;

        //top-right
        m_vertices[index + 1].position = coord2d + sf::Vector2f{pixel_size_f, 0};
        m_vertices[index + 1].color = color;

        //bottom-right
        m_vertices[index + 2].position = coord2d + sf::Vector2f{pixel_size_f, pixel_size_f};
        m_vertices[index + 2].color = color;

        //Triangle-2
        //bottom-right
        m_vertices[index + 3].position = coord2d + sf::Vector2f{pixel_size_f, pixel_size_f};
        m_vertices[index + 3].color = color;

        //bottom-left
        m_vertices[index + 4].position = coord2d + sf::Vector2f{0, pixel_size_f};
        m_vertices[index + 4].color = color;

        //top-left
        m_vertices[index + 5].position = coord2d;
        m_vertices[index + 5].color    = color;
    }

    void VirtualScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_vertices, states);
    }


}