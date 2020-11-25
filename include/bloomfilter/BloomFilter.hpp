
#ifndef __Bloom_Filter_Hpp__
#define __Bloom_Filter_Hpp__

#include <bitset>
#include <string>
//Define of BitVector and M
// int one=1;
// int LEN=one << 26;
#define LEN (1<<26)
// #define M 5
using bs=std::bitset<1<<26>;

class BloomFilter{
public:
	BloomFilter(size_t mBit);
	// BloomFilter(size_t mBit, unsigned long long int bsSize);
	BloomFilter(const char* in_path, size_t mBit);
	// BloomFilter(const char* in_path, size_t mBit, unsigned long long int bsSize);
	~BloomFilter();

	//Seralize bitset to file
	void dump(const char* out_path);
	
	//Add to Bloom Filter and set M bit to True
	void add(const ::std::string key);
	
	//if all of the M bit was set to True -> return True;if any of the M bit was set to False -> Return False
	bool test(const ::std::string key);

	//Test first, add it if not in and return false, else return false
	bool testAndadd(const ::std::string key);
private:
	 bs* _bs;//TODO: dynammic_bitset
	//  unsigned long long int  _bsSize;
	 size_t _mBit;
};

#endif
