#include "Weapon.h"

USING_NS_CC;

CWeapon CWeapon::theWeapon;

CWeapon::CWeapon()
{
	currentAmmo = 0;
	maxAmmo = 100;
	fireRate = 10;
	reloadTime = 0;
}

void CWeapon::Init()
{
	//SetWeaponSprite("weapon.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*xPos = origin.x + visibleSize.width / 2;
	yPos = origin.y + visibleSize.height / 2;
	weaponSprite->setPosition(xPos, yPos);
	weaponSprite->setScale(1.5f);*/
	currentAmmo = 0;
	maxAmmo = 100;
	fireRate = 1.0f;
	reloadTime = 0;
	type = weaponType::PISTOL;
	isActive = false;
	
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
	this->fireRate = firerate;
}

float CWeapon::GetFirerate()
{
	return this->fireRate;
}

void CWeapon::SetReloadtime(float reloadtime)
{
	this->reloadTime = reloadtime;
}

float CWeapon::GetReloadtime()
{
	return this->reloadTime;
}

void CWeapon::SwitchWeaponType()
{
	if (this->type == weaponType::PISTOL)
	{
		this->type = weaponType::MACHINE_GUN;
	}
	else if (this->type == weaponType::MACHINE_GUN)
	{
		this->type = weaponType::SHOTGUN;
	}
	else if (this->type == weaponType::SHOTGUN)
	{
		this->type = weaponType::SHOTGUN;
	}
}

void CWeapon::SetActive(bool active)
{
	this->isActive = active;
}

bool CWeapon::GetActive()
{
	return this->isActive;
}

void CWeapon::update(float dt)
{
	fireRate -= dt;
}