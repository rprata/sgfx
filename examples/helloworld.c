#include <ibutterfree.h>
#include <ibutterfree_log.h>

int main(int argc, char ** argv)
{
	ibutterfree_set_msg_level(IBUTTERFREE_MSG_LEVEL_ALL);
	ibutterfree_log(IBUTTERFREE_MSG_LEVEL_TRACK, "Initializing helloworld application");
	IBUTTERFREE_RET ret = ibutterfree_init(argc, argv);
	if (ret == IBUTTERFREE_OK)
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_TRACK, "IbutterFree Library can be initialized");
	else
		ibutterfree_log(IBUTTERFREE_MSG_LEVEL_ERROR, "IbutterFree Library cannot be initialized");
	ibutterfree_log(IBUTTERFREE_MSG_LEVEL_TRACK, "Closing helloworld application");	
	ibutterfree_close();
	return 0;
}