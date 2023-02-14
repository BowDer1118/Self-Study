package com.imooc.springmvc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class TestController {
    @GetMapping("/t") //localhost/t 就可以訪問這個method獲取String返回值
    @ResponseBody //直接向響應提供數據，不進行頁面跳轉
    public String test(){
        return "Hello Spring MVC";
    }
}
