#pragma once
#include <memory>
#include "lib.h"

__interface IEntity
{
	virtual void SetData() = 0;
	
	virtual void MoveEntity() = 0;
	
	virtual void PrintEntity() const = 0;

	virtual unsigned int OnCollide(int x, int y) = 0;

	virtual unsigned int Hit(unsigned int index) = 0;

	virtual void Shooting(std::shared_ptr<IEntity> entity) = 0;

	virtual eType GetType() const = 0;
};