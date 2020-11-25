#include "bloomfilter/BloomFilter.hpp"
#include "bloomfilter/MurmurHash3.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using std::cout;
using std::endl;
using std::bitset;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::string;
using std::ostringstream;
using namespace std;


void test_init_dump(size_t m)
{
	//Init 1
	/*
	BloomFilter bf;
	sleep(10);
	*/
	//dump
	BloomFilter bf(m);
	bf.dump("out.txt");
	// ::sleep(10);
	//Init 2
}

void test_mmh3()
{
	string str = "liheyuan";
	uint32_t out;
	MurmurHash3_x86_32(str.c_str(),str.length(),0,&out);
	cout<<out<<endl;
}

void test_bloom_filter(size_t m)
{
	string str = "Just an test";
  cout<<str<<endl;
	BloomFilter bf(m);
	cout<<bf.test(str)<<endl;
	bf.add(str);
	cout<<bf.test(str)<<endl;
}

#define TEST_LEN1 10000000
#define TEST_LEN2 20000000

void test_bloom_filter_100w(size_t m)
{
  cout<<"add 100w"<<endl;
	ostringstream oss;
	//add 100w
	BloomFilter bf(m);
	for(size_t i=0; i<TEST_LEN1; i++)
	{
		oss.str("");
		oss << i;		
		bf.add(oss.str());
	}

	//test false negitive
	size_t cnt = 0;
	for(size_t i=0; i<TEST_LEN1; i++)
	{
		oss.str("");
		oss << i;
		if(!bf.test(oss.str()))
		{
			cnt++;
		}
	}
	cout<<"False Negitive rate:"<<((double)cnt)/(TEST_LEN1)<<endl;

	//test false positive
	cnt = 0;
	for(size_t i=TEST_LEN1; i<TEST_LEN2; i++)
	{
		oss.str("");
		oss << i;
		if(bf.test(oss.str()))
		{
			cnt++;
		}
	}
	cout<<"False Positive rate:"<<((double)cnt)/(TEST_LEN2)<<endl;
}

void test_bloom_filter_dump_read(size_t m)
{
	for(int i=0;i<5;i++){
	ostringstream oss;
	//add 100w
	BloomFilter* pbf = new BloomFilter(m);
	for(size_t i=0; i<100000; i++)
	{
		oss.str("");
		oss << i;		
		pbf->add(oss.str());
	}
	pbf->dump("out.txt");
	delete pbf;
	pbf = NULL;
	cout<<"Saved"<<endl;
	// sleep(5);

	//test false negitive
	pbf = new BloomFilter("out.txt",m);
	size_t cnt = 0;
	for(size_t i=0; i<100000; i++)
	{
		oss.str("");
		oss << i;
		if(!pbf->test(oss.str()))
		{
			cnt++;
		}
	}
	cout<<"False Negitive "<<cnt<<" ."<<endl;

	//test false positive
	cnt = 0;
	for(size_t i=100000; i<200000; i++)
	{
		oss.str("");
		oss << i;
		if(pbf->test(oss.str()))
		{
			cnt++;
		}
	}
	cout<<"False Positive "<<cnt<<" ."<<endl;
	delete pbf;
	pbf = NULL;
	cout<<"tested"<<endl;
	}
	// sleep(20);
}

int main(){
	cout<<"test Start."<<endl;
  size_t m=5;
	// test_init_dump(m);
	
	// test_mmh3();

	test_bloom_filter(m);

	test_bloom_filter_100w(m);//test false negative/positive

	// test_bloom_filter_dump_read(m);

	cout<<"test End."<<endl;
	return 0;
}
