#include "../pch.h"

#include "Arrays.h"

#include <algorithm>
#include <numeric>

MJArray::MJArray(ulong size) : m_Size(size), m_Capacity(size)
{
	if (size > 0)
	{
		m_ValuesPtr = new double[size];
		m_EndPtr = m_ValuesPtr;
		m_EndPtr += size;
	}
	else
	{
		m_ValuesPtr = m_EndPtr = nullptr;
	}
}

MJArray::MJArray(const MJArray& original) : m_Size(original.m_Size), m_Capacity(original.m_Size)
{
	if (m_Size > 0)
	{
		m_ValuesPtr = new double[m_Size];
		m_EndPtr = m_ValuesPtr;
		m_EndPtr += m_Size;

		std::copy(original.m_ValuesPtr, original.m_EndPtr, m_ValuesPtr);
	}
	else
	{
		m_ValuesPtr = m_EndPtr = nullptr;
	}
}

MJArray::~MJArray()
{
	if (m_ValuesPtr != nullptr)
	{
		delete[] m_ValuesPtr;
	}
}

MJArray& MJArray::operator= (const MJArray& original)
{
	if (&original == this)
		return *this;
	
	if (original.m_Size > m_Capacity)
	{
		if (m_Capacity > 0)
			delete[] m_ValuesPtr;

		m_ValuesPtr = new double[original.m_Size];
		m_Capacity = original.m_Size;
	}

	m_Size = original.m_Size;
	m_EndPtr = m_ValuesPtr;
	m_EndPtr += m_Size;

	std::copy(original.m_ValuesPtr, original.m_EndPtr, m_ValuesPtr);

	return *this;
}

// if new size exceeds capacity, create new empty array
void MJArray::resize(ulong newSize)
{
	if (newSize > m_Capacity)
	{
		if (m_Capacity > 0)
			delete[] m_ValuesPtr;

		m_ValuesPtr = new double[newSize];
		m_Capacity = newSize;
	}

	m_Size = newSize;
	m_EndPtr = m_ValuesPtr + newSize;
}

MJArray& MJArray::operator+= (const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (m_Size != operand.m_Size)
	{
		throw("To apply += two arrays must be of same size");
	}
#endif

	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] += operand[i];

	return *this;
}

MJArray& MJArray::operator-= (const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (m_Size != operand.m_Size)
	{
		throw("To apply += two arrays must be of same size");
	}
#endif

	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] -= operand[i];

	return *this;
}

MJArray& MJArray::operator/= (const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (m_Size != operand.m_Size)
	{
		throw("To apply += two arrays must be of same size");
	}
#endif

	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] /= operand[i];

	return *this;
}

MJArray& MJArray::operator*= (const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (m_Size != operand.m_Size)
	{
		throw("To apply += two arrays must be of same size");
	}
#endif

	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] *= operand[i];

	return *this;
}


////////////////////////////////////////////////////////////

MJArray& MJArray::operator+= (const double& operand)
{
	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] += operand;

	return *this;
}

MJArray& MJArray::operator-= (const double& operand)
{
	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] -= operand;

	return *this;
}

MJArray& MJArray::operator/= (const double& operand)
{
	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] /= operand;

	return *this;
}

MJArray& MJArray::operator*= (const double& operand)
{
	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] *= operand;

	return *this;
}

MJArray& MJArray::operator= (const double& val)
{
	for (ulong i = 0; i < m_Size; ++i)
		m_ValuesPtr[i] = val;

	return *this;
}

////////////////////////////////////////////////////////////

double MJArray::sum() const
{
	return std::accumulate(m_ValuesPtr, m_EndPtr, 0.0);
}

double MJArray::prod() const
{
	return std::accumulate(m_ValuesPtr, m_EndPtr, 1.0, std::multiplies<double>());
}

// used when force all elements to be strictly positive
double MJArray::geomMean() const
{
	int k = 0;
	double prod = 1;

	for (int i = 0; i < m_Size; i++)
	{
		if (this->operator[](i) == 0)
			continue;

		prod *= this->operator[](i);
		k++;
	}

	return pow(prod, 1.0 / k);
}

double MJArray::minArray() const
{
#ifdef RANGE_CHECKING
	if (m_Size == 0)
	{
		throw("Cannot take min of empty array");
	}
#endif

	return *(std::min)(m_ValuesPtr, m_EndPtr);
}

double MJArray::maxArray() const
{
#ifdef RANGE_CHECKING
	if (m_Size == 0)
	{
		throw("Cannot take min of empty array");
	}
#endif

	return *(std::max)(m_ValuesPtr, m_EndPtr);
}

MJArray MJArray::apply(double f(double)) const
{
	MJArray result(size());
	std::transform(m_ValuesPtr, m_EndPtr, result.m_ValuesPtr, f);

	return result;
}