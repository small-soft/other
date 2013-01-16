#ifndef __OLDMSGTYPE_H__
#define __OLDMSGTYPE_H__

typedef enum _AIMsgType
{
	CNT_MESSAGE_SENT = 0,				//������������Ϣ����Ϣ��ϵ������Ϣ�Ľ�����
	CNT_MESSAGE_RECEIVED = 1,			//�����յ�����Ϣ����Ϣ��ϵ������Ϣ�ķ�����
	AUTO_REPLAY_CNT_MESSAGE = 2,		//�յ����Զ��ظ���Ϣ����Ϣ����ϵ������Ϣ�ķ�����
	SUBSCRIBE_MESSAGE = 3,				//������Ϣ  7777
	SYSTEM_MESSAGE = 4,					//ϵͳ��Ϣ  7777

	//����Ϊϵͳ�¼���Ϣ  
	ADD_CNT_SUCCESS = 10,				//�Ӻ��ѳɹ�����ϵ�������Ӻ��� 7777
	ADD_CNT_FAILED = 11,				//�Ӻ���ʧ�ܣ���Ϣ������ʧ�ܵ�ԭ���루��������szAddCntFailInfo��
	ADD_CNT_NEED_REQ = 12,				//��Ӻ���ʱ�Է���Ҫ��֤���յ�����Ϣ��Ӧ�����Ӧ��ϵ�˷�����֤����  7777
	ADDED_BY_PEER = 13,					//��ĳ��ϵ�����Ϊ����   7777
	REQ_FROM_PEER = 14,					//������ĳ��ϵ�˵���֤������Ϣ�������������ϸ��Ϣ 7777
	//
	DECLINED_BY_PEER = 15,				//��ĳ��ϵ�˾ܾ���Ϊ�������ͳ���֤������յ��Ļظ��� 7777
	ACCEPTED_BY_PEER = 16,				//����ϵ�˽��ܣ�Ϊ�������ͳ���֤������յ��Ļظ���  7777
	ADD_BLK_SUCCESS,					//��Ӻ������ɹ�
	ADD_BLK_FAILED,						//��Ӻ�����ʧ��
	REMOVE_BLK_SUCESS,					//�Ƴ��������ɹ�
	REMOVE_BLK_FAILED,					//�Ƴ�������ʧ��
	REMOVE_CNT_SUCESS,					//�Ƴ���ϵ�˳ɹ�
	REMOVE_CNT_FAILED,					//�Ƴ���ϵ��ʧ��
	ADD_CNT_WAIT_VERIFY,				//���ڵȴ��Է�����֤��Ϊ�������ͳ���֤������յ��Ļظ��� 7777
	CHG_VERIFY_OK,						//�޸���֤״̬�ɹ�	contentΪ"0"(����Ҫ��֤)"1"(��Ҫ��֤)��"2"(���������)  
	CHG_VERIFY_FAILE,					//�޸���֤״̬ʧ��
	CHG_SIGNATURE_OK,					//�޸�ǩ���ɹ�		contentΪ��ǰ��ǩ��
	CHG_SIGNATURE_FAIL,					//�޸�ǩ��ʧ��
	GET_PEER_ADD_VERIFY,				//��ȡ��ϵ��VerifyConfig�ɹ�		contentΪ������֤״̬flag, 0����Ҫ��֤��1��Ҫ��֤��2���üӺ��ѣ�3���Ѳ�����
	MSG_TYPE_TMP,						//�������
	GET_PEER_UDB_PROFILE = 30,			//Udb Profile contentΪż�����ַ�����һ��һֵ����
	GET_DEGREE_OK,						//��ȡ��ϵ�˵ȼ��� contentΪ��','�ָ�������������ֱ�Ϊ���ȼ����ܻ�Ծ�ȡ�������Ҫ��Ծ��
	GET_DEGREE_FAIL,
	GET_PEER_SEND_VERIFY,
	HELP_LOGIN_OK,						//contactΪparentId, content����','�ָ�Ķ�����˺�
	HELP_LOGIN_FAIL,					//
	CHG_SERV_MODE_OK,					//�޸�E�ͷ�����״̬�ɹ�
	CHG_SERV_MODE_FAIL,
	GET_CNTMEMO_OK,						//��ȡ�ҶԺ��ѵı�ע
	GET_CNTMEMO_FAIL

} AIM_MSG_TYPE_OLD;

#endif //__OLDMSGTYPE_H__