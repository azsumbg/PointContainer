#include "pch.h"
#include "pointcontainer.h"
#include <cstdlib>


///////////////////////////////////////////
bool point_cont_space::CONTAINER::empty() const
{
	return(m_ArrayPointer == 0);
}
size_t point_cont_space::CONTAINER::size() const
{
	return m_size;
}
void point_cont_space::CONTAINER::push_back(OnePoint data)
{
	if (m_size + 1 <= max_size)
	{
		*(m_ArrayPointer + m_size) = data;
		++m_size;
	}
}
point_cont_space::OnePoint& point_cont_space::CONTAINER::operator[] (size_t position) const
{
	OnePoint temp{ -1.0f, -1.0f };
	if (!(this->empty()) && position <= m_size - 1)return *(m_ArrayPointer + position);
	return temp;
}
///////////////////////////////////////////

float point_cont_space::FindDistance(OnePoint start, OnePoint end)
{
	float a = static_cast<float>(pow(std::abs(end.x - start.x), 2));
	float b = static_cast<float>(pow(std::abs(end.y - start.y), 2));
	return static_cast<float>(sqrt(a + b));
}


point_cont_space::OnePoint point_cont_space::FindNearestPoint(OnePoint MyPoint, CONTAINER& PointsToCheck)
{
	bool completed = false;

	while (!completed)
	{
		completed = true;

		for (size_t i = 0; i < PointsToCheck.size() - 1; i++)
		{
			if (FindDistance(MyPoint, PointsToCheck[i]) > FindDistance(MyPoint, PointsToCheck[i + 1]))
			{
				OnePoint temp = PointsToCheck[i];
				PointsToCheck[i] = PointsToCheck[i + 1];
				PointsToCheck[i + 1] = temp;
				completed = false;
			}
		}
	}
	return PointsToCheck[0];
}
