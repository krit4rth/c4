#include "BitBoard.h"
#include <iostream>
#include <bitset>
#include "SearchMTDF.h"
#include "evaluate.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
int checker(BitBoard W, BitBoard B) {
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
void printBoard(BitBoard W, BitBoard B) {
	unsigned long long Wt = W.X;
	unsigned long long Bt = B.X;
	char fill[7][9]= {
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	};
	for (int i=0 ; i<63; i++) {

		if (((Wt >>= i)&0b1L) == 1) {
			fill[i/9][(i%9)]='W';
		}
		Wt = W.X;
	}
	for (int i=0 ; i<63; i++) {
					if (((Bt >>= i)&0b1)==0b1) {
						fill[i/9][(i%9)]='B';
					}
					Bt= B.X;
				}
	for (int r =0 ; r< 7 ; r++) {
		for (int c=0 ; c<9; c++)
			std::cout << "|" << fill[6-r][c];
			std::cout << "|\n";
	}
	cout << "|1|2|3|4|5|6|7|8|9|"<<endl;
}

int main() {
	BitBoard W = BitBoard(0b0);
	BitBoard B = BitBoard(0);
	BitBoard A = BitBoard(W.X|B.X);
	int column, score;
	std::vector<int> data1(2);
	std::vector<int> data2(2);
	while (A.legalmoves().size()!=0) {
		cin >> column;
		cout << endl;
		(A.makeMove(column));
		//long start1 = system_clock::now().time_since_epoch().count();
		//data1 = search2(W, B, -9999, 9999, 5);
		//long end1 = system_clock::now().time_since_epoch().count();
		std::cout << "----------------------------------"<<endl;
		//A.makeMove(data1.at(1));
		W.X = (B.X) ^ (A.X);
//cout << endl << "White : "<< bitset<64>(W.X) << endl;
		printBoard(W, B);
		//cout << " Time Taken: " << (end1-start1)/1000000<< " BestMove is: " << data1.at(1)<<endl;
		if (checker(W, B)==9999) {
			cout << "White WON";
			break;
		}
		long start2 = system_clock::now().time_since_epoch().count();
		data2 = search(B, W, -9999, 9999,5);
		long end2 = system_clock::now().time_since_epoch().count();
		std::cout << "----------------------------------"<<endl;
		A.makeMove(data2.at(1));
		B.X = (W.X) ^ (A.X);
		printBoard(W, B);
		cout<< " Time Taken: " << (end2-start2)/1000000<< " BestMove is: " << data2.at(1)<<endl;
		if (checker(W, B)==-9999) {
			cout << "Black WON";
		break;
		}
		A.X = (W.X | B.X);

/*for(auto x:mytpt){
	//cout<<x.first;
	printBoard(x.first[0],x.first[1]);
	cout<<"("<<x.second[0]<<","<<x.second[1]<<","<<x.second[2]<<")\n";

}*/
	}
}

