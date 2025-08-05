#include <iostream>
#include <format>

#include "config/cfg.hpp"
#include "DAO/common_DAO.hpp"
#include "server.hpp"

bool init_configure(lilaomo::configure& cfg);
bool init_logger(const lilaomo::configure& cfg);
bool init_database(const lilaomo::configure& cfg);
void start_log(const lilaomo::configure& cfg);

int main() {
    lilaomo::configure cfg;
    if (!init_configure(cfg) || !init_logger(cfg) || !init_database(cfg))
        return -1;
    start_log(cfg);

    LLMLOG_D("server type: nonssl, ip: {}, prot: {}", cfg.serv_cfg().ip, cfg.serv_cfg().port);
    lilaomo::nonssl_server serv = lilaomo::make_nonssl_serv(std::thread::hardware_concurrency());
    serv->start(cfg.serv_cfg().ip, cfg.serv_cfg().port, 600);

    return 0;
}



bool init_configure(lilaomo::configure& cfg) {
    if (!cfg.load_config<lilaomo::detail::use_db>()) {
        std::cout << "load config json failed.\n" << cfg.error() << std::endl;
        return false;
    }
    return true;
}



bool init_logger(const lilaomo::configure& cfg) {
    auto logger = lilaomo::logger<>::instance();
    logger->init(cfg.log_cfg().hh, cfg.log_cfg().mm, cfg.log_cfg().lvl, cfg.log_cfg().sec);
    LLMLOG_D("log type: multi");
    LLMLOG_D("success init logger module. create by new time: {}:{}, flush spc sec: {}, level: {}",
        cfg.log_cfg().hh, cfg.log_cfg().mm, cfg.log_cfg().sec, static_cast<uint8_t>(cfg.log_cfg().lvl));
    return true;
}



bool init_database(const lilaomo::configure& cfg) {
    LLMLOG_D("database factory: {}", cfg.db_cfg().str_db);
    auto db = lilaomo::db_factory();
    if constexpr (lilaomo::detail::use_db == lilaomo::database_t::mysql) {
        auto& my_cfg = cfg.db_cfg().mysql_db;
        LLMLOG_D("connect to mysql, ip: {}, port: {}, user: {}, pwd: {}, db name: {}", my_cfg.ip, my_cfg.port, my_cfg.user, my_cfg.pwd, my_cfg.db);
        if (!db->connect(my_cfg.user, my_cfg.pwd, my_cfg.db, my_cfg.ip, my_cfg.port)) {
            LLMLOG_E("connect db failed. err: {}", db->last_error());
            return false;
        }
        LLMLOG_D("connect success.");
    }
    else if constexpr (lilaomo::detail::use_db == lilaomo::database_t::sqlite) {
        LLMLOG_D("connect to sqlite, db path: {}", cfg.db_cfg().sqlite_db.file_path);
        if (!db->connect(cfg.db_cfg().sqlite_db.file_path)) {
            LLMLOG_E("connect db failed. err: {}", db->last_error());
            return false;
        }
        LLMLOG_D("connect success.");
    }
    else {
        LLMLOG_E("not support this db type.");
        return false;
    }
    LLMLOG_D("init database finished.");
    return true;
}



void start_log(const lilaomo::configure& cfg) {
    LLMLOG(LINFO, "//                          _ooOoo_                               //");
    LLMLOG(LINFO, "//                         o8888888o                              //");
    LLMLOG(LINFO, "//                         88\" . \"88                              //");
    LLMLOG(LINFO, "//                         (| ^_^ |)                              //");
    LLMLOG(LINFO, "//                         O\\  =  /O                              //");
    LLMLOG(LINFO, "//                      ____/`---'\\____                           //");
    LLMLOG(LINFO, "//                    .'  \\\\|     |//  `.                         //");
    LLMLOG(LINFO, "//                   /  \\\\|||  :  |||//  \\                        //");
    LLMLOG(LINFO, "//                  /  _||||| -:- |||||-  \\                       //");
    LLMLOG(LINFO, "//                  |   | \\\\\\  -  /// |   |                       //");
    LLMLOG(LINFO, "//                  | \\_|  ''\\---/''  |   |                       //");
    LLMLOG(LINFO, "//                  \\  .-\\__  `-`  ___/-. /                       //");
    LLMLOG(LINFO, "//                ___`. .'  /--.--\\  `. . ___                     //");
    LLMLOG(LINFO, "//              .\"\" '<  `.___\\_<|>_/___.'  >'\"\".                  //");
    LLMLOG(LINFO, "//            | | :  `- \\`.;`\\ _ /`;.`/ - ` : | |                 //");
    LLMLOG(LINFO, "//            \\  \\ `-.   \\_ __\\ /__ _/   .-` /  /                 //");
    LLMLOG(LINFO, "//      ========`-.____`-.___\\_____/___.-`____.-'========         //");
    LLMLOG(LINFO, "//                           `=---='                              //");
    LLMLOG(LINFO, "//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //");
    LLMLOG(LINFO, "//               佛祖保佑       永不宕机     永无BUG                //\n");
    LLMLOG(LINFO, "database: {}, listen ip: {}, listen port: {}", cfg.db_cfg().str_db, cfg.serv_cfg().ip, cfg.serv_cfg().port);
    LLMLOG(LINFO, "version: {}", LLM_VERSION);
    LLMLOG(LINFO, "modern c++ mvc framework, made by lilaomo");
    LLMLOG(LINFO, "server started...");
}
