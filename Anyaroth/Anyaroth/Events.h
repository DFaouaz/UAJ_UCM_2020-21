#pragma once
#include <SDL2-2.0.9/include/SDL_events.h>

struct Mouse {
	int x, y;
	Mouse(int x, int y) : x(x), y(y) {}
};

struct InputEvent
{
	SDL_Event event;
	Mouse mouse;
	InputEvent(SDL_Event e, Mouse m) : event(e), mouse(m){}

	inline bool operator<(InputEvent const& a) const
	{
		return a.event.type < event.type && a.event.key.keysym.sym < event.key.keysym.sym;
	}
	inline bool operator<=(InputEvent const& a) const
	{
		return a.event.type < event.type && a.event.key.keysym.sym < event.key.keysym.sym;
	}

	inline bool operator>(InputEvent const& a) const
	{
		return a.event.type < event.type && a.event.key.keysym.sym < event.key.keysym.sym;
	}
	inline bool operator>=(InputEvent const& a) const
	{
		return a.event.type < event.type && a.event.key.keysym.sym < event.key.keysym.sym;
	}
};

struct EnemyDeathEvent
{
	int id, x, y;
	EnemyDeathEvent(int id, int x, int y) : id(id), x(x), y(y) {}

	inline bool operator<(EnemyDeathEvent const& a) const
	{
		return a.id < id;
	}
	inline bool operator<=(EnemyDeathEvent const& a) const
	{
		return a.id < id ;
	}

	inline bool operator>(EnemyDeathEvent const& a) const
	{
		return a.id < id;
	}
	inline bool operator>=(EnemyDeathEvent const& a) const
	{
		return a.id < id;
	}
};