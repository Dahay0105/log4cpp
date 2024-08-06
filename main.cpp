#include "widget.h"
#include "DsLog.h"
#include "customstream.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);

//    // 创建 PatternLayout 并设置模式
//    log4cpp::PatternLayout *layout = new log4cpp::PatternLayout();
//    layout->setConversionPattern("%d: %p %c %x: %m%n");

//    // 创建 OstreamAppender，输出到标准输出（屏幕）
//    log4cpp::OstreamAppender *appender = new log4cpp::OstreamAppender("console", &std::cout);
//    appender->setLayout(layout);

//    // 获取根 Category，并设置 Appender 和优先级
//    log4cpp::Category &root = log4cpp::Category::getRoot();
//    root.setAppender(appender);
//    root.setPriority(log4cpp::Priority::DEBUG);

//    // 输出日志信息
//    root.info("This is an informational message");
//    root.debug("This is a debug message");
//    root.warn("This is a warning message");
//    root.error("This is an error message");

//    Logger log("log.txt", true, Logger::Level::INFO);
    Logger::getInstance("log.txt", true, Logger::Level::DEBUG);
     LOG_DEBUG << "Hello, " << "world!" << std::endl;
     LOG_DEBUG << 123 << ' ' << 45.67 << std::endl;

     LOG_ERROR << "error," << "nihao" << std::endl;

     std::string str = "1111";
     LOG_DEBUG << str << std::endl;

     LOG_DEBUG << "nihao " << std::endl;

     const char *ptr = "2222";

     LOG_DEBUG << ptr << std::endl;

     QString qstr = "3333";
     LOG_DEBUG << qstr.toStdString() << std::endl;

     LOG_DEBUG << qstr.toStdString() << std::endl;

     char fileName[256] = "ssss";
     LOG_DEBUG << fileName << " huxuhai " <<  std::endl;

     return 0;
}
