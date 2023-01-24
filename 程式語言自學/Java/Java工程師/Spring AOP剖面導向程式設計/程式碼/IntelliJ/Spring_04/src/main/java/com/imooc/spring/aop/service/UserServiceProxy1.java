package com.imooc.spring.aop.service;

import java.text.SimpleDateFormat;
import java.util.Date;

public class UserServiceProxy1 implements UserService{
    private UserService userService;
    public UserServiceProxy1(UserService userService){
        this.userService=userService;
    }

    //執行委託類的工作
    public void createUser(){
        userService.createUser();
        System.out.println("====後置擴展功能====");
    }
}
