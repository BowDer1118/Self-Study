package com.imooc.springbootlearn.controller;

import com.imooc.springbootlearn.pojo.Student;
import org.springframework.web.bind.annotation.*;

@RestController
public class ParameterController {
    @GetMapping("/first_request")
    public String firstRequest(){
        return "Hello Spring Boot,我的第一個Spring Boot 接口。";
    }

    @GetMapping("/para")
    public String requestParameter(Integer num){
        return "我收到的參數為: "+num;
    }

    @PostMapping("/para")
    public String postRequest(@RequestBody Student student){
        return "我從Post Request收到的參數為: "+student.toString();
    }
}
