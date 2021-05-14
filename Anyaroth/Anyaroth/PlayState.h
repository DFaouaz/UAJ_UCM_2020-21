#pragma once
#include "GameState.h"
#include "LevelManager.h"
#include "Player.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "Cursor.h"

class PlayState : public GameState
{
private:
	Player* _player = nullptr;
	GameObject* _level = nullptr;

	BulletPool* _playerBulletPool = nullptr;
	ParticlePool* _particlePool = nullptr;

	LevelManager _levelManager;
	int _step = 0;

public:
	PlayState(Game* g);
	virtual ~PlayState();

	virtual void start();
	virtual void update(double deltaTime);
	virtual bool handleEvent(const SDL_Event& event);
	virtual bool handleEventBot(priority_queue<pair<int, InputEvent>, vector<pair<int, InputEvent>>, greater<pair<int, InputEvent>>>& events);

	void saveGame();
	void loadGame();
};