#include "PlayerController.h"

PlayerController::PlayerController(Car * car, int controllerID)
{
	PossessCar(car);
}

void PlayerController::Update(float deltaTime)
{
	if (GetAsyncKeyState('W') & 0x8000) { _car->MoveForward(deltaTime, 1.0f); }
	if (GetAsyncKeyState('S') & 0x8000) { _car->MoveForward(deltaTime, -1.0f); }
	if (GetAsyncKeyState('A') & 0x8000) { _car->MoveRight(deltaTime, -1.0f); }
	if (GetAsyncKeyState('D') & 0x8000) { _car->MoveRight(deltaTime, 1.0f); }
}

void PlayerController::PossessCar(Car * car)
{
	car = _car;
}

void PlayerController::UnPossessCar()
{
	_car = nullptr;
}
