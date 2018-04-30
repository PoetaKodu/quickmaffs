// Note: this file is not meant to be included on its own.
// Include "Polygon.hpp" instead.

namespace quickmaffs
{
	
////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon<TValueType>::Polygon(const ContainerType& points_)
	: m_points{ points_ }
{
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon<TValueType>::Polygon(ContainerType&& points_)
	: m_points{ std::forward< ContainerType >(points_) }
{
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
void Polygon<TValueType>::setPointCount(typename ContainerType::size_type const size_)
{
	m_points.resize(size_);
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
void Polygon<TValueType>::setPoint(typename ContainerType::size_type const index_, VertexType const& value_)
{
	m_points[index_] = value_;
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
void Polygon<TValueType>::addPoint(VertexType const& value_)
{
	m_points.push_back(value_);
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
bool Polygon<TValueType>::isPointInside(VertexType const& point_) const
{
	if (m_points.size() < 3)
		return false;

	// What the fuck?
	// https://stackoverflow.com/a/2922778/4386320
	bool check = false;
	for (typename ContainerType::size_type i = 0, j = m_points.size() - 1; i < m_points.size(); j = i++)
	{
		if (((m_points[i].y > point_.y) != (m_points[j].y > point_.y)) &&
			(point_.x < (m_points[j].x - m_points[i].x) * (point_.y - m_points[i].y) / (m_points[j].y - m_points[i].y) +
				m_points[i].x))
		{
			check = !check;
		}
	}
	return check;
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
typename Polygon<TValueType>::ContainerType::size_type Polygon<TValueType>::getPointCount() const
{
	return m_points.size();
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
typename Polygon<TValueType>::ContainerType const& Polygon< TValueType >::getPoints() const
{
	return m_points;
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon<TValueType> Polygon<TValueType>::rectangle(ValueType const width_, ValueType const height_, bool const centered_)
{
	if (centered_)
	{
		return Polygon{
				{
					{ -width_ / ValueType(2), -height_ / ValueType(2) }, // top left
					{  width_ / ValueType(2), -height_ / ValueType(2) }, // top right
					{  width_ / ValueType(2),  height_ / ValueType(2) }, // bottom right
					{ -width_ / ValueType(2),  height_ / ValueType(2) }, // bottom left
				}
			};
	}
	else
	{
		return Polygon{
				{
					{ ValueType(0), ValueType(0) }, // top left
					{ width_,		ValueType(0) }, // top right
					{ width_,		height_ }, // bottom right
					{ ValueType(0), height_ }, // bottom left
				}
			};
	}
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon<TValueType> Polygon<TValueType>::square(ValueType const size_, bool const centered_)
{
	return Polygon::rectangle(size_, size_, centered_);
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon<TValueType> Polygon<TValueType>::ellipse(ValueType const xRadius_, ValueType const yRadius_,
													std::size_t pointCount_)
{
	pointCount_ = std::max(std::size_t(3), pointCount_);

	ContainerType points(pointCount_);
	for (std::size_t i = 0; i < pointCount_; ++i)
	{
		double const angleRad = convertToRadians(i * (360.0 / pointCount_));
		points[i] = {
				static_cast< ValueType >(std::cos(angleRad) * xRadius_),
				static_cast< ValueType >(std::sin(angleRad) * yRadius_)
			};
	}

	return Polygon{ std::move(points) };
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon<TValueType> Polygon<TValueType>::circle(ValueType const radius_, std::size_t pointCount_)
{
	return Polygon::ellipse(radius_, radius_, pointCount_);
}

}