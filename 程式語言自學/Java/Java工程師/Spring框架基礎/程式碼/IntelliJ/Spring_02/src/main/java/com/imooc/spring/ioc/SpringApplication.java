package com.imooc.spring.ioc;

import com.imooc.spring.ioc.entity.Apple;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringApplication {
    public static void main(String[] args) {
        //classpath指定的是類路徑位置開始查找，也就是resources資料夾
        ApplicationContext context= new ClassPathXmlApplicationContext("classpath:applicationContext.xml");
        Apple a1=context.getBean("apple5",Apple.class);
        Apple a2=context.getBean("test",Apple.class);
        //a1與a2都來自同一個物件
        System.out.println("a1==a2:"+(a1==a2));
    }
}
