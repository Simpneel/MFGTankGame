#include <iostream>
#include <enet/enet.h>
#include <stdexcept>
#include "enet_wrapper.h"

//class ENetWrapper {
//public:
//	ENetWrapper() {
//		if (enet_initialize() != 0) throw std::runtime_error("Failed to initialize | line 8");
//	}
//	~ENetWrapper() {
//		enet_deinitialize();
//	}
//	ENetPeer* createClient(const char* serverAdd, enet_uint16 port) {
//		ENetAddress address;
//		ENetHost* client;
//
//		if (enet_address_set_host(&address, serverAdd) != 0) throw std::runtime_error("Invalid server address | line 16");
//		address.port = port;
//
//		client = enet_host_create(NULL, 1, 2, 0, 0);
//		if (client == NULL) throw std::runtime_error("Client creation failed | line 18");
//
//		ENetPeer* peer = enet_host_connect(client, &address, 2, 0);
//		if (peer == NULL) std::cerr << "No peers found | line 20";
//
//		return peer;
//	}
//
//	int handleEvents(ENetHost* client, ENetEvent* event, int timeout) {
//		return enet_host_service(client, event, timeout);
//	}
//
//	void destroyPeer(ENetPeer* peer) {
//		enet_peer_disconnect(peer, 0);
//		ENetEvent event;
//		while (enet_host_service(peer->host, &event, 3000) > 0) {
//			switch (event.type) {
//			case ENET_EVENT_TYPE_RECEIVE:
//				enet_packet_destroy(event.packet);
//				break;
//			case ENET_EVENT_TYPE_DISCONNECT:
//				std::cout << "DISCONNECTED\n";
//				break;
//			default:
//				break;
//			}
//		}
//	}
//};
ENetWrapper::ENetWrapper() : host(nullptr), peer(nullptr), isServer(false) {}

ENetWrapper::~ENetWrapper() {
    Deinitialize();
}

bool ENetWrapper::Initialize() {
    if (enet_initialize() != 0) {
        std::cerr << "An error occurred while initializing ENet.\n";
        return false;
    }
    return true;
}

void ENetWrapper::Deinitialize() {
    if (host != nullptr) {
        enet_host_destroy(this->host);
        host = nullptr;
    }
    enet_deinitialize();
}

bool ENetWrapper::CreateServer() {
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 2331;

    host = enet_host_create(&address, 1, 2, 0, 0);
    if (host == nullptr) {
        std::cerr << "An error occurred while trying to create an ENet server host.\n";
        return false;
    }
    isServer = true;
    return true;
}

bool ENetWrapper::CreateClient() {
    host = enet_host_create(nullptr, 1, 2, 0, 0);
    if (host == nullptr) {
        std::cerr << "An error occurred while trying to create an ENet client host.\n";
        return false;
    }
    isServer = false;
    return true;
}

bool ENetWrapper::Connect(const char* address, enet_uint16* port) {
    ENetAddress enet_address;
    enet_address_set_host(&enet_address, address);
    enet_address.port = *port;

    peer = enet_host_connect(host, &enet_address, 2, 0);
    if (peer == nullptr) {
        std::cerr << "No available peers for initiating an ENet connection.\n";
        return false;
    }
    return true;
}

void ENetWrapper::Disconnect() {
    if (peer != nullptr) {
        enet_peer_disconnect(peer, 0);
        peer = nullptr;
    }
}

void ENetWrapper::SendPacket(const void* data, size_t size) {
    if (peer == nullptr && !isServer) return;

    ENetPacket* packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
    if (isServer) {
        enet_host_broadcast(host, 0, packet);
    }
    else {
        enet_peer_send(peer, 0, packet);
    }
}

bool ENetWrapper::ReceivePackets(GameState* newState) {
    if (host == nullptr) return false;

    ENetEvent event;
    if (enet_host_service(host, &event, 250) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            if (isServer) std::cout << "A new client connected.\n";
            else std::cout << "Connected successfully!\n";
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            std::cout << "Packet received.\n";
            *newState = *(GameState*)event.packet->data;
            enet_packet_destroy(event.packet);
            return true;
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "Disconnected successfully!\n";
            break;
        default:
            enet_peer_reset(peer);
            break;
        }
    }
    return false;
}

bool ENetWrapper::IsServer() const {
    return isServer;
}
