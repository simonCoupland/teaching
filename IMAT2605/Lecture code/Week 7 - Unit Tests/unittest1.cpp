#include "stdafx.h"
#include "CppUnitTest.h"

#include "vector2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Week7UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// Arrange
			Vector2D a(499, 477);

			// Act
			float x = a.getX();
			float y = a.getY();

			// Assert
			Assert::AreEqual(x, 499.f);
			Assert::AreEqual(y, 477.f);
		}

	};
}