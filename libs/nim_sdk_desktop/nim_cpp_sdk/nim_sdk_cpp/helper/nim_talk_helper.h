﻿/** @file nim_talk_helper.h
  * @brief Talk 辅助方法和数据结构定义
  * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/10/16
  */

#ifndef _NIM_SDK_CPP_TALK_HELPER_H_
#define _NIM_SDK_CPP_TALK_HELPER_H_

#include <string>
#include <list>
#include <functional>
#include "json.h"
#include "nim_common_helper.h"

/**
* @namespace nim
* @brief IM
*/
namespace nim
{

#include "nim_talk_def.h"
#include "nim_session_def.h"
#include "nim_msglog_def.h"
#include "nim_res_code_def.h"

/** @brief 消息属性设置 */
struct MessageSetting
{
	BoolStatus resend_flag_;			/**< 该消息是否为重发状态 */
	BoolStatus server_history_saved_;	/**< 该消息是否存储云端历史 */
	BoolStatus roaming_;				/**< 该消息是否支持漫游 */
	BoolStatus self_sync_;				/**< 该消息是否支持发送者多端同步 */
	BoolStatus need_push_; 				/**< 是否需要推送 */
	BoolStatus push_need_badge_;		/**< 是否要做消息计数 */
	BoolStatus push_need_nick_;			/**< 需要推送昵称 */
	Json::Value push_payload_;
	std::string push_content_;
	Json::Value server_ext_;
	std::string local_ext_;

	/** 构造函数 */
	MessageSetting() : server_history_saved_(BS_NOT_INIT)
		, roaming_(BS_NOT_INIT)
		, self_sync_(BS_NOT_INIT)
		, need_push_(BS_NOT_INIT)
		, push_need_badge_(BS_NOT_INIT)
		, push_need_nick_(BS_NOT_INIT)
		, resend_flag_(BS_NOT_INIT){}

	/** @fn void ToJsonValue(Json::Value& message) const
	  * @brief 组装Json Value字符串
	  * @param[out] message 消息Json
	  * @return void
      */
	void ToJsonValue(Json::Value& message) const
	{
		if (server_history_saved_ != BS_NOT_INIT)
			message[kNIMMsgKeyHistorySave] = server_history_saved_;
		if (roaming_ != BS_NOT_INIT)
			message[kNIMMsgKeyMsgRoaming] = roaming_;
		if (self_sync_ != BS_NOT_INIT)
			message[kNIMMsgKeyMsgSync] = self_sync_;
		if (push_need_badge_ != BS_NOT_INIT)
			message[kNIMMsgKeyNeedBadge] = push_need_badge_;
		if (need_push_ != BS_NOT_INIT)
			message[kNIMMsgKeyPushEnable] = need_push_;
		if (push_need_nick_ != BS_NOT_INIT)
			message[kNIMMsgKeyNeedPushNick] = push_need_nick_;
		if (resend_flag_ != BS_NOT_INIT)
			message[kNIMMsgKeyResendFlag] = resend_flag_;
		if (!push_payload_.empty())
			message[kNIMMsgKeyPushPayload] = GetJsonStringWithNoStyled(push_payload_);
		if (!push_content_.empty())
			message[kNIMMsgKeyPushContent] = push_content_;
		if (!server_ext_.empty())
			message[kNIMMsgKeyServerExt] = GetJsonStringWithNoStyled(server_ext_);
		if (!local_ext_.empty())
			message[kNIMMsgKeyLocalExt] = local_ext_;
	}

