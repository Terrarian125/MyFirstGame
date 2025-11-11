#include "GameObject.h"
#include "SphereCollider.h"
#include <Windows.h>

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const string& name)
	: pParent_(parent), objectName_(name), isDead_(false)
{
	if (parent != nullptr)
	{
		transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{

}

void GameObject::DrawSub()
{
//自分と子オブジェクトを描画
	Draw();
	for (auto child : childList_) {
		child->DrawSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end(); ) 
	{
		if ((*itr)->isDead_) 
		{
			(*itr)->ReleaseSub();
			delete (*itr);
			itr = childList_.erase(itr);
		}
		else 
		{
			++itr;
		}
	}
}

void GameObject::UpdateSub()
{
	transform_.Calculation();
	this->Update();

	RoundRobin(this);
	for (auto child : childList_) 
	{
		child->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end(); )
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			delete (*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void GameObject::ReleaseSub()
{
	this->Release();//自分を解放
	for (auto child : childList_) {
		child->ReleaseSub();
	}
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_ = { x, y, z };
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindChildObject(const string& name)
{
	if (this->objectName_ == name)
	{
		return this;//自分が探されてた
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* result = child->FindChildObject(name);
			if (result != nullptr)
			{
				return result;//見つかった
			}
		}
		return nullptr;//見つからなかった
	}
}

GameObject* GameObject::FindObject(const string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(name);
	return result;
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	//this->pCollider_とpTarget->pCollider_の当たり判定を行う
	// ⓪閾値＝お互いの半径+半径
	float thisR = this->pCollider_->GetRadius();
	float tgrR = pTarget->pCollider_->GetRadius();
	float thre = (thisR + tgrR) * (thisR + tgrR);
	//①２つのコライダーの距離計算を行う
	XMFLOAT3 thisP = this->transform_.position_;
	XMFLOAT3 tgrP = pTarget->transform_.position_;
	float dist = (thisP.x - tgrP.x) * (thisP.x - tgrP.x)
				+  (thisP.y - tgrP.y) * (thisP.y - tgrP.y)
				+  (thisP.z - tgrP.z) * (thisP.z - tgrP.z);
	//②コライダーどうしが交差したら

	if (dist <= thre) {
		//当たり判定成立
		this->onCollision(pTarget);
		pTarget->onCollision(this);
		//MessageBoxA(0, "ぶつかった", "Collider", MB_OK);
	}

}



void GameObject::RoundRobin(GameObject* pTarget)
{
	//①自分にコライダーがなかったらreturn
	if (pCollider_ == nullptr) 
		return;
	//②自分とターゲット自体のコライダーの当たり判定
	if(pTarget->pCollider_ != nullptr)
		Collision(pTarget);
	//③再帰的な奴で、ターゲットの子オブジェクトを当たり判定してく
	for (auto itr : pTarget->childList_) {
		RoundRobin(itr);
	}
}
