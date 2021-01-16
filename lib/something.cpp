#include<vector>
#include<string>
using namespace std;

typedef unsigned int size_t;

/** 
 * @brief 分割字符串
 * @author https://zhuanlan.zhihu.com/p/56163976
*/
void split(const string& s, vector<string>& tokens, char delim = ' ') {
    tokens.clear();
    auto string_find_first_not = [s, delim](size_t pos = 0) -> size_t {
        for (size_t i = pos; i < s.size(); i++) {
            if (s[i] != delim) return i;
        }
        return string::npos;
    };   
    size_t lastPos = string_find_first_not(0);
    size_t pos = s.find(delim, lastPos);
    while (lastPos != string::npos) {
        tokens.emplace_back(s.substr(lastPos, pos - lastPos));
        lastPos = string_find_first_not(pos);
        pos = s.find(delim, lastPos);
    }
}

string& replace_all(string& str,const string& old_value,const string& new_value) {     
    for(size_t pos(0); pos!=string::npos; pos+=new_value.length()) {     
        if((pos=str.find(old_value,pos))!=string::npos)     
            str.replace(pos,old_value.length(),new_value);     
        else break;     
    }     
    return str;     
}

int getRand(int min, int max) {
    return rand()%max;
}

int isOK(string id, string f) {
    if(f=="-1") return true;

    vector<string> vs;
    split(f,vs,'|');
    for(size_t i=0;i<vs.size();i++) {
        if(id.substr(0,vs[i].size()) == vs[i]) return true;
    }
    return false;
}