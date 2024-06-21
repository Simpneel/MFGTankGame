#include <iostream>
#include <enet/enet.h>
#include <stdexcept>

class ENetWrapper {
public:
	ENetWrapper() {
		if (enet_initialize() != 0) throw std::runtime_error("Failed to initialize | line 8");
	}
	~ENetWrapper() {
		enet_deinitialize();
	}
	ENetPeer* createClient(const char* serverAdd, enet_uint16 port) {
		ENetAddress address;
		ENetHost* client;

		if (enet_address_set_host(&address, serverAdd) != 0) throw std::runtime_error("Invalid server address | line 16");
		address.port = port;

		client = enet_host_create(NULL, 1, 2, 0, 0);
		if (client == NULL) throw std::runtime_error("Client creation failed | line 18");

		ENetPeer* peer = enet_host_connect(client, &address, 2, 0);
		if (peer == NULL) std::cerr << "No peers found | line 20";

		return peer;
	}

	int handleEvents(ENetHost* client, ENetEvent* event, int timeout) {
		return enet_host_service(client, event, timeout);
	}

	void destroyPeer(ENetPeer* peer) {
		enet_peer_disconnect(peer, 0);
		ENetEvent event;
		while (enet_host_service(peer->host, &event, 3000) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "DISCONNECTED\n";
				break;
			default:
				break;
			}
		}
	}
};

