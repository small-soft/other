/************************************************************************/
//dengxiang:���ļ���������Э�����¼����ͺ�ԭ��,����ֱ�Ӱ�����ͷ�ļ�.
/************************************************************************/
/************************************************************************/
// ����MACRO_DEF_EXTERNΪ�ⲿʹ�����ͣ�����Ϊ�ڲ�ʹ��
/************************************************************************/
/************************************************************************/
// Э�����ڲ��Զ���Ŀ�����127������(0x00000001 ~ 0x0000007F)
/************************************************************************/
//�ر�ģ��
MACRO_DEF(PC_SHUTDOWN_IND						, 0x00000001					, PcShutdownInd)

#ifdef SOCKET_ASYNC
MACRO_DEF(PC_SOCKET_IND							, 0x00000002					, PcSocketInd)
#endif

MACRO_DEF(PC_SET_HEALTH_CHECK_CONFIG			, 0x00000003					, PcHealthCheckConfig)
MACRO_DEF(PC_CLEAR_VAR_IND 					    , 0x00000004					, PcClearVarInd)

//��������
MACRO_DEF(PC_SET_NETWORK_CONFIG					, 0x00000010					, PcNetworkConfig)
MACRO_DEF(PC_CNF_NETWORK_CONFIG					, 0x00000011					, PcCnfNetworkConfig)
MACRO_DEF_EXTERN(PC_EVENT_NETWORK_CONFIG		, PC_CNF_NETWORK_CONFIG			, PcEventNetworkConfig)

//�����쳣
MACRO_DEF(PC_SEND_EXCEPTION_IND					, 0x00000012					, PcSendExceptionInd)
MACRO_DEF_EXTERN(PC_EVENT_SEND_EXCEPTION		, PC_SEND_EXCEPTION_IND			, PcEventSendException)

//�����쳣
MACRO_DEF(PC_RECV_EXCEPTION_IND					, 0x00000013					, PcRecvExceptionInd)
MACRO_DEF_EXTERN(PC_EVENT_RECV_EXCEPTION_IND	, PC_RECV_EXCEPTION_IND			, PcEventRecvException)

//���ճ���
MACRO_DEF(PC_EXCEED_EXCEPTION_IND				, 0x00000014					, PcExceedExceptionInd)
MACRO_DEF_EXTERN(PC_EVENT_EXCEED_EXCEPTION_IND	, PC_EXCEED_EXCEPTION_IND		, PcEventExceedException)

//����쳣
MACRO_DEF(PC_PACK_EXCEPTION_IND					, 0x00000015					, PcPackExceptionInd)
MACRO_DEF_EXTERN(PC_EVENT_PACK_EXCEPTION_IND	, PC_PACK_EXCEPTION_IND			, PcEventPackException)

//����쳣
MACRO_DEF(PC_UNPACK_EXCEPTION_IND				, 0x00000016					, PcUnpackExceptionInd)
MACRO_DEF_EXTERN(PC_EVENT_UNPACK_EXCEPTION_IND	, PC_UNPACK_EXCEPTION_IND		, PcEventUnpackException)


