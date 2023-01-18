package com.imooc.spring.ioc.context;

public interface ApplicationContext {
    public Object getBean(String beanId); //提取bean
}
