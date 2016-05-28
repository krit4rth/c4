/*
 * BitBoard.cpp
 *
 *  Created on: 22-Sep-2015
 *      Author: kritarth
 */

#include "BitBoard.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <list>

BitBoard BitBoard::makeMove(int c) {
	int i =0;
	while (((X >> (9*i+c-1))&1L)&&i<7)  {
			i++;
		}
	X ^= (1L<<(i*9+c-1));
	return BitBoard(X);
}

BitBoard BitBoard::undoMove(int c) {
	int i =0;
	while (((X >> (9*i+c-1))&1L)&&i<7)  {
			i++;
		}
	X ^= (1L<<((i-1)*9+c-1));
	return BitBoard(X);
}

int BitBoard::numSet() {
	int ans=0;
	for (int i=0; i<64; i++) {
		if ((X>>i)&1L) ans++;
	}
	return ans;
}

std::vector<int> BitBoard::legalmoves() {
	std::vector<int> lm;
	unsigned long long L = ((X<<9)|0b111111111L)^X;
	std::vector<int>::iterator it;
	it = lm.begin();
	for (int i=0; i<63; i++) {
		if ((L>>i)&1L) it = lm.insert(it, (i%9)+1);
	}
	/*for (std::vector<int>::iterator it = lm.begin(); it != lm.end(); ++it) {
	    std::cout << ' ' << *it;
	  	  std::cout << " ";}*/
	return lm;
}

/*int main() {
	int c, c1;
	BitBoard bb = BitBoard(0b111111111111111111111111111111111111111111111111111111111111L);
	//while (true) {
	//std::cin >> c;
	//bb.makeMove(c);
	//std::cout << std::bitset<64>(bb.X) << std::endl;
	//std::cin >> c1;
	//bb.undoMove(c1);
	std::cout << std::bitset<64>(bb.X) << std::endl;

	std::cout << "lol "<<bb.legalmoves().size();}*/

