// File description:
// Implements base class for 3D vector manipulation.
// TODO: implement iterators for Vector3.

#pragma once

// Precompiled header:
#include QUICKMAFFS_PCH

// Custom includes:
#include "Helper.hpp"
#include "VectorStringBuilder.hpp"

#include "TypeTraits.hpp"

namespace quickmaffs
{

/// <summary>
/// Implements templated three dimensional vector arithmetic class.
/// </summary>
template <typename TVectorType>
class Vector3
{
public:
	using ValueType = TVectorType;

	// Allow every non-cv qualified arithmetic type but bool.
	static_assert(
		type_traits::isMathScalarV<ValueType>,
		"ValueType of a vector must be a non-cv qualified scalar type."
	);

	ValueType x, y, z;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Vector3"/> class.
	/// </summary>
	constexpr Vector3()
		: x{ 0 }, y{ 0 }, z{ 0 }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="Vector3"/> class.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	/// <param name="z_">The z value.</param>
	constexpr Vector3(ValueType const x_, ValueType const y_, ValueType const z_)
		: x{ x_ }, y{ y_ }, z{ z_ }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="Vector3"/> class.
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	constexpr Vector3(Vector3 const &rhs_)
		: x{ rhs_.x }, y{ rhs_.y }, z{ rhs_.z }
	{
	}

	/// <summary>
	/// Returns number of components contained by this vector.
	/// </summary>
	/// <returns>Number of components contained by this vector</returns>
	constexpr std::size_t size() const {
		return 3;
	}

	/// <summary>
	/// Sets values of the vector.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	/// <param name="z_">The z value.</param>
	constexpr void set(ValueType const x_, ValueType const y_, ValueType const z_)
	{
		x = static_cast<ValueType>(x_);
		y = static_cast<ValueType>(y_);
		z = static_cast<ValueType>(z_);
	}

	// not constexpr - std::sqrt is not constexpr :(
	/// <summary>
	/// Returns length of the vector.
	/// </summary>
	/// <returns>Length of the vector.</returns>
	template <typename TLengthType = ValueType,
		typename = std::enable_if_t< type_traits::isMathScalarV<TLengthType> > >
	TLengthType length() const
	{
		if constexpr(std::is_same_v<TLengthType, ValueType>)
			return std::sqrt(x * x + y * y + z * z);
		else
		{
			auto conv = this->convert<TLengthType>();
			return std::sqrt(conv.x * conv.x + conv.y * conv.y + conv.z * conv.z);
		}
	}

	/// <summary>
	/// Returns squared length of the vector.
	/// </summary>
	/// <returns>Squared length of the vector.</returns>
	template <typename TLengthType = ValueType,
		typename = std::enable_if_t< type_traits::isMathScalarV<TLengthType> > >
	constexpr TLengthType lengthSquared() const
	{
		if constexpr(std::is_same_v<TLengthType, ValueType>)
			return x * x + y * y + z * z;
		else
		{
			auto conv = this->convert<TLengthType>();
			return static_cast<TLengthType>(conv.x * conv.x + conv.y * conv.y + conv.z * conv.z);
		}
	}

	// not constexpr - length() is not constexpr :(
	/// <summary>
	/// Computes distance between two instances.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Distance between two instances.</returns>
	template <typename TDistanceType = ValueType,
		typename = std::enable_if_t< type_traits::isMathScalarV<TDistanceType> > >
	TDistanceType distance(Vector3 const & other_) const
	{
		return (*this - other_).template length<TDistanceType>();
	}
	
	/// <summary>
	/// Computes squared distance between two instances.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Squared distance between two instances.</returns>
	template <typename TDistanceType = ValueType,
		typename = std::enable_if_t< type_traits::isMathScalarV<TDistanceType> > >
	constexpr TDistanceType distanceSquared(Vector3 const & other_) const
	{
		return (*this - other_).template lengthSquared<TDistanceType>();
	}

