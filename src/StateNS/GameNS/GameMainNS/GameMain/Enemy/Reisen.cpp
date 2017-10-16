#include "Reisen.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{


bool Reisen::imgLoad = false;
int Reisen::images[8];


	
Reisen::Reisen(int x, int y) :
Reisen(x, y, true)
{ }

Reisen::Reisen(int _x, int _y, bool _isOriginal) : 
EnemyChild(_isOriginal ? 1000 : 1, _x, _y, 32, 32, _isOriginal, true),
isOriginal(_isOriginal)
{
	loadImage();
	
	initialize();
}

Reisen::~Reisen()
{
	SAFE_DELETE(replica);
}

void Reisen::initialize()
{
	this->mTime = 0;
	this->nowMoving = false;
	this->makeReplica = false;

	if (isOriginal)
	{
		replica = new Reisen(p->raw_x / vectorRate, p->raw_y / vectorRate, false);
	}
	else
	{
		replica = 0;
	}
}

void Reisen::update(const StageChild* _stage, const Vector2* _camera)
{
	this->mDirection = player->raw_x > this->p->raw_x;

	++mTime;
	if (mTime % 90 == 0 && !nowMoving)attack();
	//if (!nowMoving && abs(player->raw_x - this->p->raw_x) < 64000)

	if (mTime % jump_interval == 0)
	{
		nowMoving = false;
	}

	//�ړ�
	//360 ��jump_interval�̋����{
	if(mTime == 360)
	{
		nowMoving = true;
	}
	//���ɖ߂�
	//660 ��jump_interval�̊�{
	if (mTime == 660)
	{
		nowMoving = true;
		mTime = jump_interval;
	}


	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(_camera);
		}
	}
	standardAction(_stage);


	//�ȉ��C���g�֘A�̏���
	if (!isOriginal)return;

	//���g�����
	//���łɍ���Ă��Ă���Ă����� replica->isAlive() �� false �ɂȂ�
	if (CheckHitKey(KEY_INPUT_Q))
	{
		makeReplica = replica->isAlive();
	}

	//���g��update
	if (makeReplica)
	{
		replica->update(_stage, _camera);
		makeReplica = replica->isAlive();
	}
	

}

vector<Attack*> Reisen::getAttacks() const
{
	//���g�Ȃ炻�̂܂ܕԂ�
	if (!isOriginal)return attacks;

	//�{�̂Ȃ番�g�̒e�ƈꏏ�ɕԂ�
	vector<Attack*> ret = attacks;
	for (auto& a : replica->getAttacks())
	{
		ret.push_back(a);
	}

	return ret;
}

void Reisen::draw(const Vector2* _camera) const
{
	//��ʓ��ɂ��Ȃ����return
	//if (!mIsAlive)return;


	//��ʓ��ɂ��Ȃ����return
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	//DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage2, true, mDirection);
	draw_other(_camera);
}

void Reisen::move(const StageChild* _stage, int& _dx, int& _dy)
{
	//�����Ȃ���Η�����������
	_dy = getBottomDiffer(_stage, 4000, true);
	if (!nowMoving)return;

	//�ړ���
	float theta = pi(1 / (float)jump_interval) * (mTime % (jump_interval * 2));

	float sin1 = sinf(theta);
	float sin2 = sinf(theta * 2.0f);

	_dx = getHorizontalDiffer(_stage, (int)(-16000 * sin1), sin2 < 0.0f);
	_dy = ((sin2 < 0) ? getTopDiffer(_stage, (int)(-20000 * sin2), _dx < 0) : getBottomDiffer(_stage, (int)(-20000 * sin2), _dx < 0));
}

void Reisen::draw_other(const Vector2* _camera) const
{
	//���g��draw
	if (makeReplica && isOriginal)
	{
		SetDrawBlendMode(DX_BLENDMODE_PMA_ADD, 100);
		replica->draw(_camera);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 20);
	}

	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	//DrawString(draw_x - 16, draw_y - 32, "���", BLUE);
	DrawRotaGraph(draw_x, draw_y-16, 1.0, 0.0, images[0], true, !mDirection);

	//for Debug
	DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Reisen::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Character/chip_Reisen.png", 32, 8, 4, 32, 64, images);
		assert(tmp != -1 && "Reisen�摜�ǂݍ��݃G���[");
	}
	imgLoad = true;
}

void Reisen::hittedAction()
{

}

void Reisen::attack()
{
	//�g���Ă��Ȃ��I�u�W�F�N�g���ė��p
	for (auto& a : attacks)
	{
		if (!a->isActive)
		{
			a->setStatus(*p, this->mDirection);
			a->isActive = true;
			return;
		}
	}

	//���ׂĎg���Ă�����new����
	attacks.push_back(new Shot(this, player, this->p->raw_x, this->p->raw_y));
}

//==============================================
//Shot�N���X
//==============================================
Reisen::Shot::Shot(const EnemyChild* _parent, const Vector2* _player, int _x, int _y) :
Attack(_parent, _x, _y, 32, 32, ObjectID::ID_NONE),
player(_player)
{
	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/shot0.png");
	assert(mImage != -1 && "���Shot�摜�ǂݍ��݃G���[");

	initialize();
}

Reisen::Shot::~Shot()
{
	DeleteGraph(mImage);
}

void Reisen::Shot::initialize()
{
	mDirection = player->raw_x > this->p->raw_x;
	dx = (mDirection) ? fast_speed : -fast_speed;
	p->raw_x += ((mDirection) ? 16000 : -16000);
	time = 0;
	nowFast = true;
}

void Reisen::Shot::update()
{
	time++;
	if (time < 60)
	{
		//������
		return;
	}

	if (
		nowFast && ( //�v���C���[�ɋ߂��Ȃ����猸��
		(mDirection  && this->player->raw_x < this->p->raw_x + fast_speed * 15) ||
		(!mDirection && this->player->raw_x > this->p->raw_x - fast_speed * 15)
		))
	{
		this->dx = ((this->dx < 0) ? -slow_speed : slow_speed);
		nowFast = false;
	}

	this->p->raw_x += dx;

	//���@���痣���Ə���
	if (abs(this->p->raw_x - player->raw_x) > 640000)this->isActive = false;
}

void Reisen::Shot::draw(const Vector2* _camera) const
{
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();


	//�������Ȃ�
	if (time < 60)
	{
		unsigned ring_color = GetColor(255, min(time * 6, 255), 255);
		DrawCircle(draw_x, draw_y, (60 - time), ring_color, 0);
	}
	else
	{
		DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
	}
}

void Reisen::Shot::setStatus(Vector2 _pos, int direction)
{
	*(this->p) = _pos;
	initialize();
}

void Reisen::Shot::hittedAction()
{

}


}
}
}