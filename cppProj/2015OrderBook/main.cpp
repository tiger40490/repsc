#include "FeedHandler.h"

int main(int, char**) {
	FeedHandler feed;
    ifstream in2("src/exchange_feed.txt");
    cin.rdbuf(in2.rdbuf()); //redirect std::cin to the file
	string line;
	while (std::getline(std::cin, line)){
		if (feed.process1Msg(line.c_str())){
			if (DEBUG) feed.printOrdBook2();
		}
	}
	feed.printOrdBookTop();
}
