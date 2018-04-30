#include "QuickMaffsTestsPCH.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuickMaffsTests
{		
	TEST_CLASS(ShapesAlgorithmTests)
	{
	public:
		
		TEST_METHOD(Should_return_true_if_point_is_inside_circle)
		{
			struct TestCaseType {
				math::Circle2f	circle;
				math::Vector2f	point;
				bool			expectedValue;
			};

			std::vector<TestCaseType> testCases = {
				{ { { 20, 20 }, 10 }, { 16, 22 }, true },
				{ { { 20, 20 }, 2 }, { 16, 22 }, false },
			};

			for(auto const & testCase : testCases)
			{
				bool const result = math::isPointInside(testCase.circle, testCase.point);

				Assert::AreEqual(testCase.expectedValue, result, L"", LINE_INFO());
			}
		}
	};
}