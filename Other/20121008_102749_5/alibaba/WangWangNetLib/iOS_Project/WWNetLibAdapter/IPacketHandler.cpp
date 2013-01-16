#include "IPacketHandler.h"
//#include "IPacketMgr.h"


IPacketHandler::IPacketHandler()
{
//	m_pPacketMgr = NULL;
//	m_pCallback = NULL;
}

IPacketHandler::~IPacketHandler()
{
    /*
	Cmds_t::const_iterator b = m_registeredCmds.begin();
	Cmds_t::const_iterator e = m_registeredCmds.end();
	for (; b != e; ++b)
	{
		UnregisterPacket(*b);
	}
    */
}

#if 0
void IPacketHandler::SetIPacketMgr(IPacketMgr* pPacketMgr)
{
	m_pPacketMgr = pPacketMgr;
	
	if (m_pPacketMgr)
		m_pCallback = m_pPacketMgr->GetIWangWangNetCallback();
}

void IPacketHandler::RegisterPacket(uint32_t nCmd)
{
	if (!m_pPacketMgr)
	{
		return;
	}
	
	m_pPacketMgr->RegisterPacketHandler(nCmd, this);
	
	m_registeredCmds.insert(nCmd);
}

void IPacketHandler::UnregisterPacket(uint32_t nCmd)
{
	if (!m_pPacketMgr)
	{
		return;
	}
	
	m_pPacketMgr->UnregisterPacketHandler(nCmd, this);
	
	m_registeredCmds.erase(nCmd);
}

void IPacketHandler::CloseSocket(bool bSync)
{
	if (!m_pPacketMgr)
	{
		return;
	}
	
	m_pPacketMgr->CloseSocket(bSync);
}

void IPacketHandler::SendPacket(const std::string& strPacket)
{
	if (!m_pPacketMgr)
	{
		return;
	}
	
	m_pPacketMgr->SendPacket(strPacket);
}
#endif

