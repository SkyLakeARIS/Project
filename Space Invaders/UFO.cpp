#include <cstdlib>
#include <ctime>
#include "UFO.h"

//�´� �κи� ��ǥ����
void UFO::SetData()
{
	if (mMoveDir == LEFT)
	{
		for (int i = 0; i < 3; i++)
		{
			mposition.emplace_back(22 + i, 1);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			mposition.emplace_back(0 + i, 1);
		}
	}
}
//UFO�� ���⿡ ���� �̵�
void UFO::MoveEntity()
{
	if (mbUFO_Flag == true)
	{
		// << ���� �̵�
		if (mMoveDir == LEFT)
		{
			if (true == CheckEntityPOS(mposition.at(0).x - 1, mposition.at(0).y))
			{
				for (unsigned int i = 0; i < mposition.size(); i++)
				{
					Remove_FootPrint(mposition[i].x, mposition[i].y);
					gotoxy(mposition[i].x, mposition[i].y - 1);
					std::cout << "      ";

					mposition[i].x--;
				}
			}
		}
		// >> ���� �̵�
		if (mMoveDir == RIGHT)
		{
			if (true == CheckEntityPOS(mposition.at(2).x + 1, mposition.at(2).y))
			{
				for (unsigned int i = 0; i < mposition.size(); i++)
				{
					Remove_FootPrint(mposition[i].x, mposition[i].y);
					gotoxy(mposition[i].x, mposition[i].y - 1);
					std::cout << "      ";

					mposition[i].x++;
				}
			}
		}
	}
	else
	{
		//mbUFO_Flag�� false�̸� ����
		GenerateUFO();
	}
}
//UFO�� �ݴ������� ������ Ȯ��
bool UFO::CheckEntityPOS(int x, int y)
{
	if (mMoveDir == LEFT)
	{
		if (x >= 0 && y == 1)
		{
			return true;
		}
	}
	if (mMoveDir == RIGHT)
	{
		if (x <= MAP_SIZE - 1 && y == 1)
		{
			return true;
		}
	}
	//mbUFO_Flag�� false�̹Ƿ� ������ ����
	DestroyUFO();

	return false;
}
//UFO ���
void UFO::PrintEntity() const
{
	if (mbUFO_Flag == true)
	{
		gotoxy(mposition.at(0).x, mposition.at(0).y - 1);
		PaintColor(mposition.at(0).y);
		std::cout << "������";
		gotoxy(mposition.at(0).x, mposition.at(0).y);
		PaintColor(mposition.at(0).y);
		std::cout << "�Т͢�";
	}
}
//UFO ����
void UFO::GenerateUFO()
{
	srand((unsigned int)time(NULL));
	int is_create = rand() % 100;

	//1~30�� ���ڰ� ������ mbUFO_Flag�� false�� ������ �� UFO����
	if (mbUFO_Flag == false && (2 > is_create || 97 < is_create))
	{
		mbUFO_Flag = true;
		mMoveDir = LEFT;
		//iscreate�� 2�����̸� ������->���� �̵�  98�̻��̸� ���� -> ������ 
		if (is_create > 97)
		{
			mMoveDir = RIGHT;
		}
		SetData();
	}
}
//UFO�� �÷��̾� �Ѿ˷κ��� �¾Ҵ��� Ȯ���ϴ� �Լ�
unsigned int UFO::OnCollide(int x, int y)
{
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		if (x == mposition[i].x && y == mposition[i].y)
		{
			return Hit(i);
		}
	}
	return MISS;
}
//�ǰݽ� �ı� ȿ�� �� ������ ����
unsigned int UFO::Hit(unsigned int index)
{
	SetColor(DARK_RED);
	gotoxy(mposition[0].x, mposition[0].y);
	std::cout << "�ءء�";
	gotoxy(mposition[0].x, mposition[0].y-1);
	std::cout << "�ءء�";

	Sleep(50);

	gotoxy(mposition[0].x, mposition[0].y);
	SetColor(YELLOW);
	std::cout << " +300 ";

	Sleep(100);

	DestroyUFO();

	return Get_UFO_Point;
}
//�Ѿ��� �߻����� ����
void UFO::Shooting(std::shared_ptr<IEntity> entity)
{
	//do nothing
}
//UFO ����
void UFO::DestroyUFO()
{
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		Remove_FootPrint(mposition[i].x, mposition[i].y);
	}
	gotoxy(mposition[0].x, mposition[0].y - 1);
	std::cout << "      ";

	unsigned int remove_size = mposition.size();

	for (unsigned int loop = 0; loop < remove_size; loop++)
	{
		mposition.pop_back();
	}

	mbUFO_Flag = false;
}