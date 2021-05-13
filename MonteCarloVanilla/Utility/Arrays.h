#pragma once

#ifndef MJARRAYS_H
#define MJARRAYS_H

#ifdef USE_VAL_ARRAY

#include <valarray>

typedef std::valarray<double> MJArray

#else		// ifdef USE_VAL_ARRAY

typedef unsigned long ulong;

class MJArray
{
public:
	explicit MJArray(ulong size = 0);
	MJArray(const MJArray& original);

	~MJArray();

	MJArray& operator= (const MJArray& original);
	MJArray& operator= (const double& val);

	MJArray& operator+= (const MJArray& operant);
	MJArray& operator-= (const MJArray& operant);
	MJArray& operator*= (const MJArray& operant);
	MJArray& operator/= (const MJArray& operant);

	MJArray& operator+= (const double& operant);
	MJArray& operator-= (const double& operant);
	MJArray& operator*= (const double& operant);
	MJArray& operator/= (const double& operant);

	MJArray apply(double f(double)) const;

	inline double operator[] (ulong i) const;
	inline double& operator[] (ulong i);

	inline ulong size() const;

	void resize(ulong newSize);

	double sum() const;
	double minArray() const;	// use longer name to avoid error caused by windows.h
	double maxArray() const;

private:
	double* m_ValuesPtr;
	double* m_EndPtr;

	ulong m_Size;
	ulong m_Capacity;

};

inline double MJArray::operator[] (ulong i) const
{
#ifdef RANGE_CHECKING
	if (i >= m_Size)
	{
		throw("Index out of bounds");
	}

#endif 

	return m_ValuesPtr[i];
}

inline double& MJArray::operator[] (ulong i)
{
#ifdef RANGE_CHECKING
	if (i >= m_Size)
	{
		throw("Index out of bounds");
	}

#endif 

	return m_ValuesPtr[i];
}

inline ulong MJArray::size() const
{
	return m_Size;
}

#endif // ifdef USE_VAL_ARRAY
#endif // ifndef MJARRAY_H

