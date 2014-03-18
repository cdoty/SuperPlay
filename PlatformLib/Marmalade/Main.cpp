#include "Platform.h"
#include "System.h"

int main()
{
	int	iRetVal	= 0;
	
	if (false == SPlay::System::initialize()  || false == SPlay::Platform::runLoop())
	{
		iRetVal	= 1;
	}

	SPlay::System::close();
	
	return	iRetVal;
}
