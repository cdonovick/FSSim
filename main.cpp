#include "standard.h"
#include "logfilesystem.h"
#include "segment.h"

int main(int argc, char **argv) {   
    LogFileSystem lfs(32, 16, .4, .5);
	return 0;
}

