#pragma once
// 超簡単球コライダーclass
class SphereCollider
{
public:
	SphereCollider(float radius);
	float GetRadius() { return (radius_); }//インライン宣言
	//bool isHit(SphereCollider* pTarget, float thisX, float thisY, float thisZ, float targetX, float targetY, float targetZ);
private:
	float radius_;//半径
};