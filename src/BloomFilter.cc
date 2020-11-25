#include <string>
#include <fstream>
#include <stdint.h>
#include "bloomfilter/BloomFilter.hpp"
#include "bloomfilter/MurmurHash3.hpp"

BloomFilter::BloomFilter(size_t mBit)
:_bs(NULL)
,_mBit(mBit)
// ,_bsSize(bsSize)//TODO: not use now
{
	this->_bs = new bs();
	this->_bs->reset();
}

BloomFilter::BloomFilter(const char* in_path, size_t mBit)
:_bs(NULL)
,_mBit(mBit)
// ,_bsSize(bsSize)//TODO: not use now
{
	::std::ifstream in(in_path);
	::std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	this->_bs = new bs(str);//0100011...: 二进制字符串
	in.close();
}

BloomFilter::~BloomFilter(){
	if(this->_bs)
	{
		delete _bs;	
	}
}

void BloomFilter::dump(const char* out_path){
	::std::ofstream out(out_path);
	out<<this->_bs->to_string();
	out.close();
}

void BloomFilter::add(const ::std::string key)
{
	uint32_t seed = 0;
	for(size_t i=0; i<_mBit; i++)//每个key哈希M次，置M个bit位
	{
		uint32_t pos = 0;
		MurmurHash3_x86_32(key.c_str(), key.length(), seed, &pos);//每次hash出来一个pos
		seed = pos;
		pos %= LEN;
		this->_bs->set(pos);
	}
}

bool BloomFilter::test(const ::std::string key)// M个hash函数
{
	uint32_t seed = 0;
	for(size_t i=0; i<_mBit; i++)
	{
		uint32_t pos = 0;
		MurmurHash3_x86_32(key.c_str(), key.length(), seed, &pos);// 每次传入不同的seed，相当于M个hash函数
		seed = pos;
		pos %= LEN;
		if(!this->_bs->test(pos))//M位中若有一位是0，说明不在布隆过滤器内
		{
			return false;
		}
	}
	return true;// M位全是1，很有可能在布隆过滤器，有很小的可能不在，这就是布隆过滤器的假阳性。
}

bool BloomFilter::testAndadd(const ::std::string key)
{
	if(this->test(key)){
		return true;	
	}else{
		this->add(key);
		return false;
	}
}
