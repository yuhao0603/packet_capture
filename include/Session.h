/*************************************************************************
	> File Name: Session.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 01时01分40秒
 ************************************************************************/

#ifndef _SESSION_H
#define _SESSION_H
class Session{
private:
    static Session *session;
    Session(){ }
    
    ~Session(){
        freeInstance();
    }
public:
    static Session *getInstance(){
        if (session != nullptr){
            return session;
        }
        else{
            session = new Session();
            return session;
        }
    }

    static void freeInstance(){
        if (session != nullptr){
            delete(session);
        }
    }
};
#endif
