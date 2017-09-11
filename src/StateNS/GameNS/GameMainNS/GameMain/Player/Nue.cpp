#include "Nue.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "Mokou.h"


namespace StateNS {
	namespace GameNS {
		namespace GameMainNS {


			Nue::Nue(int _x, int _y, int _hp) : PlayerChild(_x, _y, 5.0f, 25.0f, 1, _hp)
			{
				initialize();
			}

			Nue::Nue(int _x, int _y) : Nue(_x, _y, 100)
			{

			}

			Nue::~Nue()
			{
				SAFE_DELETE(p);
			}

			void Nue::initialize()
			{
				//this->moveSpeed = 5.0f;
				loadImage();
				attackTime = 0;
				isUFO = false;
				
			}

			PlayerChild* Nue::update(const Stage* _stage)
			{
				PlayerChild* next = this;

				standardAction(_stage);

				//�U��
				for (auto& a : attacks)
				{
					if (a->isActive)
					{
						a->update();
						a->checkActive(camera);
					}
				}

				if (Input_ATTACK())
				{
					attack();
				}
				else
				{
					attackTime = 0;
				}
				if (isUFO) {
					ufo->update(_stage);

					if (abs(this->p->y() - ufo->p->y()) < CHIP_HEIGHT * 3 / 2 &&
						abs(this->p->x() - ufo->p->x()) < CHIP_WIDTH * 3 / 2)
					{	
							this->warpCharacter(ufo->p->x(), ufo->p->y() - 48);
							nowJumpCount = 0;
							jumpPower = 0.0f;
					}
						//this->warpCharacter(this->p->x(), ufo->p->y() - CHIP_HEIGHT-1);

					if (ufo->onActiveArea(this->getVector2()))
						ufo->apply(this);

					if (ufo->rideOnGimmick(this->getVector2()))
						this->moveCharacter(ufo->getDX(), ufo->getDY());
					
				}
				//for Debug
				if (canChangeCharacter())
				{
					animationTime = 0;
					int x = p->raw_x / MyData::vectorRate;
					int y = p->raw_y / MyData::vectorRate;
					ufo->isActive = false;
					next = new Mokou(x, y, hpController.getHP());
				}
				specialAction();
				return next;
			}

			int Nue::specialAction() {
				int x = 0;
				if (Input_C() && !isUFO) {
					ufo =new UFO((p->x()/CHIP_WIDTH+1)*CHIP_WIDTH-CHIP_WIDTH/2, (p->y() / CHIP_HEIGHT + 1)*CHIP_HEIGHT - CHIP_HEIGHT / 2);
					isUFO = true;
				}
//				prePushC = Input_C();
				return x;
			}

			//==============================================
			//�����v���C�x�[�g�֐�
			//==============================================
			void Nue::attack()
			{
				if (attacks.size() == 0)
				{
					attacks.push_back(new Spear(0, 0, 32, 32, true));
					//attacks.push_back(new Spear(0, 0, 32, 32, true));
					//attacks.push_back(new Spear(0, 0, 32, 32, true));
				}

				++attackTime;
				//if (attackTime > 0)
				int new_pos = 32000 * ((direction) ? -1 : 1);

				attacks[0]->setStatus(Vector2(this->p->raw_x + new_pos * 1, this->p->raw_y, true), this->direction);
//				if (attackTime > 10)attacks[1]->setStatus(Vector2(this->p->raw_x + new_pos * 2, this->p->raw_y, true), this->direction);
//				if (attackTime > 20)attacks[2]->setStatus(Vector2(this->p->raw_x + new_pos * 3, this->p->raw_y, true), this->direction);

			}

			void Nue::draw_other() const
			{
				for (const auto& a : attacks)
				{
					if (a->isActive)a->draw(camera);
				}

				if(isUFO)ufo->draw(camera);

				//for Debug
				DrawFormatString(0, 30, MyData::BLACK, "Nue");
			}


			void Nue::loadImage()
			{
				//	mImage = LoadGraph("Data/Image/Nue.png");
				LoadDivGraph("Data/Image/Character/chip_Nue.png", 40, 8, 5, 32, 64, mImage, TRUE);
				assert(*mImage != -1 && "���@�摜�ǂݍ��݃G���[");
			}

			//==============================================
			//Spear�N���X
			//==============================================
			Nue::Spear::Spear(int _x, int _y, int _w, int _h, bool _direction) :
				Attack(_x, _y, _w, _h, ObjectID::A_SPEAR)
			{
				this->mTime = 0;
				mDirection = _direction;

				//for Debug
				this->damageValue = 20;

				mImage = LoadGraph("Data/Image/Spear.png");
				assert(mImage != -1 && "Spear�摜�ǂݍ��݃G���[");
			}

			Nue::Spear::~Spear()
			{
				DeleteGraph(mImage);
			}

			void Nue::Spear::update()
			{
				mTime++;
				isActive = false;
			}

			void Nue::Spear::setStatus(Vector2 _pos, int direction)
			{
				*(this->p) = _pos;
				this->mDirection = direction;

				isActive = true;

			}

			void Nue::Spear::hittedAction()
			{
				//do nothing
			}



		}
	}
}