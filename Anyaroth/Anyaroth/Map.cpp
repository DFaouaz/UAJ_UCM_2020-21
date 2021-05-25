#include "Map.h"
#include "BodyComponent.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "StaticFlyingEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "BomberEnemy.h"
#include "NormalSpawner.h"
#include "DistanceSpawner.h"
#include "StaticSpawnerEnemy.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Player.h"
#include "NPC.h"
#include "Shop.h"
#include "TutorialBullsEye.h"
#include "TutorialTurret.h"
#include "TutorialBuddy.h"
#include "AmmoPackage.h"
#include "AidKit.h"
#include "DialogueTrigger.h"
#include "MissileTurret.h"
#include "FloatingHead.h"
#include "SpawnerBoss.h"
#include "GoodCredits.h"
#include "BadCredits.h"
#include "GameManager.h"
#include <json.hpp>

using namespace nlohmann;

Map::Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool) : GameObject(game), _player(player), _bulletPool(bulletPool)
{
	_tilemap = new Tilemap(game, tileset);
	_tilemap->loadTileMap(filename);
	addChild(_tilemap);

	_objects = new GameObject(_game);
	addChild(_objects);

	json j;
	fstream file;
	file.open(filename);

	if (file.is_open())
	{
		file >> j;
		j = j["layers"];

		for (int i = 0; i < j.size(); i++)
		{
			auto it = j[i].find("name");
			if (it != j[i].end())
			{
				if (*it != "Map" && *it != "Ground" && *it != "Platform" && *it != "Door" && *it != "Death" && *it != "Props")
					_objectLayers.push_back(new ObjectLayer(filename, *it));
				else if (*it == "Map")
				{
					it = j[i].find("height");
					_height = *it;
					_height = _height * TILES_SIZE;

					it = j[i].find("width");
					_width = *it;
					_width = _width * TILES_SIZE;
				}
			}
		}
		file.close();
	}

	createObjects();
}

Map::~Map()
{
	for (int i = 0; i < _objectLayers.size(); i++)
		delete _objectLayers[i];

	_objectLayers.clear();
}

