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
    "���Ĺ�ʫ�����������������\n"
    "����:\n"
    "   -h �鿴����\n"
    "   <����> ָ��������Ŀ��������ָ��Ĭ��Ϊ5��\n"
    "   <��Χ> ָ�����ⷶΧ����ʽΪ'�꼶(+����)'�������'|'��������ָ����Ϊȫ����\n"
    "ʹ����:\n"
    "   10 91 (����10����,���ⷶΧ�Ǿ��꼶�ϲ�)\n"
    "   20 8|91(����20����,���ⷶΧ�ǰ��꼶���²�����꼶�ϲ�)\n"
    "   100 7|8|9 (����100����,���ⷶΧ���������н׶�)\n"
    ;
    cout << guide;
    return 0;
}

/**
 * @brief ��ʼ��
 * 
 * @return 0 OK
*/
int init() {
    //�����������
    srand((int) time(NULL));
    
    //���������ļ�
    stringstream fss_config;
    ifstream finc("database/config.json");
    fss_config << finc.rdbuf();
    finc.close();
    config.Parse(fss_config.str());

    //����ʫ�ʿ�
    stringstream fss_poems;
    ifstream finp("database/poems.json");
    fss_poems << finp.rdbuf();
    finp.close();
    poems.Parse(fss_poems.str());

    return 0;
}

/**
 * @brief ��������
 * 
 * @param a �������������
 * @param f ������������Ʒ�Χ�������'|'������e.g. 91(���꼶�ϲ�),8|91(���꼶&���꼶�ϲ�),7|8|9(���н׶�)
 * @param strpro ���ɵ�����ᱻ������ñ����С�
 * @param strans ��������Ĵ𰸻ᱻ������ñ����С�
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
        //ѡ��ʫ��(s0)
        CJsonObject poem;
        while(1) {
            int ra0 = getRand(0,arraySize);
            poem = poems["poems"][ra0];
            if(poem("disable")=="1") continue;
            if(isOK(poem("id"),f)) break;
        }
        string s0 = poem("context");

        //ѡ��ʫ��(s1)
        vector<string> v1;
        split(s0,v1,' ');
        int ra1 = getRand(0,v1.size());
        string s1 = v1[ra1];

        //ѡ��ʫ����Ҫ����յĵط�(s2)
        vector<string> v2;
        string s1copy = s1;
        for(int j=0;j<(int)sr1.size();j++) replace_all(s1copy,sr1[j],"|");
        split(s1copy,v2,'|'); remove(begin(v2),end(v2),"");
        int ra2 = getRand(0,v2.size());
        string s2 = v2[ra2];
        for(int j=0;j<(int)sr2.size();j++) replace_all(s2,sr2[j],"");

        //���������
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
 * @brief ��������
*/
string generate(int a, string f) {
    string strp,stra;
    generate(a,f,strp,stra);
    return strp+"\nAnswer:\n"+stra;
}

/**
 * @brief ���������
 * 
*/
int main(int argc, char** argv) {
    init();
    
    int a=5; string f="";
    cin >> a >> f;
    cout << generate(a,f);

    return 0;
}