﻿#pragma once
#include "bubble_item.h"
#include "module/service/team_service.h"

namespace nim_comp
{
/** @class TeamItem
  * @brief 高级群会话中右侧成员列表项控件
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2015/9/11
  */
class TeamItem : public ui::ListContainerElement
{
public:

	/** 
	* 初始化控件内部指针	
	* @return void 无返回值
	*/
	void InitControl();

	/**
	* 初始化控件外观
	* @param[in] info 群成员信息（如果是第一次加载此用户的信息，则此的信息不完整，此时头像图片还未下载下来）
	* @return void 无返回值
	*/
	void InitInfo(const nim::TeamMemberProperty &info);

	/** 
	* 设置本成员为管理员
	* @param[in] admin 设置/取消 为管理员 	
	* @return void 无返回值
	*/
	void SetAdmin(bool admin);

	/**
	* 设置本成员为管理员
	* @param[in] admin 设置/取消 为管理员
	* @return void 无返回值
	*/
	void SetOwner(bool is_owner);

	/** 
	* 获取此群成员的成员类型	
	* @return NIMTeamUserType 群成员类型	
	*/
	nim::NIMTeamUserType GetTeamUserType();
	
	/**
	* 获取此群成员的群昵称
	* @return string 群成员昵称
	*/
	std::string GetTeamCard() const;

	/** 
	* 设置群成员在群成员列表中显示的名字（以昵称优先，无昵称则设置为用户名字）
	* @param[in] uinfo 用户信息 
	* @param[in] team_card 新的群昵称			
	* @return void 无返回值
	*/
	void SetMemberName(const std::string& team_card);
private:
	ui::Button*		member_icon_;
	ui::Label*		member_name_;
	ui::Control*	icon_admin_;
	std::string		team_card_;
	nim::NIMTeamUserType team_user_type_;
	AutoUnregister	unregister_cb;
};
}