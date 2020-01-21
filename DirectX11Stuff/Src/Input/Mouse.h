#pragma once

#include <queue>
#include <bitset>

namespace G3D

{
	class Mouse

	{
	public:
		class Event

		{
		public:
			enum class Type

			{
				LPress,
				LRelease,
				RPress,
				RRelease,
				WheelUp,
				WheelDown,
				Move,
				RAW_MOVE,
				Enter,
				Leave,
				Invalid

			};

		private:
			Type type;
			bool leftIsPressed = false;
			bool rightIsPressed = false;
			u16 x = 0u;
			u16 y = 0u;

		public:
			Event() :
				type(Type::Invalid),
				leftIsPressed(false),
				rightIsPressed(false),
				x(0u),
				y(0u)
			{}

			Event(Type type, const Mouse& parent) :
				type(type),
				leftIsPressed(parent.leftIsPressed),
				rightIsPressed(parent.rightIsPressed),
				x(parent.x),
				y(parent.y)
			{}

			inline bool IsValid() const { return type != Type::Invalid; }
			inline Type GetType() const { return type; }
			inline std::pair<u16, u16> GetPos() const { return{ x, y }; }
			inline u16 GetPosX() const { return x; }
			inline u16 GetPosY() const { return y; }
			inline bool LeftIsPresed() const { return leftIsPressed; }
			inline bool RightIsPressed() const { return rightIsPressed; }
		};

	public:
		Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse& operator=(const Mouse&) = delete;

		inline std::pair<u16, u16> GetPos() const { return { x, y }; }
		inline u16 GetPosY() const { return y; }
		inline u16 GetPosX() const { return x; }
		inline std::pair<u16, u16> GetDelta() const { return { dx, dy }; }
		inline u16 GetDeltaX() const { return dx; }
		inline u16 GetDeltaY() const { return dy; }
		inline bool IsInWindow() const { return isInWindow; }
		inline bool LeftIsPressed() const { return leftIsPressed; }
		inline bool RightIsPressed() const { return rightIsPressed; }
		Mouse::Event Read();
		inline bool IsEmpty() const { return buffer.empty(); }
		inline void Flush() { buffer = std::queue<Event>(); }

		void OnMouseMove(u16 newX, u16 newY);
		void OnMouseMoveRaw(u16 newX, u16 newY);
		inline void OnMouseLeave()
		{
			isInWindow = false;

			buffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
			TrimBuffer();
		}

		inline void OnMouseEnter()
		{
			isInWindow = true;

			buffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
			TrimBuffer();
		}

		inline void OnLeftPressed(u16 x, u16 y)
		{
			leftIsPressed = true;

			buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
			TrimBuffer();
		}

		inline void OnLeftReleased(u16 x, u16 y)
		{
			leftIsPressed = false;

			buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
			TrimBuffer();
		}

		inline void OnRightPressed(u16 x, u16 y)
		{
			rightIsPressed = true;

			buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
			TrimBuffer();
		}

		inline void OnRightReleased(u16 x, u16 y)
		{
			rightIsPressed = false;

			buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
			TrimBuffer();
		}

		inline void OnWheelUp(u16 x, u16 y)
		{
			buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
			TrimBuffer();
		}

		inline void OnWheelDown(u16 x, u16 y)
		{
			buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
			TrimBuffer();
		}

		inline void TrimBuffer()
		{
			while (buffer.size() > bufferSize)
			{
				buffer.pop();
			}
		}

	private:
		static constexpr u16 bufferSize = 16u;
		u16 x = 0u;
		u16 y = 0u;
		u16 dx = 0u;
		u16 dy = 0u;
		bool leftIsPressed = false;
		bool rightIsPressed = false;
		bool isInWindow = false;
		std::queue<Event> buffer;
	};
}