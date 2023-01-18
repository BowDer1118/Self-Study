package com.imooc.spring.ioc;

import com.imooc.spring.ioc.controller.UserController;
import com.imooc.spring.ioc.dao.UserDao;
import com.imooc.spring.ioc.service.UserService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

//使用Configuration來表示:當前Class為配置類，用來替代applicationContext.xml
@Configuration
//通知Spring IoC容器進行package掃描，將有註解的Class也都進行管理
@ComponentScan(basePackages = "com.imooc")
public class Config {
    /* Java Config利用method(方法)創建物件，並將方法的返回值(也就是創建出來的物件)
    *  放入IoC容器中，beanId為method的名稱
    * */
    @Bean //使用Bean來表示bean
    public UserDao userDao(){
        UserDao userDao=new UserDao();
        System.out.println("已創建"+userDao);
        return userDao;
    }


    @Bean
    //傳入要依賴的物件到method中，IoC會自動依照變數名稱匹配IoC容器中的beanId進行傳入
    public UserService userService(UserDao userDao){
        UserService userService=new UserService();
        System.out.println("已創建"+userService);
        //調用Setter對IoC匹配到的物件進行依賴注入
        userService.setUserDao(userDao);
        System.out.println("調用setUserDao"+userDao);
        return userService;
    }

    @Bean
    public UserController userController(UserService userService){
        UserController userController=new UserController();
        System.out.println("已創建"+userController);
        userController.setUserService(userService);
        System.out.println("調用setUserService"+userService);
        return userController;
    }

}
