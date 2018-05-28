#define _CRT_SECURE_NO_WARNINGS
#include "log_deffine.h"
#include "Logger.h"
#include "LogManager.h"


extern std::unique_ptr<Logger> g_logPtr;

void  _log_write(EnumLogLevel nLevel, const char *pFmt, ...)
{
	if (g_logPtr.get() == nullptr)
	{
		g_logPtr.reset(new Logger);
	}

	char pTemp[2048 * 100] = { 0 };
	va_list arg_ptr;
	va_start(arg_ptr, pFmt);
	vsprintf(pTemp + strlen(pTemp), pFmt, arg_ptr);
	va_end(arg_ptr);
	if (g_logPtr)
	{
		g_logPtr->Write2Caching(nLevel, pTemp);
	}
}