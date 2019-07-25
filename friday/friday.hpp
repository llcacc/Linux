#pragma once
#include<string>
#include<sstream>
#include<json/json.h>
#include<iostream>
#include<memory>
#include<unistd.h>
#include"speech.h"
#include"base/http.h"
using namespace std;

class robot
{
private:
	string url ="http://openapi.tuling123.com/openapi/api/v2";
	string api_key ="6a685aeaf43c4de2b0e48fda72d702e8";
	string user_id = "1";
	aip::HttpClient client;

public:
	robot()
	{}
	

	string Talk(string &message)
	{
		Json::Value root;
		Json::Value item1;
		Json::Value item2;
		root["reqType"]= 0;
		item1["text"] = message;
		item2["inputText"]= item1;
		item1.clear();
		root["preception"]= item2;
		item2.clear();
		item2["apiKey"]= api_key;
		item2["userId"]= user_id;
		root["userInfo"]= item2;
		item2.clear();
		cout<< root.toStyledString()<<endl;
		Json::Value ret = PostRequest(root);
		cout<< ret.toStyledString()<<endl;
		//Json::Value _re = ret["results"];
		//Json::Value txt = _re[0]["values"];
		//cout<<"Robot# "<<txt["text"].asString()<<endl;
		//return txt["text"].asString();
	
	}
	Json::Value PostRequest(Json::Value data)
	{
		string response;
		Json::Value obj;
		Json::CharReaderBuilder rb;
		int code = this->client.post(url,nullptr,&data,nullptr,&response);
		if(code!= CURLcode::CURLE_OK)
		{
			obj[aip::CURL_ERROR_CODE]=code;
			return obj;
		}
		string error;
		unique_ptr<Json::CharReader> reader(rb.newCharReader());
		reader->parse(response.data(),response.data()+response.size(),&obj,&error);
		return obj;
	}

	~robot()
	{}
};
class Friday
{
private:
	robot rb;
public:
	void Run()
	{
		volatile bool quit = false;
		string message = "你好";
		while(!quit)
		{
			cout<< "Me #"<<message<<endl;
			string play_massage = rb.Talk(message);
		}
	}

	Friday()
	{}
	~Friday()
	{}

};
class SpeechRec
{

};


