#include "PCH.h"
#include "Keyboard.h"

G3D::Keyboard::Event G3D::Keyboard::ReadKey()
{
	if (keyBuffer.size() > 0u)
	{
		Keyboard::Event e = keyBuffer.front();
		keyBuffer.pop();
		return(e);
	}
	else
	{
		return(Keyboard::Event());
	}
}

u16 G3D::Keyboard::ReadChar()
{
	if (charBuffer.size() > 0u)
	{
		u16 charcode = charBuffer.front();
		charBuffer.pop();

		return(charcode);
	}
	else
	{
		return(0);
	}
}