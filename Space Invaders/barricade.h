#pragma once
#include"IEntity.h"

class Barricade : public IEntity
{
public:
	Barricade()
	{
		SetData();
	}

	void SetData() override;

	void MoveEntity() override;

	void Shooting(std::shared_ptr<IEntity> entity) override;

	void PrintEntity() const override;

	unsigned int OnCollide(int x, int y) override;

	unsigned int Hit(unsigned int index) override;

	void ClearData();

	eType GetType() const override
	{
		return eType::BARRICADE;
	}

private:
	std::vector<POS> mposition;
};