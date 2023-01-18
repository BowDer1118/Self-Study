package com.imooc.spring.ioc;

import com.imooc.spring.ioc.service.UserService;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringApplication {
    public static void main(String[] args) {
        ApplicationContext context=new ClassPathXmlApplicationContext("classpath:applicationContext.xml");
        UserService userService=context.getBean("userService", UserService.class);
        System.out.println("userSerivce中IUserDao使用的實現類"+userService.getUdao().getClass().getName());
        //        String[] ids=context.getBeanDefinitionNames();
//        for(String id:ids){
//            System.out.println("Bean id:"+id+"\nObject:"+context.getBean(id));
//        }
    }
}
