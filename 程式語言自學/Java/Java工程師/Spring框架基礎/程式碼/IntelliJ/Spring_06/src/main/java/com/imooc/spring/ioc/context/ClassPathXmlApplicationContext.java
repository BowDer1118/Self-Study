package com.imooc.spring.ioc.context;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;

import java.io.File;
import java.lang.reflect.Method;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

//實現一個ApplicationContext
public class ClassPathXmlApplicationContext implements ApplicationContext{
    private Map iocContainer=new HashMap(); //用來保存IoC容器中的物件(<key,value> 為 <bean的id,物件>)
    public ClassPathXmlApplicationContext(){
        try{
            //獲取XML檔案的路徑
            String filePath=this.getClass().getResource("/applicationContext.xml").getPath();
            //處理中文問題
            filePath=new URLDecoder().decode(filePath,"UTF-8");
            //XML解析器
            SAXReader reader=new SAXReader();
            //解析XML
            Document document=reader.read(new File(filePath));
            //從Root Node獲取子標籤
            List<Node> beans=document.getRootElement().selectNodes("bean");
            for(Node node:beans){
                Element ele=(Element) node;
                //獲取bean標籤的id和class名稱
                String id=ele.attributeValue("id");
                String className=ele.attributeValue("class");
                //利用反射動態創建物件
                Class c=Class.forName(className);
                //依照className創建物件
                Object obj=c.newInstance();
                List<Node> properties=ele.selectNodes("property");
                for(Node p:properties){
                    Element property=(Element) p;
                    String propName=property.attributeValue("name");
                    String propValue=property.attributeValue("value");
                    //利用反射獲取方法
                    String setMethodName="set"+propName.substring(0,1).toUpperCase()+propName.substring(1);
                    System.out.println("準備執行"+setMethodName+"方法注入資料");
                    //使用反射獲取method
                    Method setMethod=c.getMethod(setMethodName,String.class);
                    setMethod.invoke(obj,propValue);
                }
                //將物件加入IoC容器中
                iocContainer.put(id,obj);
            }
            System.out.println(iocContainer);
            System.out.println("IoC容器初始化完畢");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    public Object getBean(String beanId){
        return iocContainer.get(beanId);
    }
}
