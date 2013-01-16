//
//  ConstDef.h
//  AlibabaMobile
//
//  Created by  on 11-12-27.
//  Copyright (c) 2011 __Alibaba__. All rights reserved.
//

#ifndef Common_ConstDef_h
#define Common_ConstDef_h

// Debug server switch
//#define USING_DEBUG_SERVER

#ifdef USING_DEBUG_SERVER

#define AMCONST_HOST @"10.20.172.18:8780"
#define AMCONST_BASE_URL @"http://10.20.172.18:8780/api/json2/1/cn.ali.mobile"
#define AMCONST_BASE_URL4PARAM @"http://10.20.172.18:8780/api/param2/1/cn.ali.mobile"
#define AMCONST_BASE_URL4OAUTH @"https://10.249.200.45:1443/api/param2/2/system.oauth2"

// Ocean app key and signature key
#define AMCONST_APP_KEY @"10003939"
#define AMCONST_SIGNATURE_KEY @"M2NqNQWwyGeogo8WOpUfzQ=="
#define AMCONST_OCEAN_PREFIX @"json2/1/cn.ali.mobile"

// For Logistics and message notification request
#define AMCONST_OCEAN_PREFIX_PARAM @"param2/1/cn.ali.mobile"

// For login request
#define AMCONST_OCEAN_PREFIX_OAUTH @"param2/2/system.oauth2"

#else
#define AMCONST_HOST @"gw.open.china.alibaba.com"
#define AMCONST_BASE_URL @"http://gw.open.china.alibaba.com/openapi/json2/1/ali.mobile"
#define AMCONST_BASE_URL4PARAM @"http://gw.open.china.alibaba.com/openapi/param2/1/ali.mobile"
#define AMCONST_BASE_URL4OAUTH @"https://gw.open.china.alibaba.com/openapi/param2/1/system.oauth2"//#define AMCONST_BASE_URL4OAUTH @"https://gw.open.china.alibaba.com/openapi/param2/2/system.oauth2" 

// Ocean app key and signature key
#define AMCONST_APP_KEY @"5005"
#define AMCONST_SIGNATURE_KEY @"kd823b5dsa"
#define AMCONST_OCEAN_PREFIX @"json2/1/ali.mobile"

// For Logistics and message notification request
#define AMCONST_OCEAN_PREFIX_PARAM @"param2/1/ali.mobile"

// For login request
#define AMCONST_OCEAN_PREFIX_OAUTH @"param2/1/system.oauth2"//解决错误param2/2/system.oauth2
#endif //USING_DEBUG_SERVER

//xiejin screen width and height
#define SCREEN_WIDTH = 320;
#define SCREEN_HEIGHT = 480;

// Application identifier
#define AMCONST_APP_ID @"com.alibaba.wireless4ios"

