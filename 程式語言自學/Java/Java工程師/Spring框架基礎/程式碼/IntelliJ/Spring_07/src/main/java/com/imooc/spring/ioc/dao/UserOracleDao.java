package com.imooc.spring.ioc.dao;

import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Repository;

@Repository()
@Primary //如果有多個實現類，則優先使用此類進行動態注入
public class UserOracleDao implements IUserDao{
    public UserOracleDao(){
        System.out.println("正在創建UserOracleDao物件:"+this);
    }
}
