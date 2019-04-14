#pragma once
class AIAbility
{
public:
	unsigned char unknown[8];
	unsigned short ability;
	unsigned short targetType;
	int pointer;
	AIAbility();
	~AIAbility();
};

