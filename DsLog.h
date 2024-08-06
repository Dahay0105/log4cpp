/******************************************************************************
 * Copyright 2024-Dakewe(shenzhen) Medical Equipment Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       DsLog.h
 * @brief      日志 Function
 * 消息类别：日志传输消息兼容char*、std::string、 QString;
 * @author    胡徐海<huxuhai@dakewe.com>
 * @date       2024/06/17
 * @history
 *****************************************************************************/
#ifndef _DS_LOG_H_
#define _DS_LOG_H_

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

#include <string>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <ctime>
#include <QString>
#include <string>
#include <memory>
#include <mutex>

// 优先级 NOTSET < DEBUG < INFO < NOTICE < WARN < ERROR < CRIT < ALERT < FATAL = EMERG
#define COUNT_PRITY			log4cpp::Priority::DEBUG;		// 控制台
#define LOG_PRITY			log4cpp::Priority::DEBUG;		// 本地文件

/*采用单例模式设计，包含两个category对象，一个负责输出到屏幕的信息，一个负责记录到日志的信息，
通过设置优先级差别，可以实现所有信息都记录在日志中，遇到error及以上的信息时打印到屏幕上*/
class DsLog {
private:
    DsLog(bool b) {
        outToScreen = b;
    }
    ~DsLog() {}
    static DsLog * log;
    bool outToScreen;//是否输出日志信息到屏幕
    static std::string _screenInfo;//屏幕日志信息
    static std::string _logName;//文件日志名称

    static log4cpp::Category& logCat;
    static log4cpp::Category& coutCat;

    static log4cpp::FileAppender* logFile;//文件日志输入
    static log4cpp::OstreamAppender* logScreen;//屏幕日志输入
    static log4cpp::RollingFileAppender *rollLogFile;	/* 回卷用这个 */

    static log4cpp::Priority::PriorityLevel logPri;//文件日志优先级
    static log4cpp::Priority::PriorityLevel coutPri;//屏幕日志优先级

    static log4cpp::PatternLayout* logLayout;//日志布局
    static log4cpp::PatternLayout* screenLayout;//屏幕布局
    static log4cpp::PatternLayout* logLayout2;	/* 回卷用这个 */

private:
    // 返回当前年月日时分秒
    static std::string getCurrentTime(std::string& year, std::string& month, std::string& day, std::string& hour, std::string& min, std::string& sec);

    // 将 QString 转换为 std::string
//    static std::string QStringToStdString(const QString& qstr){
//        return qstr.toStdString();
//      }
public:
    // 初始化日志配置信息
    static bool init(std::string logName = "time", bool toScreen = false);
    //获取日志函数
    static DsLog* getLog();
    //销毁日志对象
    static void destoryLog();
    //设置日志记录优先级
    static void setPri(log4cpp::Priority::PriorityLevel coutLevel, log4cpp::Priority::PriorityLevel logLevel);

 public:
    // 模板函数，记录日志
    template <typename T>
    void logMessage(log4cpp::Priority::PriorityLevel level, const T& msg, int line, const char *function) {
        std::stringstream stream;
           stream << "[Function: " << function  << ", Line: " << line << "] " << msg;
           logCat.log(level, stream.str());
           if (outToScreen) {
               coutCat.log(level, stream.str());
           }
    }

    // 特化模板函数，处理 QString 类型
//    template <>
//    void logMessage<QString>(log4cpp::Priority::PriorityLevel level, const QString& msg, int line, const char *function) {
//        logMessage(level, QStringToStdString(msg), line, function);
//    }

    // 警告信息
    template <typename T>
    void warn(const T& msg, int line, const char *function) {
        logMessage(log4cpp::Priority::WARN, msg, line, function);
    }

    // 错误信息
    template <typename T>
    void error(const T& msg, int line, const char *function) {
        logMessage(log4cpp::Priority::ERROR, msg, line, function);
    }

    // 调试信息
    template <typename T>
    void debug(const T& msg, int line, const char *function) {
        logMessage(log4cpp::Priority::DEBUG, msg, line, function);
    }

