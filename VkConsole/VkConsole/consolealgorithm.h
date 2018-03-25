#pragma once

#include <iostream>
#include "VkMaster\api.h"
/////////////////////////

struct HeadCap
{
	unsigned int nMessages;
	unsigned int nNotification;
	std::string caption;
};

struct Post
{
	std::string postType;
	std::string postAutor;
	std::string postAutorURL;
	int postAutorId;
	unsigned int postTime;
	std::string postText;
	std::vector <int> postPhotoOwnerId;
	std::vector <int> postPhotoId;
	std::vector <std::string> minPostPhotoURL;
	std::vector <std::string> maxPostPhotoURL;
	std::vector <int> postAudioOwnerId;
	std::vector <int> postAudioId;
	std::vector <std::string> postAudioName;
	std::vector <std::string> postAudioURL;
	std::vector <int> postDocOwnerId;
	std::vector <int> postDocId;
	std::vector <std::string> postDocName;
	unsigned int postDocSize;
	std::vector <std::string> postDocURL;
	std::vector <int> postLinkOwnerId;
	std::vector <int> postLinkId;
	std::vector <std::string> postLinkName;
	std::vector <std::string> postLinkURL;
	std::vector <int> postNoteOwnerId;
	std::vector <int> postNoteId;
	std::vector <std::string> postNoteName;
	std::vector <std::string> postNoteURL;
	unsigned int nPostLikes;
	unsigned int nPostComments;
	unsigned int nPostReposts;
	unsigned int nPostViews;
	bool isDone;
	unsigned int postId;
};

struct ListElement
{
	unsigned int listNumber;
	std::string listElementType;
	int listElementOwnerId;
	int listElementId;
	std::string listElementName;
	std::string listElementURL;
	std::string listElementMaxPhoto;
	std::string listElementMinPhoto;
	std::string listElementText;
	unsigned int listElementIntInfo;
	bool isRead;
	};

class VkBase
{
private:
	std::string accessToken, login, pass;

protected:

public:
	static int userId;
	static std::string userName;
	static HeadCap headLine;

	static std::vector <Post> temp;
	static std::vector <ListElement> temp;

	VkBase(std::string aT, std::string l, std::string p);
	~VkBase();
	std::string getUserName();
	int getUserId();

	/*Post findPostData(const VK::json &freshPostData);		//�������� �������
	Post findMessagePostData(const VK::json &freshPostData);
	Post findCommentPostData(const VK::json &freshPostData);
	ListElement findFriendsListData(const VK::json &freshListData);
	ListElement findDialogsListData(const VK::json &freshListData);
	ListElement findAccountInfoListData(const VK::json &freshListData);
	ListElement findAudioListData(const VK::json &freshListData);
	ListElement findGroupsListData(const VK::json &freshListData);
	ListElement findVideoListData(const VK::json &freshListData);
	ListElement findDocListData(const VK::json &freshListData);*/
	void printPost(const Post &postData, const unsigned int &nElements);		//� ��������� ��������� �� Post temp
	void printList(const VK::json &postList, const unsigned int &nElements);		//� ��������� ��������� �� ListElement Temp
	
	void like();		//const std::string &objectType, const int &objectOwnerId, const int &objectId//https://vk.com/dev/likes.add
	void dislike();		//const std::string &objectType, const int &objectOwnerId, const int &objectId//https://vk.com/dev/likes.delete
	Post getObjectComments(const unsigned int &nObjectComment);		//const std::string &objectType, const int &objectAutorId, const int &objectId, //���������� � Post temp//count = 1, offset ������//post -> https://vk.com/dev/wall.getComments //photo -> https://vk.com/dev/photos.getComments // video->https://vk.com/dev/video.getComments
	
	void sendComment(const std::string &text);		//const std::string &objectType, const int &objectOwnerId, const int &objectId, //post -> https://vk.com/dev/wall.createComment //photo -> https://vk.com/dev/photos.createComment // video->https://vk.com/dev/video.createComment
	void sendComment(const std::string &text, const std::vector <ListElement> &files);		//const std::string &objectType, const int &objectOwnerId, const int &objectId,//���� � �� ��������, ��� ��� ������� �����������

	void repost(const std::string &text);		//const std::string &objectType, const int &objectId, //post ������ wall//https://vk.com/dev/wall.repost
	void repost(const std::string &recipientName, const std::string &text);		// const std::string &objectURL,//https://vk.com/dev/messages.searchDialogs (���� ���������) -> https://vk.com/dev/messages.send
	//�������� ���������� �������, ����, ������ ������ � ����, ���������� �����.
};

class Messages : public VkBase
{
private:
	VK::params_map temp;
protected:

public:
	void send(const std::string &text);										//const int &recipientId, �� "���������" id//https://vk.com/dev/messages.send
	void send(const std::vector <ListElement> &files);		//const int &recipientId, �� "���������" id//���� �� ��� � �������
	void send(const std::string text, const std::vector <ListElement> &files);		//const int &recipientId, �� "���������" id//���� �� ��� � �������

	Post getHistory();		//sender -> string//offset = 0, count = 1//const int &recipientId �� ���������//https://vk.com/dev/messages.getHistory
	ListElement getHistoryFiles(const std::string &fileType);		//count = 1//const int &recipientId, �� "���������"//https://vk.com/dev/messages.getHistoryAttachments
	void addUserInDialog(const std::string &recipientName);		//const unsigned int &chatId, �� "���������"//https://vk.com/dev/friends.search (offset=0, count=1) -> https://vk.com/dev/messages.addChatUser
	void clearDialog();		//count = 1,offset = 0//������ ���� �� ��������, ��� ����� offset ������� ���//const int &recipientId �� "���������"//https://vk.com/dev/messages.deleteDialog
	
