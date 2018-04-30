#pragma once

#include QUICKMAFFS_PCH

#include <QuickMaffs/Math/Vector2.hpp>
#include <QuickMaffs/Math/Vector3.hpp>

namespace quickmaffs
{

/// <summary>
/// A ball shape (a circle or sphere).
/// </summary>
template <template <typename> typename TVectorType, typename TValueType>
struct Ball
{
	// Aliases:
	using ValueType		= TValueType;
	using VectorType	= TVectorType<ValueType>;

	// Methods:
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	constexpr Ball() = default;

	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	/// <param name="center_">The center.</param>
	/// <param name="radius_">The radius.</param>
	constexpr Ball(VectorType const& center_, ValueType const radius_);

	/// <summary>
	/// Sets the ball diameter.
	/// </summary>
	/// <param name="extent_">The ball diameter.</param>
	constexpr void setDiameter(ValueType const diameter_);

	/// <summary>
	/// Sets the ball radius.
	/// </summary>
	/// <param name="radius_">The ball radius.</param>
	constexpr void setRadius(ValueType const radius_);

	/// <summary>
	/// Returns ball diameter.
	/// </summary>
	/// <returns>Ball diameter.</returns>
	constexpr ValueType getDiameter() const;

	/// <summary>
	/// Returns ball radius.
	/// </summary>
	/// <returns>Ball radius.</returns>
	constexpr ValueType getRadius() const;

	VectorType	center;
private:
	ValueType	m_radius;
};

template <typename TValueType>
using Circle2 = Ball<Vector2, TValueType>;

template <typename TValueType>
using Sphere3 = Ball<Vector3, TValueType>;

using Circle2f		= Circle2<float>;
using Circle2d		= Circle2<double>;
using Circle2ld		= Circle2<long double>;
using Circle2i8		= Circle2<std::int8_t>;
using Circle2i16	= Circle2<std::int16_t>;
using Circle2i32	= Circle2<std::int32_t>;
using Circle2i64	= Circle2<std::int64_t>;
using Circle2u8		= Circle2<std::uint8_t>;
using Circle2u16	= Circle2<std::uint16_t>;
using Circle2u32	= Circle2<std::uint32_t>;
using Circle2u64	= Circle2<std::uint64_t>;

using Sphere3f		= Sphere3<float>;
using Sphere3d		= Sphere3<double>;
using Sphere3ld		= Sphere3<long double>;
using Sphere3i8		= Sphere3<std::int8_t>;
using Sphere3i16	= Sphere3<std::int16_t>;
using Sphere3i32	= Sphere3<std::int32_t>;
using Sphere3i64	= Sphere3<std::int64_t>;
using Sphere3u8		= Sphere3<std::uint8_t>;
using Sphere3u16	= Sphere3<std::uint16_t>;
using Sphere3u32	= Sphere3<std::uint32_t>;
using Sphere3u64	= Sphere3<std::uint64_t>;

}


#include "Ball.inl"