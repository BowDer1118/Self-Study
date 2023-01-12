package com.imooc.mybatis.dto;

import com.imooc.mybatis.entity.Goods;

//Data Transfer Object:對Goods類做出擴展的類 用來接收多表查詢的結果
public class GoodsDTO {
    private Goods goods=new Goods();
    private String categoryName;

    public Goods getGoods() {
        return goods;
    }

    public void setGoods(Goods goods) {
        this.goods = goods;
    }

    public String getCategoryName() {
        return categoryName;
    }

    public void setCategoryName(String categoryName) {
        this.categoryName = categoryName;
    }
}
