package com.imooc.mybatis.datasource;

import com.mchange.v2.c3p0.ComboPooledDataSource;
import org.apache.ibatis.datasource.unpooled.UnpooledDataSourceFactory;

//讓Mybatis運用C3P0連接池
public class C3P0DataSourceFactory extends UnpooledDataSourceFactory {
    public C3P0DataSourceFactory(){
        //使用由C3P0所提供的dataSource
        this.dataSource=new ComboPooledDataSource();
    }
}
