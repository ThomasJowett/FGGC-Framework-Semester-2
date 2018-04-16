#pragma once
#include "Car.h"

class PlayerController
{
public:
	PlayerController(Car* car, int controllerID);
	~PlayerController() { UnPossessCar(); }
	void Update(float deltaTime);
	void PossessCar(Car* car);
	void UnPossessCar();
private:
	Car* _car;
	int _controllerID;
};