	/** @fn void ParseMessageSetting(const Json::Value& message)
	  * @brief 从Json Value解析出消息属性设置
	  * @param[in] message 消息Json
	  * @return void
      */
	void ParseMessageSetting(const Json::Value& message)
	{
		if (message.isMember(kNIMMsgKeyHistorySave))
			server_history_saved_ = (BoolStatus)message[kNIMMsgKeyHistorySave].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyMsgRoaming))
			roaming_ = (BoolStatus)message[kNIMMsgKeyMsgRoaming].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyMsgSync))
			self_sync_ = (BoolStatus)message[kNIMMsgKeyMsgSync].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyNeedBadge))
			push_need_badge_ = (BoolStatus)message[kNIMMsgKeyNeedBadge].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyPushEnable))
			need_push_ = (BoolStatus)message[kNIMMsgKeyPushEnable].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyNeedPushNick))
			push_need_nick_ = (BoolStatus)message[kNIMMsgKeyNeedPushNick].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyResendFlag))
			resend_flag_ = (BoolStatus)message[kNIMMsgKeyResendFlag].asInt() == 1 ? BS_TRUE : BS_FALSE;

		Json::Reader reader;
		if (!reader.parse(message[kNIMMsgKeyServerExt].asString(), server_ext_) || !server_ext_.isObject())
			//assert(0);
		if (!reader.parse(message[kNIMMsgKeyPushPayload].asString(), push_payload_) || !push_payload_.isObject())
			//assert(0);
		local_ext_ = message[kNIMMsgKeyLocalExt].asString();
		push_content_ = message[kNIMMsgKeyPushContent].asString();
	}
};

/** @brief P2P和群组消息 */
struct IMMessage
{
public:
	NIMResCode	rescode_;						/**< 错误码 */
	NIMMessageFeature	feature_;				/**< 消息属性 */

public:
	NIMSessionType	session_type_;				/**< 会话类型 */
	std::string		receiver_accid_;			/**< 接收者ID */
	std::string		sender_accid_;				/**< 发送者ID */
	__int64			timetag_;					/**< 消息时间戳（毫秒） */
	std::string		content_;					/**< 消息内容 */
	NIMMessageType	type_;						/**< 消息类型 */
	std::string		attach_;					/**< 消息附件 */
	std::string		client_msg_id_;				/**< 消息ID（客户端） */
	bool			resend_flag_;				/**< 重发标记 */
	MessageSetting	msg_setting_;				/**< 消息属性设置 */

public:
	std::string	   local_res_path_;				/**< 媒体文件本地绝对路径（客户端） */
	std::string	   local_talk_id_;				/**< 会话ID（客户端） */
	std::string	   local_res_id_;				/**< 媒体文件ID（客户端） */
	NIMMsgLogStatus	status_;					/**< 消息状态（客户端） */
	NIMMsgLogSubStatus	sub_status_;			/**< 消息子状态（客户端） */

public:
	int			   readonly_sender_client_type_;	/**< 发送者客户端类型（只读） */
	std::string	   readonly_sender_device_id_;		/**< 发送者客户端设备ID（只读） */
	std::string	   readonly_sender_nickname_;		/**< 发送者昵称（只读） */
	__int64		   readonly_server_id_;				/**< 消息ID（服务器，只读） */

	/** 构造函数 */
	IMMessage() : resend_flag_(false)
				, readonly_sender_client_type_(0) 
				, readonly_server_id_(0)
				, feature_(kNIMMessageFeatureDefault)
				, session_type_(kNIMSessionTypeP2P)
				, timetag_(0)
				, status_(nim::kNIMMsgLogStatusNone)
				, sub_status_(nim::kNIMMsgLogSubStatusNone) {}

