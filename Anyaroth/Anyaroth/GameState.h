#pragma once
#include <list>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "Canvas.h"
#include "PlayStateHUD.h"
#include "MenuStateHUD.h"
#include "PauseStateHUD.h"
#include "DebugDraw.h"
#include "CollisionManager.h"
#include <Anyaroth/InputEvent.h>

class Game;
class CutScene;

class GameState
{
private:
	vector<GameObject*> items_ToDelete;
	bool _hasToStart;
	bool _gameLoaded;

	void initializeCamera();

protected:
	Game* _gameptr = nullptr;
	b2World* _world = nullptr;

	string _type = "";

	list<GameObject*> _stages;

	Camera* _mainCamera = nullptr;
	Canvas* _canvas = nullptr;
	PlayStateHUD* _playHud = nullptr;
	MenuStateHUD* _menuHud = nullptr;
	PauseStateHUD* _pauseHud = nullptr;
	CutScene* _cutScene = nullptr;

	DebugDraw _debugger;
	CollisionManager _colManager;

	int _mouseX = 0, _mouseY = 0;
	int _mouseScreenX = 0, _mouseScreenY = 0;

public:
	GameState(Game* g);
	virtual ~GameState();

	bool hasToStart() const { return _hasToStart; }
	void setStarted(bool b) { _hasToStart = !b; }

	bool gameLoaded() const { return _gameLoaded; }
	void setLoaded(bool b) { _gameLoaded = b; }

	virtual void start() = 0;
	virtual void render() const;

	virtual void update(double deltaTime);
	virtual void post_update();

	virtual bool pre_handleEvent();
	virtual bool handleEvent(const SDL_Event& event);
	virtual bool handleEventBot(priority_queue<pair<int, InputEvent>, vector<pair<int, InputEvent>>, greater<pair<int, InputEvent>>>& events);

	virtual void updateWorld(float timestep, int p_iterations, int V_iterations);
	inline b2World* getWorld() const { return _world; }

	virtual void addObject(GameObject* obj);
	virtual void destroyObject(GameObject* obj);
	inline virtual list<GameObject*>& getObjects() { return _stages; }

	inline virtual Camera* getMainCamera() const { return _mainCamera; }
	inline virtual PlayStateHUD* getPlayHUD() const { return _playHud; }
	inline virtual MenuStateHUD* getMenuHUD() const { return _menuHud; }
	inline virtual PauseStateHUD* getPauseHUD() const { return _pauseHud; }
	inline virtual CutScene* getCutScene() const { return _cutScene; }
	inline virtual void setCanvas(Canvas* canvas) { _canvas = canvas; }

	virtual void addCutScene(CutScene* cutScene);

	Vector2D getMousePositionInWorld() const;
	Vector2D getMousePositionInWorldBot() const;
	Vector2D getMousePositionOnScreenBot() const;
	Vector2D getMousePositionOnScreen() const;
	Vector2D getMousePositionOnCamera() const;
	void setMousePositionInWorld(Vector2D coord);
	void setMousePositionInWorldBot(Vector2D coord);

	void setMousePositionOnScreenBot(Vector2D coord);

	string getType() { return _type; }
};