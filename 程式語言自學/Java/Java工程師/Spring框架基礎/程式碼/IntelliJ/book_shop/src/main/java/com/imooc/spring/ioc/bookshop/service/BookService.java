package com.imooc.spring.ioc.bookshop.service;

import com.imooc.spring.ioc.bookshop.dao.BookDao;

public class BookService {
    //採購新的書本
    private BookDao bookDao; //在IoC中動態注入

    public BookDao getBookDao() {
        return bookDao;
    }

    public void setBookDao(BookDao bookDao) {
        this.bookDao = bookDao;
    }

    public void purchase(){
        System.out.println("正在執行圖書採購業務方法");
        bookDao.insert();
    }
}
