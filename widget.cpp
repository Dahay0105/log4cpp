#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
#if 0
    /* 1.日志输出到控制台 */
        {
            log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
            appender1->setLayout(new log4cpp::BasicLayout());	// 默认配置

            log4cpp::Category& root = log4cpp::Category::getRoot();
            root.setPriority(log4cpp::Priority::WARN);
            root.addAppender(appender1);

            // 1.use of functions for logging messages
            root.debug("root debug");
            root.warn("root warn");
            root.error("root error");
            root.info("root info");

            // 2.printf-style for logging variables
            root.warn("%d + %d == %s ?", 1, 1, "two");

            // 3.use of streams for logging messages
            root << log4cpp::Priority::ERROR << "Streamed root error";
            root << log4cpp::Priority::INFO << "Streamed root info";

            // 4.or this way:
            root.errorStream() << "Another streamed error";
            root.debugStream() << "Another streamed debug";
        }

        /* 2.日志输出到控制台和本地文件 */
        {
            log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
            appender2->setLayout(new log4cpp::BasicLayout());

            log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
            sub1.addAppender(appender2);

            sub1.error("sub1 error");
            sub1.warn("sub1 warn");

            sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
            sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";
        }

        /* 3.日志输出到本地文件 */
        {
            std::string logFileName = "test.log";

            // 优先级
            log4cpp::Priority::PriorityLevel logPri = log4cpp::Priority::DEBUG;

            // 自定义布局
            log4cpp::PatternLayout* logLayout = new log4cpp::PatternLayout();
            logLayout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S} [%p] : %m%n");

            // 日志输出到本地文件
            log4cpp::FileAppender* logFile = new log4cpp::FileAppender("default", logFileName);
            logFile->setLayout(logLayout);	// 设置自定义布局

            // 输出日志的操作类
            log4cpp::Category& logCat = log4cpp::Category::getInstance("logCat");
            logCat.addAppender(logFile);

            //设置优先级
            logCat.setPriority(logPri);

            logCat.error("测试 error");
            logCat.debug("测试 debug");

            logCat.warn("%d + %d == %s ?", 1, 1, "two");

            logCat << log4cpp::Priority::ERROR << "Streamed root error";
            logCat << log4cpp::Priority::INFO << "Streamed root info";

            logCat.errorStream() << "Another streamed error";
            logCat.debugStream() << "Another streamed debug";
        }

        // 关闭日志
        log4cpp::Category::shutdown();

#endif

        if (!DsLog::init("C:\\Users\\hu_xuhai\\Desktop\\huxuhai\\log.txt", true)) {
                fprintf(stderr, "init log module failed.\n");
//                return -1;
            }

        // 记录不同优先级的日志信息
//           DsLogINFO("This is an info message.");
//           DsLogDEBUG(QString("This is a debug message."));
//           DsLogWARN(std::string("This is a warning message."));
//           DsLogERROR("This is an error message.");

//           // 记录QString类型的日志信息
//           QString qstr = "This is a QString message.";
//           DsLogINFO(qstr);
//           DsLogDEBUG(qstr);
//           DsLogWARN(qstr);
//           DsLogERROR(qstr);

}

Widget::~Widget()
{
    DsLog::destoryLog();
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    for(int idx = 0; idx < 10; ++idx){
//    DsLogDEBUG("init")
//            DsLogDEBUG(QString("init"));
//    DsLogDEBUG(std::string("init"));

//        std::cout << "huxuhai" <<std::endl;
    }

}


void Widget::on_pushButton_2_clicked()
{
}

