#ifndef XUMINGGANG_IM_IPACKETHANDLER_H
#define XUMINGGANG_IM_IPACKETHANDLER_H

//#include <set>
//#include "CommonDefs.h"
//#include "../Protocol/sc_head.h"

#include "IWangWangNetCallback.h"

class IPacketMgr;

class IPacketHandler
{
public:
	IPacketHandler();
	virtual ~IPacketHandler();
	
	void SetIPacketMgr(IPacketMgr* pPacketMgr);
	
//	virtual void OnPacket(uint32_t nCmd, const CScHead& header, std::string& pack) = 0;
	
public:
	void RegisterPacket(uint32_t nCmd);
	void UnregisterPacket(uint32_t nCmd);
	
protected:
	void SendPacket(const std::string& strPacket);
	void CloseSocket(bool bSync);
protected:
//	typedef std::set<uint32_t>		Cmds_t;
	
	IPacketMgr						*m_pPacketMgr;
	
//	Cmds_t							m_registeredCmds;
	
	IWangWangNetCallback			*m_pCallback;
};

#endif XUMINGGANG_IM_IPACKETHANDLER_H