	/** 构造函数 */
	IMMessage(const std::string &json_msg) : resend_flag_(false)
		, readonly_sender_client_type_(0) 
		, readonly_server_id_(0)
		, feature_(kNIMMessageFeatureDefault)
		, session_type_(kNIMSessionTypeP2P)
		, timetag_(0)
		, status_(nim::kNIMMsgLogStatusNone)
		, sub_status_(nim::kNIMMsgLogSubStatusNone) 
	{
		Json::Value values;
		Json::Reader reader;
		if (reader.parse(json_msg, values) && values.isObject())
		{
			session_type_ = (NIMSessionType)values[kNIMMsgKeyToType].asUInt();
			receiver_accid_ = values[kNIMMsgKeyToAccount].asString();
			sender_accid_ = values[kNIMMsgKeyFromAccount].asString();
			readonly_sender_client_type_ = values[kNIMMsgKeyFromClientType].asUInt();
			readonly_sender_device_id_ = values[kNIMMsgKeyFromDeviceId].asString();
			readonly_sender_nickname_ = values[kNIMMsgKeyFromNick].asString();
			timetag_ = values[kNIMMsgKeyTime].asUInt64();

			type_ = (NIMMessageType)values[kNIMMsgKeyType].asUInt();
			content_ = values[kNIMMsgKeyBody].asString();
			attach_ = values[kNIMMsgKeyAttach].asString();
			client_msg_id_ = values[kNIMMsgKeyClientMsgid].asString();
			readonly_server_id_ = values[kNIMMsgKeyServerMsgid].asUInt64();
			resend_flag_ = values[kNIMMsgKeyResendFlag].asUInt() > 0;

			local_res_path_ = values[kNIMMsgKeyLocalFilePath].asString();
			local_talk_id_ = values[kNIMMsgKeyLocalTalkId].asString();
			local_res_id_ = values[kNIMMsgKeyLocalResId].asString();
			status_ = (NIMMsgLogStatus)values[kNIMMsgKeyLocalLogStatus].asUInt();
			sub_status_ = (NIMMsgLogSubStatus)values[kNIMMsgKeyLocalLogSubStatus].asUInt();

			msg_setting_.ParseMessageSetting(values);
		}
	}

	/** @fn std::string ToJsonString() const
	  * @brief 组装Json Value字符串
	  * @return string Json Value字符串 
      */
	std::string		ToJsonString(bool use_to_send) const
	{
		Json::Value values;
		values[kNIMMsgKeyToType] = session_type_;
		values[kNIMMsgKeyToAccount] = receiver_accid_;
		values[kNIMMsgKeyFromAccount] = sender_accid_;
		values[kNIMMsgKeyTime] = timetag_;
		values[kNIMMsgKeyType] = type_;
		values[kNIMMsgKeyBody] = content_;
		values[kNIMMsgKeyAttach] = attach_;
		values[kNIMMsgKeyClientMsgid] = client_msg_id_;
		values[kNIMMsgKeyResendFlag] = resend_flag_ ? 1 : 0;
		values[kNIMMsgKeyLocalFilePath] = local_res_path_;
		values[kNIMMsgKeyLocalTalkId] = receiver_accid_;
		values[kNIMMsgKeyLocalResId] = local_res_id_;
		values[kNIMMsgKeyLocalLogStatus] = status_;
		values[kNIMMsgKeyLocalLogSubStatus] = sub_status_;

		msg_setting_.ToJsonValue(values);

		if (!use_to_send)
		{
			values[kNIMMsgKeyFromClientType] = readonly_sender_client_type_;
			values[kNIMMsgKeyFromDeviceId] = readonly_sender_device_id_;
			values[kNIMMsgKeyFromNick] = readonly_sender_nickname_;
			values[kNIMMsgKeyServerMsgid] = readonly_server_id_;
		}
		return GetJsonStringWithNoStyled(values);
	}
};

/** @brief 文件消息附件 */
struct IMFile
{
	std::string	md5_;				/**< 文件内容MD5 */
	__int64		size_;				/**< 文件大小 */
	std::string url_;				/**< 上传云端后得到的文件下载地址 */
	std::string display_name_;		/**< 用于显示的文件名称 */
	std::string file_extension_;	/**< 文件扩展名 */

	/** 构造函数 */
	IMFile() : size_(0) {}

	/** @fn std::string ToJsonString(Json::Value &attach) const
	  * @brief 组装Json Value字符串
	  * @param[in] attach Json Value字符串
	  * @return string Json Value字符串 
      */
	std::string ToJsonString(Json::Value &attach) const
	{
		//以下客户端可以选填
		if (!display_name_.empty())
			attach[kNIMFileMsgKeyDisplayName] = display_name_;
		if (!file_extension_.empty())
			attach[kNIMFileMsgKeyExt] = file_extension_;
		if (!md5_.empty())
			attach[kNIMFileMsgKeyMd5] = md5_;
		if (size_ > 0)
			attach[kNIMFileMsgKeySize] = size_;
		if (!url_.empty())
			attach[kNIMMsgAttachKeyUrl] = url_;

		return GetJsonStringWithNoStyled(attach);
	}