void Map::createObjects()
{
	Boss1* spenta = nullptr;
	Boss2* azura = nullptr;
	Boss3* angra = nullptr;

	int enemyCont = 0;

	for (int i = 0; i < _objectLayers.size(); i++)
	{
		string name = _objectLayers[i]->getName();
		vector<pair<Vector2D, string>> objectData = _objectLayers[i]->getObjectsData();

		for (int j = 0; j < objectData.size(); j++)
		{
			Vector2D pos = objectData[j].first;
			string data = objectData[j].second;

			if (name == "Player")
			{
				_player->setPlayerPosition(Vector2D(pos.getX() / M_TO_PIXEL, (pos.getY() - TILES_SIZE * 2) / M_TO_PIXEL));
				_player->resetDustParticle();
			}
			else if (name == "Bullseye")
			{
				_objects->addChild(new TutorialBullsEye(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE)));
				enemyCont++;
			}
			else if (name == "Ammo")
			{
				_objects->addChild(new AmmoPackage(_game, Vector2D(pos.getX(), pos.getY() - TILES_SIZE), 5));
			}
			else if (name == "Aidkit")
			{
				_objects->addChild(new AidKit(_game, Vector2D(pos.getX(), pos.getY() - TILES_SIZE), 100));
			}
			else if (name == "TutorialTurret")
			{
				_objects->addChild(new TutorialTurret(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE), _bulletPool));
			}
			else if (name == "TutorialBuddy")
			{
				_objects->addChild(new TutorialBuddy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "Trigger")
			{
				_objects->addChild(new DialogueTrigger(_game, data, _player, pos.getX(), pos.getY() - TILES_SIZE * 2));
			}
			else if (name == "Melee")
			{
				Enemy* enemy = new MeleeEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2));
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "Martyr")
			{
				Enemy* enemy = new MartyrEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2));
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "DistanceStatic")
			{
				Enemy* enemy = new DistanceStaticEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool);
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "FlyingDistance")
			{
				Enemy* enemy = new StaticFlyingEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool);
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "DistanceDynamic")
			{
				Enemy* enemy = new DistanceDynamicEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool);
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "Spawner")
			{
				Enemy* enemy = new StaticSpawnerEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2));
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "MeleeShip")
			{
				Enemy* enemy = new NormalSpawner<MeleeEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2));
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "DistanceShip")
			{
				Enemy* enemy = new DistanceSpawner<DistanceDynamicEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool);
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "Bomber")
			{
				Enemy* enemy = new BomberEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool);
				_objects->addChild(enemy);
				enemy->setEnemyId(enemyCont);
				enemyCont++;
			}
			else if (name == "Boss1")
			{
				spenta = (new Boss1(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
				_objects->addChild(spenta);
				spenta->setBossPanel(_game->getCurrentState()->getPlayHUD()->getBossPanel());
			}
			else if (name == "Misil")
			{
				_objects->addChild(new MissileTurret(_game, spenta, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2.8), stoi(data)));
			}
			else if (name == "Boss2")
			{
				azura = (new Boss2(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
				_objects->addChild(azura);
				azura->setBossPanel(_game->getCurrentState()->getPlayHUD()->getBossPanel());
			}
			else if (name == "Lasers")
			{
				LaserHandler* l = new LaserHandler(_game, _game->getTexture("LaserContainer"), _game->getTexture("Laser"), _player, 8, stoi(data), pos + Vector2D{ 0, 0 });
				addChildFront(l);
				azura->setLasers(l);
			}
			else if (name == "Boss3")
			{
				angra = (new Boss3(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
				_objects->addChild(angra);
				angra->setBoss3Panel(_game->getCurrentState()->getPlayHUD()->getBoss3Panel());
			}
			else if (name == "FloatingHead")
			{
				FloatingHead* head = new FloatingHead(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE), _bulletPool, angra);

				_game->getCurrentState()->getPlayHUD()->getEnemyLifePanel()->addEnemy(head);
				head->setLifePanel(_game->getCurrentState()->getPlayHUD()->getEnemyLifePanel());

				angra->addChild(head);
				angra->push_backHead(head);
			}
			else if (name == "SpawnerBoss")
			{
				SpawnerBoss* spawner = new SpawnerBoss(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _spawnType, _bulletPool);

				angra->addChild(spawner);
				angra->push_backSpawner(spawner);
				_spawnType++;
			}
			else if (name == "Throne")
			{
			SpriteObject* throne;

			if (GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss3)
			{
				throne = new SpriteObject(_game, _game->getTexture("Throne"), Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2));

				AnimatedSpriteComponent* throneAnim = throne->getComponent<AnimatedSpriteComponent>();
				throneAnim->reset();
				throneAnim->addAnim(AnimatedSpriteComponent::ThroneIdle, 14, true);
				throneAnim->addAnim(AnimatedSpriteComponent::ThroneEnd1, 14, false);
				throneAnim->addAnim(AnimatedSpriteComponent::ThroneEnd2, 13, false);

				throneAnim->playAnim(AnimatedSpriteComponent::ThroneIdle);
				angra->setAnimThrone(throneAnim);
			}
			else
			{
				throne = new SpriteObject(_game, _game->getTexture("ThroneEmpty"), Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2));

				AnimatedSpriteComponent* throneAnim = throne->getComponent<AnimatedSpriteComponent>();
				throneAnim->reset();
				throneAnim->addAnim(AnimatedSpriteComponent::ThroneIdle, 1, false);

				throneAnim->playAnim(AnimatedSpriteComponent::ThroneIdle);
			}

			_objects->addChildFront(throne);
			}
			else if (name == "AngraCorpse")
			{
			BossCorpse* _corpse = new BossCorpse(_game, Vector2D(0, 0), _game->getTexture("AngraCorpse"));
			_corpse->setActive(false);
			angra->setAnimCorpse(_corpse);
			_objects->addChildFront(_corpse);
			}
			else if (name == "NPC")
			{
				NPC* npc = new NPC(_game, _game->getTexture(data), Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _game->getDialogue(data + " " + to_string(GameManager::getInstance()->getCurrentLevel())));
				npc->setDialoguePanel(_game->getCurrentState()->getPlayHUD()->getDialoguePanel());
				_objects->addChild(npc);
			}
			else if (name == "Shop")
			{
				Shop* tienda = new Shop(_game, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2.6), _game->getCurrentState()->getPlayHUD()->getShop());
				_objects->addChild(tienda);
			}
			else if (name == "GoodCredits")
			{
				_objects->addChild(new GoodCredits(_game, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "BadCredits")
			{
				_objects->addChild(new BadCredits(_game, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
		}
	}
}

void Map::restartLevel()
{
	if (_objects->getChildren().size() != 0)
	{
		_objects->destroyAllChildren();
		createObjects();
	}
}

void Map::killEnemy(EnemyDeathEvent info)
{
	int i = 0;
	for (auto object : _objects->getChildren())
	{
		if (i == info.id)
		{
			Enemy* enemy = static_cast<Enemy*>(object);
			if (!enemy->isDead())
			{
				enemy->getComponent<BodyComponent>()->getBody()->SetTransform(b2Vec2(info.x, info.y), 
											enemy->getComponent<BodyComponent>()->getBody()->GetAngle());
				enemy->die();
			}
			break;
		}
		i++;
	}
}

bool Map::handleEvent(const SDL_Event & event)
{
	return GameObject::handleEvent(event);
}

void Map::update(double deltaTime)
{
	GameObject::update(deltaTime);
}

void Map::render(Camera * c) const
{
	GameObject::render(c);
}