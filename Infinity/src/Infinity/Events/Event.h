#pragma once

#include "Infinity\Core.h"

namespace Infinity
{
	// Events in Infinity are currently blocking, which basically means when an event occurs,
	// it immediately gets dispatched and must be dealt with right there and then.
	// Alternatively (Likely in the future), we will buffer the events in an event bus and
	// process them during the "Event" part of our update.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// FLAGS EFFECTIVELY
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	// Saves typing this out in every event type as the usually have very repetitive steps, with tint variants.
	// Therefore, having this template means I can auto-setup a GetStaticType method with ##type for the type.
	// And I can then return the string version of whats passed in with #type.
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }

	// This is similar to above but for the flags, very repetitive with slight variants so a macro is fitting.
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
				
	/// <summary>
	/// This is the base class for Events
	/// </summary>
	class INFINITY_API Event 
	{
		friend class EventDispacher;
	public:
		// Must have methods
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName()    const = 0;
		virtual int GetCategoryFlags()   const = 0;

		// Optional override if you want to tack on additional data from the event in ToString
		virtual std::string ToString()   const { return GetName(); }

		// Simply returns if it appears atleast once in a category
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	public:
		bool Handled = false;
	};

	// Handles dispatching events at a very high level.
	// Allows us to pass through just an Event on more specific events such as, KeyEvent for example.
	class EventDispacher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispacher(Event& event)
			: m_Event(event)
		{ }

		template<typename T> 
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}