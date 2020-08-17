#pragma once
#include <vector>

template <typename T>
class Matrix
{
private:
	unsigned int width;
	unsigned int height;
	std::vector<T> data;
public:
	// Skapar en tom matris.
	Matrix()
		: width(0),
		  height(0) {}

	// Skapar en matris.
	Matrix(unsigned int width, unsigned int height)
		: width(width),
		  height(height),
		  data(std::size_t(width) * std::size_t(height)) {}

	/*
	 * Tillgång utan gränskontroller.
	 * Användning: matris[x][y]
	*/
	T* operator[](unsigned int x)
	{
		return &data[x * height];
	}

	/*
	 * Const-tillgång utan gränskontroller.
	 * Användning: matris[x][y]
	*/
	const T* operator[](unsigned int x) const
	{
		return &data[x * height];
	}

	// Tillgång med gränskontroller.
	T& at(unsigned int x, unsigned int y)
	{
		if (x >= 0 &&
			x < width &&
			y >= 0 &&
			y < height)
		{
			return data[y + x * height];
		}
		else
		{
			throw std::out_of_range("Matrix cell out of range");
		}
	}

	// Const-tillgång med gränskontroller.
	const T& at(unsigned int x, unsigned int y) const
	{
		if (x >= 0 &&
			x < width &&
			y >= 0 &&
			y < height)
		{
			return data[y + x * height];
		}
		else
		{
			throw std::out_of_range("Matrix cell out of range");
		}
	}

	// Ändrar (x, y) till t om det är en giltig position, annars händer inget.
	void set(unsigned int x, unsigned int y, T t)
	{
		if (x >= 0 &&
			x < width &&
			y >= 0 &&
			y < height)
		{
			data[y + x * height] = std::move(t);
		}
	}

	unsigned int getWidth() const noexcept
	{
		return width;
	}

	unsigned int getHeight() const noexcept
	{
		return height;
	}
};