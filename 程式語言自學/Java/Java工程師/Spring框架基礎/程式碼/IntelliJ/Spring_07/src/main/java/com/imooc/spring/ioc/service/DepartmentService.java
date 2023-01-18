package com.imooc.spring.ioc.service;

import com.imooc.spring.ioc.dao.IUserDao;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class DepartmentService {
    /* @Resource使用方法
    *  [方法1]設置name屬性:依照name在IoC容器中將bean注入，未找到則報錯
    *  [方法2]不設置name屬性:
    *       狀況1:案屬性名稱作為bean name在IoC容器中查找bean並注入
    *       狀況2:案屬性名稱匹配失敗，則按類型進行匹配，此時@Resource就跟@Autowired一樣了，
    *            需要加入@Primary解決類型衝突問題
    *
    *   使用建議:使用@Resource物件時，推薦設定name名稱或保證屬性名稱與bean名稱相同
    * */
    @Resource(name = "userOracleDao") //使用指定name來匹配bean
    private IUserDao udao;
    @Resource//不設置name屬性，用狀況1，屬性的名稱當作匹配值去匹配bean id
    private IUserDao userOracleDao; //使用userOracleDao這個屬性名稱匹配
}
