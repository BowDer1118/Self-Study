package com.imooc.mybatis.utils;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.Reader;

//MyBatis的工具類:用於創建全局唯一的SqlSessionFactory物件
public class MyBatisUtils {
    //運用static的唯一性(屬於類不屬於物件的概念)來保存SqlSessionFactory保證其為唯一的
    private static SqlSessionFactory sqlSessionFactory=null;
    //static塊是用於初始化static修飾的物件
    static{
        try {
            //初始化sqlSessionFactory
            Reader reader=Resources.getResourceAsReader("mybatis-config.xml");
            sqlSessionFactory=new SqlSessionFactoryBuilder().build(reader);
        } catch (IOException e) {
            e.printStackTrace();
            //拋出 初始化發生錯誤 的異常
            throw new ExceptionInInitializerError(e);
        }
    }
    //獲取SqlSession物件
    public static SqlSession openSession(){
        return sqlSessionFactory.openSession();
    }
    //用來關閉SqlSession
    public static void closeSession(SqlSession sqlSession){
        //如果sqlSession被開啟，則要關閉
        if(sqlSession!=null){
            sqlSession.close();
//            System.out.println("成功關閉SqlSession");
        }
    }

}
