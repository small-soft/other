#ifndef __IAIMESSAGE_H__
#define __IAIMESSAGE_H__

#include "AMTypes.h"
#include "AIMEnum.h"

#ifdef __cplusplus
extern "C" {
#endif	

	typedef enum
	{									// contactId				content
		eMSG_TYPE_CHAT_SEND = 0x100,	// receiver						msg
		eMSG_TYPE_CHAT_RECV,			// sender						msg
		eMSG_TYPE_CHAT_AUTO,			// sender						msg

		eMSG_TYPE_SMS_SEND,				// undefined					undefined
		eMSG_TYPE_SMS_RECV,				// undefined					undefined

		eMSG_TYPE_TRIBE,				// undefined					undefined
		eMSG_TYPE_MULTY,				// undefined					undefined

		eMSG_TYPE_OFFLINE,				// sender						msg

		eMSG_TYPE_FILE,					// contact						below
		/*
		<xparam>
			<dwImageSize>1666</dwImageSize>
			<strImageHash>5bd7a70c88f636a33b04c8d98f85f5bd</strImageHash>
			<llSID>309998873034619878</llSID>
			<strImageExtend>.jpg</strImageExtend>
		</xparam>
		*/
		eMSG_TYPE_SYSTEM,				//stile&title					url
		eMSG_TYPE_CONTACT_ADD_OK,		// contact						null
		eMSG_TYPE_CONTACT_ADD_FAIL,		// contact						null
		eMSG_TYPE_CONTACT_NEED_REQ,		// contact						null
		eMSG_TYPE_CONTACT_WAIT_VERIFY,	// contact						null
		eMSG_TYPE_CONTACT_ADDED_BY,		// contact						null
		eMSG_TYPE_CONTACT_REQ_FROM,		// contact						msg
		eMSG_TYPE_CONTACT_REJECTED_BY,	// contact						msg
		eMSG_TYPE_CONTACT_ACCEPTED_BY,	// contact						null

		eMSG_TYPE_SUBSCRIBE,			// contact						***||***||***
		eMSG_TYPE_EVIDENCE,				// undefined					undefined

		eMSG_TYPE_OPERATION,			// contact						msg
	}AIM_MSG_TYPE;

	/**
	* @brief				get message id.
	*/
	AIM_RESULT IAIMessage_GetID( AMHandle hMessage, AMInt64 *pID);

	/**
	* @brief				get message type
	*/
	AIM_RESULT IAIMessage_GetType( AMHandle hMessage, AIM_MSG_TYPE *peType);

	/**
	* @brief				get message contact
	* @param pszContactID	[in/out] return the pointer to the long ID.	
	* @more					Long ID is a const string of Message, terminated with '\0'. Do not modify or free it!
	*/
	AIM_RESULT IAIMessage_GetContactID( AMHandle hMessage, const AMChar **pszContactID);

	/**
	* @brief				get message body
	* @param pszContent		[in/out] return the pointer to the msg content.	
	* @more					content is a const string of Message, terminated with '\0'. Do not modify or free it!
	* @more					content varies according to type.
	*/
	AIM_RESULT IAIMessage_GetContent( AMHandle hMessage, const AMChar **pszContent);

	/**
	* @brief				get message time.
	*/
	AIM_RESULT IAIMessage_GetTime( AMHandle hMessage, AMInt32 *pTime);

	/**
	* @brief				get message read
	*/
	AIM_RESULT IAIMessage_IsRead( AMHandle hMessage, AMBool *pbRead);

#ifdef __cplusplus
};
#endif
#endif // __IAMESSAGE_H__