#include "RelayRace.h"

bool RelayRace::registerID() {
	return wifi->registerID(ID);
}

void RelayRace::waitLaunchSignal() {
	CommMsg msg;
	while(1) {
		if(wifi->receiveMessage(&msg)) {
			if(!strcmp(msg.buffer, "LIFT OFF")) return;
		}
		delay(500);
	}
}

void RelayRace::askRFID(uint8_t *sn) {
	CommMsg msg;
	msg.type = MSG_REQUEST_RFID;
	for (int i = 0; i < 4; i++) {
		msg.buffer[i] = sn[i];
	}

	wifi->sendMessage(&msg);
}

bool RelayRace::receiveMessage(CommMsg &msg) {
	return wifi->receiveMessage(&msg);
}

void RelayRace::sendReachSignal() {
	wifi->sendToClient(LEADER_ID, "FINISH");

	wifi->endBRCClient();
	return;
}

void RelayRace::waitRoundStart() {
	CommMsg msg;
	while(1) {
		if(wifi->receiveMessage(&msg)) {
			if(msg.type == MSG_ROUND_START) return;
		}
		delay(500);
	}
}

void RelayRace::sendFinishSignal() {
	CommMsg msg = {
		.type = MSG_ROUND_COMPLETE
	};
	while(!wifi->sendMessage(&msg));

	wifi->endBRCClient();
}

void RelayRace::activeCar() {
	wifi->sendToClient(members[cnt], "LIFT OFF");
}

void RelayRace::waitCarFinish() {
	CommMsg msg;
	while(1) {
		if(wifi->receiveMessage(&msg)) {
			if(!strcmp(msg.buffer, "FINISH")) return;
		}
		delay(500);
	}
}
