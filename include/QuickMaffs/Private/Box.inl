// Note: this file is not meant to be included on its own.
// Include "Box.hpp" instead.

namespace quickmaffs
{

template <template <typename> class TVectorType, typename TValueType>
constexpr Box< TVectorType, TValueType >::Box(VectorType const& center_, VectorType const& halfExtent_)
	:
	center{ center_ },
	m_halfExtent{ halfExtent_ }
{
}

template <template <typename> class TVectorType, typename TValueType>
constexpr void Box< TVectorType, TValueType >::setExtent(VectorType const& extent_)
{
	m_halfExtent = extent_.absolute() / static_cast< ValueType >(2);
}

template <template <typename> class TVectorType, typename TValueType>
constexpr void Box< TVectorType, TValueType >::setHalfExtent(VectorType const& halfExtent_)
{
	m_halfExtent = halfExtent_.absolute();
}

template <template <typename> class TVectorType, typename TValueType>
constexpr typename Box< TVectorType, TValueType >::VectorType Box< TVectorType, TValueType >::getExtent() const
{
	return m_halfExtent * static_cast< ValueType >(2);
}

template <template <typename> class TVectorType, typename TValueType>
constexpr typename Box< TVectorType, TValueType >::VectorType Box< TVectorType, TValueType >::getHalfExtent() const
{
	return m_halfExtent;
}

}