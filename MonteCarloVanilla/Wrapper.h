#pragma once

template <typename T>
class Wrapper
{
public:
	Wrapper() : m_DataPtr(0) {}


	Wrapper(const T& inner)
	{
		m_DataPtr = inner.clone();
	}

	~Wrapper()
	{
		delete m_DataPtr;
	}

	Wrapper(const Wrapper<T>& original)
	{
		if (original.m_DataPtr != 0)
			m_DataPtr = original.m_DataPtr->clone();
		else
			m_DataPtr = 0;
	}

	Wrapper& operator= (const Wrapper<T>& original)
	{
		if (*this != original)
		{
			if (m_DataPtr != 0)
				delete m_DataPtr;

			m_DataPtr = (original.m_DataPtr != 0) ? original.m_DataPtr->clone() : 0;
		}

		return *this;
	}

	inline bool operator!= (const Wrapper<T>& second) const
	{
		return m_DataPtr != second.m_DataPtr;
	}

	inline T& operator* ()
	{
		return *m_DataPtr;
	}

	inline const T& operator* () const
	{
		return *m_DataPtr;
	}

	inline T* operator-> ()
	{
		return m_DataPtr;
	}

	inline const T* const operator-> () const
	{
		return m_DataPtr;
	}

private:
	T* m_DataPtr;
};
