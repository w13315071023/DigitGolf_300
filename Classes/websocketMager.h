#pragma once
#include "Tools.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <cstdlib>
#include <iostream>
#include <sstream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class websocketMager:public Reseaver
{
public:
	static websocketMager* sInstence;
	typedef websocketpp::lib::shared_ptr<websocketMager> ptr;
	
	static websocketMager* getInstence();
	websocketMager(int id, websocketpp::connection_hdl hdl, std::string uri);
	~websocketMager();
	void closewebsocket();
	void on_open(client * c, websocketpp::connection_hdl hdl);
	void on_fail(client * c, websocketpp::connection_hdl hdl);
	void on_close(client * c, websocketpp::connection_hdl hdl);
	void on_message(websocketpp::connection_hdl, client::message_ptr msg);

	int m_id;
	int m_curMsg;
	websocketpp::connection_hdl m_hdl;
	static websocketMager::ptr metadata_ptr;
	static client endpoint;
	static client::connection_ptr con;
	std::string m_status;
	std::string m_uri;
	std::string m_server;
	std::string m_error_reason;
};