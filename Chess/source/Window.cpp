#include "Window.h"
#include "interface/IWindow.h"
#include "interface/IRectangleShape.h"
#include "interface/IEvent.h"

bool Window::PollEvent(IEvent& event)
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

void Window::Draw(const IRectangleShape& drawable)
{
    m_window.draw(drawable);
}

bool Window::IsOpen() const
{
    return m_window.isOpen();
}

const sf::RenderWindow* Window::GetSfmlWindow() const
{
    return &m_window;
}

void Window::Create(Resolution res, const std::string& title)
{
    m_window.create(sf::VideoMode(res.width, res.height), title);
}
