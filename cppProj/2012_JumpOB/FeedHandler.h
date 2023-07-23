#include "OrdBookForOneSymbol.h"
#include "OrdLookup.h"

#ifndef FEEDHANDLER_H_
#define FEEDHANDLER_H_

bool checkHasText(char const* c) {
	for (; *c; ++c)
		if (!isspace(*c))
			break; //better than return true -- can check *c
//	if (*c) {
//		cout << "has text\n";
//	} else {
//		cout << "all space\n";
//	}
	return *c; //implicitly cast to bool.
}
class FeedHandler {
	OrdLookup orderLookupAcrossSymbols;
	OrdBookForOneSymbol book;
public:
	void printCurrentOrderBook() {
		book.printCurrentOrderBook();
	}
	void processMsg(char const * cstr) {
		cout<<"\n>>>"<<cstr<<endl;
		char * commStart = strstr(cstr, "//");
		if (commStart) {//found
			// remaining str length
			const unsigned int len = commStart - cstr;
			char dup2[len + 1];
			strncpy(dup2, cstr, len);
			dup2[len] = '\0';
			if (!checkHasText(dup2))
				return;
		} else {
			if (!checkHasText(cstr))
				return;
		}
		//		string line(cstr);
		//		unsigned int commentStart = line.find("//");
		//		if (commentStart < line.npos)
		//			line.erase(commentStart);
		//
		//		line.erase(find_if(line.rbegin(), line.rend(), not1(ptr_fun<int, int> (
		//				isspace))).base(), line.end()); //rtrim
		//		if (line.empty())
		//			return;
		//		stringstream lineStream(line);
		//		string token;
		//		vector<string> dto;
		char const * pattern = ",";
		char copy[strlen(cstr) + 1];
		strcpy(copy, cstr);
		vector<const char*> dto;
		for (char const* tok = strtok(copy, pattern); tok; tok
				= strtok(0, pattern)) {
			dto.push_back(tok);
		}
		//		while (getline(lineStream, token, ',')) {
		//			dto.push_back(token);
		////			dto2.push_back(token.c_str());
		//		}
		dump1(dto);

		if (dto[0][0] == 'A') {
			add1Order(dto);
		} else if (dto[0][0] == 'X') {
			remove1order(dto);
		} else if (dto[0][0] == 'M') {
			modify1order(dto);
		} else if (dto[0][0] == 'T') {
			book.printCummulative(dto);
		}
		book.printMidQuote();
	}
	void add1Order(vector<char const *> const & dto) {
		LimitOrder * const newOrder = new LimitOrder(dto[1], dto[2][0], dto[3],
				dto[4]);
		//cout << newOrder << endl;
		if (newOrder->isDead())
			return;
		ListType & tmpList = book.get1QueueInOrderBook(newOrder->buySell(),
				newOrder->px());
		if (tmpList.size()){
			cout<<tmpList.size()<<endl;
		}
		newOrder->pushInto(tmpList);
		book.updateBestAfterAdd(newOrder);
		orderLookupAcrossSymbols.save(newOrder);
	}
	void modify1order(vector<char const *> const & dto) {
		const unsigned int tmp_id = atoi(dto[1]);
		if (tmp_id < 0) {
			//log error
			return;
		}

		const unsigned int qty = atoi(dto[3]);
		if (qty <= 0) {
			throw new exception();//zero qty should use X not M
		}

		LimitOrder* const order2mod = orderLookupAcrossSymbols[tmp_id];
		if (order2mod == NULL) {
			//log error
			return;
		}
		//todo: validate BS, price etc

		order2mod->qty(qty);
	}
	void remove1order(vector<char const *> const & dto) {
		unsigned int const tmp_id = atoi(dto[1]);
		if (tmp_id < 0) {
			//log error
			return;
		}
		LimitOrder* order = orderLookupAcrossSymbols[tmp_id];
		if (order == NULL) {
			//log error
		} else {
			order ->remove();
			book.updateBestAfterRemove(order->buySell(), order->px());
			delete order;
			orderLookupAcrossSymbols.nullify(tmp_id);
		}
	}
};
#endif /* FEEDHANDLER_H_ */
