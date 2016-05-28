/*
 * SearchMTDF.cpp
 *
 *  Created on: 22-Sep-2015
 *      Author: kritarth
 */
#include <math.h>
#include "BitBoard.h"
#include "evaluate.h"
#include <iostream>

int check(BitBoard W, BitBoard B) {
	for (int i =0 ; i< 7; i++) {
			for (int j=1; j<7; j++) {
				int rW=0, rB=0;
				for (int k=0; k<4; k++) {
					rW += (W.X >> (9*i+j+k-1)) & 1;
					rB += (B.X >> (9*i+j+k-1)) & 1;}
					if (rW==4) return 9999;
					if (rB==4) return -9999;}}
	for (int c=0; c<9; c++) {
			for (int r=0; r<4; r++) {
				int rW=0, rB=0;
				for (int k=0 ; k<4; k++) {
					rW = rW + ((W.X >> (9*(r+k)+c)) & 1);
					rB = rB + ((B.X >> (9*(r+k)+c)) & 1);}
					if (rW==4) return 9999;
					if (rB==4) return -9999;}}
	for (int i =0 ; i< 6; i++) {
			for (int j=0; j<4; j++) {
				int rW=0, rB=0;
				for (int k=0; k<4; k++) {
					rW += ((W.X >> (i+10*k+9*j)) & 1);
					rB += ((B.X >> (i+10*k+9*j)) & 1);}
					if (rW==4) return 9999;
					if (rB==4) return -9999;}}
	for (int i =3 ; i< 9; i++) {
			for (int j=0; j<4; j++) {
				int rW=0, rB=0;
				for (int k=0; k<4; k++) {
					rW += ((W.X >> (i+8*k+9*j)) & 1);
					rB += ((B.X >> (i+8*k+9*j)) & 1);}
					if (rW==4) return 9999;
					if (rB==4) return -9999;}}
	return 0;
}

std::vector<int> search(BitBoard W, BitBoard B, int alpha, int beta, int d) {
	BitBoard A = BitBoard(W.X | B.X);
	int score, a, b, bm, bm2;
	int chk = check(W, B);
	std::vector<int> v (2);
	BitBoard c = BitBoard(0);
	if (d==0) score = evaluate(W, B);
	else if (W.numSet()<B.numSet()) {
		score = -9999;
		a= alpha;
		std::vector<int> ll = A.legalmoves();
		std::vector<int>::iterator itw;
		itw = ll.begin();
		int s=ll.size()-1;
		A.makeMove(*itw);
		c.X = A.X ^ B.X;
		while ((score < beta)&&(/*ChildLeft*/s!=0)) {
			int ss = search(c, B, a, beta, d-1).at(0);
			if (ss > score) {
				score = ss;
				bm = *itw;
				//std::cout << bm;
			}
			//score = std::max(score, search(c, B, a, beta, d-1));
			a = std::max(a, score);
			A.undoMove(*itw);
			itw++;
			A.makeMove(*itw);
			c.X = A.X ^ B.X;
			s--;
		}
	}
	else {
		score = 9999; b = beta;
		std::vector<int> llb = A.legalmoves();
		std::vector<int>::iterator itb;
		itb = llb.begin();
		int s=llb.size()-1;
		A.makeMove(*itb);
		c.X = A.X ^ W.X;
		while ((score > alpha)&&(/*ChildLeft*/s!=0)) {
			score = std::min(score, search(W, c, alpha, b, d-1).at(0));
			b = std::min(b, score);
			A.undoMove(*itb);
			itb++;
			A.makeMove(*itb);
			c.X = A.X ^ W.X;
			s--;
		}
	}
	v.at(0)= score;
	if (chk!=0) v.at(0)=chk;
	v.at(1)= bm;
	return v;
}

std::vector<int> search2(BitBoard W, BitBoard B, int alpha, int beta, int d) {
	BitBoard A = BitBoard(W.X | B.X);
	int score, a, b, bm;
	int chk = check(W, B);
	std::vector<int> v (2);
	BitBoard c = BitBoard(0);
	if (d==0) score = evaluate(W, B);
	else if (W.numSet()==B.numSet()) {
		score = -9999;
		a= alpha;
		std::vector<int> ll = A.legalmoves();
		std::vector<int>::iterator itw;
		itw = ll.begin();
		int s=ll.size()-1;
		A.makeMove(*itw);
		c.X = A.X ^ B.X;
		while ((score < beta)&&(/*ChildLeft*/s!=0)) {
			int ss = search2(c, B, a, beta, d-1).at(0);
			if (ss > score) {
				score = ss;
				bm = *itw;
				//std::cout << bm;
			}
			//score = std::max(score, search(c, B, a, beta, d-1));
			a = std::max(a, score);
			A.undoMove(*itw);
			itw++;
			A.makeMove(*itw);
			c.X = A.X ^ B.X;
			s--;
		}
	}
	else {
		score = 9999;
		b = beta;
		std::vector<int> llb = A.legalmoves();
		std::vector<int>::iterator itb;
		itb = llb.begin();
		int s=llb.size()-1;
		A.makeMove(*itb);
		c.X = A.X ^ W.X;
		while ((score > alpha)&&(/*ChildLeft*/s!=0)) {
			score = std::min(score, search2(W, c, alpha, b, d-1).at(0));
			b = std::min(b, score);
			A.undoMove(*itb);
			itb++;
			A.makeMove(*itb);
			c.X = A.X ^ W.X;
			s--;
		}
	}
	v.at(0)= score;
	if (chk!=0) v.at(0)=chk;
	v.at(1)= bm;
	return v;
}


