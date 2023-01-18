package com.imooc.spring.ioc.entity;

//訂單
public class Order {
    private Float price; //價位
    private Integer quantity; //數量
    private Float total; //訂單總價

    public Order(){
        System.out.println("創建Order物件:"+this);
    }
    public void init(){
        System.out.println("執行init()方法計算total:"+price+"*"+quantity);
        total=price*quantity;
    }

    public void destroy(){
        System.out.println("釋放與Order物件相關的資源");
    }

    public void pay(){
        System.out.println("訂單金額為:"+total);
    }
    public Float getPrice() {
        return price;
    }

    public void setPrice(Float price) {
        System.out.println("已調用setPrice方法:"+price);
        this.price = price;
    }

    public Integer getQuantity() {
        return quantity;
    }

    public void setQuantity(Integer quantity) {
        System.out.println("已調用setQuantity方法"+quantity);
        this.quantity = quantity;
    }

    public Float getTotal() {
        return total;
    }

    public void setTotal(Float total) {
        this.total = total;
    }
}