	/// <summary>
	/// Computes dot product of two vectors (this and other).
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Dot product of two vectors.</returns>
	template <typename TDotType = ValueType,
		typename = std::enable_if_t< type_traits::isMathScalarV<TDotType> > >
	constexpr TDotType dot(Vector3 const & other_) const
	{
		if constexpr(std::is_same_v<TDotType, ValueType>)
			return x * other_.x + y * other_.y + z * other_.z;
		else
		{
			auto convThis = this->convert<TDotType>();
			auto convOther = other_.convert<TDotType>();

			return static_cast<TDotType>(
				convThis.x * convOther.x +
				convThis.y * convOther.y +
				convThis.z * convOther.z
				);
		}
	}

	/// <summary>
	/// Computes cross product of two vectors (this and other_).
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Cross product of two vectors.</returns>
	constexpr Vector3 cross(Vector3 const & other_) const
	{
		return Vector3{
			y * other_.z - z * other_.y,
			z * other_.x - x * other_.z,
			x * other_.y - y * other_.x
		};
	}

	/// <summary>
	/// Computes reflection vector of specified normal.
	/// </summary>
	/// <param name="normal_">The surface normal.</param>
	/// <returns>Reflection vector of specified normal</returns>
	constexpr Vector3 reflect(Vector3 const & normal_) const
	{
		auto normal = normal_.normalize();
		return (*this) - (normal * normal.dot(*this) * ValueType { 2 });
	}

	/// <summary>
	/// Computes reflection vector of specified normal and assigns it to self.
	/// </summary>
	/// <param name="normal_">The normal.</param>
	/// <returns>Reference to self after computing reflection of specified normal.</returns>
	constexpr Vector3& reflectSelf(Vector3 const & normal_)
	{
		auto normal = normal_.normalize();
		*this -= normal * normal.dot(*this) * ValueType { 2 };
		return *this;
	}

	/// <summary>
	/// Computes normalized vector.
	/// </summary>
	/// <returns>Normalized vector</returns>
	constexpr Vector3 normalize() const
	{
		auto len = this->length();
		if (len != 0) {
			return  Vector3{ x / len, y / len, z / len };
		}
		return *this;
	}

	/// <summary>
	/// Normalizes self and returns reference.
	/// </summary>
	/// <returns>Reference to normalized self.</returns>
	constexpr Vector3& normalizeSelf()
	{
		auto len = this->length();
		if (len != 0) {
			x /= len; y /= len; z /= len;
		}
		return *this;
	}

	/// <summary>
	/// Returns vector with absolute values.
	/// </summary>
	/// <returns>Vector with absolute values.</returns>
	Vector3 absolute() const
	{
		return Vector3{ std::abs(x), std::abs(y), std::abs(y) };
	}

	// yet non-constexpr
	/// <summary>
	/// Converts vector to string.
	/// </summary>
	/// <param name="setup_">The string building setup.</param>
	/// <returns>Vector converted to std::string.</returns>
	std::string toString(VectorStringBuilder const & setup_ = VectorStringBuilder{}) const
	{
		std::stringstream stream;
		switch (setup_.wrap)
		{
		case VectorStringBuilder::Wrap::Round:	{ stream << "( "; break; }
		case VectorStringBuilder::Wrap::Square: { stream << "[ "; break; }
		case VectorStringBuilder::Wrap::Curly:	{ stream << "{ "; break; }
		default: break;
		}

		if (setup_.mantissaFixed)
			stream << std::fixed;

		stream.precision(setup_.precision);

		switch (setup_.compVisibility)
		{
		case VectorStringBuilder::CompVisibility::WithColon: {
			stream	<< "x: " << x << setup_.separator << ' '
					<< "y: " << y << setup_.separator << ' '
					<< "z: " << z;
			break;
		}
		case VectorStringBuilder::CompVisibility::WithEqual: {
			stream	<< "x = " << x << setup_.separator << ' '
					<< "y = " << y << setup_.separator << ' '
					<< "z = " << z;
			break;
		}
		default: {
			stream << x << setup_.separator << ' ' << y << setup_.separator << ' ' << z;
			break;
		}
		}

		switch (setup_.wrap)
		{
		case VectorStringBuilder::Wrap::Round:	{ stream << " )"; break; }
		case VectorStringBuilder::Wrap::Square: { stream << " ]"; break; }
		case VectorStringBuilder::Wrap::Curly:	{ stream << " }"; break; }
		default: break;
		}
		return stream.str();
	}

