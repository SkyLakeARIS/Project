#pragma once
#include "IEntity.h"

class Player : public IEntity
{
public:
	Player()
	{
		SetData();
	}

	void SetData() override;

	void MoveEntity() override;

	void PrintEntity() const override;

	unsigned int OnCollide(int x, int y) override;

	unsigned int Hit(unsigned int index) override;

	void Shooting(std::shared_ptr<IEntity> entity) override;

	eType GetType() const override
	{
		return eType::PLAYER;
	}

	int GetLife() const
	{
		return mLife;
	}

	unsigned int GetScore() const
	{ 
		return mScore;
	}

	void DeleteBullet();

	void UpdateInfo() const;

	void RePosition();

	void DrawDestroyPlayer() const;

	void ClearData();

private:
	std::vector<POS> mposition;
	std::vector<POS> mbullet;
	int mLife;
	unsigned int mScore = 0;
	bool mbShooting_Flag = false;
};