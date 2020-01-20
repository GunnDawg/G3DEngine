#include "PCH.h"
#include "Mouse.h"

G3D::Mouse::Event G3D::Mouse::Read()
{
	if (buffer.size() > 0u)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else

	{
		return Mouse::Event();
	}
}

void G3D::Mouse::OnMouseMove(u16 newX, u16 newY)
{
	x = newX;
	y = newY;

	buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	TrimBuffer();
}