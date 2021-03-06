#pragma once
#include "Include/FTPluginCore.h"
#include "Include/FTPluginQuoteInterface.h"
#include "Include/FTPluginTradeInterface.h"
#include "Protocol/ProtoDataStruct_Trade.h"
#include "TimerWnd.h"
#include "MsgHandler.h"
#include "JsonCpp/json.h"

class CPluginUSTradeServer;

class CPluginQueryUSHisDeal : public CTimerWndInterface, public CMsgHandlerEventInterface
{
public:
	CPluginQueryUSHisDeal();
	virtual ~CPluginQueryUSHisDeal();
	
	void Init(CPluginUSTradeServer* pTradeServer, ITrade_US*  pTradeOp);
	void Uninit();	
	void SetTradeReqData(int nCmdID, const Json::Value &jsnVal, SOCKET sock);
	void NotifyOnQueryUSHisDeal(Trade_Env enEnv, UINT32 nCookie, INT32 nCount, const Trade_DealItem* pArrDeal);

	void NotifySocketClosed(SOCKET sock);

protected:
	//CTimerWndInterface 
	virtual void OnTimeEvent(UINT nEventID);

	//CMsgHandlerEventInterface
	virtual void OnMsgEvent(int nEvent,WPARAM wParam,LPARAM lParam);

protected:
	//tomodify 1
	typedef QueryUSHisDeal_Req	TradeReqType;
	typedef QueryUSHisDeal_Ack	TradeAckType;
	typedef QueryUSHisDealAckItem TradeAckItemType;

	struct	StockDataReq
	{
		SOCKET	sock;
		DWORD	dwReqTick;
		DWORD	dwLocalCookie;
		TradeReqType req;
	};
	
	typedef std::vector<StockDataReq*>		VT_REQ_TRADE_DATA;	
	
protected:	
	void HandleTimeoutReq();
	void HandleTradeAck(TradeAckType *pAck, SOCKET	sock);
	void SetTimerHandleTimeout(bool bStartOrStop);
	void ClearAllReqAckData();
	
private: 
	bool DoDeleteReqData(StockDataReq* pReq); 
	void DoGetFilterCode(const std::string& strFilter, std::set<std::wstring>& setCode);
	bool IsFitFilter(const TradeAckItemType& AckItem, const std::set<std::wstring>& setCode);

private:
	void DoClearReqInfo(SOCKET socket);

protected:
	CPluginUSTradeServer	*m_pTradeServer;
	ITrade_US				*m_pTradeOp;	
	BOOL					m_bStartTimerHandleTimeout;
	
	CTimerMsgWndEx		m_TimerWnd;
	CMsgHandler			m_MsgHandler;

	VT_REQ_TRADE_DATA	m_vtReqData;
};