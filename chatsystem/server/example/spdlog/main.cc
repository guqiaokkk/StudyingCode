#include "logger.hpp"
#include <gflags/gflags.h>

DEFINE_bool(mode, false, "程序的运行模式，false-调试； true-发布");
DEFINE_string(log_file, "", "发布模式下，用于指定日志的输出文件");
DEFINE_int32(log_level, 0, "发布模式下，用于指定日志输出等级");


int main(int32_t argc, char *argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    init_logger(FLAGS_mode, FLAGS_log_file, FLAGS_log_level);
    LOG_DEBUG("你好:{}", "guqiao");
    LOG_INFO("你好:{}", "guqiao");
    LOG_WARN("你好:{}", "guqiao");
    LOG_ERROR("你好:{}", "guqiao");
    //g_default_logger->error((std::string("[{}:{}] ") + "你好:{}").c_str(), __FILE__, __LINE__, "guqiao");
    LOG_FATAL("你好:{}", "guqiao");
    LOG_DEBUG("这是一个测试");
    return -1;
}