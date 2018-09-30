#pragma once
#include <memory>
#include <ip/message_factory.h>
#include <network/news.h>
#include <google/protobuf/message.h>
#include <network/network_convert.h>
#include <map>
#include <functional>
using namespace google::protobuf;

namespace happy
{
	namespace utils
	{
		namespace network
		{
			class UtilMessageFactory : public happy::asio::ip::MessageFactory
			{
			public:
				/*--------------------------------------------------------
				����˵��
					network_convert������������
					is_read_print���Ƿ��ӡ��ȡ������Ϣ
					is_response���Ƿ�Ӧ�����ݣ��ͻ�������������б�
				--------------------------------------------------------*/
				UtilMessageFactory(NetworkConvert* network_convert, const bool is_read_print, const bool is_response, const string& session_id = "");
			protected:
				NetworkConvert* network_convert_;
				const bool is_read_print_;
				const bool is_response_;
				map <string, function <shared_ptr <Message>(const shared_ptr<Message>)>> handler_;
			protected:
				virtual shared_ptr <Message> Produce(const shared_ptr <News> news);
				virtual void PrintMessage(const shared_ptr<Message> message);
				virtual bool IsConsumedForRead(const uint8_t* buffer, const size_t& length
					, size_t& deal_length, bool& has_package) override final;
				virtual bool HandleRead(const uint8_t* buffer, const size_t& length, string& response) override final;
			};
		}
	}
}
