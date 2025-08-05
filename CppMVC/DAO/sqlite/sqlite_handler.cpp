#include "sqlite_handler.h"

lilaomo::detail::sqlite_handler::sqlite_handler() : db_(nullptr) {

}

lilaomo::detail::sqlite_handler::~sqlite_handler() {
    disconnect();
}



bool lilaomo::detail::sqlite_handler::connect(const std::string& db_path) {
    disconnect();

    int ret = sqlite3_open(db_path.c_str(), &db_);
    if (ret) {
        last_err_ = sqlite3_errmsg(db_);
        return false;
    }
    return true;
}



void lilaomo::detail::sqlite_handler::disconnect() {
    if (db_ != nullptr) {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}



bool lilaomo::detail::sqlite_handler::execute(const std::string& sql) {
    if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
        last_err_ = sqlite3_errmsg(db_);
        return false;
    }
    return true;
}
