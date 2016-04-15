//##############################################################################
//#	title:	Logger test
//#	c-date:	Apr-15-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################

#include <pcore/pcore.h>

int main()
{
	PRoot *root = new PRoot();
	root->init();
	PCORE_LOG_TRACE("hi");

	return 0;
}


