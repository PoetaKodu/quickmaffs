// Note: this file is not meant to be included on its own.
// Include "Polygon2.hpp" instead.

namespace quickmaffs
{
	
////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon2<TValueType>::Polygon2(const ContainerType& points_)
	: m_points{ points_ }
{
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon2<TValueType>::Polygon2(ContainerType&& points_)
	: m_points{ std::forward< ContainerType >(points_) }
{
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
void Polygon2<TValueType>::setPointCount(typename ContainerType::size_type const size_)
{
	m_points.resize(size_);
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
void Polygon2<TValueType>::setPoint(typename ContainerType::size_type const index_, VertexType const& value_)
{
	m_points[index_] = value_;
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
void Polygon2<TValueType>::addPoint(VertexType const& value_)
{
	m_points.push_back(value_);
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
typename Polygon2<TValueType>::ContainerType::size_type Polygon2<TValueType>::getPointCount() const
{
	return m_points.size();
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
typename Polygon2<TValueType>::ContainerType const& Polygon2< TValueType >::getPoints() const
{
	return m_points;
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon2<TValueType> Polygon2<TValueType>::rectangle(ValueType const width_, ValueType const height_, bool const centered_)
{
	if (centered_)
	{
		return Polygon2{
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
		return Polygon2{
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
Polygon2<TValueType> Polygon2<TValueType>::square(ValueType const size_, bool const centered_)
{
	return Polygon2::rectangle(size_, size_, centered_);
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon2<TValueType> Polygon2<TValueType>::ellipse(ValueType const xRadius_, ValueType const yRadius_,
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

	return Polygon2{ std::move(points) };
}

////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
Polygon2<TValueType> Polygon2<TValueType>::circle(ValueType const radius_, std::size_t pointCount_)
{
	return Polygon2::ellipse(radius_, radius_, pointCount_);
}

}