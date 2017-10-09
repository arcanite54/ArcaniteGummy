#include "Fran.h"
#include "Shot.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
bool Fran::imgLoad = false;
int Fran::images[32];


	
Fran::Fran(int _x, int _y) : 
EnemyChild(1000, _x, _y, 32, 64, false, true),
initial_pos(Vector2(_x, _y))
{
	loadImage();
	
	initialize();
}

Fran::~Fran()
{
	//DeleteGraph(mImage2);
}

void Fran::initialize()
{
	this->mImage = images[0];
	this->mTime = 0;
	this->init_attacks = false;
}

void Fran::initialize_attacks()
{

	stars.reserve(maxStarBowNum);
	waves.reserve(maxWave495Num);

	//*
	for (auto i = 0; i < maxStarBowNum; i++)
	{
		auto sb_tmp = new StarBow(player, this);
		sb_tmp->addAttacks(attacks);

		stars.push_back(sb_tmp);
	}
	//*/

	//*
	for (auto i = 0; i < maxWave495Num; i++)
	{
		auto wave_tmp = new Wave495(player, this);
		wave_tmp->addAttacks(attacks);

		waves.push_back(wave_tmp);
	}
	//*/

	//*
	kind4 = new Kind4(p, this);
	kind4->addAttacks(attacks);
	//*/

	attacks.shrink_to_fit();
	init_attacks = true;
}

void Fran::update(const StageChild* _stage, const Vector2* _camera)
{
	if (!init_attacks)initialize_attacks();

	++mTime;
	this->mDirection = this->p->raw_x > player->raw_x;
	standardAction(_stage);


	//�e��update
	processAttack(_stage);
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Fran::move(const StageChild* _stage, int& _dx, int& _dy)
{
	/*
	_dx = dx;
	if (p->raw_x + dx < initial_pos.raw_x - 200000 || initial_pos.raw_x + 200000 < p->raw_x + dx)
	{
		dx = -dx;
		p->raw_x += dx;
	}
	//*/
}

void Fran::draw_other(const Vector2* _camera) const
{
	if (init_attacks)
	{
		for (auto& sb : stars)
		{
			if (sb->isActive())
				sb->draw(_camera);
		}
		
		for (auto& wave : waves)
		{
			if (wave->isActive())
				wave->draw(_camera);
		}

		if(kind4->isActive())kind4->draw(_camera);
	}

	//for Debug
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	//DrawString(draw_x - 16, draw_y - 32, "�t����", BLUE);

	//for Debug
	//DrawFormatString(draw_x - 16, draw_y - 64, GREEN, "%d", hpController.getHP());



}

void Fran::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Character/chip_fran.png", 32, 8, 4, 32, 64, images);
		assert(tmp != -1 && "Fran�摜�ǂݍ��݃G���[");
	}
	imgLoad = true;
}


void Fran::hittedAction()
{

}

void Fran::processAttack(const StageChild* _stage)
{
	//udpate
	for (auto& sb : stars)
	{
		if (sb->isActive())
		{
			sb->update();
			sb->checkActive(_stage);
		}
	}

	for (auto& wave : waves)
	{
		if (wave->isActive())
		{	
			wave->update();
			wave->checkActive(_stage);
		}
	}

	if (kind4->isActive())kind4->update();

	//�e����

	//for Debug

	/*
	//if(�X�^�[�{�E�u���C�N�I�Ȃ�)
	if (mTime % 17 == 0)
	{
		for (auto& sb : stars)
		{
			if (!sb->isActive())
			{
				sb->setStatus(this->p);
				sb->setActive(true);
				break;
			}
		}
	}
	//*/

	/*
	//if(Q.E.D�Ȃ�)
	if (mTime % 17 == 0)
	{
		for (auto& wave : waves)
		{
			if (!wave->isActive())
			{
				wave->setStatus(&Vector2(p->raw_x + GetRand(100000) - 50000, p->raw_y + GetRand(100000) - 50000, true));
				wave->setActive(true);
				break;
			}
		}
	}
	//*/

	//*
	//if(Kind4�Ȃ�)
	if (!kind4->isActive())
	{
		kind4->setStatus(p);
		kind4->setActive(true);
	}
	//*/

	//for Debug
	//�e������
	if (CheckHitKey(KEY_INPUT_W))
	{
		for (auto& sb : stars)
		{
			sb->setActive(false);
		}
	}

}

