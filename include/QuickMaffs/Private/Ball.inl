// Note: this file is not meant to be included on its own.
// Include "Ball.hpp" instead.

namespace quickmaffs
{

////////////////////////////////////////////////////////////////////////////////////
template <template <typename> class TVectorType, typename TValueType>
constexpr Ball< TVectorType, TValueType >::Ball(VectorType const& center_, ValueType const radius_)
	:
	center{ center_ },
	m_radius{ radius_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
template <template <typename> class TVectorType, typename TValueType>
constexpr void Ball< TVectorType, TValueType >::setDiameter(ValueType const diameter_)
{
	m_radius = std::abs(diameter_) / static_cast< ValueType >(2);
}

////////////////////////////////////////////////////////////////////////////////////
template <template <typename> class TVectorType, typename TValueType>
constexpr void Ball< TVectorType, TValueType >::setRadius(ValueType const radius_)
{
	m_radius = std::abs(radius_);
}

////////////////////////////////////////////////////////////////////////////////////
template <template <typename> class TVectorType, typename TValueType>
constexpr typename Ball< TVectorType, TValueType >::ValueType Ball< TVectorType, TValueType >::getDiameter() const
{
	return m_radius * static_cast< ValueType >(2);
}

////////////////////////////////////////////////////////////////////////////////////
template <template <typename> class TVectorType, typename TValueType>
constexpr typename Ball< TVectorType, TValueType >::ValueType Ball< TVectorType, TValueType >::getRadius() const
{
	return m_radius;
}

}
