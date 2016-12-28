#include <BRCClient.h>
#include <Arduino.h>

#define ID1 0x36
#define ID2 0x37
#define ID3 0x38

#define LEADER_ID 0x39

class RelayRace {
	public:
		RelayRace(BRCClient *comm, char ID)
			:wifi(comm), cnt(0), ID(ID), members {ID1, ID2, ID3} {}
		
		bool registerID();

		/* Methods for group member */
		void waitLaunchSignal();
		void sendReachSignal();
		void askRFID(uint8_t *sn);
		bool receiveMessage(CommMsg &msg);

		/* ------------------------ */

		/* Method for leader car */
		void waitRoundStart();
		void sendFinishSignal();
		void activeCar();
		void waitCarFinish();
		/* --------------------- */
	private:
		BRCClient *wifi;
		int cnt;
		char ID;
		char members[3];
};
