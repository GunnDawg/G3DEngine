#pragma once
#include <queue>
#include <bitset>

namespace G3D
{
	class Keyboard
	{
	public:
		class Event
		{
		public:
			enum class Type
			{
				Press,
				Release,
				Invalid
			};

		private:
			Type type;
			u16 code;

		public:
			Event() noexcept :
				type(Type::Invalid),
				code(0u)
			{}

			Event(Type type, u16 code) :
				type(type),
				code(code)
			{}

			inline bool IsPress() const { return type == Type::Press; }
			inline bool IsRelease() const { return type == Type::Release; }
			inline bool IsValid() const { return type != Type::Invalid; }
			inline u16 GetCode() const { return code; }
		};

	public:
		Keyboard() = default;
		Keyboard(const Keyboard& kb) = delete;
		Keyboard& operator= (const Keyboard& kb) = delete;

		//Key event stuff
		Event ReadKey();
		inline bool KeyIsPressed(u16 keycode) const { return(keyStates[keycode]); }
		inline bool KeyIsEmpty() const { return(keyBuffer.empty()); }
		inline void FlushKey() { keyBuffer = std::queue<Event>(); }

		//Char event stuff
		u16 ReadChar();
		inline bool CharIsEmpty() const { return(charBuffer.empty()); }
		inline void FlushChar() { charBuffer = std::queue<u16>(); }
		inline void Flush()
		{
			FlushKey();
			FlushChar();
		};

		//Autorepeat control
		inline void EnableAutorepeat() { autorepeatEnabled = true; }
		inline void DisableAutorepeat() { autorepeatEnabled = false; }
		inline bool AutorepeatIsEnabled() const { return autorepeatEnabled; }

		inline void OnKeyPressed(u16 keycode)
		{
			keyStates[keycode] = true;
			keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
			TrimBuffer(keyBuffer);
		}

		inline void OnKeyReleased(u16 keycode)
		{
			keyStates[keycode] = false;
			keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
			TrimBuffer(keyBuffer);
		}

		inline void OnChar(u16 character)
		{
			charBuffer.push(character);
			TrimBuffer(charBuffer);
		}

		inline void ClearState() { keyStates.reset(); }

		template<typename T>
		inline static void TrimBuffer(std::queue<T>& buffer)
		{
			while (buffer.size() > bufferSize)
			{
				buffer.pop();
			}
		}

	private:
		static constexpr u16 nKeys = 256u;
		static constexpr u16 bufferSize = 16u;
		bool autorepeatEnabled = false;
		std::bitset<nKeys> keyStates;
		std::queue<Event> keyBuffer;
		std::queue<u16> charBuffer;
	};
}