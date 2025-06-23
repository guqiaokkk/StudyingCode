#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <iostream>

int main()
{
    //设置全局的刷新策略
    //每秒刷新
    spdlog::flush_every(std::chrono::seconds(1));
    //遇到debug以上等级的日志立即刷新
    spdlog::flush_on(spdlog::level::level_enum::debug);
    //设置全局的日志输出等级 --其实无所谓，每个日志器可以独立进行设置
    spdlog::set_level(spdlog::level::level_enum::debug);

    //创建同步日志器（标准输出/文件） --工厂接口默认创建的就是同步日志器
    //auto logger = spdlog::stdout_color_mt("testlogger");
    auto logger = spdlog::basic_logger_mt("testlogger", "sync.log");
    //设置日志器的刷新策略，以及设置日志器的输出等级，这里就不设置，用上面设置的全局默认的
    //自定义日志输出格式
    logger->set_pattern("[%n][%H:%M:%S][%t][%-8l]%v");
    //进行简单的日志输出
    logger->trace("hello! {}", "guqaio");
    logger->debug("hello! {}","guqaio");
    logger->info("hello! {}", "guqaio");
    logger->warn("hello! {}", "guqaio");
    logger->error("hello! {}","guqaio");
    logger->critical("hello! {}","guqaio"); 
    std::cout << "Logger Test All" << std::endl;
    return 0;
}