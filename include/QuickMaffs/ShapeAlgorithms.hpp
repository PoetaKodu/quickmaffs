#pragma once

#include "Vector2.hpp"

#include "Polygon2.hpp"
#include "Ball.hpp"
#include "Box.hpp"

namespace quickmaffs
{

/// <summary>
/// Determines whether the specified point is inside a polygon shape.
/// </summary>
/// <param name="polygon_">The polygon_ shape.</param>
/// <param name="point_">The point.</param>
/// <returns>
///   <c>true</c> if point is inside; otherwise, <c>false</c>.
/// </returns>
template <typename T>
bool isPointInside(Polygon2<T> const & polygon_, Vector2< typename type_traits::identity<T>::type > const & point_);

/// <summary>
/// Determines whether the specified point is inside a ball shape.
/// </summary>
/// <param name="ball_">The ball shape.</param>
/// <param name="point_">The point.</param>
/// <returns>
///   <c>true</c> if point is inside; otherwise, <c>false</c>.
/// </returns>
template <template<typename> typename T, typename V>
constexpr bool isPointInside(Ball<T, V> const & ball_, typename Ball<T, V>::VectorType const & point_);

/// <summary>
/// Determines whether the specified point is inside a ball shape.
/// </summary>
/// <param name="box_">The box shape.</param>
/// <param name="point_">The point.</param>
/// <returns>
///   <c>true</c> if point is inside; otherwise, <c>false</c>.
/// </returns>
template <template<typename> typename T, typename V>
constexpr bool isPointInside(Box<T, V> const & box_, typename Box<T, V>::VectorType const & point_);

}

#include "Private/ShapeAlgorithms.inl"