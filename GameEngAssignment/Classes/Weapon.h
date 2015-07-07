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
public:

	CWeapon();
	~CWeapon();

	void Init();

	void SetWeaponSprite(string filename);
	Sprite* getWeaponSprite();

	void SetWeaponType(weaponType type);
	weaponType GetWeaponType();

	void SetCurrentAmmo(int currentAmmo);
	int GetCurrentAmmo();

	void SetMaxAmmo(int maxAmmo);
	int GetMaxAmmo();

	void SetFirerate(float firerate);
	int GetFirerate();

	void SetReloadtime(float reloadtime);
	float GetReloadtime();

	void weaponFiring();

	void update(float dt);

private:
	Sprite* weaponSprite;

	float xPos;
	float yPos;

	float firerate;
	float reloadtime;

	int currentAmmo;
	int maxAmmo;

	int weaponSelect;
	int weaponSwitch[3];

	weaponType type;
};

#endif // __WEAPON_H__