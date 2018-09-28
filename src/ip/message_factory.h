#pragma once
#include <stdint.h>
#include <string>
#include <memory>
using namespace std;

namespace happy
{
	namespace asio
	{
		namespace ip
		{
			enum ClosedType
			{
				CLOSED_BY_TIMEOUT,
				CLOSED_BY_REMOTE,
			};

			class MessageFactory
			{
			public:
				MessageFactory(const string& session_id = "")
					: session_id_(session_id)
				{}
				virtual shared_ptr <happy::asio::ip::MessageFactory> Create(const string& session_id) 
				{ 
					return make_shared <happy::asio::ip::MessageFactory>(session_id); 
				}
				virtual void HandleCreate(string& response){}
				/*--------------------------------------------------------
				����
					buffer���������ݻ�����
					length���������ݳ���
					response��Ӧ�����ݻ�����
				����ֵ
					true��ҵ��㴦�����ݰ��ɹ������µ����Ự�ĳ�ʱʱ�䣩
					false��ҵ��㴦�����ݰ�ʧ��
				--------------------------------------------------------*/
				virtual bool HandleRead(const uint8_t* buffer, const size_t& length, string& response) 
				{
					return true;
				}
				virtual void HandleClose(const ClosedType closed_type) {}
				virtual void HandleWrite(const string& tag) {};
				/*--------------------------------------------------------
				����
					buffer���������ݻ�����
					length���������ݳ���
					deal_length���Ѵ����������ݳ���
					has_package���Ƿ��к������ݰ�   
				����ֵ
					true�����ݰ�����ɹ����յ�һ�������İ���
					false�����ݴ���ʧ�ܣ�has_packageΪtrue��ʾ�յ�һ���������İ���has_packageΪfalse��ʾ��Ҫ����deal_length�����ݰ���
				--------------------------------------------------------*/ 
				virtual bool IsConsumedForRead(const uint8_t* buffer, const size_t& length, size_t& deal_length, bool& has_package)
				{
					deal_length = length;

					return true;
				}
			protected:
				string session_id_;
			};
		}
	}
}