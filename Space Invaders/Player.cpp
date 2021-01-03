#include "Player.h"

//좌표 값 설정
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
//캐릭터 컨트롤
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
//플레이어 캐릭터와 총알 출력
void Player::PrintEntity() const
{
	gotoxy(mposition[0].x, mposition[0].y);
	PaintColor(mposition[0].y);
	std::cout << "A";

	gotoxy(mposition[1].x, mposition[1].y);
	PaintColor(mposition[1].y);
	std::cout << "〓▤〓";
	
	if (mbShooting_Flag == true)
	{
		gotoxy(mbullet.at(0).x, mbullet.at(0).y);
		std::cout << "‡";
	}
}
//플레이어가 적의 총알에 맞았는지 체크
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
//플레이어가 적의 총알에 맞았을 때 처리
unsigned int Player::Hit(unsigned int index)
{
	mLife--;
	
	DrawDestroyPlayer();

	//죽으면 원위치로 돌아감.
	RePosition();

	UpdateInfo();

	return NoPoint;
}
//플레이어가 쏜 총알이 적, 바리케이드에 맞았는지 체크
void Player::Shooting(std::shared_ptr<IEntity> entity)
{
	if (mbShooting_Flag == true)
	{
		unsigned int GetPoint = 0;

		//인자로 받은 entity가 총알에 맞았는지 체크
		GetPoint = entity->OnCollide(mbullet.at(0).x, mbullet.at(0).y);
		if (GetPoint != MISS)
		{
			mScore += GetPoint;

			DeleteBullet();

			UpdateInfo();
		}
		else
		{
			//맵 끝에 갔는지 체크
			if (mbullet.at(0).y <= 0)
			{
				DeleteBullet();
			}
		}
	}
}
//총알 삭제
void Player::DeleteBullet()
{
	//이펙트 효과
	gotoxy(mbullet[0].x, mbullet[0].y);
	std::cout << "※";
	Sleep(50);

	Remove_FootPrint(mbullet.at(0).x, mbullet.at(0).y);
	mbullet.pop_back();
	mbShooting_Flag = false;
}
//바뀐 플레이어 정보를 출력해주는 함수
void Player::UpdateInfo() const
{
	//점수 출력
	gotoxy(27, 11);
	SetColor(BLUE);
	std::cout << mScore;
	//mLife 출력
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
//플레이어가 적 총알에 맞을 때 리스폰 함.
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
//피격시 파괴 효과
void Player::DrawDestroyPlayer() const
{
	for (unsigned int i = 0; i < mposition.size(); i++)
	{
		gotoxy(mposition[i].x, mposition[i].y);
		std::cout << "※";
	}
	Sleep(60);
}
//적을 모두 잡으면 다음 라운드를 위해 정보 초기화
void Player::ClearData()
{
	if (mbShooting_Flag != false)  //Assert(mbShooting_Flag);
	{
		DeleteBullet();
	}
	RePosition();
}