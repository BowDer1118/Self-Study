package com.imooc.springmvc.controller;

import com.imooc.springmvc.entity.Form;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.Arrays;
import java.util.List;

@Controller
public class FormController {
//    @PostMapping("/apply")
    @ResponseBody
    public String apply1(@RequestParam(value = "name",defaultValue = "ANON") String name
            , String course, Integer[] purpose){
        System.out.println(name);
        System.out.println(course);
        System.out.println(Arrays.toString(purpose));
        return "SUCCESS";
    }

//    @PostMapping("/apply")
    @ResponseBody
    public String apply2(@RequestParam(value = "name",defaultValue = "ANON") String name
            , String course, @RequestParam List<Integer> purpose){
        System.out.println(name);
        System.out.println(course);
        System.out.println(purpose);
        return "SUCCESS";
    }
//    @PostMapping("/apply")
    @ResponseBody
    public String apply3(Form form){
        System.out.println(form);
        return "SUCCESS";
    }
    @PostMapping("/apply")
    @ResponseBody
    public String applyDelivery(Form form){
        System.out.println(form);
        return form.toString();
    }
}
