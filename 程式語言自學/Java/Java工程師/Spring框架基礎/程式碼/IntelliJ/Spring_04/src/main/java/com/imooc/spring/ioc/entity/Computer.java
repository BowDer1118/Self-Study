package com.imooc.spring.ioc.entity;

public class Computer {
    private String brand; //品牌
    private String type; //類型
    private String sn; //序列號
    private Float price;

    public Computer() {
    }

    public Computer(String brand, String type, String sn, Float price) {
        this.brand = brand;
        this.type = type;
        this.sn = sn;
        this.price = price;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getSn() {
        return sn;
    }

    public void setSn(String sn) {
        this.sn = sn;
    }

    public Float getPrice() {
        return price;
    }

    public void setPrice(Float price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return "Computer{" +
                "brand='" + brand + '\'' +
                ", type='" + type + '\'' +
                ", sn='" + sn + '\'' +
                ", price=" + price +
                '}';
    }
}