	/// <summary>
	/// Checks if two vectors are equal.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <param name="EqualityTolerance">The equality tolerance.</param>
	/// <returns>
	///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename TEqualityType = ValueType,
		typename = std::enable_if_t< std::is_floating_point_v<TEqualityType> > >
	constexpr bool nearlyEqual(Vector3 const & other_, TEqualityType const equalityTolerance_ = constants::LowTolerance<TEqualityType>) const
	{
		return (
			std::abs(static_cast<TEqualityType>(x) - static_cast<TEqualityType>(other_.x)) <= equalityTolerance_ &&
			std::abs(static_cast<TEqualityType>(y) - static_cast<TEqualityType>(other_.y)) <= equalityTolerance_ &&
			std::abs(static_cast<TEqualityType>(z) - static_cast<TEqualityType>(other_.z)) <= equalityTolerance_
			);
	}

	/// <summary>
	/// Computes lower bound vector of the two specified.
	/// </summary>
	/// <param name="left_">The lhs vector.</param>
	/// <param name="right_">The rhs vector.</param>
	/// <returns>Vector with components:
	/// { x = min(left_.x, right_.x), y = min(left_.y, right_.y), z = min(left_.z, right_.z)  }
	/// </returns>
	constexpr static Vector3 lowerBounds(Vector3 const &left_, Vector3 const & right_)
	{
		return Vector3{ std::min(left_.x, right_.x), std::min(left_.y, right_.y), std::min(left_.z, right_.z) };
	}

	/// <summary>
	/// Computes upper bound vector of the two specified.
	/// </summary>
	/// <param name="left_">The lhs vector.</param>
	/// <param name="right_">The rhs vector.</param>
	/// <returns>Vector with components:
	/// { x = max(left_.x, right_.x), y = max(left_.y, right_.y), z = max(left_.z, right_.z)  }
	/// </returns>
	constexpr static Vector3 upperBounds(Vector3 const & left_, Vector3 const & right_)
	{
		return Vector3{ std::max(left_.x, right_.x), std::max(left_.y, right_.y), std::min(left_.z, right_.z) };
	}

	/// <summary>
	/// Computes lower and upper bounds for two specified vectors.
	/// </summary>
	/// <param name="lower_">The lower bound vector.</param>
	/// <param name="upper_">The upper bound vecor.</param>
	/// <remarks>
	/// <para>Uses arguments as output, changes its values.</para>
	/// </remarks>
	constexpr static void bounds(Vector3 & lower_, Vector3 & upper_)
	{
		Vector3 const tempMin = lower_;
		lower_ = Vector3::lowerBounds(lower_, upper_);
		upper_ = Vector3::upperBounds(tempMin, upper_);
	}

	/// <summary>
	/// Converts vector to other type.
	/// </summary>
	/// <returns>Vector of other value type.</returns>
	template <typename TVectorType2>
	constexpr Vector3<TVectorType2> convert() const
	{
		return Vector3<TVectorType2>{
			static_cast<TVectorType2>(x),
			static_cast<TVectorType2>(y),
			static_cast<TVectorType2>(z)
		};
	}

	//////////////////////////////////////
	// Operators:
	//////////////////////////////////////

	/// <summary>
	/// Returns component with specified index by ref.
	/// </summary>
	/// <param name="index_">The component index (either 0, 1 or 2).</param>
	/// <returns>Component with specified index by ref.</returns>
	constexpr ValueType& operator[](std::size_t const index_)
	{
		switch (index_)
		{
		case 0: { return x; }
		case 1: { return y; }
		case 2: { return z; }
		default: throw std::out_of_range{ "Vector3 class has 3 components - x (id 0), y (id 1) and z (id 2)!" };
		}
	}

	/// <summary>
	/// Returns component with specified index by value.
	/// </summary>
	/// <param name="index_">The component index (either 0, 1 or 2).</param>
	/// <returns>Component with specified index by value.</returns>
	constexpr ValueType operator[](std::size_t const index_) const
	{
		switch (index_)
		{
		case 0: { return x; }
		case 1: { return y; }
		case 2: { return z; }
		default: throw std::out_of_range{ "Vector3 class has 3 components - x (id 0), y (id 1) and z (id 2)!" };
		}
	}

	/// <summary>
	/// Assigns vector to self.
	/// </summary>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self.</returns>
	constexpr Vector3 & operator = (Vector3 const & rhs_) = default;