	/** @fn std::string ToJsonString() const
	  * @brief 组装Json Value字符串
	  * @return string Json Value字符串 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMFileMsgKeyDisplayName] = display_name_;

		return ToJsonString(attach);
	}
};

/** @brief 图片消息附件 */
struct IMImage : IMFile
{
	int			width_;			/**< 图片宽度 */
	int			height_;		/**< 图片高度 */

	/** 构造函数 */
	IMImage() : width_(0), height_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief 组装Json Value字符串
	  * @return string Json Value字符串 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMImgMsgKeyWidth] = width_;
		attach[kNIMImgMsgKeyHeight] = height_;
		attach[kNIMImgMsgKeyDisplayName] = display_name_;

		return __super::ToJsonString(attach);
	}
};

/** @brief 位置消息附件 */
struct IMLocation
{
	std::string	description_;		/**< 位置描述内容 */
	double		latitude_;			/**< 位置纬度 */
	double		longitude_;			/**< 位置经度 */

	/** 构造函数 */
	IMLocation() : latitude_(0), longitude_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief 组装Json Value字符串
	  * @return string Json Value字符串 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMLocationMsgKeyTitle] = description_;
		attach[kNIMLocationMsgKeyLatitude] = latitude_;
		attach[kNIMLocationMsgKeyLongitude] = longitude_;

		return GetJsonStringWithNoStyled(attach);
	}
};

/** @brief 语音消息附件 */
struct IMAudio : IMFile
{
	int			duration_;			/**< 语音时长 */

	/** 构造函数 */
	IMAudio() : duration_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief 组装Json Value字符串
	  * @return string Json Value字符串 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMAudioMsgKeyDisplayName] = display_name_;

		return __super::ToJsonString(attach);
	}
};

/** @brief 小视频消息附件 */
struct IMVideo : IMFile
{
	int			duration_;			/**< 视频时长 */
	int			width_;				/**< 视频画面宽度 */
	int			height_;			/**< 视频画面高度 */

	/** 构造函数 */
	IMVideo() : duration_(0), width_(0), height_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief 组装Json Value字符串
	  * @return string Json Value字符串 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMVideoMsgKeyWidth] = width_;
		attach[kNIMVideoMsgKeyHeight] = height_;
		attach[kNIMVideoMsgKeyDuration] = duration_;

		return __super::ToJsonString(attach);
	}
};

/** @fn bool ParseMessage(const std::string& msg_json, IMMessage& message)
  * @brief 解析消息
  * @param[in] msg_json 消息(Json Value数据字符串)
  * @param[out] message 消息
  * @return bool 解析成功或失败 
  */
bool ParseMessage(const std::string& msg_json, IMMessage& message);

/** @fn bool ParseReceiveMessage(const std::string& msg_json, IMMessage& message)
  * @brief 解析消息
  * @param[in] msg_json 消息(Json Value数据字符串)
  * @param[out] message 消息
  * @return bool 解析成功或失败 
  */
bool ParseReceiveMessage(const std::string& msg_json, IMMessage& message);

/** @fn void ParseReceiveMessage(const Json::Value& msg_json_value, IMMessage& message)
  * @brief 解析消息
  * @param[in] msg_json_value 消息
  * @param[out] message 消息
  * @return bool 解析成功或失败 
  */
void ParseReceiveMessage(const Json::Value& msg_json_value, IMMessage& message);

/** @fn void ParseReceiveMessage(const Json::Value& msg_json, IMMessage& message)
  * @brief 解析消息
  * @param[in] msg_json 消息(Json Value数据)
  * @param[out] message 消息
  * @return void 
  */
void ParseMessage(const Json::Value& msg_json, IMMessage& message);

} //namespace nim

#endif //_NIM_SDK_CPP_TALK_HELPER_H_