// Note: this file is not meant to be included on its own.
// Include "Helper.hpp" instead.

namespace quickmaffs
{

////////////////////////////////////////////////////////////////////////
template <typename TType>
inline void minMaxRef(TType & lower_, TType & higher_)
{
	if (lower_ > higher_)
		std::swap(lower_, higher_);
}

////////////////////////////////////////////////////////////////////////
template <typename TType>
inline bool nearlyEqual(TType const & a_, TType const & b_, TType const & equalityTolerance_)
{
	return std::abs(a_ - b_) <= equalityTolerance_;
}

////////////////////////////////////////////////////////////////////////
template <typename TType>
inline TType clampChecked(TType const & current_, TType const & lowerBoundary_, TType const & upperBoundary_)
{
	auto[lower, upper] = std::minmax(lowerBoundary_, upperBoundary_);
	return std::clamp(current_, lower, upper);
}

////////////////////////////////////////////////////////////////////////
template <typename TType>
inline TType convertToRadians(TType const degrees_)
{
	return degrees_ / static_cast<TType>(180) * constants::Pi<TType>;
}

////////////////////////////////////////////////////////////////////////
template <typename TType>
inline TType convertToDegrees(TType const radians_)
{
	return radians_ * static_cast<TType>(180) / constants::Pi<TType>;
}

} // namespace