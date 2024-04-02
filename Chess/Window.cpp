#include "Window.h"

bool Window::PollEvent(sf::Event& event)
{
    return m_window.pollEvent(event);
}

void Window::Close()
{
    m_window.close();
}

void Window::Clear()
{
    m_window.clear();
}

void Window::Display()
{
    m_window.display();
}

void Window::Draw(const sf::Drawable& drawable)
{
    m_window.draw(drawable);
}

bool Window::IsOpen() const
{
    return m_window.isOpen();
}

void Window::Create(sf::VideoMode mode, const std::string& title, sf::Uint32 style)
{
    m_window.create(mode, title, style);
}
