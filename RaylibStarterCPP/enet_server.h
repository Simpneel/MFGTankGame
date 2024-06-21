#pragma once
#include "enet_wrapper.h"

class ENet_Server {
public:
	class ENetWrapper* newObject;
	ENet_Server();
	~ENet_Server();
	void SendPacket(GameState updatedState);
	bool ReceivePacket(GameState* newState);
};