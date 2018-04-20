#include "PlayerController.h"

PlayerController::PlayerController(Car * car, int controllerID)
{
	PossessCar(car);
}

void PlayerController::Update(float deltaTime)
{
	if (_car)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000) { _car->MoveForward(deltaTime, 1.0f); }
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) { _car->MoveForward(deltaTime, -1.0f); }
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { _car->Yaw(deltaTime, 1.0f); }
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) { _car->Yaw(deltaTime, -1.0f); }
	}
}

void PlayerController::PossessCar(Car * car)
{
	_car = car;
}

void PlayerController::UnPossessCar()
{
	_car = nullptr;
}
