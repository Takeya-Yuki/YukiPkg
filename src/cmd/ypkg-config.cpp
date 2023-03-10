#include "src/ypkg-common.h"
#include "src/cmd/ypkg-config.h"
#include "src/inc/ypkg-srclist.h"
#include "src/conf/ypkg-apt-config.h"

int ConfigCommand(int argc,char** argv){
    
    int ret=0;
    vector<char*> src_list=ReadSourcesList(&ret);
    if(ret!=0) return ret;

   
    int len=(src_list).size();    
    
    for(int i=0;i<len;i++){
        char* conf=(src_list)[i];
        struct SrcConfig sconf=SourceToConfig(conf);
        printf("%s\n",ParseConfigToAptConfigStr(sconf));
    }
    
    return 0;
}