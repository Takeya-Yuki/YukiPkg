#include "src/inc/ypkg-config.h"
#include "src/inc/ypkg-srclist.h"


vector<char*> ReadSourcesList(int* code)
{
    FILE *fp=fopen(SOURCES_LIST,"rb");
    if(!fp){
        printf("%s\n","failed to lock sources.list");
        *code=-1;
        return vector<char*>();
    }

    int line=5;
    char buf[1024];
    int len=0;

    char slist[4096]={0};
   

    while(fgets(buf,line,fp)!= NULL)
    {
        len=strlen(buf);
        strcat(slist,buf);
    }

    vector<char*> alist=split(slist,"\n");
    code=0;
    return alist;

}

SrcRepoType String2SrcRepoType(const char* type)
{
    if(strcmp("deb",type)==0) return SrcRepoType::Debian;
    if(strcmp("ubu",type)==0) return SrcRepoType::Ubuntu;
    if(strcmp("soft",type)==0) return SrcRepoType::MainOnly;
    if(strcmp("main",type)==0) return SrcRepoType::MainOnly;
    else return SrcRepoType::Unknown;
}

struct SrcConfig SourceToConfig(char* conf)
{
    vector<char*> sconf= split(conf," ");
    try
    {
        SrcRepoType type=String2SrcRepoType(sconf[0]);
        char* url=sconf[1];
        char* name=sconf[2];

        struct SrcConfig confObj=
        {
            type,
            url,
            name
        };
        return confObj;
    }
    catch(const std::exception& e)
    {
        printf("ERROR: %s\n",e.what());
        return {SrcRepoType::Unknown,"CONFIG ERROR","ERROR"};
    }
    
}