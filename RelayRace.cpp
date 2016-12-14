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

void RelayRace::sendReachSignal() {
	wifi->sendToClient(LEADER_ID, "FINISH");
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
		.type = MSG_ROUND_COMPELETE
	};
	while(!wifi->sendMessage(&msg));
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
