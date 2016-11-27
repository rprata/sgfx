#include <ibutterfree.h>
#include <ibutterfree_log.h>

int main(int argc, char ** argv)
{
	IBUTTERFREE_LOG_TRACK("Initializing helloworld application");
	IBUTTERFREE_RET ret = ibutterfree_init(argc, argv);
	if (ret == IBUTTERFREE_OK)
		IBUTTERFREE_LOG_TRACK("IbutterFree Library can be initialized");
	else
		IBUTTERFREE_LOG_ERROR("IbutterFree Library cannot be initialized");
	IBUTTERFREE_LOG_TRACK("Closing helloworld application");	
	ibutterfree_close();
	return 0;
}