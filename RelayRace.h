#include <BRCClient.h>
#include <Arduino.h>

#define ID1 0x36
#define ID2 0x37
#define ID3 0x38

#define LEADER_ID 0x39

class RelayRace {
	public:
		RelayRace(BRCClient *comm, char ID)
			:wifi(comm), cnt(0), ID(ID), members {ID1, ID2, ID3}, park{MAP_PARK_1, MAP_PARK_2, MAP_PARK_3, MAP_PARK_4} {}
		
		bool registerID();

		/* Methods for group member */
		void waitLaunchSignal();
		void sendReachSignal();
		bool askRFID(uint8_t *sn, bool debug = false);
		bool receiveMessage(CommMsg &msg);
		bool dead();

		/* ------------------------ */

		/* Method for leader car */
		void waitRoundStart();
		void sendFinishSignal();
		void activeCar(char);
		void waitCarFinish();
		/* --------------------- */
	private:
		BRCClient *wifi;
		int cnt;
		char ID;
		char members[3];
		char park[4];
};
