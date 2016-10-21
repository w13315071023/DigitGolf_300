#include "websocketMager.h"
#include "PostureAnalysisScene.h"

websocketMager* websocketMager::sInstence = NULL;
websocketMager::ptr websocketMager::metadata_ptr;
client websocketMager::endpoint;
client::connection_ptr websocketMager::con;

websocketMager::websocketMager(int id, websocketpp::connection_hdl hdl, std::string uri)
{
	m_id = id;
	m_hdl = hdl;
	m_status = "Connecting";
	m_uri = uri;
	m_curMsg = 0;
	sInstence = this;
}

websocketMager* websocketMager::getInstence()
{
	if(sInstence)
	{
		return sInstence;
	}
	websocketpp::lib::error_code ec;

	
	endpoint.clear_access_channels(websocketpp::log::alevel::all);
	endpoint.clear_error_channels(websocketpp::log::elevel::all);

	endpoint.init_asio();
	endpoint.start_perpetual();

	websocketpp::lib::shared_ptr<websocketpp::lib::thread> thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &endpoint);
	//con = endpoint.get_connection("ws://localhost:8000/", ec);
	//con = endpoint.get_connection("ws://192.168.2.129:8000/", ec);
	con = endpoint.get_connection("ws://172.17.1.201:8000/", ec);
	
	if (ec)
	{
		std::cout << "> Connect initialization error: " << ec.message() << std::endl;
	}
	int EXT_Id = 0;
	//metadata_ptr = websocketpp::lib::make_shared<websocketMager>(EXT_Id, con->get_handle(), "ws://localhost:8000/");
	//metadata_ptr = websocketpp::lib::make_shared<websocketMager>(EXT_Id, con->get_handle(), "ws://192.168.2.129:8000/");
	metadata_ptr = websocketpp::lib::make_shared<websocketMager>(EXT_Id, con->get_handle(), "ws://172.17.1.201:8000/");

	con->set_open_handler(websocketpp::lib::bind(
		&websocketMager::on_open,
		metadata_ptr,
		&endpoint,
		websocketpp::lib::placeholders::_1
		));
	con->set_fail_handler(websocketpp::lib::bind(
		&websocketMager::on_fail,
		metadata_ptr,
		&endpoint,
		websocketpp::lib::placeholders::_1
		));
	con->set_close_handler(websocketpp::lib::bind(
		&websocketMager::on_close,
		metadata_ptr,
		&endpoint,
		websocketpp::lib::placeholders::_1
		));
	con->set_message_handler(websocketpp::lib::bind(
		&websocketMager::on_message,
		metadata_ptr,
		websocketpp::lib::placeholders::_1,
		websocketpp::lib::placeholders::_2
		));

	endpoint.connect(con);

	return sInstence;
}
websocketMager::~websocketMager()
{
}
void websocketMager::closewebsocket()
{
	if (sInstence)
	{
		websocketpp::lib::error_code ec;
		int close_code = websocketpp::close::status::normal;
		endpoint.close(m_hdl, close_code, "close", ec);

		sInstence = NULL;
	}
}
void websocketMager::on_open(client * c, websocketpp::connection_hdl hdl)
{
	m_status = "Open";

	client::connection_ptr con = c->get_con_from_hdl(hdl);
	m_server = con->get_response_header("Server");
}

void websocketMager::on_fail(client * c, websocketpp::connection_hdl hdl)
{
	m_status = "Failed";

	client::connection_ptr con = c->get_con_from_hdl(hdl);
	m_server = con->get_response_header("Server");
	m_error_reason = con->get_ec().message();
}

void websocketMager::on_close(client * c, websocketpp::connection_hdl hdl)
{
	m_status = "Close";
}

void websocketMager::on_message(websocketpp::connection_hdl, client::message_ptr msg)
{
	std::string str = msg->get_payload();
	
	if (str.substr(2, 4) == "data")
	{
		printf("m_curMsg = data\n");
	}
	if (str.substr(2, 5) != "state")
	{
		return;
	}
	m_curMsg = atoi(str.substr(10, 1).c_str());
	printf("m_curMsg = %d\n",m_curMsg);
	if(PostureAnalysisScene::m_bIsPlayVideo||Ext_IsRecordBegin == true)
	{
		return;
	}
	if(m_curMsg == 3)
	{
		Ext_IsRecordBegin = true;
		Sleep(Ext_VideoSleep);
		Ext_IsThreadOn = false;

		if (m_Delegate1)
		{
			m_Delegate1->RecordOk();
		}
		if (m_Delegate2)
		{
			m_Delegate2->RecordOk();
		}
		PostureAnalysisScene* pLayer = (PostureAnalysisScene*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(98);
		CCMenuItemToggle* pToggle = (CCMenuItemToggle*)(pLayer->m_pMenu->getChildByTag(99));
		pToggle->setSelectedIndex(1);
		pLayer->CallbackPause(pToggle);
	}
}