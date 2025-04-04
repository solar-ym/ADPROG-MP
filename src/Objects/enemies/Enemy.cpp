#include "Enemy.h"

Enemy :: Enemy () {}

Enemy :: Enemy(string name, string textureName) : Entity(name) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);

    entSprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});
    
    if (name == "Geygar") {
        cout << "Giving geygar aattack comp" << endl;
        attackSprite = new EntityAttack(this, "ATTACK_geygar.png");
        attackSprite->alterTextureRect(IntRect({140, 0}, {10,50})); 

        addComponent(new AttackComp("AttackComp", attackSprite));
    }
}

void Enemy :: addComponent(Component* newComp) {
    newComp->attachComponent(this);
    comps.push_back(newComp);
}

void Enemy :: kill() {
    isDying = true;
    getMoveComp()->setMovingBool(false);
}

void Enemy :: squash() {
    squashed = true;
    getMoveComp()->setMovingBool(false);
}

// POSITION

void Enemy :: setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
}
int Enemy :: getTileX() {
    x = (entSprite->getPosition().x / TILE_SIZE);
    return x;
}
int Enemy :: getTileY() {
    y = (entSprite->getPosition().y / TILE_SIZE) - SKY_HEIGHT;
    return y;
}

void Enemy :: initialize() {}

void Enemy :: update() {
    if (getAtkComp() != nullptr) {
        if (getAtkComp()->getExtendBool(0)) getAtkComp()->extend();
        if (getAtkComp()->getExtendBool(1)) getAtkComp()->unextend();
    }

    getAnimComp()->animate();
    if (!ghostMode && !isAttacking)
        getMoveComp()->move();
    if (getAtkComp() != nullptr && !(getAtkComp()->isVisible()))
        isAttacking = false;
}

void Enemy :: draw(RenderWindow *window) {
    window->draw(*entSprite);
    if (attackSprite != nullptr && attackSprite->getVisibility())
        attackSprite->draw(window);
}

Sprite* Enemy :: getSprite() {
    return entSprite;
}

ColliderComp* Enemy :: getColliderComp() {
    for(Component* cmp: comps) {
        if(cmp->getName() == "ColliderComp") {
            ColliderComp* col = (ColliderComp*)cmp;
            return col;
        }
    }
        return nullptr;
}

AnimationComp* Enemy :: getAnimComp() {
    for(Component* cmp: comps) {
        if(cmp->getName() == "AnimationComp") {
            AnimationComp* anim = (AnimationComp*)cmp;
            return anim;
        }
    }
    return nullptr;
}

MovementComp* Enemy :: getMoveComp() {
    for(Component* cmp: comps) {
        if(cmp->getName() == "MoveComp") {
            MovementComp* mov = (MovementComp*)cmp;
            return mov;
        }
    }
    cout << "[ERROR] Failed to get [ENEMY: " << getName() << "] Movement Comp." << endl;
    return nullptr;
}

AttackComp* Enemy :: getAtkComp() {
    for(Component* cmp: comps) {
        if(cmp->getName() == "AttackComp") {
            AttackComp* atk = (AttackComp*)cmp;
            return atk;
        }
    }
    // cout << "[ERROR] Failed to get [ENEMY: " << getName() << "] Attack Comp." << endl;
    return nullptr;
}

EnemyBehaviorComp* Enemy :: behave() {
    for(Component* cmp: comps) {
        if(cmp->getName() == "BehaviorComp") {
            EnemyBehaviorComp* beh = (EnemyBehaviorComp*)cmp;
            return beh;
        }
    }
    return nullptr;
}

// STATES

bool Enemy :: getIsDying() {
    return isDying;
}
void Enemy :: setIsDying(bool value) {
    isDying = value;
}
bool Enemy :: getIsDead() {
    return isDead;
}
void Enemy :: setIsDead(bool value) {
    isDead = value;
}
bool Enemy :: getIsSquashed() {
    return squashed;
}
void Enemy :: setIsSquashed(bool value) {
    squashed = value;
}
bool Enemy :: getGhostMode() {
    return ghostMode;
}
void Enemy :: setGhostMode(bool value) {
    ghostMode = value;
}
void Enemy :: setIsAttacking(bool value) {
    isAttacking = value;
}
bool Enemy :: getIsAttacking() {
    return isAttacking;
}