//==============================================
//StarBow�N���X
//==============================================
Fran::StarBow::StarBow(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Fran::StarBow::~StarBow()
{

	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Fran::StarBow::initialize(const Vector2* _pos)
{
	time = 0;
	this->mIsActive = false;
	this->center_pos = (*_pos / vectorRate);

	//��Ƀ��������m�ۂ��邱�Ƃō�����
	shots.reserve(6);

	for (int i = 0; i < 6; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->isActive = false;

		//�����Œe�̐F��ݒ�
		//GetRand(3) + 1 �� 1 ~ 4 �̒l��Ԃ�
		s_tmp->setImage(GetRand(3) + 1);

		shots.push_back(s_tmp);
	}
}

void Fran::StarBow::update()
{
	++time;
	if (time < 10)return;

	if(time > 30)
	for (auto& s : shots)if (s->isActive)s->update();
}

void Fran::StarBow::draw(const Vector2* _camera) const
{
	if (time > 10)
	{
		for (auto& s : shots)
		{
			s->draw(_camera);
		}
	}
	else
	{
		int draw_x = 320 + center_pos.raw_x - _camera->x();
		int draw_y = 240 + center_pos.raw_y - _camera->y();

		for (int i = 0; i < 6; i++)
		{
			DrawCircle(draw_x + differ_x[i], draw_y, (10 - time) * 5, PURPLE, false);
		}
	}

}

void Fran::StarBow::addAttacks(vector<Attack*>& _attacks)
{
	//��Ƀ��������m�ۂ��邱�Ƃō�����
	_attacks.reserve(_attacks.size() + 6);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Fran::StarBow::setStatus(const Vector2* _pos)
{
	time = 0;
	for (int i = 0; i < 6; i++)
	{
		shots[i]->setStatus_2args(Vector2(_pos->raw_x + differ_x[i] * vectorRate, _pos->raw_y, true), 90, 3000);
		shots[i]->setImage(GetRand(3) + 1);
	}
	this->center_pos = *_pos / vectorRate;
}

void Fran::StarBow::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Fran::StarBow::checkActive(const StageChild* _stage)
{
	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive = !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}
}

//==============================================
//Wave495�N���X
//==============================================
Fran::Wave495::Wave495(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Fran::Wave495::~Wave495()
{
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Fran::Wave495::initialize(const Vector2* _pos)
{
	this->time = 0;
	this->center_pos = (*_pos / vectorRate);
	this->mIsActive = false;

	//��Ƀ��������m�ۂ��邱�Ƃō�����
	shots.reserve(maxShotNum);

	for (int i = 0; i < maxShotNum; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->isActive = false;

		//�����Œe�̐F��ݒ�
		//GetRand(3) + 1 �� 1 ~ 4 �̒l��Ԃ�
		s_tmp->setImage(GetRand(3) + 1);

		shots.push_back(s_tmp);
	}
}

void Fran::Wave495::update()
{
	++time;
	if (time < 10)return;
	if (time > 90)this->setActive(false);


	for (auto& s : shots)if (s->isActive)s->update();

}

void Fran::Wave495::draw(const Vector2* _camera) const
{
	if (time > 10)
	{
		for (auto& s : shots)
		{
			s->draw(_camera);
		}
	}
	else
	{
		int draw_x = 320 + center_pos.raw_x - _camera->x();
		int draw_y = 240 + center_pos.raw_y - _camera->y();

		for (int i = 0; i < 6; i++)
		{
			DrawCircle(draw_x, draw_y, (10 - time) * 5, PURPLE, false);
		}
	}
}

void Fran::Wave495::addAttacks(vector<Attack*>& _attacks)
{
	//��Ƀ��������m�ۂ��邱�Ƃō�����
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Fran::Wave495::setStatus(const Vector2* _pos)
{
	time = 0;
	this->center_pos = (*_pos / vectorRate);

	for (int i = 0; i < maxShotNum; i++)
	{
		int angle = 60 * i;
		shots[i]->setStatus_2args(
			Vector2(
				_pos->raw_x + (int)(radius * cosf_degree(angle)), 
				_pos->raw_y + (int)(radius * sinf_degree(angle)),
				true
			), 
			(angle), 3000
		);
	}
}

void Fran::Wave495::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Fran::Wave495::checkActive(const StageChild* _stage)
{
	if (!this->mIsActive)return;


	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive = !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}
}


//==============================================
//Kind4�N���X
//==============================================
Fran::Kind4::Kind4(const Vector2* _pos, EnemyChild* _parent)
{
	parent = _parent;
	initialize(_pos);
}

Fran::Kind4::~Kind4()
{
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();

	SAFE_DELETE(child1);
	SAFE_DELETE(child2);
	SAFE_DELETE(child3);
}

void Fran::Kind4::initialize(const Vector2* _pos)
{
	this->time = 0;
	this->mIsActive = false;

	//��Ƀ��������m�ۂ��邱�Ƃō�����
	shots.reserve(maxShotNum);

	for (int i = 0; i < maxShotNum; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->isActive = false;

		//�����Œe�̐F��ݒ�
		//GetRand(3) + 1 �� 1 ~ 4 �̒l��Ԃ�
		s_tmp->setImage(GetRand(3) + 1);

		shots.push_back(s_tmp);
	}

	child1 = new Childs(0, 0, parent, 45);
	child2 = new Childs(0, 0, parent, 45);
	child3 = new Childs(0, 0, parent, 0);
}

void Fran::Kind4::update()
{
	++time;
	for (auto& s : shots)
	{
		if(s->isActive)s->update();
	}

	child1->update();
	child2->update();
	child3->update();
}

void Fran::Kind4::draw(const Vector2* _camera) const
{
	if (time > 60)
	{
		for (auto& s : shots)
		{
			s->draw(_camera);
		}
	}
	else
	{
		int draw_x = 320 + parent->getVector2()->x() - _camera->x();
		int draw_y = 240 + parent->getVector2()->y() - _camera->y();

		DrawCircle(draw_x, draw_y, (60 - time) * 3, PURPLE, false);
	}
	child1->draw(_camera);
	child2->draw(_camera);
	child3->draw(_camera);
}

void Fran::Kind4::addAttacks(vector<Attack*>& _attacks)
{
	//��Ƀ��������m�ۂ��邱�Ƃō�����
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
	child1->addAttacks(_attacks);
	child2->addAttacks(_attacks);
	child3->addAttacks(_attacks);
}

void Fran::Kind4::setStatus(const Vector2* _pos)
{
	time = 0;
	for (int i = 0; i < maxShotNum; i++)
	{
		shots[i]->setStatus_2args(*_pos, 90 * i, 3000);
	}

	child1->setStatus(_pos->raw_x - 50000, _pos->raw_y - 10000);
	child2->setStatus(_pos->raw_x + 50000, _pos->raw_y + 10000);
	child3->setStatus(_pos->raw_x + 100000, _pos->raw_y);
}

void Fran::Kind4::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
	child1->setActive(_isActive);
	child2->setActive(_isActive);
	child3->setActive(_isActive);
}

void Fran::Kind4::checkActive(const StageChild* _stage)
{
	if (!this->mIsActive)return;

	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive = !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}

	child1->checkActive(_stage);
	child3->checkActive(_stage);
	child3->checkActive(_stage);

	mIsActive |= child1->isActive();
	mIsActive |= child2->isActive();
	mIsActive |= child3->isActive();
}

//==============================================
//Kind4�̓���Childs�N���X
//==============================================
Fran::Kind4::Childs::Childs(int _x, int _y, EnemyChild* parent, int _phase):
init_phase(_phase)
{
	this->p = new Vector2(_x, _y, true);
	time = 0;
	this->mIsActive = false;

	shots.reserve(maxShotNum);
	for (int i = 0; i < maxShotNum; i++)
	{
		Shot* s_tmp = new Shot(parent, 0, 0, 0, 0, 50);
		s_tmp->setImage(GetRand(3) + 1);
		shots.push_back(s_tmp);
	}
}

Fran::Kind4::Childs::~Childs()
{
	SAFE_DELETE(p);
	for (auto& s : shots)
	{
		SAFE_DELETE(s);
	}
	shots.clear();
	shots.shrink_to_fit();
}

void Fran::Kind4::Childs::update()
{
	++time;

	if(time > 60)for (auto& s : shots)if (s->isActive)s->update();
	if (time > 120)this->setActive(false);
}

void Fran::Kind4::Childs::draw(const Vector2* _camera) const
{
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();


	if (time > 60)
	{
		DrawCircle(draw_x, draw_y, 10, GREEN, true);
		for (auto& s : shots)
		{
			s->draw(_camera);
		}
	}
	else
	{
		DrawCircle(draw_x, draw_y, (60 - time) * 3, PURPLE, false);
	}
}

void Fran::Kind4::Childs::addAttacks(vector<Attack*>& _attacks)
{
	//��Ƀ��������m�ۂ��邱�Ƃō�����
	_attacks.reserve(_attacks.size() + maxShotNum);

	for (auto& s : shots)
	{
		_attacks.push_back(s);
	}
}

void Fran::Kind4::Childs::setStatus(int _x, int _y)
{
	time = 0;
	this->p->raw_x = _x;
	this->p->raw_y = _y;

	for (int i = 0; i < maxShotNum; i++)
	{
		shots[i]->setStatus_2args(Vector2(_x, _y, true), init_phase + 90 * i, 3000);
	}
}

void Fran::Kind4::Childs::setActive(bool _isActive)
{
	this->mIsActive = _isActive;

	for (auto& s : shots)
	{
		s->isActive = _isActive;
	}
}

void Fran::Kind4::Childs::checkActive(const StageChild* _stage)
{
	if (!this->mIsActive)return;


	this->mIsActive = false;
	for (auto& s : shots)
	{
		StageChild::ChipType chipType = _stage->getChipType(*s->getVector2(), true);
		s->isActive = !_stage->isRigid_down(chipType);

		mIsActive |= s->isActive;
	}
}


}
}
}