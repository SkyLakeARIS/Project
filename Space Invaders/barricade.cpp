#include "Barricade.h"

//�ٸ����̵� ��ǥ ����
void Barricade::SetData()
{
	for (int barri_num = 0; barri_num < 4; barri_num++)
	{
		for (int x = 0; x < 4; x++)
		{
			mposition.emplace_back(2 + (6 * barri_num) + x, 18);
			mposition.emplace_back(2 + (6 * barri_num) + x, 19);
		}
		mposition.emplace_back(2 + (6 * barri_num), 20);
		mposition.emplace_back(5 + (6 * barri_num), 20);
	}
}
//�ٸ����̵� ���
void Barricade::PrintEntity() const
{
	unsigned int barri_num = mposition.size();
	for (unsigned int i = 0; i < barri_num; i++)
	{
		gotoxy(mposition[i].x, mposition[i].y);
		PaintColor(mposition[i].y);
		std::cout << "��";
	}
}
//��, �÷��̾ �� �Ѿ��� �ٸ����̵忡 ���� �ߴ��� 
unsigned int Barricade::OnCollide(int x, int y)
{
	int delete_index = -1;
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		if (x == mposition[i].x && y == mposition[i].y)
		{
			delete_index = i;
		}
	}
	if (delete_index != -1)
	{
		Hit(delete_index);
		return NoPoint;
	}
	return MISS;
}
//�Ѿ˿� �¾����� ��ǥ vector ����
unsigned int Barricade::Hit(unsigned int index)
{
	//���� ��ǥ�� �ε����� ������ �ε������� ���� ����� ���� ���� ���� ����
	if ((mposition.at(index).x == mposition.back().x) && (mposition.at(index).y == mposition.back().y))
	{
		mposition.pop_back();
	}
	else
	{
		//���� ��ǥ�� ������ �ε����̸� �ٷ� ����
		mposition.at(index) = mposition.back();
		mposition.pop_back();
	}
	return NoPoint;
}
//�������� ����
void Barricade::MoveEntity()
{
	//do nothing
}
//�Ѿ��� �߻����� ����
void Barricade::Shooting(std::shared_ptr<IEntity> entity)
{
	//do nothing
}
//���� ��� ������ ���� ���带 ���� ���� �ʱ�ȭ
void Barricade::ClearData()
{
	//������ �����ִ� ������ ����
	unsigned int remain_block = mposition.size();
	if (remain_block > 0)
	{
		for (unsigned int i = 0; i < remain_block; i++)
		{
			mposition.pop_back();
		}
	}
	SetData();
}