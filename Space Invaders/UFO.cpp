#include <cstdlib>
#include <ctime>
#include "UFO.h"

//맞는 부분만 좌표설정
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
//UFO를 방향에 따라 이동
void UFO::MoveEntity()
{
	if (mbUFO_Flag == true)
	{
		// << 방향 이동
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
		// >> 방향 이동
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
		//mbUFO_Flag가 false이면 생성
		GenerateUFO();
	}
}
//UFO가 반대편으로 갔는지 확인
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
	//mbUFO_Flag가 false이므로 데이터 삭제
	DestroyUFO();

	return false;
}
//UFO 출력
void UFO::PrintEntity() const
{
	if (mbUFO_Flag == true)
	{
		gotoxy(mposition.at(0).x, mposition.at(0).y - 1);
		PaintColor(mposition.at(0).y);
		std::cout << "／Ａ＼";
		gotoxy(mposition.at(0).x, mposition.at(0).y);
		PaintColor(mposition.at(0).y);
		std::cout << "☜♨☞";
	}
}
//UFO 생성
void UFO::GenerateUFO()
{
	srand((unsigned int)time(NULL));
	int is_create = rand() % 100;

	//1~30의 숫자가 나오고 mbUFO_Flag가 false인 상태일 때 UFO생성
	if (mbUFO_Flag == false && (2 > is_create || 97 < is_create))
	{
		mbUFO_Flag = true;
		mMoveDir = LEFT;
		//iscreate가 2이하이면 오른쪽->왼쪽 이동  98이상이면 왼쪽 -> 오른쪽 
		if (is_create > 97)
		{
			mMoveDir = RIGHT;
		}
		SetData();
	}
}
//UFO가 플레이어 총알로부터 맞았는지 확인하는 함수
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
//피격시 파괴 효과 및 데이터 삭제
unsigned int UFO::Hit(unsigned int index)
{
	SetColor(DARK_RED);
	gotoxy(mposition[0].x, mposition[0].y);
	std::cout << "※※※";
	gotoxy(mposition[0].x, mposition[0].y-1);
	std::cout << "※※※";

	Sleep(50);

	gotoxy(mposition[0].x, mposition[0].y);
	SetColor(YELLOW);
	std::cout << " +300 ";

	Sleep(100);

	DestroyUFO();

	return Get_UFO_Point;
}
//총알을 발사하지 않음
void UFO::Shooting(std::shared_ptr<IEntity> entity)
{
	//do nothing
}
//UFO 삭제
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