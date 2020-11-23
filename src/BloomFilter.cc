#include <string>
#include <fstream>
#include <stdint.h>
#include "bloomfilter/BloomFilter.hpp"
#include "bloomfilter/MurmurHash3.hpp"

BloomFilter::BloomFilter()
:_bs(NULL)
{
	this->_bs = new bs();
	this->_bs->reset();
}

BloomFilter::BloomFilter(const char* in_path)
:_bs(NULL)
{
	::std::ifstream in(in_path);
	::std::string str((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
	this->_bs = new bs(str);
	in.close();
}

BloomFilter::~BloomFilter()
{
	if(this->_bs)
	{
		delete _bs;	
	}
}

void BloomFilter::Dump(const char* out_path)
{
	::std::ofstream out(out_path);
	out<<this->_bs->to_string();
	out.close();
}

void BloomFilter::Add(const ::std::string key)
{
	uint32_t seed = 0;
	for(size_t i=0; i<M; i++)
	{
		uint32_t pos = 0;
		MurmurHash3_x86_32(key.c_str(), key.length(), seed, &pos);
		seed = pos;
		pos %= LEN;
		this->_bs->set(pos);
	}
}

bool BloomFilter::Test(const ::std::string key)
{
	uint32_t seed = 0;
	for(size_t i=0; i<M; i++)
	{
		uint32_t pos = 0;
		MurmurHash3_x86_32(key.c_str(), key.length(), seed, &pos);
		seed = pos;
		pos %= LEN;
		if(!this->_bs->test(pos))
		{
			return false;
		}
	}
	return true;
}

bool BloomFilter::TestAndAdd(const ::std::string key)
{
	if(this->Test(key))
	{
		return true;	
	}
	else
	{
		this->Add(key);
		return false;
	}
}
