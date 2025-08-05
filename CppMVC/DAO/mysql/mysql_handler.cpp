#include "mysql_handler.h"

lilaomo::detail::mysql_handler::mysql_handler() : db_(nullptr) {

}

lilaomo::detail::mysql_handler::~mysql_handler() {
	disconnect();
}



bool lilaomo::detail::mysql_handler::connect(const std::string& user, const std::string& pwd, const std::string& db, 
	const std::string& ip, uint32_t port, uint32_t timeout) 
{
	disconnect();

	db_ = mysql_init(nullptr);
	if (timeout > 0) {
		mysql_options(db_, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);
	}
	//char reconnect = 1;
	//mysql_options(db_, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(db_, MYSQL_SET_CHARSET_NAME, "utf8");

	if (mysql_real_connect(db_, ip.c_str(), user.c_str(), pwd.c_str(), db.c_str(), port, nullptr, 0) == nullptr) {
		last_err_ = mysql_error(db_);
		return false;
	}
	return true;
}



void lilaomo::detail::mysql_handler::disconnect() {
	if (db_ != nullptr) {
		mysql_close(db_);
		db_ = nullptr;
	}
}
