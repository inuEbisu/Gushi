#include<bits/stdc++.h>
#include"lib/cJSON.c"
#include"lib/CJsonObject.cpp"
#include"lib/something.cpp"
using namespace std;
using namespace neb;

CJsonObject poems;

//#define debug

int help() {
    string guide = 
    "语文古诗词文言文填空生成器\n"
    "帮助:\n"
    "   -h 查看帮助\n"
    "   -a <数量> 指定生成题目数量。不指定默认为5。\n"
    "   -f <范围> 指定出题范围。格式为'年级(.册数)'。多个用'|'隔开。不指定则为全部。\n"
    "使用例:\n"
    "   -a 10 -f 9.1 (生成10道题,出题范围是九年级上册)\n"
    "   -a 20 -f 8|9.1(生成20道题,出题范围是八年级上下册与九年级上册)\n"
    "   -a 100 -f 7|8|9 (生成100道题,出题范围是整个初中阶段)\n"
    ;
    cout << guide;
    return 0;
}
int init() {
    //置随机数种子
    srand((int) time(NULL));
    
    //导入诗词库
    stringstream jsonstr;
    ifstream fin("database/poems.json");
    jsonstr << fin.rdbuf();
    fin.close();
    poems.Parse(jsonstr.str());

    return 0;
}
string generate(int a,string f) {
    stringstream ss,ssa;
    int arraySize = poems["poems"].GetArraySize();
    for(int i=0;i<a;i++) {
        //选择诗文(s0)
        int ra0 = getRand(0,arraySize);
        CJsonObject poem = poems["poems"][ra0];
        string s0 = poem("context");

        //选择诗句(s1)
        vector<string> v1;
        split(s0,v1,' ');
        int ra1 = getRand(0,v1.size());
        string s1 = v1[ra1];

        //选择诗句中要你填空的地方(s2)
        vector<string> v2;
        string s1copy = s1;
        replace_all(s1copy,"?",",");replace_all(s1copy,"!",",");replace_all(s1copy,"？",",");replace_all(s1copy,"！",",");replace_all(s1copy,"，",",");
        split(s1copy,v2,',');
        int ra2 = getRand(0,v2.size());
        string s2 = v2[ra2];
        replace_all(s2,".","");replace_all(s2,"!","");replace_all(s2,"?","");replace_all(s2,"。","");replace_all(s2,"？",",");replace_all(s2,"！",",");

        //调整并输出
        string s = replace_all(s1,s2,"_____");
        ss << i+1 << ". " << s << ("(" + poem("author") + "<<" + poem("title") + ">>)") << endl;
        ssa << i+1 << ". "  << s2 << endl;

        #ifdef debug
            ss << s0 << "|" << s1 << "|" << s2 << endl;
        #endif
    }

    return ss.str()+"\nAnswer:\n"+ssa.str();
}
int main(int argc, char** argv) {
    init();

    int a=5; string f="";
    cin >> a >> f;
    
    cout << generate(a,f);

    return 0;
}