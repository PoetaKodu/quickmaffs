#pragma once

#include QUICKMAFFS_PCH

#include <QuickMaffs/Math/Vector2.hpp>
#include <QuickMaffs/Math/TypeTraits.hpp>

namespace quickmaffs
{

/// <summary>
/// Provides basic polygon implementation.
/// </summary>
template <typename TValueType>
class Polygon2
{
public:

	using ValueType			= TValueType;
	using VertexType		= Vector2<TValueType>;
	using ContainerType		= std::vector< VertexType >;

	// Allow every non-cv qualified arithmetic type but bool.
	static_assert(
		type_traits::isMathScalarV<ValueType>,
		"ValueType of a polygon must be a non-cv qualified math scalar type."
	);

	/// <summary>
	/// Initializes a new instance of the <see cref="Polygon2"/> class.
	/// </summary>
	Polygon2() = default;

	/// <summary>
	/// Initializes a new instance of the <see cref="Polygon2"/> class.
	/// </summary>
	/// <param name="points_">The points.</param>
	Polygon2(const ContainerType& points_);

	/// <summary>
	/// Initializes a new instance of the <see cref="Polygon2"/> class.
	/// </summary>
	/// <param name="points_">The points.</param>
	Polygon2(ContainerType&& points_);

	/// <summary>
	/// Sets the point count.
	/// </summary>
	/// <param name="size_">The size.</param>
	void setPointCount(typename ContainerType::size_type const size_);

	/// <summary>
	/// Sets the point with specified index position.
	/// </summary>
	/// <param name="index_">The index.</param>
	/// <param name="value_">The value.</param>
	void setPoint(typename ContainerType::size_type const index_, VertexType const& value_);

	/// <summary>
	/// Adds the point to the end of the point list.
	/// </summary>
	/// <param name="value_">The value.</param>
	void addPoint(VertexType const& value_);

	/// <summary>
	/// Determines whether the specified point is inside polygon.
	/// </summary>
	/// <param name="point_">The point.</param>
	/// <returns>
	///   <c>true</c> if point is inside; otherwise, <c>false</c>.
	/// </returns>
	bool isPointInside(VertexType const& point_) const;

	/// <summary>
	/// Returns the point count.
	/// </summary>
	/// <returns>Point count.</returns>
	typename ContainerType::size_type getPointCount() const;

	/// <summary>
	/// Returns cref to point container.
	/// </summary>
	/// <returns>Point container by cref.</returns>
	ContainerType const& getPoints() const;

	/// <summary>
	/// Creates rectangle-shaped polygon with specified width and height.
	/// </summary>
	/// <param name="width_">The width.</param>
	/// <param name="height_">The height.</param>
	/// <returns>Rectangle shaped polygon.</returns>
	static Polygon2 rectangle(ValueType const width_, ValueType const height_, bool const centered_ = true);

	/// <summary>
	/// Creates square shaped polygon with specified edge length.
	/// </summary>
	/// <param name="size_">The size.</param>
	/// <returns>Square shaped polygon.</returns>
	static Polygon2 square(ValueType const size_, bool const centered_ = true);

	/// <summary>
	/// Creates ellipse shaped polygon with specified x-axis radius and y-axis radius.
	/// </summary>
	/// <param name="xRadius_">The x radius.</param>
	/// <param name="yRadius_">The y radius.</param>
	/// <param name="pointCount_">The point count.</param>
	/// <returns>Ellipse shaped polygon.</returns>
	static Polygon2 ellipse(ValueType const xRadius_, ValueType const yRadius_, std::size_t pointCount_ = 32);

	/// <summary>
	/// Creates circle shaped polygon with specified radius.
	/// </summary>
	/// <param name="radius_">The radius.</param>
	/// <param name="pointCount_">The point count.</param>
	/// <returns>Circle shaped polygon.</returns>
	static Polygon2 circle(ValueType const radius_, std::size_t pointCount_ = 32);

protected:
	ContainerType m_points; // List (vector) of 2d points. Interpreted as connected lines, each starting at the end of previous. Last line connects last point to the first one.
};

// 2D Polygon class templated with float
using Polygon2f = Polygon2<float>;
// 2D Polygon class templated with double
using Polygon2d = Polygon2<double>;
// 2D Polygon class templated with long double
using Polygon2ld = Polygon2<long double>;
// 2D Polygon class templated with std::int8_t
using Polygon2i8 = Polygon2<std::int8_t>;
// 2D Polygon class templated with std::int16_t
using Polygon2i16 = Polygon2<std::int16_t>;
// 2D Polygon class templated with std::int32_t
using Polygon2i32 = Polygon2<std::int32_t>;
// 2D Polygon class templated with std::int64_t
using Polygon2i64 = Polygon2<std::int64_t>;
// 2D Polygon class templated with std::uint8_t
using Polygon2u8 = Polygon2<std::uint8_t>;
// 2D Polygon class templated with std::uint16_t
using Polygon2u16 = Polygon2<std::uint16_t>;
// 2D Polygon class templated with std::uint32_t
using Polygon2u32 = Polygon2<std::uint32_t>;
// 2D Polygon class templated with std::uint64_t
using Polygon2u64 = Polygon2<std::uint64_t>;

// 2D Polygon class templated with std::size_t
using Polygon2size = Polygon2<std::size_t>;

}

#include "Polygon2.inl"