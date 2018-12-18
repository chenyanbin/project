#include "YVMessage.h"
#include <climits>


using namespace YVSDK;

_YVMessage::_YVMessage(YVMessageType inType, YVMessageStatus instate)
{
	static uint64 sid = 1;
	id = sid++;
	if (sid == 0) sid = 1;

	type = inType;
	state = instate;
}

 _YVMessage::~_YVMessage()
{

}

 bool  _YVMessage::operator <= (const _YVMessage& msg)
 {
	 return this->sendTime <= msg.sendTime ?
		true : false;
 }

 _YVMessageList::_YVMessageList()
 {
	 setMaxNum(UINT_MAX);
 }

void _YVMessageList::clear()
{
	m_msssageList.clear();
}

void _YVMessageList::setMaxNum(uint32 maxNum)
{
	m_maxMessageNum = maxNum;
}

std::vector<YVMessagePtr>& _YVMessageList::getMessageList()
{
	return m_msssageList;
}

void _YVMessageList::insertMessage(YVMessagePtr& msg)
{
	if (msg == NULL) return;

	std::vector<YVMessagePtr>::iterator insertIt = m_msssageList.end();
	for (std::vector<YVMessagePtr>::iterator it = m_msssageList.begin();
		it != m_msssageList.end(); ++it
		)
	{
		//int msgID = (*it)->id;
		if ((*it)->id == msg->id) return;
		//��ǰλ�õ���Ϣ���ڴ�����Ϣ
		if (insertIt == m_msssageList.end()  && !(**it <= *msg) )
		{
			insertIt = it;
		}
	}

	if (insertIt == m_msssageList.end())
	{
		m_msssageList.push_back(msg);
	}
	else
	{
		m_msssageList.insert(insertIt, msg);
	}
	
	//m_msssageList.push_back(msg);

	//��֤��Ϣ���Ȳ�����m_maxMessageNum��ȷ���ڴ�ʹ��
	while (m_msssageList.size() > m_maxMessageNum)
	{
		m_msssageList.erase(m_msssageList.begin());
	}
}

YVMessagePtr _YVMessageList::getMessageById(uint64 mssageID)
{
	for (std::vector<YVMessagePtr>::iterator it = m_msssageList.begin();
		it != m_msssageList.end(); ++it)
	{
		if ((*it)->id == mssageID)
		{
			return *it;
		}
	}
	return NULL;
}

void  _YVMessageList::delMessageById(uint64 mssageID)
{
	for (std::vector<YVMessagePtr>::iterator it = m_msssageList.begin();
		it != m_msssageList.end(); ++it)
	{
		if ((*it)->id == mssageID)
		{
			m_msssageList.erase(it);
			return;
		}
	}
}
