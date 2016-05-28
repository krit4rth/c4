/*
 * evaluate.cpp
 *
 *  Created on: 23-Sep-2015
 *      Author: kritarth
 */
#include "BitBoard.h"
#include <iostream>
int evaluate(BitBoard W, BitBoard B) {
	//return 0;
	//for rows

	int scoreB=0, scoreW=0;

	for (int i =0 ; i< 7; i++) {
		for (int j=1; j<7; j++) {
			int rW=0, rB=0;
			for (int k=0; k<4; k++) {
				rW += (W.X >> (9*i+j+k-1)) & 1;
				rB += (B.X >> (9*i+j+k-1)) & 1;}
				if (rW==4 && rB==0) return 9999;
				if (rB==4 && rW==0) return -9999;
				if (rW==0 && rB==3)	scoreB += 100*rB;
				if (rB==0 && rW==3) scoreW += 100*rW;
				if (rW==0 && rB==2)	scoreB += 5*rB;
				if (rB==0 && rW==2) scoreW += 5*rW;
				if (rW==0 && rB==1)	scoreB += rB;
				if (rB==0 && rW==1) scoreW += rW;

		}
	}

	//for column
	for (int c=0; c<9; c++) {
		for (int r=0; r<4; r++) {
			int rW=0, rB=0;
			for (int k=0 ; k<4; k++) {
				rW = rW + ((W.X >> (9*(r+k)+c)) & 1);
				rB = rB + ((B.X >> (9*(r+k)+c)) & 1);}
				if (rW==4 && rB==0) return 9999;
				if (rB==4 && rW==0) return -9999;
				if (rW==0 && rB==3)	scoreB += 100*rB;
				if (rB==0 && rW==3) scoreW += 100*rW;
				if (rW==0 && rB==2)	scoreB += 5*rB;
				if (rB==0 && rW==2) scoreW += 5*rW;
				if (rW==0 && rB==1)	scoreB += rB;
				if (rB==0 && rW==1) scoreW += rW;

		}
	}

	//for diagonal "\"

	for (int i =0 ; i< 6; i++) {
		for (int j=0; j<4; j++) {
			int rW=0, rB=0;
			for (int k=0; k<4; k++) {
				rW += ((W.X >> (i+10*k+9*j)) & 1);
				rB += ((B.X >> (i+10*k+9*j)) & 1);}
				if (rW==4 && rB==0) return 9999;
				if (rB==4 && rW==0) return -9999;
				if (rW==0 && rB==3)	scoreB += 100*rB;
				if (rB==0 && rW==3) scoreW += 100*rW;
				if (rW==0 && rB==2)	scoreB += 5*rB;
				if (rB==0 && rW==2) scoreW += 5*rW;
				if (rW==0 && rB==1)	scoreB += rB;
				if (rB==0 && rW==1) scoreW += rW;
		}
	}

	//for diagonal /

	for (int i =3 ; i< 9; i++) {
		for (int j=0; j<4; j++) {
			int rW=0, rB=0;
			for (int k=0; k<4; k++) {
				rW += ((W.X >> (i+8*k+9*j)) & 1);
				rB += ((B.X >> (i+8*k+9*j)) & 1);}
				if (rW==4 && rB==0) return 9999;
				if (rB==4 && rW==0) return -9999;
				if (rW==0 && rB==3)	scoreB += 100*rB;
				if (rB==0 && rW==3) scoreW += 100*rW;
				if (rW==0 && rB==2)	scoreB += 5*rB;
				if (rB==0 && rW==2) scoreW += 5*rW;
				if (rW==0 && rB==1)	scoreB += rB;
				if (rB==0 && rW==1) scoreW += rW;
				//if (rW==0 && rB==0)

		}
	}
	//score[0]=scoreW;
	//score[1]=scoreB;
	//return score;
	return scoreW-scoreB;
}
/*
int main() {
	BitBoard A = BitBoard(0b111000L);
	BitBoard B = BitBoard(0b0000000000L);
	std::cout << evaluate(A, B);
}
*/



