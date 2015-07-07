#include "Weapon.h"

USING_NS_CC;

CWeapon::CWeapon()
{
	currentAmmo = 0;
	maxAmmo = 0;
	firerate = 0;
	reloadtime = 0;
	weaponSprite = NULL;
}

void CWeapon::Init()
{
	//SetWeaponSprite("weapon.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	xPos = origin.x + visibleSize.width / 2;
	yPos = origin.y + visibleSize.height / 2;
	weaponSprite->setPosition(xPos, yPos);
	weaponSprite->setScale(1.5f);
}

void CWeapon::SetWeaponSprite(string filename)
{
	this->weaponSprite = Sprite::create(filename);
}

Sprite* CWeapon::getWeaponSprite()
{
	return weaponSprite;
}

void CWeapon::SetWeaponType(weaponType type)
{
	this->type = type;
}

weaponType CWeapon::GetWeaponType()
{
	return this->type;
}

void CWeapon::SetCurrentAmmo(int currentAmmo)
{
	this->currentAmmo = currentAmmo;
}

int CWeapon::GetCurrentAmmo()
{
	return this->currentAmmo;
}

void CWeapon::SetMaxAmmo(int maxAmmo)
{
	this->maxAmmo = maxAmmo;
}

int CWeapon::GetMaxAmmo()
{
	return this->maxAmmo;
}

void CWeapon::SetFirerate(float firerate)
{
	this->firerate = firerate;
}

int CWeapon::GetFirerate()
{
	return this->firerate;
}

void CWeapon::SetReloadtime(float reloadtime)
{
	this->reloadtime = reloadtime;
}

float CWeapon::GetReloadtime()
{
	return this->reloadtime;
}

void CWeapon::weaponFiring()
{
	if (weaponSelect == weaponType::PISTOL)
	{
		firerate = 5;
	}
	else if (weaponSelect == weaponType::SHOTGUN)
	{
		firerate = 3;
	}
	else if (weaponSelect == weaponType::MACHINE_GUN)
	{
		firerate = 100;
	}
}

void CWeapon::update(float dt)
{
	if (weaponSelect == 1)
	{
		weaponType::PISTOL;
	}
	else if (weaponSelect == 2)
	{
		weaponType::SHOTGUN;
	}
	else if (weaponSelect == 3)
	{
		weaponType::MACHINE_GUN;
	}
}