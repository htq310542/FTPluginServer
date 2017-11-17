#pragma once
#include "ProtoDataStruct_Trade.h"
#include "ProtoParseBase.h"

class CProtoPushUSDeal : public CProtoParseBase
{
public:
	//tomodify 1
	typedef PushUSDeal_Req		ProtoReqDataType;
	typedef PushUSDeal_Ack		ProtoAckDataType;

	//tomodify 2
	typedef PushUSDealReqBody	ProtoReqBodyType;
	typedef PushUSDealAckBody	ProtoAckBodyType;

public:
	CProtoPushUSDeal();
	virtual ~CProtoPushUSDeal();

	virtual bool ParseJson_Req(const Json::Value &jsnVal);
	virtual bool ParseJson_Ack(const Json::Value &jsnVal);
	virtual bool MakeJson_Req(Json::Value &jsnVal);
	virtual bool MakeJson_Ack(Json::Value &jsnVal);

	void	SetProtoData_Req(ProtoReqDataType *pData);
	void	SetProtoData_Ack(ProtoAckDataType *pData);
		
private:	
	bool ParseProtoBody_Req(const Json::Value &jsnVal, ProtoReqDataType &data);
	bool ParseProtoBody_Ack(const Json::Value &jsnVal, ProtoAckDataType &data);
	bool MakeProtoBody_Req(Json::Value &jsnVal, const ProtoReqDataType &data); 
	bool MakeProtoBody_Ack(Json::Value &jsnVal, const ProtoAckDataType &data);

	void GetProtoBodyField_Req(VT_PROTO_FIELD &vtField, const ProtoReqBodyType &reqData);
	void GetProtoBodyField_Ack(VT_PROTO_FIELD &vtField, const ProtoAckBodyType &ackData);

private:
	ProtoReqDataType	*m_pReqData;
	ProtoAckDataType	*m_pAckData;
};