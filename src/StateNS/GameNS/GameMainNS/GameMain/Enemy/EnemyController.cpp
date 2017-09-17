#include "EnemyController.h"

#include "EnemyChild.h"
#include "Usagi.h"
#include "Balloon.h"

#include "..\Player\PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{




EnemyController::EnemyController()
{
	enemies.push_back(new Balloon(300, 1450));
	enemies.push_back(new Usagi(200, 1450));
	//enemies.push_back(new Usagi(320, 240));
}

EnemyController::~EnemyController()
{
	for (auto& enemy : enemies)
	{
		SAFE_DELETE(enemy);
	}
	enemies.clear();
	enemies.shrink_to_fit();
}

void EnemyController::update(const Stage* _stage)
{
	for (auto& enemy : enemies)
	{
		enemy->update(_stage);
	}
}

void EnemyController::draw(const Vector2* _camera) const
{
	for (auto& enemy : enemies)
	{
		enemy->draw(_camera);
	}
}

//���@�ƓG�̖{�̓��m�̏Փ˔���
void EnemyController::processCollision(PlayerChild* _player)
{
	for (auto& enemy : enemies)
	{
		if (_player->isHit(enemy))
		{
			_player->hpController.damage(10);
		}
	}
}

void EnemyController::createEnemy(/*�񋓌^�œG�w��*/)
{

}

void EnemyController::deleteEnemy(int _ID)
{

}

void EnemyController::setPlayerPos(const Vector2* player)
{
	for (auto& enemy : enemies)
	{
		enemy->setPlayer(player);
	}
}



}
}
}