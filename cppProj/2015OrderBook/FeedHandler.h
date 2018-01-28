#ifndef FEEDHANDLER_H_
#define FEEDHANDLER_H_

#include "OrdBookFor1Name.h"
#include "OrdLookup.h"
#include "LimitOrder.h"

bool checkHasText(char const* c) {
	for (; *c; ++c)
		if (!isspace(*c))
			break; //better than return true -- can check *c
	return *c; //implicitly cast to bool.
}
class FeedHandler {
	OrdLookup orderLookupAcrossNames;
	OrdBookFor1Name book;

	void add1Order(const vector<const char*> & dto){
        const char *ordId = dto[2];
        LimitOrder *const newOrder = new LimitOrder(ordId, dto[5][0], dto[4], dto[3]);
        //cout << newOrder << endl;
        if(newOrder->isDead())
            return;

        ListType & tmpList = book.get1QueueInOrderBook(newOrder->buySell(), newOrder->px());
        newOrder->pushInto(tmpList);
        orderLookupAcrossNames.save(newOrder);
    }
	const OrdLocator locateOrd(const char * ordId){//return by value!
		OrdLocator ret;
		ret.str = ordId;
		ret.id = atoll(ordId);
		if(ret.id <= 0){
			ret.id=0;
	    }else{
	    	ret.ord = orderLookupAcrossNames[ret.id];
	    }
	    if (ret.ord  == NULL) {
	    	DC<<ordId<<" .. unknown order id"<<endl;
	    }
	    return ret;
	}
	void processTradeMsg(const vector<const char*> & dto){//see comment in OrkLookup.h
		for (int i = 2; i<=3; ++i){
			OrdLocator loc = locateOrd(dto[i]);
			if (!loc.ord) continue;
            const int newQty =loc.ord->qty() - atoi(dto[5]);
 			if (newQty < 0){
				continue;
			}else if (newQty > 0){
				loc.ord->qty(newQty);
				//cout<<"reduced "<<loc.ord<<endl;
			}else {
				remove1OrdId(dto[i]);
			}
		}
    }
    void remove1OrdId(const char *ordId){
    	OrdLocator loc = locateOrd(ordId);
    	if (loc.ord){
			loc.ord ->remove();//pimpl
			delete loc.ord;
			orderLookupAcrossNames.nullify(loc.id);
			book.removeEmptyPxLevels();
		}
    }
    void processMod(const vector<const char*> & dto){
    	OrdLocator loc = locateOrd(dto[2]);
    	if (!loc.ord){
    		if (loc.id) add1Order(dto);
    		return;
    	}
        const long newPx = atol(dto[3]);
        if (abs(loc.ord->px()-newPx)<0.001){//same price
            const unsigned int qty = atoi(dto[4]);
        	loc.ord->qty(qty);
        	return;
        }else{
        	remove1OrdId(dto[2]);
        	add1Order(dto);
        }
    }
public:
    void printOrdBookTop(int count=5)
    {
        book.printOrderBook4col(count);
    }

    void printOrdBook2()
    {
        book.printOrderBook2_debug();
    }

    bool process1Msg(const char *ccstr)
    {
    	char * cstr = const_cast<char*>(ccstr);
    	// needed by the c++ compiler on HackerEarth!

    	DC << "\n>>>" << cstr << endl;
        char *commStart = strstr(cstr, "//");
        if(commStart){
            *commStart = '\0';
            if(!checkHasText(cstr)){
                //cout<<"full-comment line... skipped"<<endl;
                return false;
            }
        }
        else{
            if(!checkHasText(cstr)) return false;
        }
        const char * pattern = ",";
		char copy[strlen(cstr) + 1];
		strcpy(copy, cstr);
		vector<const char*> dto; // data transfer object
		int i = 0;
		for (char * tok = strtok(copy, pattern); tok;
				tok = strtok(0, pattern), ++i) {
			if (i==2){ //strip the trailing zeros
				tok[strlen(tok) - 7] = 0;
			}
			dto.push_back(tok);
		}
		if (DEBUG) dumpDTO(dto);

		if        (dto[1][0] == 'N') {
			add1Order(dto);
		} else if (dto[1][0] == 'M') {
			processMod(dto);
		} else if (dto[1][0] == 'X') {
			remove1OrdId(dto[2]);
		} else if (dto[1][0] == 'T') {
			processTradeMsg(dto);
		}
		return true;
	}

};
#endif /* FEEDHANDLER_H_ */
