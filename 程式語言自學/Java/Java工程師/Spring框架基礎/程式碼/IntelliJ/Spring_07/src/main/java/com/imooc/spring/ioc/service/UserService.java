package com.imooc.spring.ioc.service;

import com.imooc.spring.ioc.dao.IUserDao;
import com.imooc.spring.ioc.dao.UserDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Service;

import javax.annotation.PostConstruct;

@Service
@Scope("prototype") //設定Scope屬性
public class UserService {
    //從config檔案中加載資料，使用${key}來獲取value
    @Value("${metaData}")
    private String metaData;
    @Value("${connection.password}")
    private String password;
    @Autowired
    //如果裝配註解放在屬性上，則IoC會自動通過反射將private修飾符自動改為public並進行附值 不再執行set
    private IUserDao udao;

    @PostConstruct //也就是XML中bean init-method
    public void init(){
        System.out.println("初始化UserService物件,metaData="+metaData);
    }

    public  UserService(){
        System.out.println("正在創建UserService:"+this);
    }
    public UserService(UserDao udao) {
        this.udao = udao;
    }

    public IUserDao getUdao() {
        return udao;
    }
//    @Autowired
    //如果裝配註解放在set方法上，則自動按照類型或名稱set方法進行注入
    public void setUdao(UserDao udao) {
        System.out.println("setUdao:"+udao);
        this.udao = udao;
    }
}
