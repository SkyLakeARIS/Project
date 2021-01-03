#include "Barricade.h"

//바리케이드 좌표 설정
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
//바리케이드 출력
void Barricade::PrintEntity() const
{
	unsigned int barri_num = mposition.size();
	for (unsigned int i = 0; i < barri_num; i++)
	{
		gotoxy(mposition[i].x, mposition[i].y);
		PaintColor(mposition[i].y);
		std::cout << "▦";
	}
}
//적, 플레이어가 쏜 총알이 바리케이드에 명중 했는지 
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
//총알에 맞았을때 좌표 vector 삭제
unsigned int Barricade::Hit(unsigned int index)
{
	//맞은 좌표의 인덱스를 마지막 인덱스에서 덮어 씌우고 덮어 씌운 정보 삭제
	if ((mposition.at(index).x == mposition.back().x) && (mposition.at(index).y == mposition.back().y))
	{
		mposition.pop_back();
	}
	else
	{
		//맞은 좌표가 마지막 인덱스이면 바로 삭제
		mposition.at(index) = mposition.back();
		mposition.pop_back();
	}
	return NoPoint;
}
//움직이지 않음
void Barricade::MoveEntity()
{
	//do nothing
}
//총알을 발사하지 않음
void Barricade::Shooting(std::shared_ptr<IEntity> entity)
{
	//do nothing
}
//적을 모두 잡으면 다음 라운드를 위해 정보 초기화
void Barricade::ClearData()
{
	//기존에 남아있던 데이터 삭제
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