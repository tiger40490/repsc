#include "Util.h"

#ifndef LOIMPL_H_
#define LOIMPL_H_
class LOImpl {
public:
	enum BuySellEnum {
		B = 'B', S = 'S', BAD_FORMAT
	};
	static BuySellEnum const lookupBuySell(const char b_or_s) {
		if (b_or_s == 'B')
			return B;
		if (b_or_s == 'S')
			return S;
		return BAD_FORMAT;
	}
	LOImpl(const char * const _id, const char _bs, const char * const _qty,
			const char * const _px) :
		id(atoi(_id)), bs(lookupBuySell(_bs)), px(atof(_px)), qty(
				atoi(_qty)) {
	}
	~LOImpl() {
		//cout << "~LOImpl() " << id << endl;
	}
	unsigned int const getqty() const{
		return qty;
	}
	friend ostream & operator <<(ostream & os, const LOImpl & p);
	friend class LimitOrder;
	const unsigned int id;
	const BuySellEnum bs;
	const double px;
	//above are const; below are mutable
private:
	unsigned int qty; //mutable. Should be protected by a mutex
};
ostream & operator<<(ostream &os, LOImpl::BuySellEnum const& p) {
	if (p == LOImpl::B)
		os << "Buy ";
	if (p == LOImpl::S)
		os << "Sell";
	return os;
}
#endif /* LOIMPL_H_ */