// Transaction 定义
#define AMTRANSACTION_TYPE_LOGIN                            1
#define AMTRANSACTION_TYPE_SEZRCH_OFFER               2
#define AMTRANSACTION_TYPE_SEARCH_COMPANY         3
#define AMTRANSACTION_TYPE_OFFER_DETAIL           4
#define AMTRANSACTION_TYPE_COMPANY_DETAIL         5
#define AMTRANSACTION_TYPE_COMPANY_CREDIT_RESULT  6
#define AMTRANSACTION_TYPE_OFFER_LIST_BY_COMPANY  7
#define AMTRANSACTION_TYPE_CATEGORY_LIST          8
#define AMTRANSACTION_TYPE_COMPANY_MAP_DATA       9
#define AMTRANSACTION_TYPE_HOTAREA_RESULT         10
#define AMTRANSACTION_TYPE_SUGGEST_LIST           11
#define AMTRANSACTION_TYPE_SMART_NAVIGATION       12
#define AMTRANSACTION_TYPE_PRIMARY_CATEGORIES     13
#define AMTRANSACTION_TYPE_SUBCATEGORY_LIST       14
#define AMTRANSACTION_TYPE_PRICE_LIST             15
#define AMTRANSACTION_TYPE_MESSAGE_LIST           16
#define AMTRANSACTION_TYPE_HISTORYPRICE		    17
#define AMTRANSACTION_TYPE_NEWSCATEGORY_LIST	    18
#define AMTRANSACTION_TYPE_NEWS_LIST			    19  
#define AMTRANSACTION_TYPE_NEWS_DETAIL		    20
#define AMTRANSACTION_TYPE_PRICE_HISTORY          21
#define AMTRANSACTION_TYPE_NEWS_PICTURE_DETAIL  22
#define AMTRANSACTION_TYPE_HOT_NEWS			    23
#define AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST  24
#define AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST  25
#define AMTRANSACTION_TYPE_FAVORITE_PRICE_LIST  26
#define AMTRANSACTION_TYPE_FAVORITE_OFFER_LIST_DELETE  27
#define AMTRANSACTION_TYPE_FAVORITE_COMPANY_LIST_DELETE  28
#define AMTRANSACTION_TYPE_FAVORITE_PRICE_ADD  29
#define AMTRANSACTION_TYPE_FAVORITE_PRICE_DELETE  30
#define AMTRANSACTION_TYPE_FAVORITE_OFFER_ADD  31
#define AMTRANSACTION_TYPE_FAVORITE_COMPANY_ADD  32
#define AMTRANSACTION_TYPE_AREA_AND_CATEGORY  33
#define AMTRANSACTION_TYPE_FAVORITE_LOGISTICS_TRACESTEP  34
#define AMTRANSACTION_TYPE_NEWS_PICTURE_DATA  35
#define AMTRANSACTION_TYPE_MESSAGE_READ  36
#define AMTRANSACTION_TYPE_MESSAGE_COUNT  37
#define AMTRANSACTION_TYPE_CATEGORY_SUB_CATEGORY  38
#define AMTRANSACTION_TYPE_UPDATE_CHECKER  39
#define AMTRANSACTION_TYPE_QUERY_LOGIS_SIMPLE_ORDER  40
#define AMTRANSACTION_TYPE_AUTH  41
#define AMSAVE_PASSWORD_TO_SERVER  42
#define AMTRANSACTION_TYPE_FEEDBACK  43
#define AMTRANSACTION_TYPE_GEOGRAPHICINFO  44
#define AMTRANSACTION_TYPE_MESSAGE_TYPE  45 // 消息中心 消息类型
#define AMTRANSACTION_TYPE_MESSAGE_DELETE  46
#define AMTRANSACTION_TYPE_DEVICE_REGIST 47
#define AMTRANSACTION_TYPE_MESSAGE_DETAIL  48
#define AMTRANSACTION_TYPE_CUSTOMER_ALL_VISITOR  49 //增加询盘管理--所有访客类型
#define AMTRANSACTION_TYPE_PRECISION_GET_USERINFO  50 //精准营销--用户信息
#define AMTRANSACTION_TYPE_PRECISION_VISITOR_LIST  51 //精准营销--访客列表
#define AMTRANSACTION_TYPE_PRECISION_VISITOR_STATUS  52 //精准营销--访客状态
#define AMTRANSACTION_TYPE_PRECISION_TALK_PERMISSION  53 //精准营销--free用户的洽谈权限
#define AMTRANSACTION_TYPE_PRECISION_SAVE_FREE_USER_RES 54 //精准营销--更新free用户权限已使用
#define AMTRANSACTION_TYPE_PRECISION_VISITOR_DETAIL 55 //精准营销--访客详情
#define AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_ADD 56 //访客详情--添加推荐客户
#define AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_LIST 57 //访客详情--获取推荐客户列表
#define AMTRANSACTION_TYPE_CUSTOMER_SUGGEST_STATE 58 //访客详情--获取推荐客户状态

#define AMTRANSACTION_TYPE_HOMEPAGE_DRESS_REQUEST 59
#define AMTRANSACTION_TYPE_SUBPAGE_REQUEST 60
#define AMTRANSACTION_TYPE_HOME_EVENT1_LIST 61
#define AMTRANSACTION_TYPE_HOME_EVENT2_LIST 62
#define AMTRANSACTION_TYPE_HOME_EVENT3_LIST 63
#define AMTRANSACTION_TYPE_HOME_PRICE_LIST 64 // 首页价格行情
#define AMTRANSACTION_TYPE_HOTRANK_OFFER_LIST 65
#define AMTRANSACTION_TYPE_HOTRANK_COMPANY_LIST 66

// 消息中心消息类型
#define MSG_TYPE_WW_OFFLINE_MSG @"ww_offline_msg"

// 安全释放
#define AM_RELEASE_SAFELY(__POINTER) { if (nil != (__POINTER)) { [__POINTER release]; __POINTER = nil; } }

// OCEAN鉴权错误，包含access token过期等多个错误的返回值。
#define AM_OCEAN_ERROR_NEED_AUTHENTICATED @"401"

//行业首页页面选择。
#define AM_INDUSTRY_SELECT_HOME_DRESS     1
#define AM_INDUSTRY_SELECT_HOME_PRODUCT   2
#define AM_INDUSTRY_SELECT_HOME_FURNITURE 3
#define AM_INDUSTRY_SELECT_HOME_INDUSTRY  4
#define AM_INDUSTRY_SELECT_HOME_MATERIAL  5

//NSURLErrorDomain Code=-1009 "The Internet connection appears to be offline
#define NSURLErrorConnectionToBeOffline -1009

#endif //USING_DEBUG_SERVER