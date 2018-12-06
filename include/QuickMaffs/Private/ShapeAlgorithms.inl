// Note: this file is not meant to be included on its own.
// Include "ShapeAlgorithms.hpp" instead.

namespace quickmaffs
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename TValueType>
bool isPointInside(Polygon2<TValueType> const & polygon_, Vector2< typename type_traits::identity<TValueType>::type > const & point_)
{
	using SizeType = typename Polygon2<TValueType>::ContainerType::size_type;

	auto const & vertices = polygon_.getPoints();
	if (vertices.size() < 3)
		return false;

	// What the fuck?
	// https://stackoverflow.com/a/2922778/4386320
	bool check = false;
	for (SizeType i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++)
	{
		if (((vertices[i].y > point_.y) != (vertices[j].y > point_.y)) &&
			(point_.x < (vertices[j].x - vertices[i].x) * (point_.y - vertices[i].y) / (vertices[j].y - vertices[i].y) +
				vertices[i].x))
		{
			check = !check;
		}
	}
	return check;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<template <typename> typename T, typename V>
constexpr bool isPointInside(Ball<T, V> const & ball_, typename Ball<T, V>::VectorType const & point_)
{
	return ball_.center.distanceSquared(point_) <= ( ball_.getRadius() * ball_.getRadius() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<template <typename> typename T, typename V>
constexpr bool isPointInside(Box<T, V> const & box_, typename Box<T, V>::VectorType const & point_)
{
	auto diff = (box_.center - point_).absolute();

	for (std::size_t i = 0; i < diff.size(); i++) {
		if (diff[i] >= box_.getHalfExtent()[i])
			return false;
	}
	return true;
}


}