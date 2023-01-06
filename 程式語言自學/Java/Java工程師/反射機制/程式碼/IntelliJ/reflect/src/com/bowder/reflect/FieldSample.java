package com.bowder.reflect;

import com.bowder.reflect.entity.Employee;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;

//透過Filed訪問Class的public屬性
public class FieldSample {
    public static void main(String[] args) {
        try {
            Class employeeClass=Class.forName("com.bowder.reflect.entity.Employee");
            Constructor constructor=employeeClass.getConstructor(new Class[]{Integer.class,String.class,Float.class,String.class});
            Employee employee=(Employee) constructor.newInstance(new Object[]{100,"寶德",60000.0f,"資訊部"});
            //透過getField()獲得Field物件
            Field enameField=employeeClass.getField("ename");
            //透過get()方法獲取field
            String name= (String) enameField.get(employee);
            System.out.println("員工名稱:"+name);
            enameField.set(employee,"可愛狗勾");
            name=employee.ename;
            System.out.println("修改後的員工名稱:"+name);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
