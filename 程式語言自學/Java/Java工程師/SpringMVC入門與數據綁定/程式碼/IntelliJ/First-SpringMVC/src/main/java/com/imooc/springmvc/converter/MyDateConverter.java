package com.imooc.springmvc.converter;


import org.springframework.core.convert.converter.Converter;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

//轉換器類別:SpringMVC要求實現Converter interface
public class MyDateConverter implements Converter<String,Date> {
    /**
     *
     * @param s 前端輸入的字串
     * @return 轉換後的Date物件 or 轉換失敗回傳null
     */
    @Override
    public Date convert(String s) {
        SimpleDateFormat sdf= new SimpleDateFormat("yyyy-MM-dd");
        try {
            Date d=sdf.parse(s);
            return d;
        } catch (ParseException e) {
            return null;
        }
    }
}
