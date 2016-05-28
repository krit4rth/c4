/*
 * BitBoard.h
 *
 *  Created on: 22-Sep-2015
 *      Author: kritarth
 */

#ifndef BITBOARD_H_
#define BITBOARD_H_
#include <vector>
class BitBoard {
public:
	unsigned long long X;
	BitBoard();
	BitBoard(unsigned long long Y) {
		X = Y;
	};
	BitBoard makeMove(int);
	BitBoard undoMove(int);
	int numSet();
	std::vector<int> legalmoves();
};
#endif /* BITBOARD_H_ */





