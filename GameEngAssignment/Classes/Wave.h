#pragma once

class CWave
{
public:
	CWave();
	~CWave();

	void setWave(int);

	int getNormalMonsters(){ return normal; }
	int getTotalMonsters(){ return normal; }

	void spawnedNormalMonster(){ --normal; }

private:
	int normal;
};

