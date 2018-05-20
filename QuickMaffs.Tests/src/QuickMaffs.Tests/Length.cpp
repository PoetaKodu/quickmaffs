#include "QuickMaffsTestsPCH.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuickMaffsTests
{
TEST_CLASS(LengthTests)
{
public:

	TEST_METHOD(Should_return_length_converted_to_kilometers)
	{
		constexpr double cxMaxError			= 0.001;
		constexpr double cxExpectedValue	= 2.0 / 1000.0;

		constexpr math::Meters twoMeters = 2.0;
		Assert::IsTrue(std::abs(math::Kilometers{ twoMeters }.value - cxExpectedValue) <= cxMaxError);
	}
};
}