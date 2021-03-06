#include "RelayRace.h"

bool RelayRace::registerID() {
	return wifi->registerID(ID);
}

void RelayRace::waitLaunchSignal() {
	CommMsg msg;
	while(1) {
		if(wifi->receiveMessage(&msg)) {
			if(!strcmp(msg.buffer, "LIFT OFF")) return;
			if(!strcmp(msg.buffer, "1") && ID == ID1) return;
			if(!strcmp(msg.buffer, "2") && ID == ID2) return;
			if(!strcmp(msg.buffer, "3") && ID == ID3) return;
		}
		delay(500);
	}
}

bool RelayRace::askRFID(uint8_t *sn, bool debug) {
	CommMsg msg;
	msg.type = MSG_REQUEST_RFID;
	for (int i = 0; i < 4; i++) {
		msg.buffer[i] = sn[i];
	}

	wifi->sendMessage(&msg);

	wifi->receiveMessage(&msg);

	if(debug) {
		wifi->complete();
		wifi->sendToClient(LEADER_ID, "FINISH");

		wifi->endBRCClient();

		return true;
	}

	if(ID == ID1 && msg.buffer[6] == MAP_PARK_1) {
		wifi->complete();
		wifi->sendToClient(LEADER_ID, "FINISH");

		wifi->endBRCClient();

		return true;
	}

	if(ID == ID2 && msg.buffer[6] == MAP_PARK_2) {
		wifi->complete();
		wifi->sendToClient(LEADER_ID, "FINISH");

		wifi->endBRCClient();

		return true;
	}

	if(ID == ID3 && msg.buffer[6] == MAP_PARK_3) {
		wifi->complete();
		wifi->sendToClient(LEADER_ID, "FINISH");

		wifi->endBRCClient();

		return true;
	}

	if(ID == LEADER_ID && msg.buffer[6] == MAP_PARK_4) {
		wifi->complete();
		return true;
	}

	return false;
}

bool RelayRace::receiveMessage(CommMsg &msg) {
	return wifi->receiveMessage(&msg);
}

void RelayRace::sendReachSignal() {
	wifi->sendToClient(LEADER_ID, "FINISH");

	wifi->endBRCClient();
	return;
}

bool RelayRace::dead() {
	CommMsg msg;
	if(wifi->receiveMessage(&msg)) {
		if(((!strcmp(msg.buffer, "K1") && ID == ID1) || (!strcmp(msg.buffer, "K2") && ID == ID2)) || ((!strcmp(msg.buffer, "K3") && ID == ID3) || (!strcmp(msg.buffer, "K4") && ID == LEADER_ID))) {
			wifi->complete();
			wifi->endBRCClient();
			return true;
		}
	}
	return false;
}

void RelayRace::waitRoundStart() {
	CommMsg msg;
	while(1) {
		if(wifi->receiveMessage(&msg)) {
			if(msg.type == MSG_ROUND_START) return;
			if(!strcmp(msg.buffer, "START")) return;
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

void RelayRace::activeCar(char ID) {
	wifi->sendToClient(ID, "LIFT OFF");
}

void RelayRace::waitCarFinish() {
	CommMsg msg;
	while(1) {
		if(wifi->receiveMessage(&msg)) {
			if(!strcmp(msg.buffer, "FINISH")) return;
			if(!strcmp(msg.buffer, "4") && ID == LEADER_ID) return;
		}
		delay(500);
	}
}
