package com.imooc.spring.ioc;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class SpringApplication {
    public static void main(String[] args) {
        //基於Config類，來完成IoC的初始化操作
        ApplicationContext context=
                new AnnotationConfigApplicationContext(Config.class);
        System.out.println("=======================");
        String[] ids=context.getBeanDefinitionNames();
        for(String id:ids){
            System.out.println("BeanId:"+id);
            System.out.println("ClassName:"+context.getBean(id).getClass().getName());
        }
    }
}
