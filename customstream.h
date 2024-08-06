//// customstream.h
//#ifndef CUSTOMSTREAM_H
//#define CUSTOMSTREAM_H

//#include "DsLog.h" // 确保包含 DsLog 类头文件
//#include <sstream>
//#include <string>
//#include <memory>
//#include <mutex>

//class Logger {
//public:
//    enum class Level {
//        DEBUG,
//        INFO,
//        WARNING,
//        ERROR
//    };

//    // 获取 Logger 的唯一实例
//    static Logger& getInstance(const std::string& logName = "logfile.log", bool toScreen = true, Level level = Level::INFO) {
//        static std::unique_ptr<Logger> instance;
//        static std::mutex mutex;

//        if (!instance) {
//            std::lock_guard<std::mutex> lock(mutex);
//            if (!instance) {
//                instance.reset(new Logger(logName, toScreen, level));
//            }
//        }
//        return *instance;
//    }

//    // 设置日志等级
//    void setLevel(Level level) {
//        logLevel = level;
//    }

//    template<typename T>
//      Logger& operator<<(const T& value) {
//          std::ostringstream oss;
//          oss << value;
//          buffer << oss.str(); // 将消息添加到缓存
//          return *this;
//      }

//      Logger& operator<<(const char* value) {
//          buffer << value;
//          return *this;
//      }

//      Logger& operator<<(std::ostream& (*manip)(std::ostream&)) {
//          if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
//              log(buffer.str(), currentFunction, currentLine); // 将缓存的整条消息记录下来
//              buffer.str(""); // 清空缓存
//              buffer.clear(); // 清除缓存的状态
//          }
//          return *this;
//      }

//      // 设置当前日志等级
//      Logger& debug(const char* func = "", int line = 0) {
//          currentLevel = Level::DEBUG;
//          currentFunction = func;
//          currentLine = line;
//          return *this;
//      }

//      Logger& info(const char* func = "", int line = 0) {
//          currentLevel = Level::INFO;
//          currentFunction = func;
//          currentLine = line;
//          return *this;
//      }

//      Logger& warning(const char* func = "", int line = 0) {
//          currentLevel = Level::WARNING;
//          currentFunction = func;
//          currentLine = line;
//          return *this;
//      }

//      Logger& error(const char* func = "", int line = 0) {
//          currentLevel = Level::ERROR;
//          currentFunction = func;
//          currentLine = line;
//          return *this;
//      }

//private:
//    Logger(const std::string& logName, bool toScreen, Level level)
//        : logLevel(level) {
//        DsLog::init(logName, toScreen);
//    }

//    void log(const std::string& message, const char* function, int line) {
//           if (shouldLog(currentLevel)) {
//               std::ostringstream oss;
//               oss << message;
//               switch (currentLevel) {
//                   case Level::DEBUG:
//                       DsLog::getLog()->debug(oss.str(), line, function);
//                       break;
//                   case Level::INFO:
//                       DsLog::getLog()->info(oss.str(), line, function);
//                       break;
//                   case Level::WARNING:
//                       DsLog::getLog()->warn(oss.str(), line, function);
//                       break;
//                   case Level::ERROR:
//                       DsLog::getLog()->error(oss.str(), line, function);
//                       break;
//               }
//           }
//       }


//    bool shouldLog(Level level) const {
//        return level >= logLevel;
//    }
//private:
//    std::ostringstream buffer; // 消息缓存
//    Level logLevel; // 当前日志等级
//    Level currentLevel; // 当前操作的日志等级
//    const char* currentFunction; // 当前函数名
//    int currentLine; // 当前行号
//};

//// 宏定义
//#define LOG_DEBUG Logger::getInstance().debug(__FUNCTION__, __LINE__)
//#define LOG_INFO  Logger::getInstance().info(__FUNCTION__, __LINE__)
//#define LOG_WARN  Logger::getInstance().warning(__FUNCTION__, __LINE__)
//#define LOG_ERROR Logger::getInstance().error(__FUNCTION__, __LINE__)

//#endif // CUSTOMSTREAM_H
