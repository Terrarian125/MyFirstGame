#pragma once
// 超簡単球コライダーclass
class SphereCollider
{
public:
	SphereCollider(float radius);
	float GetRadius() { return (radius_); }

private:
	float radius_;//半径
};