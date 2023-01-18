package com.imooc.spring.ioc.dao;

import org.springframework.stereotype.Repository;

/*
    使用@Repository表示當前Class用於資料持久化，對資料庫做增刪改查
    bean id默認為類名首字母小寫:userDao
    也可以在註解後面手動給id
 */
@Repository
public class UserDao implements IUserDao{
    public UserDao(){
        System.out.println("正在創建UserDao:"+this);
    }
}
