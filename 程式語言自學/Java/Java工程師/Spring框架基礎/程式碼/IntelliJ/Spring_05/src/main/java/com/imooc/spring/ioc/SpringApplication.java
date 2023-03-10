package com.imooc.spring.ioc;

import com.imooc.spring.ioc.dao.UserDao;
import com.imooc.spring.ioc.entity.Order;
import com.imooc.spring.ioc.service.UserService;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringApplication {
    public static void main(String[] args) {
        ApplicationContext context=new ClassPathXmlApplicationContext("classpath:applicationContext.xml");
        System.out.println("IoC容器已初始化");
//        UserDao userDao=context.getBean("userDao2", UserDao.class);
//        UserDao userDao2=context.getBean("userDao2", UserDao.class);
//        UserDao userDao3=context.getBean("userDao2", UserDao.class);
//        UserService userService1= context.getBean("userService", UserService.class);
//        UserService userService2= context.getBean("userService", UserService.class);
//        UserService userService3= context.getBean("userService", UserService.class);
//        UserService userService4= context.getBean("userService", UserService.class);
        Order order1=context.getBean("order1", Order.class);
        order1.pay();
        //銷毀IoC容器
        ((ClassPathXmlApplicationContext)context).registerShutdownHook();
        System.out.println("IoC容器開始銷毀");
    }
}
