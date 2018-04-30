// Note: this file is not meant to be included on its own.
// Include "Random.hpp" instead.

namespace quickmaffs::random
{

namespace detail
{
constexpr bool cxNoRandomDevice = false;

////////////////////////////////////////////////////////////////////////////////////////////////////
inline std::mt19937& getGenerator()
{
	// Note: older platforms can crash on std::random_device. If it crashes set `cxprNoRandomDevice` to true.
	if constexpr (cxNoRandomDevice)
	{
		// We need to convert system_clock::time_point::duration to int32_t seconds.
		// Simple static_cast could give incorrect values (losing precision), so we use duration_cast to int32_t seconds.
		// std::mt19937 engine constructor requires std::uint32_t seed, so best we can do is just taking an absolute value.
		// Steps of generating seed:
		//   1. Take time since epoch (system_clock::time_point::duration | most likely duration<std::int64_t, std::nano>);
		//   2. Cast it to duration<std::int32_t>;
		//   3. Get count of seconds (allow negative values) - std::int32_t;
		//   4. Get absolute seconds value;
		//   5. Cast it to std::uint32_t.
		// This method is used to prevent crashing when somebody set system time to pre-epoch (needs verification).

		using namespace std::chrono;
		using int32seconds = duration<std::int32_t>;
		static std::mt19937 generator{
			static_cast<std::uint32_t>(std::abs(duration_cast<int32seconds>(system_clock::now().time_since_epoch()).count()))
		};
		return generator;
	}
	else
	{
		// Consider using thread_local, if multiple threads are used.
		static std::mt19937 generator{ std::random_device{}() };
		return generator;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline std::mt19937_64& getGenerator64()
{
	// Note: older platforms can crash on std::random_device. If it crashes set `cxprNoRandomDevice` to true.
	if constexpr (cxNoRandomDevice)
	{
		// We need to convert system_clock::time_point::duration to int32_t seconds.
		// Simple static_cast could give incorrect values (losing precision), so we use duration_cast to int32_t seconds.
		// std::mt19937 engine constructor requires std::uint32_t seed, so best we can do is just taking an absolute value.
		// Steps of generating seed:
		//   1. Take time since epoch (system_clock::time_point::duration | most likely duration<std::int64_t, std::nano>);
		//   2. Cast it to duration<std::int32_t>;
		//   3. Get count of seconds (allow negative values) - std::int32_t;
		//   4. Get absolute seconds value;
		//   5. Cast it to std::uint32_t.
		// This method is used to prevent crashing when somebody set system time to pre-epoch (needs verification).

		using namespace std::chrono;
		using int32seconds = duration<std::int32_t>;
		static std::mt19937_64 generator{
			static_cast<std::uint32_t>(std::abs(duration_cast<int32seconds>(system_clock::now().time_since_epoch()).count()))
		};
		return generator;
	}
	else
	{
		// Consider using thread_local, if multiple threads are used.
		static std::mt19937_64 generator{ std::random_device{}() };
		return generator;
	}
}

} // namespace

//////////////////////////////////////////////////////////////////////////////
template <typename TType>
inline TType generate(TType const & from_, TType const & to_)
{
	// Check at compile time if the type is an integer.
	constexpr bool cxIsIntegerType = std::is_same_v<TType, short> || std::is_same_v<TType, unsigned short>
		|| std::is_same_v<TType, int> || std::is_same_v<TType, unsigned int>
		|| std::is_same_v<TType, long> || std::is_same_v<TType, unsigned long>
		|| std::is_same_v<TType, long long> || std::is_same_v<TType, unsigned long long>;

	// Check at compile time if the type is a floating point number.
	constexpr bool cxIsFloatType = std::is_same_v<TType, float> || std::is_same_v<TType, double> || std::is_same_v< TType, long double>;

	// Check if the type require 64 bit engine or not.
	constexpr bool cxCanUse32BitEngine = sizeof(TType) <= 4;

	// Assert compilation, when type is not supported.
	static_assert(cxIsIntegerType || cxIsFloatType, "math::random does not support this type.");

	// Calculate min and max value:
	auto[minValue, maxValue] = std::minmax(static_cast<TType>(from_), static_cast<TType>(to_));


	// For every integer type:
	if constexpr(cxIsIntegerType)
	{
		if constexpr(cxCanUse32BitEngine)
			return std::uniform_int_distribution<TType>(minValue, maxValue)(detail::getGenerator());
		else
			return std::uniform_int_distribution<TType>(minValue, maxValue)(detail::getGenerator64());
	}
	else // For every real (floating point) type:
	{
		if constexpr(cxCanUse32BitEngine)
			return std::uniform_real_distribution<TType>(minValue, maxValue)(detail::getGenerator());
		else
			return std::uniform_real_distribution<TType>(minValue, maxValue)(detail::getGenerator64());
	}
}

}