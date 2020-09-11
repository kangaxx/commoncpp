/******************************************************
 *
 *    gxx log_helper base on log4cpp 
 *    log save to /tmp/send_acc_log
 *
 *****************************************************/
#ifndef LOG_HELPER_H
#define LOG_HELPER_H
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/DailyRollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>

using namespace std;

#define cards_count 30
#define success_flag 2
#define NO_CHANGE -1
#define IS_CHANGE 0
#define IS_GOTA 1 //1 后 0 先
#ifdef LOG4CPP_HAVE_IO_H
#    include <io.h>
#endif
#ifdef LOG4CPP_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#ifndef WIN32    // only available on Win32
#include <dirent.h>
#else
#include <direct.h> // 原作者如此 add by gxx  
#endif


#ifdef WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif
using namespace log4cpp;
using namespace std;
#ifndef WIN32 
#define PATHDELIMITER "/" 
#else 
#define PATHDELIMITER "\\"
#endif

namespace commonfunction_c {
//日记滚动模式
class DailyRollingLog
{
  Category& daily_root = Category::getRoot(); 
  
public:  
  DailyRollingLog()
  {
    char strProcessPath[2048] = {0}; 
    pid_t pid = getpid();
    char pid_ch[20];
    sprintf(pid_ch, "%d", pid);
    char logName[512];

    if (readlink("/proc/self/exe", strProcessPath, 2048) <= 0)
    {
      strcpy(logName, "/var/log/work_runner.log");
    }
    else
    {
      strcpy(logName, "/var/log");
      strcat(logName, strrchr(strProcessPath, '/'));
      strcat(logName, "_");
      strcat(logName, pid_ch);
      strcat(logName, ".log");
    }
    DailyRollingFileAppender* dailyApp = new DailyRollingFileAppender("daily-rolling-appender", logName, 1);
    dailyApp->setMaxDaysToKeep(30);
    log4cpp::PatternLayout *fileLayout = new log4cpp::PatternLayout();
    fileLayout->setConversionPattern("%d: %p %c %x: %m %n");
    dailyApp->setLayout(fileLayout);
    daily_root.addAppender(dailyApp);
    daily_root.setPriority(Priority::DEBUG);
     
  }
  ~DailyRollingLog(){}
 
  void info(string msg)
  {
    daily_root.info(msg);
  }

  void warn(string msg)
  {
    daily_root.warn(msg);
  }

  void error(string msg)
  {
    daily_root.error(msg);
  }

};

} //namespace

#endif //LOG_HELPER_H
