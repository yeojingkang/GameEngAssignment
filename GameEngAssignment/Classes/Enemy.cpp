#include "Enemy.h"

USING_NS_CC;

CEnemy::CEnemy() :
typeName(""),
hp(0),
bounty(0),
thePlayer(NULL)
{
}
CEnemy::~CEnemy()
{
	thePlayer = NULL;
}

CEnemy* CEnemy::create()
{
	CEnemy* eSprite = new CEnemy();

	if (eSprite->initWithFile("enemy.png"))
	{
		eSprite->autorelease();
		return eSprite;
	}

	CC_SAFE_DELETE(eSprite);
	return NULL;
}

void CEnemy::Init(CEnemy* eSprite, cocos2d::Vec2 playerPos, CEnemyType type, CPlayer* player){
	
	if (CCRANDOM_0_1() > 0.5f)
		position = Vec2(round(CCRANDOM_0_1()) * 1280, CCRANDOM_0_1() * 720);
	else
		position = Vec2(CCRANDOM_0_1() * 1280, round(CCRANDOM_0_1()) * 720);

	direction = (playerPos - position).getNormalized();

	//theSprite = cocos2d::Sprite::create("enemy.png");
	eSprite->setPosition(position);
	eSprite->setScale(1.0f);
	eSprite->setTag(ENEMY_TAG);
	eSprite->setColor(type.getColor());

	auto enemyBody = PhysicsBody::createBox(eSprite->getContentSize());

	//enemyBody->setDynamic(false);
	enemyBody->setGravityEnable(false);
	//enemyBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	//enemyBody->setCategoryBitmask(BULLET_COLLISION_BITMASK);
	enemyBody->setContactTestBitmask(0xFFFFFFFF);

	eSprite->setPhysicsBody(enemyBody);

	this->typeName = type.getName();
	this->thePlayer = player;

	this->hp = type.getHP();
	this->bounty = type.getBounty();
	this->speed = type.getSpeed();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CEnemy::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void CEnemy::Update(float dt, cocos2d::Vec2 playerPos){
	
}

void CEnemy::finishedMoving(Ref *pSender){
	CEnemy *eSprite = (CEnemy *)pSender;
	this->MoveToPlayer(eSprite);
}

void CEnemy::MoveToPlayer(CEnemy* eSprite)
{
	//float distance = thePlayer->getPlayerSprite()->getPosition().distance(theSprite->getPosition());
	float time = 10 / speed;
	Vec2 targetPosition = eSprite->getPosition() + (thePlayer->getPosition() - eSprite->getPosition()).getNormalized() * 10;

	auto actionMove = MoveTo::create(time, targetPosition);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(CEnemy::finishedMoving, this));
	eSprite->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void CEnemy::Die(){
	thePlayer->AddGold(bounty);
}

//handler for handling collision
bool CEnemy::onContactBegin(PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == BULLET_TAG && nodeB->getTag() == ENEMY_TAG)
		{
			dynamic_cast<CEnemy*>(nodeB)->decreaseHP(50);
			//play enemy ouch sound
			auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

			// play a sound effect, just once.
			audio->playEffect("Sounds/Shot.mp3", false, 1.0f, 1.0f, 1.0f);

			if (dynamic_cast<CEnemy*>(nodeB)->hp <= 0)
			{
				Die();
				nodeB->removeFromParentAndCleanup(false);
			}
		}
		else if (nodeB->getTag() == BULLET_TAG && nodeA->getTag() == ENEMY_TAG)
		{
			dynamic_cast<CEnemy*>(nodeA)->decreaseHP(50);
			//play enemy ouch sound
			auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

			// play a sound effect, just once.
			audio->playEffect("Sounds/Shot.mp3", false, 1.0f, 1.0f, 1.0f);

			if (dynamic_cast<CEnemy*>(nodeA)->hp <= 0)
			{
				Die();
				nodeA->removeFromParentAndCleanup(false);
			}
			
		}
	}
	return true;
}