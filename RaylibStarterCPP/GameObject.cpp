#include "GameObject.h"
#include <algorithm>

using Vec3 = MathClasses::Vector3;
using Mat3 = MathClasses::Matrix3;

GameObject::GameObject()
{
	Parent = nullptr;
	LocalPosition = Vec3(0, 0, 1);
	LocalRotation = 0.0f;
	LocalScale = Vec3(1, 1, 1);
}

void GameObject::Update(float deltaTime)
{
	OnUpdate(deltaTime);
}

void GameObject::Draw()
{
	OnDraw();
}

void GameObject::OnUpdate(float deltaTime)
{
}

void GameObject::OnDraw()
{
}

void GameObject::SetParent(GameObject* newParent)
{
	if (Parent != nullptr) {
		auto findIt = std::find(Parent->Children.begin(), Parent->Children.end(), this);
		if (findIt != Parent->Children.end()) {
			Parent->Children.erase(findIt);
			Parent = nullptr;
		}
	}
	if (newParent != nullptr) {
		Parent = newParent;
		Parent->Children.push_back(this);
	}
}

GameObject* GameObject::GetParent()
{
	return Parent;
}

const GameObject* GameObject::GetParent() const
{
	return Parent;
}

GameObject* GameObject::GetChild(size_t childIndex)
{
	return Children[childIndex];
}

const GameObject* GameObject::GetChild(size_t childIndex) const {
	return Children[childIndex];
}

Vec3 GameObject::GetLocalPosition() const
{
	return LocalPosition;
}

void GameObject::SetLocalPosition(Vec3 newPosition)
{
	LocalPosition = newPosition;
}

void GameObject::SetLocalPosition(float x, float y)
{
	LocalPosition.x = x;
	LocalPosition.y = y;
}

float GameObject::GetLocalRotation() const
{
	return LocalRotation;
}

void GameObject::SetLocalRotation(float newRotation)
{
	LocalRotation = newRotation;
}

Vec3 GameObject::GetLocalScale() const
{
	return LocalScale;
}

void GameObject::SetLocalScale(Vec3 newScale)
{
	LocalScale = newScale;
}

void GameObject::SetLocalScale(float x, float y)
{
	LocalScale.x = x;
	LocalScale.y = y;
}

Mat3 GameObject::GetLocalMatrix() const
{
	return Mat3::MakeTranslation(LocalPosition) *
		Mat3::MakeRotateZ(LocalRotation) *
		Mat3::MakeScale(LocalScale.x, LocalScale.y);
}

Mat3 GameObject::GetWorldMatrix() const
{
	if (Parent == nullptr) return GetLocalMatrix();

	else return Parent->GetWorldMatrix() * GetLocalMatrix();
}

Vec3 GameObject::GetWorldPosition() const
{
	Mat3 worldMat = GetWorldMatrix();
	return Vec3(worldMat.m7, worldMat.m8, worldMat.m9);
}

float GameObject::GetWorldRotation() const
{
	Vec3 fwd = GetForward();
	return atan2(fwd.x, fwd.y);
}

Vec3 GameObject::GetWorldScale() const
{
	Mat3 myTransform = GetWorldMatrix();
	return Vec3(Vec3(myTransform.m1, myTransform.m2, 0).Magnitude(),
		Vec3(myTransform.m4, myTransform.m5, 0).Magnitude(),		1.0f);
}

Vec3 GameObject::GetForward() const
{
	auto mat = GetWorldMatrix();
	return Vec3(mat.m1, mat.m2, mat.m3);
}

void GameObject::Translate(float x, float y)
{
	LocalPosition = LocalPosition + Vec3(x, y, 0);
}

void GameObject::Translate(MathClasses::Vector3 translation)
{
	LocalPosition = LocalPosition + translation;
}

void GameObject::Rotate(float rad)
{
	LocalRotation += rad;
}

void GameObject::Scale(float x, float y)
{
	LocalScale = LocalScale + Vec3(x, y, 1);
}

void GameObject::Scale(MathClasses::Vector3 scalar)
{
	LocalScale = LocalScale + scalar;
}

