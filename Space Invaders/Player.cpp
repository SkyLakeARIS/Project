#include "Player.h"

//��ǥ �� ����
void Player::SetData()
{
	mposition.emplace_back(12, 22);
	for (int x = 0; x < 3; x++)
	{
		mposition.emplace_back(11 + x, 23);
	}
	mLife = 3;
	mbShooting_Flag = false;
}
//ĳ���� ��Ʈ��
void Player::MoveEntity()
{
	if (GetAsyncKeyState(VK_LEFT) && mposition[1].x > 0 )
	{
		for (int i = 0; i < 4; i++)
		{
			Remove_FootPrint(mposition[i].x, mposition[i].y);
			mposition[i].x--;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) && mposition[1].x < (MAP_SIZE - 3))
	{
		for (int i = 0; i < 4; i++)
		{
			Remove_FootPrint(mposition[i].x, mposition[i].y);
			mposition[i].x++;
		}
	}
	if ((GetAsyncKeyState(VK_SPACE) && 0x8000) && mbShooting_Flag == false)
	{
		mbShooting_Flag = true;
		mbullet.emplace_back(mposition.front().x, mposition.front().y);
	}
	if (mbShooting_Flag == true)
	{
		Remove_FootPrint(mbullet[0].x, mbullet[0].y);
		mbullet.at(0).y--;
	}
}
//�÷��̾� ĳ���Ϳ� �Ѿ� ���
void Player::PrintEntity() const
{
	gotoxy(mposition[0].x, mposition[0].y);
	PaintColor(mposition[0].y);
	std::cout << "A";

	gotoxy(mposition[1].x, mposition[1].y);
	PaintColor(mposition[1].y);
	std::cout << "��ǡ�";
	
	if (mbShooting_Flag == true)
	{
		gotoxy(mbullet.at(0).x, mbullet.at(0).y);
		std::cout << "��";
	}
}
//�÷��̾ ���� �Ѿ˿� �¾Ҵ��� üũ
unsigned int Player::OnCollide(int x, int y)
{
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		if (x == mposition[i].x && y == mposition[i].y)
		{
			Hit(i);
			return HIT;
		}
	}
	return MISS;
}
//�÷��̾ ���� �Ѿ˿� �¾��� �� ó��
unsigned int Player::Hit(unsigned int index)
{
	mLife--;
	
	DrawDestroyPlayer();

	//������ ����ġ�� ���ư�.
	RePosition();

	UpdateInfo();

	return NoPoint;
}
//�÷��̾ �� �Ѿ��� ��, �ٸ����̵忡 �¾Ҵ��� üũ
void Player::Shooting(std::shared_ptr<IEntity> entity)
{
	if (mbShooting_Flag == true)
	{
		unsigned int GetPoint = 0;

		//���ڷ� ���� entity�� �Ѿ˿� �¾Ҵ��� üũ
		GetPoint = entity->OnCollide(mbullet.at(0).x, mbullet.at(0).y);
		if (GetPoint != MISS)
		{
			mScore += GetPoint;

			DeleteBullet();

			UpdateInfo();
		}
		else
		{
			//�� ���� ������ üũ
			if (mbullet.at(0).y <= 0)
			{
				DeleteBullet();
			}
		}
	}
}
//�Ѿ� ����
void Player::DeleteBullet()
{
	//����Ʈ ȿ��
	gotoxy(mbullet[0].x, mbullet[0].y);
	std::cout << "��";
	Sleep(50);

	Remove_FootPrint(mbullet.at(0).x, mbullet.at(0).y);
	mbullet.pop_back();
	mbShooting_Flag = false;
}
//�ٲ� �÷��̾� ������ ������ִ� �Լ�
void Player::UpdateInfo() const
{
	//���� ���
	gotoxy(27, 11);
	SetColor(BLUE);
	std::cout << mScore;
	//mLife ���
	switch (mLife)
	{
	case 2:
		gotoxy(4, 27);
		SetColor(SKY_BLUE);
		std::cout << "   A   ";
		break;
	case 1:
		gotoxy(4, 27);
		SetColor(SKY_BLUE);
		std::cout << "       ";
		break;
	default:
		//Assert();
		break;
	}
}
//�÷��̾ �� �Ѿ˿� ���� �� ������ ��.
void Player::RePosition()
{
	unsigned int player_size = mposition.size();

	for (unsigned int i = 1; i <= player_size; i++)
	{
		Remove_FootPrint(mposition[player_size - i].x, mposition[player_size - i].y);
		mposition.pop_back();
	}

	mposition.emplace_back(12, 22);
	for (int x = 0; x < 3; x++)
	{
		mposition.emplace_back(11 + x, 23);
	}
}
//�ǰݽ� �ı� ȿ��
void Player::DrawDestroyPlayer() const
{
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		gotoxy(mposition[i].x, mposition[i].y);
		std::cout << "��";
	}
	Sleep(60);
}
//���� ��� ������ ���� ���带 ���� ���� �ʱ�ȭ
void Player::ClearData()
{
	if (mbShooting_Flag != false)  //Assert(mbShooting_Flag);
	{
		DeleteBullet();
	}
	RePosition();
}