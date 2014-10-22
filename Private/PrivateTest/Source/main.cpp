#ifndef __PRIVATE_TEST__
#define __PRIVATE_TEST__

#include <iostream>

class PrivateTest;
typedef void(PrivateTest::* PrivateMethod)();

// basic class for test.
class PrivateTest
{
	private:
		// Private attribute, just editable inside the class.
		int privateAttribute = 10;
		void privateMethod()
		{
			std::cout << "Private Method Called." << std::endl;
		}

	public:
		
		// Test method, assign the address of the private attribute to the param-pointer.
		void testAttributeAddress(int ** ptr) const
		{
			*ptr = const_cast<int*>(&privateAttribute);
		}

		void testMethodAddress(PrivateMethod *ptrMethod)
		{
			*ptrMethod = &PrivateTest::privateMethod;
			std::cout << "Private Method Address[iinside]: " << ptrMethod << std::endl;
		}

		// Just to show that the "value" attribute was changed outside of the class.
		void showValue() const
		{
			std::cout << "Private Attribute Address[iinside]: " << &privateAttribute << std::endl;
			std::cout << "Value: " << privateAttribute << std::endl;
		}
};
#endif

int main(int argc, char** argv)
{
	// ---------------------------------------------- Private Attribute Test.
	PrivateTest * tmp = new PrivateTest;
	tmp -> showValue();
	int * ptrValue = nullptr;
	tmp->testAttributeAddress(&ptrValue);
	std::cout << "Private Attribute Address[outside]: " << ptrValue << std::endl;
	*ptrValue = 50;
	tmp -> showValue();

	// ----------------------------------------------- Private Method Test.
	PrivateMethod ptrMethod = nullptr;
	tmp->testMethodAddress(&ptrMethod);
	std::cout << "Private Method Address[outside]: " << &ptrMethod << std::endl;
	(tmp->*ptrMethod)();

	// Release memory.
	delete tmp;

	getchar();
	return 0;
}