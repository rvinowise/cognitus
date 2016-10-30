#include "debugStuff.h"

void debug_msg(QString string)
{
#ifdef debug_msg_core
    qDebug(string.toLocal8Bit());
#endif
}
