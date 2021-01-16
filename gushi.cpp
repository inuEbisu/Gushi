/**
 * @file   gushi.app
 * @author inuEbisu
*/

#include<bits/stdc++.h>
#include"lib/cJSON.c"
#include"lib/CJsonObject.cpp"
#include"lib/something.cpp"
using namespace std;
using namespace neb;

CJsonObject poems;
CJsonObject config;

//#define debug

int help() {
    string guide = 
    "语文古诗词文言文填空生成器\n"
    "帮助:\n"
    "   -h 查看帮助\n"
    "   <数量> 指定生成题目数量。不指定默认为5。\n"
    "   <范围> 指定出题范围。格式为'年级(+册数)'。多个用'|'隔开。不指定则为全部。\n"
    "使用例:\n"
    "   10 91 (生成10道题,出题范围是九年级上册)\n"
    "   20 8|91(生成20道题,出题范围是八年级上下册与九年级上册)\n"
    "   100 7|8|9 (生成100道题,出题范围是整个初中阶段)\n"
    ;
    cout << guide;
    return 0;
}

/**
 * @brief 初始化
 * 
 * @return 0 OK
*/
int init() {
    //置随机数种子
    srand((int) time(NULL));
    
    //导入配置文件
    stringstream fss_config;
    ifstream finc("database/config.json");
    fss_config << finc.rdbuf();
    finc.close();
    config.Parse(fss_config.str());

    //导入诗词库
    stringstream fss_poems;
    ifstream finp("database/poems.json");
    fss_poems << finp.rdbuf();
    finp.close();
    poems.Parse(fss_poems.str());

    return 0;
}

/**
 * @brief 生成试题
 * 
 * @param a 生成试题的数量
 * @param f 生成试题的限制范围。多个用'|'隔开。e.g. 91(九年级上册),8|91(八年级&九年级上册),7|8|9(初中阶段)
 * @param strpro 生成的试题会被存放至该变量中。
 * @param strans 生成试题的答案会被存放至该变量中。
 * 
 * @return 0 OK
*/
int generate(int a, string f, string& strpro, string& strans) {
    vector<string> sr1,sr2;
    for(int i=0;i<config["s1r"].GetArraySize();i++) sr1.push_back(config["s1r"](i));
    for(int i=0;i<config["s2r"].GetArraySize();i++) sr2.push_back(config["s2r"](i));

    stringstream ss,ssa;
    int arraySize = poems["poems"].GetArraySize();
    for(int i=0;i<a;i++) {
        //选择诗文(s0)
        CJsonObject poem;
        while(1) {
            int ra0 = getRand(0,arraySize);
            poem = poems["poems"][ra0];
            if(poem("disable")=="1") continue;
            if(isOK(poem("id"),f)) break;
        }
        string s0 = poem("context");

        //选择诗句(s1)
        vector<string> v1;
        split(s0,v1,' ');
        int ra1 = getRand(0,v1.size());
        string s1 = v1[ra1];

        //选择诗句中要你填空的地方(s2)
        vector<string> v2;
        string s1copy = s1;
        for(int j=0;j<(int)sr1.size();j++) replace_all(s1copy,sr1[j],"|");
        split(s1copy,v2,'|'); remove(begin(v2),end(v2),"");
        int ra2 = getRand(0,v2.size());
        string s2 = v2[ra2];
        for(int j=0;j<(int)sr2.size();j++) replace_all(s2,sr2[j],"");

        //调整并输出
        string s = replace_all(s1,s2,config("replacement"));
        ss << i+1 << ". " << s << ("(" + poem("author") + "<<" + poem("title") + ">>)") << endl;
        ssa << i+1 << ". "  << s2 << endl;

        #ifdef debug
            ss << s0 << "|" << s1 << "|" << s2 << endl;
        #endif
    }

    strpro = ss.str();
    strans = ssa.str();
    return 0;
}

/**
 * @deprecated
 * 
 * @brief 生成试题
*/
string generate(int a, string f) {
    string strp,stra;
    generate(a,f,strp,stra);
    return strp+"\nAnswer:\n"+stra;
}

/**
 * @brief 主程序入口
 * 
*/
int main(int argc, char** argv) {
    init();
    
    int a=5; string f="";
    cin >> a >> f;
    cout << generate(a,f);

    return 0;
}