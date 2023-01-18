package com.imooc.spring.ioc.bookshop;

import com.imooc.spring.ioc.bookshop.service.BookService;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class BookShopApplication {
    public static void main(String[] args) {
        //透過applicationContext-*.xml 掃描所有applicationContext開頭的xml檔案
        ApplicationContext context=new ClassPathXmlApplicationContext("classpath:applicationContext-*.xml");
        BookService bookService=context.getBean("bookService",BookService.class);
        bookService.purchase();
    }
}
