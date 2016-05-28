/*
 * State.h
 *
 *  Created on: 22-Sep-2015
 *      Author: kritarth
 */
#ifndef STATE_H_
#define STATE_H_

class State {
	BitBoard X;
	BitBoard Y;
	int lb, ub, bm;
	State(BitBoard X, BitBoard Y, int a, int b, int c) {
			this->X.X = X.X;
			this->Y.X = Y.X;
			lb =a;
			ub = b;
			bm = c;
		}
};

#endif /* STATE_H_ */
