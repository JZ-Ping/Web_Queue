// Project UID c1f28c309e55405daf00c565d57ff9ad
#include "List.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <cassert>

using nlohmann::json;
using namespace std;

class OHQueue {
public:
  int read_req();
private:
  struct Student {
    string uniqname;
    string location;
  };
  List<Student> queue;
  void queue_push_back(json new_stu); 
    // Add a new student to the end of queue
  void bad_req();
  void route_list();
  void del_response();
  void empty_response();
  void print_queue();
  void print_head();
  void print_last();
  string check_input();
  void add_and_respond(string length);
  void print_queue(string route, string length);
};


int main(){
    OHQueue new_queue;
    while(!cin.eof()){
      new_queue.read_req();
      //cin.ignore();
    }
    return 0;
}

string OHQueue::check_input(){
  string host;
  getline(cin, host);
  assert(host == "Host: localhost");
  string content_type;
  getline(cin, content_type);
  //cout<<content_type<<endl;
  assert(content_type=="Content-Type: application/json; charset=utf-8");
  string content_length, length;
  cin >> content_length >> length;
  assert(content_length=="Content-Length:");
  cin.ignore();
  cin.ignore();
  return length;
}

void OHQueue::add_and_respond(string length){
      json newStudent;
      cin >> newStudent;
      string jstring = newStudent.dump(4)+"\n";
      int content_length = jstring.length();
      if(stoi(length)!=content_length) bad_req();
      queue_push_back(newStudent); 
      // Output
      print_last();
}

void OHQueue::print_queue(string route, string length){
    if(stoi(length)!=0) bad_req();
    if(route == "/api/"){
      route_list();
    }
    else if(route == "/api/queue/"){
      // Read all queue positions
      if(queue.empty()) empty_response();
      else print_queue();// Print Queue;
    }
    else if(route == "/api/queue/head/"){
      // Read first queue position
      print_head();
    }
    else bad_req(); // Undesired implementation
}

int OHQueue::read_req(){
  string req_type, route, version, length;
  cin >> req_type >> route >> version;
  if(req_type == "") return 0;//
  cin.ignore(); // Ignores newline
  assert(version == "HTTP/1.1");
  length = check_input();
  if(req_type == "GET"){
    print_queue(route, length);
  }
  else if(req_type == "POST"){
    if(route == "/api/queue/tail/"){
      // Create last queue position
      add_and_respond(length);
    }
    else bad_req(); // Undesired implementation
  }
  else if(req_type == "DELETE"){
    assert(stoi(length)==0);
    if(route == "/api/queue/head/"){
      // Delete first queue position
      if(queue.empty()){
        bad_req();
      }
      queue.pop_front();
      del_response();
    }
    else bad_req(); // Undesired implementation
  }
  else bad_req();

  return 0;
}


void OHQueue::queue_push_back(json new_stu){  
    // Adds a new student to the end of queue
    Student temp_stu;
    temp_stu.location = new_stu["location"];
    temp_stu.uniqname = new_stu["uniqname"];
    queue.push_back(temp_stu);
  }

void OHQueue::bad_req(){
  // Print if request failed
  std::cout<<"HTTP/1.1 400 Bad Request"<<endl;
  std::cout<<"Content-Type: application/json; charset=utf-8"<<endl;
  std::cout<<"Content-Length: 0"<<endl<<endl;
  exit(0);
}

void OHQueue::route_list(){
  // Print if GET /api/ is requested
  std::cout<<"HTTP/1.1 200 OK"<<endl;
  std::cout<<"Content-Type: application/json; charset=utf-8"<<endl;
  std::cout<<"Content-Length: 160"<<endl<<endl;
  std::cout<<"{"<<endl;
  std::cout<<"    \"queue_head_url\": \"http://localhost/queue/head/\","<<endl,
  std::cout<<"    \"queue_list_url\": \"http://localhost/queue/\","<<endl;
  std::cout<<"    \"queue_tail_url\": \"http://localhost/queue/tail/\""<<endl;
  std::cout<<"}"<<endl<<endl; 
}

void OHQueue::del_response(){
  // Print if deletion gets called
  std::cout<<"HTTP/1.1 204 No Content"<<endl;
  //std::cout<<"Host: localhost"<<endl;
  std::cout<<"Content-Type: application/json; charset=utf-8"<<endl;
  std::cout<<"Content-Length: 0"<<endl<<endl;
}
   
void OHQueue::empty_response(){
  std::cout<<"HTTP/1.1 200 OK"<<endl;
  std::cout<<"Content-Type: application/json; charset=utf-8"<<endl;
  std::cout<<"Content-Length: 40"<<endl<<endl;
  std::cout<<"{"<<endl;
  std::cout<<"    \"count\": 0,"<<endl;
  std::cout<<"    \"results\": null"<<endl;
  std::cout<<"}"<<endl;
}

void OHQueue::print_queue(){
  assert(!queue.empty());
  json out;
  json outlist;
  int pos = 1;
  for (List<Student>::Iterator i = queue.begin(); i != queue.end(); ++i) {
    json stud{     
          {"position", pos},
          {"uniqname" , (*i).uniqname},
          {"location" , (*i).location}
        };
        outlist.push_back(stud);
        ++pos;
    }
  out["count"] = pos-1;
  out["results"] = outlist;
  string str = out.dump(4) + '\n';
  size_t content_length = str.length();
  cout << "HTTP/1.1 200 OK" << '\n';
  cout << "Content-Type: application/json; charset=utf-8" << '\n';
  cout << "Content-Length: " << content_length << '\n' <<'\n';
  cout << str;
}

void OHQueue::print_head(){
  assert(!queue.empty());
  List<Student>::Iterator i = queue.begin();
  json stud{     
          {"position", 1},
          {"uniqname" , (*i).uniqname},
          {"location" , (*i).location}
  };
  string str = stud.dump(4) + '\n';
  size_t content_length = str.length();
  cout << "HTTP/1.1 200 OK" << '\n';
  cout << "Content-Type: application/json; charset=utf-8" << '\n';
  cout << "Content-Length: " << content_length << '\n';
  cout << str;
}

void OHQueue::print_last(){
  assert(!queue.empty());
  List<Student>::Iterator i = queue.begin();
  int s = queue.size();
  for(int pos = 0; pos < s-1; ++pos) {
      ++i;
  }
  json stud{     
      {"position", s},
      {"uniqname" , (*i).uniqname},
      {"location" , (*i).location}
  };
  string str = stud.dump(4) + '\n';
  size_t content_length = str.length();
  cout << "HTTP/1.1 201 Created" << '\n';
  cout << "Content-Type: application/json; charset=utf-8" << '\n';
  cout << "Content-Length: " << content_length << "\n\n";
  cout << str;
}