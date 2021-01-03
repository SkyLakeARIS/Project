#pragma once
#include "IEntity.h"

class Enemy : public IEntity
{
public:
	Enemy()
	{
		SetData();
	}

	enum eEnemy
	{
		Octopus,
		Crab,
		Squid,
		Empty
	};

	enum eDirection
	{
		UP = -1,
		DOWN = 1,
		LEFT = -1,
		RIGHT = 1
	};

	struct Type1 : POS
	{
		eEnemy enemy;
		Type1() = default;
		Type1(int x, int y, eEnemy type) : POS(x, y), enemy(type) {}
	};

	void SetData() override;

	void MoveEntity() override;

	void PrintEntity() const override;

	unsigned int OnCollide(int x, int y) override;

	unsigned int Hit(unsigned int index) override;

	void Shooting(std::shared_ptr<IEntity> entity) override;

	void CreateBullet();

	void DeleteBullet(int index);

	void ControlEnemyDirection();

	void FindCanShootEnemy();
	
	bool IsEnemyGoToEndLine() const;

	void ClearData();

	eType GetType() const override
	{
		return eType::ENEMY;
	}

	unsigned int GetEnemySize()
	{
		return mEnemy_Size;
	}

private:
	POS mbase;
	std::vector<Type1> mposition;
	std::vector<POS> mbullet;
	std::vector<Type1*> mLowLine;
	eDirection mLeftRight_Flag = RIGHT;
	bool mbDown_Flag = false;
	unsigned int mEnemy_Size;
};