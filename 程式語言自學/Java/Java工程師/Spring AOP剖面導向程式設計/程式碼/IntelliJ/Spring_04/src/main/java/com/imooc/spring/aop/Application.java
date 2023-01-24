package com.imooc.spring.aop;

import com.imooc.spring.aop.service.UserService;
import com.imooc.spring.aop.service.UserServiceImpl;
import com.imooc.spring.aop.service.UserServiceProxy;
import com.imooc.spring.aop.service.UserServiceProxy1;

public class Application {
    public static void main(String[] args) {
        //最原始:使用者直接面向委託類
        System.out.println("[使用者面直接向委託類]");
        UserService userService=new UserServiceImpl();
        userService.createUser();

        System.out.println("");

        //一次代理:使用者面向一次代理類
        System.out.println("[使用者面向代理類]");
        userService=new UserServiceProxy(new UserServiceImpl());
        userService.createUser();

        System.out.println("");

        System.out.println("[使用者面向二次代理類]");
        //使用者面向的是二次代理類:也就是代理了代理類(可以一直嵌套下去)
        userService=new UserServiceProxy1(new UserServiceProxy(new UserServiceImpl()));
        userService.createUser();
    }
}