	ListElement getDialogs();					//count = 1//https://vk.com/dev/messages.getDialogs
	ListElement getDialogs(const bool &isRead);		//�������������?

	void markMessagesAsRead();		//���� ������ ������ �� ����������, �� ������� ��� ������������//const int &recipientId �� "���������"//https://vk.com/dev/messages.markAsRead
	ListElement searchInDialogs(const std::string &searchText, const unsigned int &nSearchResults);		//https://vk.com/dev/messages.searchDialogs
};

class News : public VkBase
{
private:
	VK::params_map temp;
protected:

public:
	Post getNews(const unsigned int &nNewsPost);																									//count = 1, offset ������//https://vk.com/dev/newsfeed.get
	Post getNews(const unsigned int &nNewsPost, const unsigned int &startNewsTime, const unsigned int &endNewsTime);		//�������������� �����
	Post getNews(const unsigned int &nNewsPost, const std::string &postNewsFilter);		//post,video,photo
	Post getNews(const unsigned int &nNewsPost, const unsigned int &startNewsTime, const unsigned int &endNewsTime, const std::string &postNewsFilter);

};

class Groups : public VkBase
{
private:
	VK::params_map temp;
protected:

public:
	ListElement getGroups();		//��� ���� ����� �����//extended=1//description,members_count,type//offset=1,count=1//const int &userId �� "���������"//https://vk.com/dev/groups.get

	Post getGroupInfo(const int &groupId);		//description,links,members_count,type//id ��� ������ ������//https://vk.com/dev/groups.getById
	
	Post getPosts(const unsigned int &nGroupsPost);										//count = 1, offset ������//const int &groupId, �� "���������"//https://vk.com/dev/wall.get
	Post getPosts(const unsigned int &nGroupsPost, const unsigned int &startNewsTime, const unsigned int &endNewsTime);		//�������������� �����//const int &groupId,  �� "���������"
	
	ListElement getGroupsVideos(const unsigned int &nGroupsVideos);		//count = 1, offset ������//const int &groupId, �� "���������"//https://vk.com/dev/video.get
	ListElement getGroupsPhotos(const std::string &albumName, const unsigned int &nGroupsPhotos);		//count = 1, offset ������//wall,profile,saved...//const int &groupId, �� "���������"//https://vk.com/dev/photos.get
	ListElement getGroupsDocs(const unsigned int &nGroupsDocs);								//count = 1, offset ������//const int &groupId, �� "���������"//https://vk.com/dev/docs.get
	ListElement getGroupsDocs(const unsigned int &docsType, const unsigned int &nGroupsDocs);	//1,2,3,4,5,6,7,8//const int &groupId, �� "���������"

	ListElement searchInGroups(const std::string &searchText, const unsigned int &nSearchResults);		//count = 1, offset ������//https://vk.com/dev/groups.search
	void joinGroup();		//id ��� ������ ������//const int &groupId �� "���������"//https://vk.com/dev/groups.join
	void leaveGroup();		//id ��� ������ ������//const int &groupId �� "���������"//https://vk.com/dev/groups.leave
};

class Pages : public VkBase
{
private:
	VK::params_map temp;
protected:

public:
	ListElement getFriends(const unsigned int &nFriends);		//count = 1, offset ������//fields=nickname//��� ���� - �����//, const int &userId//https://vk.com/dev/friends.get

	Post getPageInfo();		//��� ����// status, sex, bdate, city, country,schools, interests, music, movies, tv, books, games, about - ��� � text//, const int &userId � "��������"//https://vk.com/dev/users.get

	Post getUsersPosts(const unsigned int &nUsersPost);										//count = 1, offset ������//const int &userId,  � "��������"//https://vk.com/dev/wall.get
	Post getUsersPosts(const unsigned int &nUsersPost, const unsigned int &startNewsTime, const unsigned int &endNewsTime);		//�������������� �����//const int &userId,  � "��������"

	ListElement getUsersVideos(const unsigned int &nUsersVideos);		//count = 1, offset ������//const int &userId,  �� "���������"//https://vk.com/dev/video.get
	ListElement getUsersPhotos(const std::string &albumName, const unsigned int &nUsersPhotos);		//count = 1, offset ������//wall,profile,saved...//const int &userId,  �� "���������"//https://vk.com/dev/photos.get
	ListElement getUsersDocs(const unsigned int &nUsersDocs);								//count = 1, offset ������//const int &userId,  �� "���������"//https://vk.com/dev/docs.get
	ListElement getUsersDocs(const unsigned int &docsType, const unsigned int &nUsersDocs);	//1,2,3,4,5,6,7,8//const int &userId,  �� "���������"

	ListElement searchInUsers(const std::string &searchText, const unsigned int &nSearchResults);		//count = 1, offset ������//status,bdate, city, country//https://vk.com/dev/users.search
	
	void addInFriends();		//const int &userId �� "���������"//https://vk.com/dev/friends.add
	void addInFriends(const std::string &messageText);		//const int &userId, �� "���������" 
};
//���������� ��������� � ������ �������