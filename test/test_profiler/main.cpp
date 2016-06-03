//##############################################################################
//#	title:	Test for profiler
//#	c-date:	Apr-16-2016
//#	author:	Pouya Shahinfar (Pswin) - pswinpo@gmail.com
//##############################################################################


#include <pcore/pcore.h>
#include <cmath>
#include <iostream>

//=====================================
// foo
//=====================================
void foo()
{
	// profiling this function
	PCORE_PROFILE_FUNCTION();

	double res = 0;
	for ( int i = 0; i < 999999999;  i++ )
	{
		res = res + sqrt( i );
	}
	std::cout << res << std::endl;
}


//=====================================
// bar
//=====================================

double bar( int i )
{
	return sqrtf(i);
}


//=====================================
// zoo
//=====================================

double zoo( int i )
{
	PCORE_PROFILE_FUNCTION();
	return sqrtf(i);
}



//=====================================
// main
//=====================================
int main(int argc, char *argv[])
{
	// initialize pcore
	PCORE_INIT();


	// calling foo
	foo();


	// profiling a block
	PCORE_PROFILE_BLOCK_START( _bar, "bar" );
	double res = 0;
	for ( int i = 0; i < 999999999;  i++ )
	{
		res += bar( i );
	}
	PCORE_PROFILE_BLOCK_END( _bar );


	// counting call number
	for ( int i = 0; i < 1000;  i++ )
	{
		res += zoo( i );
	}


	// saving profiles to a file
	pProfileManager->printToFile( "benchmark.txt" );


	return 0;
}
