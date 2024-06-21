#pragma once
#include "enet_wrapper.h"

class ENet_Client {
public:
	ENetWrapper* newObject;
	ENet_Client();
	~ENet_Client();
	void SendPacket(GameState updatedState);
	bool ReceivePacket(GameState* newState);
};