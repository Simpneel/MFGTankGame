#pragma once
#include <vector>
#include "Matrix3.h"
#include "Vector3.h"

class GameObject {
protected:
	MathClasses::Vector3 LocalPosition;
	float LocalRotation;
	MathClasses::Vector3 LocalScale;
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw();

	GameObject* Parent;
	std::vector<GameObject*> Children;
public:
	GameObject();
	void Update(float deltaTime);
	void Draw();

	void SetParent(GameObject* newParent);
	GameObject* GetParent();
	const GameObject* GetParent() const;

	GameObject* GetChild(size_t childIndex);
	const GameObject* GetChild(size_t childIndex) const;

	MathClasses::Vector3 GetLocalPosition() const;
	void SetLocalPosition(MathClasses::Vector3 newPosition);
	void SetLocalPosition(float x, float y);

	MathClasses::Vector3 GetWorldPosition() const;

	float GetLocalRotation() const;
	void SetLocalRotation(float newRotation);

	float GetWorldRotation() const;

	MathClasses::Vector3 GetLocalScale() const;
	void SetLocalScale(MathClasses::Vector3 newScale);
	void SetLocalScale(float x, float y);

	MathClasses::Vector3 GetWorldScale() const;

	MathClasses::Vector3 GetForward() const;

	MathClasses::Matrix3 GetLocalMatrix() const;
	MathClasses::Matrix3 GetWorldMatrix() const;

	void Translate(float x, float y);
	void Translate(MathClasses::Vector3 translation);

	void Rotate(float rad);

	void Scale(float x, float y);
	void Scale(MathClasses::Vector3 scalar);
};