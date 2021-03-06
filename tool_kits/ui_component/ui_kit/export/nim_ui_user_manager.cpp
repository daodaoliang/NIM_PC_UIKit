﻿#include "nim_ui_user_manager.h"

namespace nim_ui
{

UserManager::UserManager()
{

}

UserManager::~UserManager()
{

}

void UserManager::InvokeRegisterAccount(const std::string &username, const std::string &password, const std::string &nickname, const OnRegisterAccountCallback& cb)
{
	nim_comp::UserService::GetInstance()->InvokeRegisterAccount(username, password, nickname, cb);
}

void UserManager::InvokeGetAllUserInfo(const OnGetUserInfoCallback& cb)
{
	nim_comp::UserService::GetInstance()->InvokeGetAllUserInfo(cb);
}

nim::NIMFriendFlag UserManager::GetUserType(const std::string &id)
{
	return nim_comp::UserService::GetInstance()->GetUserType(id);
}

bool UserManager::GetUserInfo(const std::string &account, nim::UserNameCard &info)
{
	return nim_comp::UserService::GetInstance()->GetUserInfo(account, info);
}

void UserManager::GetUserInfos(const std::list<std::string>& ids, std::list<nim::UserNameCard>& uinfos)
{
	nim_comp::UserService::GetInstance()->GetUserInfos(ids, uinfos);
}

const std::map<std::string, nim::UserNameCard>& UserManager::GetAllUserInfos()
{
	return nim_comp::UserService::GetInstance()->GetAllUserInfos();
}

void UserManager::InvokeUpdateUserInfo(const nim::UserNameCard & new_info, const OnUpdateUserInfoCallback & cb)
{
	nim_comp::UserService::GetInstance()->InvokeUpdateUserInfo(new_info, cb);
}

void UserManager::InvokeChangeUserPhoto(const std::string & url, const OnUpdateUserInfoCallback & cb)
{
	nim_comp::UserService::GetInstance()->InvokeChangeUserPhoto(url, cb);
}

std::wstring UserManager::GetUserName(const std::string &id, bool alias_prior/* = true */)
{
	return nim_comp::UserService::GetInstance()->GetUserName(id, alias_prior);
}

std::wstring UserManager::GetFriendAlias(const std::string & id)
{
	return nim_comp::UserService::GetInstance()->GetFriendAlias(id);
}

std::wstring UserManager::GetUserPhoto(const std::string &icon)
{
	return nim_comp::UserService::GetInstance()->GetUserPhoto(icon);
}

std::wstring UserManager::GetUserPhotoDir()
{
	return nim_comp::UserService::GetInstance()->GetUserPhotoDir();
}

UnregisterCallback UserManager::RegFriendListChange(const OnFriendListChangeCallback & callback)
{
	return nim_comp::UserService::GetInstance()->RegFriendListChange(callback);
}

UnregisterCallback UserManager::RegUserInfoChange(const OnUserInfoChangeCallback& callback)
{
	return nim_comp::UserService::GetInstance()->RegUserInfoChange(callback);
}

UnregisterCallback UserManager::RegMiscUInfoChange(const OnUserInfoChangeCallback & callback)
{
	return nim_comp::UserService::GetInstance()->RegMiscUInfoChange(callback);
}

UnregisterCallback UserManager::RegUserPhotoReady(const OnUserPhotoReadyCallback & callback)
{
	return nim_comp::UserService::GetInstance()->RegUserPhotoReady(callback);
}

}

