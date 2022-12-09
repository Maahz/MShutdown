#pragma once

#include <Windows.h>
#include "Worker.h"
#include <iostream>



void Worker::Shutdown()
{
	
	system("shutdown -s -t 0 -f");
}
