#pragma once
#ifndef eNet_Wrapper
#define eNet_Wrapper
#include "Vector3.h"
using Vec3 = MathClasses::Vector3;

struct GameState {
    Vec3 serverPosition;
    float serverRotation;
    Vec3 clientPosition;
    float clientRotation;
    int playerHP = 5;
    int enemyHP = 5;
};

#include <iostream>

class ENetWrapper {
public:
    ENetWrapper();
    ~ENetWrapper();

    bool Initialize();
    void Deinitialize();

    bool CreateServer();
    bool CreateClient();

    bool Connect(const char* address, uint16_t* port);
    void Disconnect();

    void SendPacket(const void* data, size_t size);
    bool ReceivePackets(GameState* newState);

    bool IsServer() const;

private:
    ENetHost* host;
    ENetPeer* peer;
    bool isServer;
};

#endif // ENETWRAPPER_H
