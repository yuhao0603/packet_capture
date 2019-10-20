/*************************************************************************
	> File Name: log.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 13时44分00秒
 ************************************************************************/

#ifndef _LOG_H
#define _LOG_H
#define MAX_FILE_NAME_LEN 127
class Log{
private:
    char logFile[MAX_FILE_NAME_LEN+1];
public:
    Log(char *file_name){
        if(file_name != nullptr){
            strcpy(logFile, file_name);
        }
        else{
            Log();
        }
    }

    Log(){
        strcpy(logFile, file_name);
    }

    MyLog(){

    }
}
#endif
