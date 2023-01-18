package com.imooc.spring.ioc;

import com.imooc.spring.ioc.entity.Company;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringApplication {
    public static void main(String[] args) {
        ApplicationContext context=new ClassPathXmlApplicationContext("classpath:applicationContext.xml");
        Company company=context.getBean("company", Company.class);
        System.out.println(company);
        System.out.println(company.getInfo().getProperty("website"));

        //查詢IoC容器中所有的beanId
        String[] beanNames=context.getBeanDefinitionNames();
        for(String beanName :beanNames){
            //使用getBean先獲取bean再獲取該Class然後獲取Class的名稱Z
            String beanClassName=context.getBean(beanName).getClass().getName();
            System.out.println("beanId:"+beanName+" beanClassName:"+beanClassName);
        }
    }
}
