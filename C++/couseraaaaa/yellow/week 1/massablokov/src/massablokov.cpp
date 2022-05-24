//============================================================================
// Name        : massablokov.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

class Block{
public:
	uint64_t GetVolume() const{
		return volume;
	}
	Block(const uint16_t& a=0,const uint16_t& b=0,const uint16_t& c=0){
		volume=static_cast<uint64_t>(a)*b*c;
	}
	Block (const uint64_t& vol){
		volume=vol;
	}
	void Print(){
		cout << volume;
	}
private:
	uint64_t volume;
};

istream& operator >>(istream& stream,Block& block){
	uint16_t a,b,c;
	stream.ignore(1);
	stream >> a >> b >> c;
	block = Block(a,b,c);
    return stream;
}

ostream& operator <<(ostream& stream,Block& block){
stream << block.GetVolume();
	return stream;
}

Block operator +(const Block& a,const Block& b){
	Block c(a.GetVolume()+b.GetVolume());
    return c;
}


class SetOfBlocks{
public:
	SetOfBlocks (const uint16_t& R=0){
		density=R;
	}
	void Add(const Block& block){
    blocks.push_back(block);
    }
    uint64_t GetWeight(){
    	Block helper;
    	for(auto x:blocks){
    		helper=helper+x;
    	}
    	return static_cast<uint64_t>(density)*helper.GetVolume();
    }
    void PrintSet(){
    	for(auto x: blocks){
    		cout << x << " ";
    	}
    	cout << endl << "Density is " << density << endl;
    }
private:
	vector<Block> blocks;
	uint16_t density;
};



int main() {

	uint16_t  R;
	uint32_t N;
	cin >> N >> R;
	SetOfBlocks blocks(R);
	Block block;
	for(uint32_t i=0;i+1<=N;i++){
		cin >> block;
		blocks.Add(block);
	}
	cout << blocks.GetWeight() << endl;
	return 0;
}
