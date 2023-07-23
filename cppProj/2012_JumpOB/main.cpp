#include "FeedHandler.h"

int main(int, char**) {
	FeedHandler feed;
	string line;
	ifstream in("C:\\0x\\0bak\\ideWorkspace\\ec_jump\\src\\exchange_feed.txt");
	for (int i = 0; !getline(in, line).eof(); ++i) {
		feed.processMsg(line.c_str());
		if (i % 10 == 0) {//%10!=0 means dump 9 time out of 10
			feed.printCurrentOrderBook();
		}
	}
	feed.printCurrentOrderBook();
}
