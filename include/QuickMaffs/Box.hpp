#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"

namespace quickmaffs
{

/// <summary>
/// A box shape (a cuboid or rectangle).
/// </summary>
template <template <typename> typename TVectorType, typename TValueType>
struct Box
{	
	// Aliases:
	using ValueType		= TValueType;
	using VectorType	= TVectorType<ValueType>;

	// Methods:
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	constexpr Box() = default;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> struct.
	/// </summary>
	/// <param name="center_">The center.</param>
	/// <param name="halfExtent_">The half extent.</param>
	constexpr Box(VectorType const& center_, VectorType const& halfExtent_);

	/// <summary>
	/// Sets the box full extent.
	/// </summary>
	/// <param name="extent_">The extent.</param>
	constexpr void setExtent(VectorType const& extent_);

	/// <summary>
	/// Sets the box half extent.
	/// </summary>
	/// <param name="halfExtent_">The half extent.</param>
	constexpr void setHalfExtent(VectorType const& halfExtent_);

	/// <summary>
	/// Returns box full extent.
	/// </summary>
	/// <returns>Box full extent.</returns>
	constexpr VectorType getExtent() const;

	/// <summary>
	/// Returns box half extent.
	/// </summary>
	/// <returns>Box half extent.</returns>
	constexpr VectorType getHalfExtent() const;

	VectorType center;
private:
	VectorType m_halfExtent;
};

template <typename TValueType>
using Rect2			= Box<Vector2, TValueType>;

template <typename TValueType>
using Cuboid3		= Box<Vector3, TValueType>;

using Rect2f		= Rect2<float>;
using Rect2d		= Rect2<double>;
using Rect2ld		= Rect2<long double>;
using Rect2i8		= Rect2<std::int8_t>;
using Rect2i16		= Rect2<std::int16_t>;
using Rect2i32		= Rect2<std::int32_t>;
using Rect2i64		= Rect2<std::int64_t>;
using Rect2u8		= Rect2<std::uint8_t>;
using Rect2u16		= Rect2<std::uint16_t>;
using Rect2u32		= Rect2<std::uint32_t>;
using Rect2u64		= Rect2<std::uint64_t>;

using Cuboid3f		= Cuboid3<float>;
using Cuboid3d		= Cuboid3<double>;
using Cuboid3ld		= Cuboid3<long double>;
using Cuboid3i8		= Cuboid3<std::int8_t>;
using Cuboid3i16	= Cuboid3<std::int16_t>;
using Cuboid3i32	= Cuboid3<std::int32_t>;
using Cuboid3i64	= Cuboid3<std::int64_t>;
using Cuboid3u8		= Cuboid3<std::uint8_t>;
using Cuboid3u16	= Cuboid3<std::uint16_t>;
using Cuboid3u32	= Cuboid3<std::uint32_t>;
using Cuboid3u64	= Cuboid3<std::uint64_t>;

}

#include "Private/Box.inl"