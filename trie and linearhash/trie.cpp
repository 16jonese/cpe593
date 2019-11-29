/*
Author: Ethan Jones
Pledge: I pledge my honor that I have abided by the stevens honor system
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;

//#ifdef _WIN32
//#define WINPAUSE system("pause")
//#endif


class Trie {
private:
	class Node {
	public:
		Node *next[26];
		bool isWord;
  	//Node(Node* next[26], bool isWord) : next(next), isWord(isWord) {}
    Node() : next(/*new Node[26]*/), isWord(false){}

    void print(int level, char buf[]){
      for(int i = 0; i < 26; i++){
        if(next[i]){
          const char a = (const char)(97 + i);
          buf[level] = a;
          next[i]->print(level + 1, buf);
        }
      }
      if(isWord){
        cout << buf << endl;
      }
  }
};
	Node* root;
public:
	Trie() {
    root = new Node();
  }
	~Trie() {
    //delete[]next;
  }

  Trie(const Trie& orig) = delete;
  Trie& operator =(const Trie& orig) = delete;

	void load(const char* dictionary) {
    int index = 0;
    bool working = false;
    while(index < strlen(dictionary)){
      char word[35];
      int wordIndex = 0;
      while(dictionary[index] != ' ' && index < strlen(dictionary)){
        word[wordIndex] = dictionary[index];
        wordIndex++;
        index++;
        working = true;
      }
        if(wordIndex > 0){
          word[wordIndex] = '\0';
          cout << "Loading Word: " << word << endl;
          add(word);
        }
      index++;
      }
    }


	void add(const char* word){
      Node* p = root;
      int index;
      for(int i = 0; i < strlen(word); i++){
        index = (int)word[i] - 97;
        if(!p->next[index])
          p->next[index] = new Node();
        p = p->next[index];
      }
      p->isWord = true;
  }

	void remove(const char* word){
    Node* p = root;
    Node* temp;
    bool possibleDelete = false;
    int index;
    for(int i = 0; i < strlen(word); i++){
      index = (int)word[i] - 97;
      if(!p->next[index])
        return;
      if(countChildren(p) < 2 && !possibleDelete){
        temp = p;
        possibleDelete = true;
      }
      else if(countChildren(p) > 1){
        possibleDelete = false;
      }
      p = p->next[index];
    }
    p->isWord = false;
    if(countChildren(p) == 0)
      delete temp;
  }

  bool contains(const char* word){
    Node* p = root;
    int index;
    for(int i = 0; i < strlen(word); i++){
      index = (int)word[i] - 97;
      if(!p->next[index] || index < 0 || index > 25)
        return false;
      p = p->next[index];
    }
    return p->isWord;
  }

  bool containsPrefix(const char* word){
    Node* p = root;
    int index;
    for(int i = 0; i < strlen(word); i++){
      index = (int)word[i] - 97;
      if(!p->next[index])
        return false;
      p = p->next[index];
    }
    return true;
  }

  int countChildren(const Node* p){
    int count = 0;
    if(!p)
      throw "node is Null";
    for(int i = 0; i < 26; i++){
      if(p->next[i])
        count++;
    }
    return count;
  }

	void print() const{
    char buf[35];
    int level = 0;
    root->print(level, buf);
  }

  int nonWords(){
      ifstream file;
      file.open ("prideandprejudice.txt");
      string word;
      int nonWords = 0;
      if (!file){
        cout << "file: prideandprejudice not found";
        return false;
      }
      while (file >> word){
        char charWord[word.size() + 1];
        for(int i = 0; i < word.size() + 1; i++){
          if(i == word.size())
            charWord[i] = '\0';
          else{
            charWord[i] = word[i];
          }
        }
        if(!contains(charWord)){
          nonWords++;
        }
      }
      return nonWords;
  }

  bool updateTrieSmall(const char* filename){
      ifstream file;
      file.open(filename);
      string word;
      string dict;
      if (!file){
        cout << "file: " << filename << " not found" << endl;
        return false;
      }
      while (file >> word){
          dict = dict + " " + word;
      }
      char charWord[dict.size() + 1];
      for(int i = 0; i < dict.size() + 1; i++){
        if(i == dict.size())
          charWord[i] = '\0';
        else{
          charWord[i] = dict[i];
        }
      }
      load(charWord);
      return true;
  }


  bool updateTrie(const char* filename){
      ifstream file;
      file.open(filename);
      if (!file){
        cout << "file: " << filename << " not found" << endl;
        return false;
      }
      string word;
      char newWord[1000000];
      char extraWord[1000000];
      string dict;
      int index = 0;
      while (file >> word){
            for(int i = 0; i < word.size() + 1; i++){
              if(index > (2000000 - word.size() -1)){
                if(index < 2000000){
                  newWord[index] = '\0';
                  index = 2000000;
                }
                else if(i == word.size())
                  extraWord[index-2000000] = ' ';
                else
                  extraWord[index-2000000] = word[i];
              }
              else if(index > (1000000 - word.size() -1)){
                if(index < 1000000){
                  newWord[index] = '\0';
                  load(newWord);
                  index = 1000000;
                }
                else if(i == word.size())
                  newWord[index-1000000] = ' ';
                else
                  newWord[index-1000000] = word[i];
              }

              else {
                if(i == word.size())
                  newWord[index] = ' ';
                else
                  newWord[index] = word[i];
              }
              index++;
            }
          cout << index << endl;
      }
      load(newWord);
      load(extraWord);
      return true;
  }


  bool printContains(){
      ifstream file;
      file.open("testContains.txt");
      string word;
      int index = 0;
      if (!file){
        cout << "testContains file not found";
        return false;
      }
      cout << "This file contains the words: "<< endl;
      while(file >> word){
        char charWord[word.size() + 1];
        for(int i = 0; i < word.size() + 1; i++){
          if(i == word.size())
            charWord[i] = '\0';
          else{
            charWord[i] = word[i];
          }
        }
        if(contains(charWord)){
          cout << word << endl;;
        }
      }
      return true;
  }

  bool printPrefixes(){
      ifstream file;
      file.open("testTriePrefix.txt");
      string word;
      if (!file){
        cout << "testTriePrefix file not found";
        return false;
      }
      cout << "This file contains the determined prefixes in the following words: "<< endl;
      while(file >> word){
        char charWord[word.size() + 1];
        for(int i = 0; i < word.size() + 1; i++){
          if(i == word.size())
            charWord[i] = '\0';
          else{
            charWord[i] = word[i];
          }
        }
        if(containsPrefix(charWord)){
          cout << word << endl;;
        }
      }
      return true;
  }

  bool removeText(){
      ifstream file;
      file.open("testRemove.txt");
      string word;
      if (!file){
        cout << "testRemove file not found";
        return false;
      }
      cout << "The following words have been removed: "<< endl;
      while(file >> word){
        char charWord[word.size() + 1];
        for(int i = 0; i < word.size() + 1; i++){
          if(i == word.size())
            charWord[i] = '\0';
          else{
            charWord[i] = word[i];
          }
        }
        if(contains(charWord)){
          remove(charWord);
          cout << word << "has been removed " << endl;;
        }
      }
      return true;
  }

};

int main(){
  Trie spellCheck;
  Trie dict;
  const char* testAdd = "testAdd.txt";
  if(spellCheck.updateTrieSmall(testAdd)){
    spellCheck.printContains();
    spellCheck.printPrefixes();


    spellCheck.removeText();
    spellCheck.print();
  }
  const char* dictFile = "dict.txt";
  if(dict.updateTrie(dictFile)){
    cout << "The file has " << dict.nonWords() << " non words" << endl;
  }
  //cout << "it was false";
  cin.get();
}
