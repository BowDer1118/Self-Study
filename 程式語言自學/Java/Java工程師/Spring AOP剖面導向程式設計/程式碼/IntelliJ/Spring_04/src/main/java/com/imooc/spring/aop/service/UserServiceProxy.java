package com.imooc.spring.aop.service;

import java.text.SimpleDateFormat;
import java.util.Date;

//代理類:靜態代理是需要手動創建代理類的代理模式
public class UserServiceProxy implements UserService{
    //持有委託類物件
    private UserService userService;
    public UserServiceProxy(UserService userService){
        this.userService=userService;
    }

    //執行額外功能與委託類的工作
    public void createUser(){
        //前置額外功能
        System.out.println("===="+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss SSS").format(new Date()) +"====");
        //委託類的工作
        userService.createUser();
    }
}
