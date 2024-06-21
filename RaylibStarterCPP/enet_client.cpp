#include "enet_client.h"

ENet_Client::ENet_Client() {
	newObject->Initialize();
	if (newObject->CreateClient()) std::cout << "Client creation successful!\n";
	if (newObject->Connect("192.168.56.1", (uint16_t*)2331)) std::cout << "Connection to default gateway successful!\n";
}

ENet_Client::~ENet_Client() {
	newObject->Disconnect();
	delete newObject;
}

void ENet_Client::SendPacket(GameState updatedState) {
	newObject->SendPacket(&updatedState, sizeof(GameState));
}

bool ENet_Client::ReceivePacket(GameState* newState) {
	if (newObject->ReceivePackets(newState) == true) return true;
	else return false;
}
