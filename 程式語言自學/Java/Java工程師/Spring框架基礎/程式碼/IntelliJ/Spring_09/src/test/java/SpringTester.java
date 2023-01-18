import com.imooc.spring.ioc.service.UserService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import javax.annotation.Resource;

//使用RunWith註解:將Junit的執行權交給SpringTest模塊
// 在測試執行前，自動初始化IoC容器
@RunWith(SpringJUnit4ClassRunner.class)
//使用ContextConfiguration通知Spring要加載那些配置檔案
@ContextConfiguration(locations = {"classpath:applicationContext.xml"})
public class SpringTester {
    //使用Resource告訴Spring依賴注入beanId為userService的物件
    @Resource(name = "userService")
    private UserService userService;


    //由於已經自動初始化完成IoC容器，因此userService物件已經自動完成依賴注入
    //可以直接執行單元測式，而不用手動在初始化IoC容器與物件
    @Test
    public void testUserService(){
        userService.createUser();
    }
}
