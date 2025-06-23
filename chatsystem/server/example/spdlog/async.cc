#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>

#include <iostream>

int main()
{
    //设置全局的刷新策略
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::flush_on(spdlog::level::level_enum::debug);
    spdlog::set_level(spdlog::level::level_enum::debug);

    //初始化异步日志输出线程配置  void init_thread_pool(size_t q_size, size_t thread_count)
    spdlog::init_thread_pool(3072, 1);
    //创建异步日志器（标准输出/文件） --工厂接口默认创建的就是同步日志器
    auto logger = spdlog::stdout_color_mt<spdlog::async_factory>("async-testlogger");
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