#include "dsLog.h"

#include <time.h>
#include <log4cpp/PropertyConfigurator.hh>

DsLog* DsLog::log = NULL;
std::string DsLog::_screenInfo = "screenInfo";
std::string DsLog::_logName = "log";

log4cpp::Category& root = log4cpp::Category::getRoot();
log4cpp::Category& DsLog::logCat = root.getInstance(DsLog::_logName);
log4cpp::Category& DsLog::coutCat = root.getInstance(DsLog::_screenInfo);

// 优先级
log4cpp::Priority::PriorityLevel DsLog::coutPri = COUNT_PRITY;		// 控制台
log4cpp::Priority::PriorityLevel DsLog::logPri = LOG_PRITY;		// 本地文件

log4cpp::PatternLayout* DsLog::logLayout = NULL;
log4cpp::PatternLayout* DsLog::screenLayout = NULL;
log4cpp::PatternLayout* DsLog::logLayout2 = NULL;	/* 回卷用这个 */

log4cpp::FileAppender* DsLog::logFile = NULL;//文件日志输入
log4cpp::OstreamAppender* DsLog::logScreen = NULL;//屏幕日志输入
log4cpp::RollingFileAppender *DsLog::rollLogFile;	/* 回卷用这个 */

bool DsLog::init(std::string logName, bool toScreen) {

    // 判断如果传入文件名参数为空，或为默认参数，则使用当前年月日.log作为日志文件名
    if (logName.empty() || logName == "time") {
        std::string year, month, day, hour, min, sec;
        getCurrentTime(year, month, day, hour, min, sec);
        logName = year + month + day + ".log";
    }

    if(toScreen) setvbuf(stdout, nullptr, _IONBF, 0);  // 设置 std::cout 为无缓冲模式

    if (DsLog::log == NULL) {
        DsLog::log = new DsLog(toScreen);

        DsLog::_logName = logName;

        log4cpp::Category& logCat = root.getInstance(DsLog::_logName);
        log4cpp::Category& coutCat = root.getInstance(DsLog::_screenInfo);

        logScreen = new log4cpp::OstreamAppender("logScreen", &std::cout);
//        logFile = new log4cpp::FileAppender("logFile", DsLog::_logName);								/* 然后注释这个 */
        rollLogFile = new log4cpp::RollingFileAppender("rollLogFile", DsLog::_logName, 1024*1024, 5);	/* 回卷用这个 */	// 单个日志文件大小1M，5个回卷


        //设置布局
        DsLog::logLayout = new log4cpp::PatternLayout();	/* 然后注释这个 */
        DsLog::screenLayout = new log4cpp::PatternLayout();
        DsLog::logLayout2 = new log4cpp::PatternLayout();	/* 回卷用这个 */
        logLayout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S} [%p] %m%n");
        screenLayout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S} [%p] %m%n");
        logLayout2->setConversionPattern("%d{%Y-%m-%d %H:%M:%S} [%p] %m%n");
        DsLog::logScreen->setLayout(screenLayout);
//        DsLog::logFile->setLayout(logLayout);			/* 然后注释这个 */
        DsLog::rollLogFile->setLayout(logLayout2);	/* 回卷用这个 */


        //追加到目录
//        DsLog::logCat.addAppender(DsLog::logFile);			/* 然后注释这个 */
        DsLog::logCat.addAppender(DsLog::rollLogFile);	/* 回卷用这个 */
        DsLog::coutCat.addAppender(DsLog::logScreen);

        //设置优先级
        DsLog::logCat.setPriority(DsLog::logPri);
        DsLog::coutCat.setPriority(DsLog::coutPri);
    }

    DsLog::log->outToScreen = toScreen;
    return true;
}

//获取日志函数
DsLog* DsLog::getLog() {

    if (NULL == DsLog::log) {
        printf("DsLog::log is NULL, please use DsLog::init!\n");
        return NULL;
    }

    return DsLog::log;
}
//销毁日志对象
void DsLog::destoryLog() {
    log4cpp::Category::shutdown();
    delete DsLog::log;
}
//设置日志记录优先级
void DsLog::setPri(log4cpp::Priority::PriorityLevel coutLevel, log4cpp::Priority::PriorityLevel logLevel) {
    DsLog::logPri = logLevel;
    DsLog::coutPri = coutLevel;
    DsLog::logCat.setPriority(DsLog::logPri);
    DsLog::coutCat.setPriority(DsLog::coutPri);
}

std::string DsLog::getCurrentTime(std::string& year, std::string& month, std::string& day, std::string& hour, std::string& min, std::string& sec) {
    // 获取系统时间 - 年月日时分秒
    time_t _time;
    struct tm* target_time;
    time(&_time);
    target_time = localtime(&_time);


    year = std::to_string(target_time->tm_year + 1900);
    month = target_time->tm_mon + 1 > 9 ? std::to_string(target_time->tm_mon + 1) : "0" + std::to_string(target_time->tm_mon + 1);
    day = target_time->tm_mday > 9 ? std::to_string(target_time->tm_mday) : "0" + std::to_string(target_time->tm_mday);
    hour = target_time->tm_hour > 9 ? std::to_string(target_time->tm_hour) : "0" + std::to_string(target_time->tm_hour);
    min = target_time->tm_min > 9 ? std::to_string(target_time->tm_min) : "0" + std::to_string(target_time->tm_min);
    sec = target_time->tm_sec > 9 ? std::to_string(target_time->tm_sec) : "0" + std::to_string(target_time->tm_sec);

    return year + month + day + hour + min + sec;
}
