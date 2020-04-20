#include <iostream>

#include "core/TreeBuilder.h"

int main(int argc, char** argv)
{
	auto treebuilderPtr = std::make_shared< treefinder::TreeBuilder >("", 0);
	treebuilderPtr->getProcessedSampleTreesPtrs();
	return 0;
}
