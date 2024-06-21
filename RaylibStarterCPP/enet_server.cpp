#include "enet_server.h"

ENet_Server::ENet_Server() {
	newObject->Initialize();
	if (newObject->CreateServer()) std::cout << "Server created successfully!\n";
}

ENet_Server::~ENet_Server() {
	newObject->Disconnect();
	delete newObject;
}

void ENet_Server::SendPacket(GameState updatedState) {
	newObject->SendPacket(&updatedState, sizeof(GameState));
}

bool ENet_Server::ReceivePacket(GameState* newState) {
	if (newObject->ReceivePackets(newState) == true) return true;
	else return false;
}
