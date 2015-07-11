#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include <string>

using namespace cocos2d;
using namespace std;

enum weaponType
{
	PISTOL,
	SHOTGUN,
	MACHINE_GUN,
	TOTAL
};

class CWeapon
{

protected:
	CWeapon();

public:

	static CWeapon* getInstance()
	{
		return &theWeapon;
	}

	void Init();

	void SetWeaponType(weaponType type);
	weaponType GetWeaponType();

	void SetCurrentAmmo(int currentAmmo);
	int GetCurrentAmmo();

	void SetMaxAmmo(int maxAmmo);
	int GetMaxAmmo();

	void SetFirerate(float firerate);
	float GetFirerate();

	void SetReloadtime(float reloadtime);
	float GetReloadtime();

	void SwitchWeaponType();

	void SetActive(bool active);
	bool GetActive();

	void update(float dt);

private:

	static CWeapon theWeapon;

	float xPos;
	float yPos;

	float fireRate;
	float reloadTime;

	int currentAmmo;
	int maxAmmo;
	
	bool isActive;

	weaponType type;
};

#endif // __WEAPON_H__