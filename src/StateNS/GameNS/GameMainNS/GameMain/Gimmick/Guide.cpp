#include "Guide.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

bool Guide::imgLoad = false;
int Guide::image;

Guide::Guide(int _x, int _y, vector<string> _messages ) :
GimmickChild(Vector2(_x, _y))
{
	this->messages = _messages;
	initialize();
}

Guide::~Guide()
{
	messages.clear();
	messages.shrink_to_fit();
}

void Guide::initialize()
{
	loadImage();

	this->mTime = 0;
	this->activeWhenStopping = true;

	//�g�̕��C������ݒ�
	int max_str_num = 0;
	for (const auto& m : messages)
	{
		max_str_num = max(max_str_num, (int)m.size());
	}
	frameWidth = max_str_num * 10;
	frameHeight = (int)messages.size() * 30;
}

void Guide::update()
{
	if (this->playerLooking)mTime = min(mTime + 1, 30);
	else mTime = 0;

	this->playerLooking = false;
}

void Guide::draw(const Vector2* _camera) const
{
	//��ʓ��ɂ��Ȃ����return
	if (abs(pos.raw_x - _camera->raw_x) > 480000 || abs(pos.raw_y - _camera->raw_y) > 320000)return;

	int draw_x = MyData::CX + pos.x() - _camera->x();
	int draw_y = MyData::CY + pos.y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y - 16, 1.0, 0.0, image, true, false);

	//�v���C���[���߂��ɂ�������e��\��
	if (playerLooking)
	{
		//�������ɍ��w�i�̐����o����\��
		DrawFilledCircledBox(draw_x + 17, draw_y - 13 - frameHeight, draw_x + frameWidth + 13, draw_y - 7, 15, WHITE);
		DrawFilledCircledBox(draw_x + 20, draw_y - 10 - frameHeight, draw_x + frameWidth + 10, draw_y - 10, 15, BLACK);

		//���͂�\��
		for (unsigned i = 0; i < messages.size(); i++)
		{
			DrawString(draw_x + 30, draw_y - frameHeight + i * 30, messages[i].c_str(), WHITE);
		}
	}
}

void Guide::apply(Character* _character)
{
	this->playerLooking = true;
}

bool Guide::onActiveArea(const Vector2* _player) const
{
	//���̃M�~�b�N�����͈͂��L�߂ɂ���
	int w = frameWidth  * vectorRate;
	int h = frameHeight * vectorRate;

	return
		this->pos.raw_x - 32000 <= _player->raw_x &&
		this->pos.raw_x + w >= _player->raw_x &&
		this->pos.raw_y - h <= _player->raw_y &&
		this->pos.raw_y     >= _player->raw_y;
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Guide::loadImage()
{
	if (!imgLoad)
	{
		this->image = LoadGraph("Data/Image/Guide.png");
		assert((image != -1) && "Guide�摜�ǂݍ��݃G���[!");
	}
	imgLoad = true;
}



}
}
}