	/// <summary>
	/// Negates vector.
	/// </summary>
	/// <returns>Negated vector.</returns>
	constexpr Vector3 operator - () const {
		return Vector3{-x, -y, -z};
	}

	/// <summary>
	/// Checks if lhs vector is equal to rhs vector (with low tolerance).
	/// </summary>
	/// <param name="vector_">The other vector.</param>
	/// <returns>
	///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
	/// </returns>
	constexpr bool operator == (Vector3 const & vector_) const {
		return equals(vector_, constants::LowTolerance<ValueType>);
	}

	/// <summary>
	/// Checks if lhs vector is not equal to rhs vector (with low tolerance).
	/// </summary>
	/// <param name="vector_">The other vector.</param>
	/// <returns>
	///  <c>true</c> if vectors are not equal; otherwise, <c>false</c>.
	/// </returns>
	constexpr bool operator != (Vector3 const & vector_) const {
		return !equals(vector_, constants::LowTolerance<ValueType>);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Operators (vector& <op> rhs vector).
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="vector_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr Vector3& operator += (Vector3 const & vector_)
	{
		x += vector_.x; y += vector_.y; z += vector_.z;
		return *this;
	}

	/// <summary>
	/// Subtracts rhs vector from lhs one.
	/// </summary>
	/// <param name="vector_">The rhs vector.</param>
	/// <returns>Reference to self after operation.</returns>
	constexpr Vector3& operator -= (Vector3 const & vector_)
	{
		x -= vector_.x; y -= vector_.y; z -= vector_.z;
		return *this;
	}

	/// <summary>
	/// Multiplies two vectors.
	/// </summary>
	/// <param name="vector_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr Vector3& operator *= (Vector3 const & vector_)
	{
		x *= vector_.x; y *= vector_.y; z *= vector_.z;
		return *this;
	}

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="vector_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr Vector3& operator /= (Vector3 const & vector_)
	{
		x /= vector_.x; y /= vector_.y; z /= vector_.z;
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Operators (vector& <op> rhs scalar).
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds scalar to a vector.
	/// </summary>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector plus a scalar.</returns>
	constexpr Vector3& operator += (ValueType const scalar_)
	{
		x += scalar_; y += scalar_; z += scalar_;
		return *this;
	}

	/// <summary>
	/// Substracts scalar from a vector.
	/// </summary>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector minus a scalar.</returns>
	constexpr Vector3& operator -= (ValueType const scalar_)
	{
		x -= scalar_; y -= scalar_; z -= scalar_;
		return *this;
	}

	/// <summary>
	/// Multiplies vector by a scalar.
	/// </summary>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector times a scalar.</returns>
	constexpr Vector3& operator *= (ValueType const scalar_)
	{
		x *= scalar_; y *= scalar_; z *= scalar_;
		return *this;
	}

	/// <summary>
	/// Divides vector by a scalar.
	/// </summary>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector divided by a scalar.</returns>
	constexpr Vector3& operator /= (ValueType const scalar_)
	{
		x /= scalar_; y /= scalar_; z /= scalar_;
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Operators (lhs vector <op> rhs vector).
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="left_">The lhs vector.</param>
	/// <param name="right_">The rhs vector.</param>
	/// <returns>Sum of two vectors.</returns>
	friend constexpr Vector3 operator + (Vector3 const & left_, Vector3 const & right_)
	{
		return { left_.x + right_.x, left_.y + right_.y, left_.z + right_.z };
	}

	/// <summary>
	/// Subtracts rhs vector from lhs one.
	/// </summary>
	/// <param name="left_">The lhs vector.</param>
	/// <param name="right_">The rhs vector.</param>
	/// <returns>Difference of two vectors.</returns>
	friend constexpr Vector3 operator - (Vector3 const & left_, Vector3 const & right_)
	{
		return { left_.x - right_.x, left_.y - right_.y, left_.z - right_.z };
	}

	/// <summary>
	/// Multiplies two vectors.
	/// </summary>
	/// <param name="left_">The lhs vector.</param>
	/// <param name="right_">The rhs vector.</param>
	/// <returns>Product of two vectors.</returns>
	friend constexpr Vector3 operator * (Vector3 const & left_, Vector3 const & right_)
	{
		return { left_.x * right_.x, left_.y * right_.y, left_.z * right_.z };
	}

	/// <summary>
	/// Divides lhs vector by rhs vector.
	/// </summary>
	/// <param name="left_">The lhs vector.</param>
	/// <param name="right_">The rhs vector.</param>
	/// <returns>Quotient of two vectors.</returns>
	friend constexpr Vector3 operator / (Vector3 const & left_, Vector3 const & right_)
	{
		return { left_.x / right_.x, left_.y / right_.y, left_.z / right_.z };
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Operators (lhs vector <op> rhs scalar).
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds scalar to a vector.
	/// </summary>
	/// <param name="vector_">The lhs vector.</param>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector plus a scalar.</returns>
	friend constexpr Vector3 operator + (Vector3 const & vector_, ValueType const scalar_)
	{
		return { vector_.x + scalar_, vector_.y + scalar_, vector_.z + scalar_ };
	}

	/// <summary>
	/// Substracts scalar from a vector.
	/// </summary>
	/// <param name="vector_">The lhs vector.</param>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector minus a scalar.</returns>
	friend constexpr Vector3 operator - (Vector3 const & vector_, ValueType const scalar_)
	{
		return { vector_.x - scalar_, vector_.y - scalar_, vector_.z - scalar_ };
	}

	/// <summary>
	/// Multiplies vector by a scalar.
	/// </summary>
	/// <param name="vector_">The lhs vector.</param>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector times a scalar.</returns>
	friend constexpr Vector3 operator * (Vector3 const & vector_, ValueType const scalar_)
	{
		return { vector_.x * scalar_, vector_.y * scalar_, vector_.z * scalar_ };
	}

	/// <summary>
	/// Divides vector by a scalar.
	/// </summary>
	/// <param name="vector_">The lhs vector.</param>
	/// <param name="scalar_">The scalar.</param>
	/// <returns>Vector divided by a scalar.</returns>
	friend constexpr Vector3 operator / (Vector3 const & vector_, ValueType const scalar_)
	{
		return { vector_.x / scalar_, vector_.y / scalar_, vector_.z / scalar_ };
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Operators (lhs scalar <op> rhs vector).
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds scalar to a vector.
	/// </summary>
	/// <param name="scalar_">The scalar.</param>
	/// <param name="vector_">The rhs vector.</param>
	/// <returns>Vector plus a scalar.</returns>
	friend constexpr Vector3 operator + (ValueType const scalar_, Vector3 const & vector_)
	{
		return { vector_.x + scalar_, vector_.y + scalar_, vector_.z + scalar_ };
	}

	/// <summary>
	/// Multiplies vector by a scalar.
	/// </summary>
	/// <param name="scalar_">The scalar.</param>
	/// <param name="vector_">The rhs vector.</param>
	/// <returns>Vector times a scalar.</returns>
	friend constexpr Vector3 operator * (ValueType const scalar_, Vector3 const & vector_)
	{
		return { vector_.x * scalar_, vector_.y * scalar_, vector_.z * scalar_ };
	}
};



// 3D Vector class templated with float
using Vector3f		= Vector3<float>;
// 3D Vector class templated with double
using Vector3d		= Vector3<double>;
// 3D Vector class templated with long double
using Vector3ld		= Vector3<long double>;
// 3D Vector class templated with std::int8_t
using Vector3i8		= Vector3<std::int8_t>;
// 3D Vector class templated with std::int16_t
using Vector3i16	= Vector3<std::int16_t>;
// 3D Vector class templated with std::int32_t
using Vector3i32	= Vector3<std::int32_t>;
// 3D Vector class templated with std::int64_t
using Vector3i64	= Vector3<std::int64_t>;
// 3D Vector class templated with std::int8_t
using Vector3u8		= Vector3<std::uint8_t>;
// 3D Vector class templated with std::uint16_t
using Vector3u16	= Vector3<std::uint16_t>;
// 3D Vector class templated with std::uint32_t
using Vector3u32	= Vector3<std::uint32_t>;
// 3D Vector class templated with std::uint64_t
using Vector3u64	= Vector3<std::uint64_t>;

// 3D Vector class templated with std::size_t
using Vector3size	= Vector3<std::size_t>;

} // namespace agdk
