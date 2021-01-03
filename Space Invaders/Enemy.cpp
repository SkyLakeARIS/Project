#include <cstdlib>
#include <ctime>
#include "Enemy.h"

//적 엔티티 정보 설정
void Enemy::SetData()
{
	//Squid 라인 초기화
	for (int x = 0; x < 9; x++)
	{
		mposition.emplace_back(4 + (x * 2), 3, Squid);
	}
	//Crab 라인 초기화
	for (int y = 1; y <= 2; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			mposition.emplace_back(4 + (x * 2), 4 + ((y * 2) - 1), Crab);
		}
	}
	//Octopus 라인 초기화
	for (int y = 1; y <= 2; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			mposition.emplace_back(4 + (x * 2), 8 + ((y * 2) - 1), Octopus);
		}
	}
	//기준점
	mbase.x = mposition[0].x;
	mbase.y = mposition[0].y;
	//현재 적의 수를 저장
	mEnemy_Size = mposition.size();
	//총알을 쏠 수 있는 적을 찾음
	FindCanShootEnemy();
}
//현재 방향에 따라서 적 좌표 이동
void Enemy::MoveEntity()
{
	//down_flag가 true이면 아래줄로 이동
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
	//그렇지 않으면 좌우 이동을 계속
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
		//이동 후 좌, 우, 아래 이동을 설정함
		ControlEnemyDirection();
	}
	//발사된 총알 좌표이동
	if (mbullet.size() > 0)
	{
		for (unsigned int i = 0; i < mbullet.size(); i++)
		{
			Remove_FootPrint(mbullet[i].x, mbullet[i].y);
			mbullet[i].y++;
		}
	}

}
//왼쪽 벽이나 오른쪽 벽에 닿았을때 방향전환 및 한칸 아래로 이동
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
//적 그리기 함수
void Enemy::PrintEntity() const
{
	for (unsigned int i = 0; i < mEnemy_Size; i++)
	{
		switch (mposition.at(i).enemy)
		{
		case Octopus:
			gotoxy(mposition.at(i).x, mposition.at(i).y);
			PaintColor(mposition.at(i).y);
			std::cout << "♧";
			break;
		case Crab:
			gotoxy(mposition.at(i).x, mposition.at(i).y);
			PaintColor(mposition.at(i).y);
			std::cout << "ㆄ";
			break;
		case Squid:
			gotoxy(mposition.at(i).x, mposition.at(i).y);
			PaintColor(mposition.at(i).y);
			std::cout << "♨";
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
			SetColor(YELLOW); std::cout << "§";
		}
	}
}
//총알 생성 및 적이 발사한 총알이 어디에 맞았는지 체크
void Enemy::Shooting(std::shared_ptr<IEntity> entity)
{
	//총알 생성
	CreateBullet();

	if (mbullet.size() > 0) {
		for (unsigned int i = 0; i < mbullet.size(); i++)
		{
			//인자로 받은 entity가 총알에 맞았는지 체크
			if (MISS != entity->OnCollide(mbullet[i].x, mbullet[i].y))
			{
				DeleteBullet(i);
			}
			else
			{
				//맵 끝에 갔는지 체크
				if (mbullet[i].y >= MAP_SIZE - 1)
				{
					DeleteBullet(i);
				}
			}
		}
	}
	//적이 바리케이드와 부딪혔는지
	if (entity->GetType() == eType::BARRICADE)
	{
		for (unsigned int i = 0; i < mEnemy_Size; i++)
		{
			entity->OnCollide(mposition[i].x, mposition[i].y);
		}
	}
}
//총알 제거
void Enemy::DeleteBullet(int index)
{
	//충돌시 부과효과
	gotoxy(mbullet[index].x, mbullet[index].y);
	std::cout << "※";
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
//플레이어가 발사한 총알에 적이 맞았는지 체크
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
	//해당 인덱스의 vector 삭제
	if (delete_index != -1)
	{
		return Hit(delete_index);
	}
	return MISS;
}
//총알에 맞은 적 삭제하고 점수 반환
unsigned int Enemy::Hit(unsigned int index)
{
	//point 반환용
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

	//적 수 감소
	mEnemy_Size--;

	//총알을 발사 할 수 있는 적을 다시 계산
	FindCanShootEnemy();

	//점수 반환
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
//제일 아래에 있는 적들이 총알을 발사하는 함수
void Enemy::CreateBullet()
{
	srand((unsigned int)time(NULL));

	for (unsigned int i = 0; i < mLowLine.size(); i++)
	{
		//적 총알의 개수는 5개를 넘을 수 없음.
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
//총알을 발사 할 수 있는 제일 아래에 있는 적을 찾는 함수.
void Enemy::FindCanShootEnemy()
{
	//재할당시 이전 Vector는 비움.
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
		//index값에 저장된 인덱스가 제일 아래에 있는 적이 됨.
		if (index != -1)
		{
			mLowLine.push_back(&mposition[index]);
		}
	}
}
//적이 가장 아래까지 내려왔는지 체크(게임오버 지점)
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
//적이 모두 잡히면 다음 라운드를 위해 정보 초기화
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