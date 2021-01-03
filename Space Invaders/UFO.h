#pragma once
#include "IEntity.h"

class UFO :	public IEntity
{
public:
	UFO() {}

	enum eDirection
	{
		UP = -1,
		DOWN = 1,
		LEFT = -1,
		RIGHT = 1,
	};

	void SetData() override;

	void MoveEntity() override;

	bool CheckEntityPOS(int x, int y);

	void PrintEntity() const override;

	unsigned int OnCollide(int x, int y) override;

	unsigned int Hit(unsigned int index) override;

	void Shooting(std::shared_ptr<IEntity> entity) override;

	void GenerateUFO();

	eType GetType() const override
	{
		return eType::UFO;
	}

	void DestroyUFO();

private:
	std::vector<POS> mposition;
	bool mbUFO_Flag = false;
	eDirection mMoveDir;
};