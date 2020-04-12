#pragma once

#include <iostream>

/*This simple classes are polymorphy alternative to switch..case instructions which i didnt wanted to use */
class nucleotide
{	
public:
	nucleotide() {};
	virtual ~nucleotide() {};

public:
	virtual void complementaryRule(char& _in) = 0;									//virtual function which each derived class will define own rule

	static nucleotide* factory(char _representation) throw(std::bad_alloc);
};

class adenine final : protected nucleotide
{
	adenine() = default;

public:
	inline void complementaryRule(char& _in) override { _in = 'T'; };

	friend class nucleotide;
};

class thymine final : public nucleotide
{
	thymine() = default;

public:
	inline void complementaryRule(char& _in) override { _in = 'A'; };

	friend class nucleotide;
};

class cytosine final : protected nucleotide 
{
	cytosine() = default;

public:
	inline void complementaryRule(char& _in) override { _in = 'G'; };

	friend class nucleotide;
};

class guanine final : protected nucleotide 
{
	guanine() = default;

public:
	inline void complementaryRule(char& _in) override { _in = 'C'; };

	friend class nucleotide;
};

class special final : protected nucleotide
{
	special() = default;

public:
	inline void complementaryRule(char& _in) override { _in += 1; };

	friend class nucleotide;
};