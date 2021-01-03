#include <cstdlib>
#include <ctime>
#include "Enemy.h"

//�� ��ƼƼ ���� ����
void Enemy::SetData()
{
	//Squid ���� �ʱ�ȭ
	for (int x = 0; x < 9; x++)
	{
		mposition.emplace_back(4 + (x * 2), 3, Squid);
	}
	//Crab ���� �ʱ�ȭ
	for (int y = 1; y <= 2; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			mposition.emplace_back(4 + (x * 2), 4 + ((y * 2) - 1), Crab);
		}
	}
	//Octopus ���� �ʱ�ȭ
	for (int y = 1; y <= 2; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			mposition.emplace_back(4 + (x * 2), 8 + ((y * 2) - 1), Octopus);
		}
	}
	//������
	mbase.x = mposition[0].x;
	mbase.y = mposition[0].y;
	//���� ���� ���� ����
	mEnemy_Size = mposition.size();
	//�Ѿ��� �� �� �ִ� ���� ã��
	FindCanShootEnemy();
}
//���� ���⿡ ���� �� ��ǥ �̵�
void Enemy::MoveEntity()
{
	//down_flag�� true�̸� �Ʒ��ٷ� �̵�
	if (mbDown_Flag == true)
	{
		for (unsigned int i = 0; i < mEnemy_Size; i++)
		{
			Remove_FootPrint(mposition[i].x, mposition[i].y);
			mposition[i].y++;
		}
		mbase.y++;
		mbDown_Flag = false;
	}
	//�׷��� ������ �¿� �̵��� ���
	else
	{
		if (mLeftRight_Flag == RIGHT)
		{
			for (unsigned int i = 0; i < mEnemy_Size; i++)
			{
				Remove_FootPrint(mposition[i].x, mposition[i].y);
				mposition[i].x++;
			}
			mbase.x++;
		}
		else
		{
			for (unsigned int i = 0; i < mEnemy_Size; i++)
			{
				Remove_FootPrint(mposition[i].x, mposition[i].y);
				mposition[i].x--;
			}
			mbase.x--;
		}
		//�̵� �� ��, ��, �Ʒ� �̵��� ������
		ControlEnemyDirection();
	}
	//�߻�� �Ѿ� ��ǥ�̵�
	if (mbullet.size() > 0)
	{
		for (unsigned int i = 0; i < mbullet.size(); i++)
		{
			Remove_FootPrint(mbullet[i].x, mbullet[i].y);
			mbullet[i].y++;
		}
	}

}
//���� ���̳� ������ ���� ������� ������ȯ �� ��ĭ �Ʒ��� �̵�
void Enemy::ControlEnemyDirection()
{
	int count = 0;

	for (unsigned int i = 0; i < mEnemy_Size; i++)
	{
		if (mposition[i].x <= 0 || mposition[i].x >= MAP_SIZE - 1)
		{
			++count;
		}
	}
	if (count > 0)
	{
		mbDown_Flag = true;
		if (mLeftRight_Flag == RIGHT)
		{
			mLeftRight_Flag = LEFT;
		}
		else
		{
			mLeftRight_Flag = RIGHT;
		}
	}
}
//�� �׸��� �Լ�
void Enemy::PrintEntity() const
{
	for (unsigned int i = 0; i < mEnemy_Size; i++)
	{
		switch (mposition.at(i).enemy)
		{
		case Octopus:
			gotoxy(mposition.at(i).x, mposition.at(i).y);
			PaintColor(mposition.at(i).y);
			std::cout << "��";
			break;
		case Crab:
			gotoxy(mposition.at(i).x, mposition.at(i).y);
			PaintColor(mposition.at(i).y);
			std::cout << "��";
			break;
		case Squid:
			gotoxy(mposition.at(i).x, mposition.at(i).y);
			PaintColor(mposition.at(i).y);
			std::cout << "��";
			break;
		default:
			//Assert();
			break;
		}
	}

	if (mbullet.size() > 0)
	{
		for (unsigned int i = 0; i < mbullet.size(); i++)
		{
			gotoxy(mbullet[i].x, mbullet[i].y);
			SetColor(YELLOW); std::cout << "��";
		}
	}
}
//�Ѿ� ���� �� ���� �߻��� �Ѿ��� ��� �¾Ҵ��� üũ
void Enemy::Shooting(std::shared_ptr<IEntity> entity)
{
	//�Ѿ� ����
	CreateBullet();

	if (mbullet.size() > 0) {
		for (unsigned int i = 0; i < mbullet.size(); i++)
		{
			//���ڷ� ���� entity�� �Ѿ˿� �¾Ҵ��� üũ
			if (MISS != entity->OnCollide(mbullet[i].x, mbullet[i].y))
			{
				DeleteBullet(i);
			}
			else
			{
				//�� ���� ������ üũ
				if (mbullet[i].y >= MAP_SIZE - 1)
				{
					DeleteBullet(i);
				}
			}
		}
	}
	//���� �ٸ����̵�� �ε�������
	if (entity->GetType() == eType::BARRICADE)
	{
		for (unsigned int i = 0; i < mEnemy_Size; i++)
		{
			entity->OnCollide(mposition[i].x, mposition[i].y);
		}
	}
}
//�Ѿ� ����
void Enemy::DeleteBullet(int index)
{
	//�浹�� �ΰ�ȿ��
	gotoxy(mbullet[index].x, mbullet[index].y);
	std::cout << "��";
	Sleep(50);

	Remove_FootPrint(mbullet[index].x, mbullet[index].y);

	if ((mbullet.at(index).x == mbullet.back().x) && (mbullet.at(index).y == mbullet.back().y))
	{
		mbullet.pop_back();
	}
	else
	{
		mbullet.at(index) = mbullet.back();
		mbullet.pop_back();
	}
}
//�÷��̾ �߻��� �Ѿ˿� ���� �¾Ҵ��� üũ
unsigned int Enemy::OnCollide(int x, int y)
{
	int delete_index = -1;
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		if (x == mposition[i].x && y == mposition[i].y)
		{
			delete_index = i;
		}
	}
	//�ش� �ε����� vector ����
	if (delete_index != -1)
	{
		return Hit(delete_index);
	}
	return MISS;
}
//�Ѿ˿� ���� �� �����ϰ� ���� ��ȯ
unsigned int Enemy::Hit(unsigned int index)
{
	//point ��ȯ��
	eEnemy enemy_type = mposition[index].enemy;

	if ((mposition.at(index).x == mposition.back().x) && (mposition.at(index).y == mposition.back().y))
	{
		mposition.pop_back();
	}
	else
	{
		mposition.at(index) = mposition.back();
		mposition.pop_back();
	}

	//�� �� ����
	mEnemy_Size--;

	//�Ѿ��� �߻� �� �� �ִ� ���� �ٽ� ���
	FindCanShootEnemy();

	//���� ��ȯ
	switch (enemy_type)
	{
	case Octopus:
		return Get_Octopus_Point;
	case Crab:
		return Get_Crab_Point;
	case Squid:
		return Get_Squid_Point;
	default:
		//Assert();
		break;
	}

	return 0;
}
//���� �Ʒ��� �ִ� ������ �Ѿ��� �߻��ϴ� �Լ�
void Enemy::CreateBullet()
{
	srand((unsigned int)time(NULL));

	for (unsigned int i = 0; i < mLowLine.size(); i++)
	{
		//�� �Ѿ��� ������ 5���� ���� �� ����.
		if (mbullet.size() <= 5)
		{
			int shoot = rand() % 30 + 1;
			switch (mLowLine[i]->enemy)
			{
			case Octopus:
				if (shoot > 28)
				{
					mbullet.emplace_back(mLowLine[i]->x, mLowLine[i]->y);
				}
				break;
			case Crab:
				if (shoot > 27)
				{
					mbullet.emplace_back(mLowLine[i]->x, mLowLine[i]->y);
				}
				break;
			case Squid:
				if (shoot > 26)
				{
					mbullet.emplace_back(mLowLine[i]->x, mLowLine[i]->y);
				}
				break;
			default:
				//Assert();
				break;
			}
		}
	}
}
//�Ѿ��� �߻� �� �� �ִ� ���� �Ʒ��� �ִ� ���� ã�� �Լ�.
void Enemy::FindCanShootEnemy()
{
	//���Ҵ�� ���� Vector�� ���.
	if (mLowLine.size() > 0)
	{
		int num = mLowLine.size();
		for (int loop = 0; loop < num; loop++)
		{
			mLowLine.pop_back();
		}
	}

	Type1 FindEnemy;

	for (int x = 0; x < 9; x++)
	{
		FindEnemy.x = mbase.x + (2 * x);
		FindEnemy.y = mbase.y;

		int index = -1;

		for (unsigned int i = 0; i < mEnemy_Size; i++)
		{
			if (FindEnemy.x == mposition[i].x && FindEnemy.y < mposition[i].y)
			{
				FindEnemy.y = mposition[i].y;
				index = i;
			}
		}
		//index���� ����� �ε����� ���� �Ʒ��� �ִ� ���� ��.
		if (index != -1)
		{
			mLowLine.push_back(&mposition[index]);
		}
	}
}
//���� ���� �Ʒ����� �����Դ��� üũ(���ӿ��� ����)
bool Enemy::IsEnemyGoToEndLine() const
{
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		if (mposition[i].x == MAP_SIZE-1 && mposition[i].y == 20)
		{
			return true;
		}
	}
	return false;
}
//���� ��� ������ ���� ���带 ���� ���� �ʱ�ȭ
void Enemy::ClearData()
{
	unsigned int bullet_size = mbullet.size();
	if (bullet_size > 0)
	{
		for (unsigned int i = 0; i < bullet_size; i++)
		{
			DeleteBullet(i);
		}
	}

	SetData();
}