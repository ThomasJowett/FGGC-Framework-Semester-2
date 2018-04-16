#pragma once
class iInput
{
	virtual void MoveRight(float deltaTime, float scale) = 0;
	virtual void MoveForward(float deltaTime, float scale) = 0;

	virtual void Yaw(float deltaTime, float scale) = 0;
	virtual void Pitch(float deltaTime, float scale) = 0;
	virtual void Roll(float deltaTime, float scale) = 0;
};