    // 信息
    template <typename T>
    void info(const T& msg, int line, const char *function) {
        logMessage(log4cpp::Priority::INFO, msg, line, function);
    }
};
//为避免每次调用都要填写参数__LINE__和__FUNCTION__,可以使用带参数的宏定义
//#define  DsLogWARN(msg) DsLog::getLog()->warn(msg,__LINE__,__FUNCTION__);
//#define  DsLogINFO(msg) DsLog::getLog()->info(msg,__LINE__,__FUNCTION__);
//#define  DsLogERROR(msg) DsLog::getLog()->error(msg,__LINE__,__FUNCTION__);
//#define  DsLogDEBUG(msg) DsLog::getLog()->debug(msg,__LINE__,__FUNCTION__);

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    // 获取 Logger 的唯一实例
    static Logger& getInstance(const std::string& logName = "logfile.log", bool toScreen = true, Level level = Level::INFO) {
        static std::unique_ptr<Logger> instance;
        static std::mutex mutex;

        if (!instance) {
            std::lock_guard<std::mutex> lock(mutex);
            if (!instance) {
                instance.reset(new Logger(logName, toScreen, level));
            }
        }
        return *instance;
    }

    // 设置日志等级
    void setLevel(Level level) {
        logLevel = level;
    }

    template<typename T>
      Logger& operator<<(const T& value) {
          std::ostringstream oss;
          oss << value;
          buffer << oss.str(); // 将消息添加到缓存
          return *this;
      }

      Logger& operator<<(const char* value) {
          buffer << value;
          return *this;
      }

      Logger& operator<<(std::ostream& (*manip)(std::ostream&)) {
          if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
              log(buffer.str(), currentFunction, currentLine); // 将缓存的整条消息记录下来
              buffer.str(""); // 清空缓存
              buffer.clear(); // 清除缓存的状态
          }
          return *this;
      }

      // 设置当前日志等级
      Logger& debug(const char* func = "", int line = 0) {
          currentLevel = Level::DEBUG;
          currentFunction = func;
          currentLine = line;
          return *this;
      }

      Logger& info(const char* func = "", int line = 0) {
          currentLevel = Level::INFO;
          currentFunction = func;
          currentLine = line;
          return *this;
      }

      Logger& warning(const char* func = "", int line = 0) {
          currentLevel = Level::WARNING;
          currentFunction = func;
          currentLine = line;
          return *this;
      }

      Logger& error(const char* func = "", int line = 0) {
          currentLevel = Level::ERROR;
          currentFunction = func;
          currentLine = line;
          return *this;
      }

private:
    Logger(const std::string& logName, bool toScreen, Level level)
        : logLevel(level) {
        DsLog::init(logName, toScreen);
    }

    void log(const std::string& message, const char* function, int line) {
           if (shouldLog(currentLevel)) {
               std::ostringstream oss;
               oss << message;
               switch (currentLevel) {
                   case Level::DEBUG:
                       DsLog::getLog()->debug(oss.str(), line, function);
                       break;
                   case Level::INFO:
                       DsLog::getLog()->info(oss.str(), line, function);
                       break;
                   case Level::WARNING:
                       DsLog::getLog()->warn(oss.str(), line, function);
                       break;
                   case Level::ERROR:
                       DsLog::getLog()->error(oss.str(), line, function);
                       break;
               }
           }
       }


    bool shouldLog(Level level) const {
        return level >= logLevel;
    }
private:
    std::ostringstream buffer; // 消息缓存
    Level logLevel; // 当前日志等级
    Level currentLevel; // 当前操作的日志等级
    const char* currentFunction; // 当前函数名
    int currentLine; // 当前行号
};

// 宏定义
#define LOG_DEBUG Logger::getInstance().debug(__FUNCTION__, __LINE__)
#define LOG_INFO  Logger::getInstance().info(__FUNCTION__, __LINE__)
#define LOG_WARN  Logger::getInstance().warning(__FUNCTION__, __LINE__)
#define LOG_ERROR Logger::getInstance().error(__FUNCTION__, __LINE__)



#endif //_DS_LOG_H_
